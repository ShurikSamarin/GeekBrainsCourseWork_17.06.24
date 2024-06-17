#include <stdbool.h>
#include "vehicle.h"
#include "display.h"
#include "curses/curses.h"
#include "food.h"
#include "dir.h"
#include <stdlib.h>
#include "ai.h"
#define SPAWN_ATTEMPTS 5

bool closeProgrammFlag = false;

cart *main_dron;

int x_min;
int x_max;
int y_min;
int y_max;
//int pumpkins_eaten;




void start()
{
	//create users dron
	main_dron = create_head(10, 10);
	
	enable_draw();
	
	//enable arrow control
	keypad(stdscr, true);
	halfdelay(1);
	
	//init fields shape
	int row, col;
	get_shape(&row, &col);
	x_min = 1;
	x_max = col -2;
	y_min = 1;
	y_max = row - 2;
	
}

//checks if there are drones at a given position
bool check_cart(struct position pos)
{
	if(contain_cart(main_dron, pos))
	{
		return true;
	}
	return contain_dron(pos);
}

//tries to find a free cell in several tries
bool try_get_free_pos(position *pos)
{
	//limit the number of search attempts to prevent freezes
	for(int i = 0; i < SPAWN_ATTEMPTS; i++)
	{
		struct position result;
		result.y = rand() % (y_max - y_min + 1) + y_min;
		result.x = rand() % (x_max - x_min + 1) + x_min;
		
		if(!check_cart(result) && !contain_pumpkin(result))
		{
			*pos = result;
			return true;
		}
	}
	return false;
}

//moves the drone if there are no obstacles
void move_dron(cart *head, Direction dir)
{
	position next_pos = get_next_position(head -> pos, dir);
	
	if(next_pos.x < x_min ||
		next_pos.x > x_max ||
		next_pos.y < y_min ||
		next_pos.y > y_max)
	{
		return;
	}
	if(check_cart(next_pos))
	{
		return;
	}
	if(contain_pumpkin(next_pos))
	{
		remove_pumpkin(next_pos);
		add_cart(head);
	}
	move_carts(head, dir);
}

void process_input(int input_char)
{
	switch(input_char)
	{
		case '\n'://press enter to close program
			printf("TOTAL SCORE: %d\n", pumpkins_eaten);
			closeProgrammFlag = true;
			break;
		case KEY_LEFT:
			move_dron(main_dron, direction_left);
			break;
		case KEY_RIGHT:
			move_dron(main_dron, direction_right);
			break;
		case KEY_UP:
			move_dron(main_dron, direction_forward);
			break;
		case KEY_DOWN:
			move_dron(main_dron, direction_back);
			break;
		case ' '://add dron
			add_random_dron(try_get_free_pos);
			break;
	}
}

void update()
{
	//draw
	draw_clear_field();
	drow_carts(main_dron);
	draw_drons(drow_carts);
	draw_pumpkins(pumpkins, pumpkins_count);

	//handle input
	int inp = getch();
	process_input(inp);
	
	//pumpkin and drone systems
	update_drons(move_dron);
	update_pumpkins(try_get_free_pos);
}

void end()
{
	disable_draw();
	clean_carts(main_dron);
	clean_drons();
}

int main(int argc, char **argv)
{
	
	start();
	
	while(!closeProgrammFlag)
	{
		update();
	}
	
	end();
	
	return 0;
}
