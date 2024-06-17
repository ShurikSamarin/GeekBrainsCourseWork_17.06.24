#include "place.h"
#include <stdbool.h>
#include "food.h"
#include <time.h>
#include <math.h>
#include <stdio.h>
#include "curses/curses.h"

struct position pumpkins[PUMPKINS_BUFFER];

int pumpkins_count = 0;
int pumpkins_eaten = 0;


time_t last_spawn_time = 0;
time_t spawn_interval = 1; 


void update_pumpkins(bool try_get_free_pos(position *pos))
{
	if((time(NULL) - last_spawn_time) >= spawn_interval)
	{
		last_spawn_time = time(NULL);
		add_rand_pumpkins(try_get_free_pos);
	}
}

static int get_pumpkin_index(struct position pos)
{
	for(int i = 0; i < pumpkins_count; i++)
	{
		if(equalPositions(pumpkins[i], pos))
		{
			return i;
		}
	}
	return -1;
}

bool contain_pumpkin(struct position pos)
{
 return get_pumpkin_index(pos) != -1;
}

static void add_pumpkins(struct position pos)
{
	if(pumpkins_count >= PUMPKINS_BUFFER)
	{
		return;
	}
	pumpkins[pumpkins_count] = pos;
	pumpkins_count++;
}

void add_rand_pumpkins(bool try_get_free_pos(position *pos))
{
	position pumpkin_position;
	if(!try_get_free_pos(&pumpkin_position))
	{
		return;
	}
	
	add_pumpkins(pumpkin_position);
}

void remove_pumpkin(position pos)
{
	int idx = get_pumpkin_index(pos);
	if(idx == -1)
	{
		return;
	}
	pumpkins_count--;
	pumpkins_eaten++;
	
	printLevel(pos.y+1, pos.x+1,pumpkins_eaten);
	printLevel(pos.y-1, pos.x-1,pumpkins_eaten);
	//printLevel(pos.y+1, pos.x-1,pumpkins_eaten);
	//printLevel(pos.y-1, pos.x+1,pumpkins_eaten);
    // Вывод количества съеденных тыкв на месте последней съеденной тыквы
	refresh();
	usleep(100000);
	
	
	for(; idx < pumpkins_count; idx++)
	{
		pumpkins[idx] = pumpkins[idx + 1];
	}
}

bool try_get_closest_pumpkin(position pos, position *result)
{
	position closest;
	int closest_dist;
	if(pumpkins_count > 0)
	{
		closest = pumpkins[0];
		closest_dist = abs(pumpkins[0].x - pos.x) + 
						abs(pumpkins[0].y - pos.y);
	}
	else
	{
		return false;
	}
	
	for(int i = 1; i < pumpkins_count; i++)
	{
		int dist = abs(pumpkins[i].x - pos.x) + 
					abs(pumpkins[i].y - pos.y);
		if(dist < closest_dist)
		{
			closest = pumpkins[i];
			closest_dist = dist;
		}
	}
	*result = closest;
	return true;
}
 
