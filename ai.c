#include "vehicle.h"
#include "food.h"
#include "dir.h"
#include <stdlib.h>
#include "place.h"
#include <time.h>
#define DRONS_BUFFER 10
//#define sign(x) ((x) == 0 ? 0 : ((x)<0 ? -1 : 1))
#define get_horizontal_by_sign(x) ((x)<0 ? direction_left : direction_right)
#define get_vertical_by_sign(x) ((x)<0 ? direction_forward : direction_back)


static cart* drons[DRONS_BUFFER];
static position targets[DRONS_BUFFER];
static clock_t last_move_time[DRONS_BUFFER] = {0};
static int drons_count = 0;

clock_t move_time_interval = 100;

static void add_dron(struct position pos)
{
	if(drons_count >= DRONS_BUFFER)
	{
		return;
	}
	drons[drons_count] = create_head(pos.x, pos.y);
	drons_count++;
}

static Direction get_direction_to_target(position srs, position dst)
{
	int dx = dst.x - srs.x;
	int dy = dst.y - srs.y;
	
	//add unpredictability to artificial intelligence
	if(dx != 0 && dy != 0)
	{
		return rand() % 2 == 0 ? get_horizontal_by_sign(dx) : get_vertical_by_sign(dy);
	}
	if(dx != 0)
	{
		return get_horizontal_by_sign(dx);
	}
	else
	{
		return get_vertical_by_sign(dy);
	}
}

void add_random_dron(bool try_get_free_pos(position *pos))
{
	position head_position;
	if(!try_get_free_pos(&head_position))
	{
		return;
	}
	add_dron(head_position);
}

void update_drons(void move_dron(cart *head, Direction dir))
{
	for(int i = 0; i < drons_count; i++)
	{
		if((clock() - last_move_time[i]) < move_time_interval)
		{
			continue;
		}
		last_move_time[i]  = clock();
		
		if(!contain_pumpkin(targets[i]))
		{
			if(!try_get_closest_pumpkin(drons[i] -> pos, &targets[i]))
			{
				continue;
			}
		}
		Direction move_dir = get_direction_to_target(drons[i] -> pos, targets[i]);
		move_dron(drons[i], move_dir);
	}
}

void clean_drons()
{
	for(int i = 0; i < drons_count; i++)
	{
		clean_carts(drons[i]);
	}
}

void draw_drons(void drow_carts(cart *head))
{
	for(int i = 0; i < drons_count; i++)
	{
		drow_carts(drons[i]);
	}
}

bool contain_dron(struct position pos)
{
	for(int i = 0; i < drons_count; i++)
	{
		if(contain_cart(drons[i], pos))
		{
			return true;
		}
	}
	return false;
}
