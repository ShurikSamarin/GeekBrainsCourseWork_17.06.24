#include <stdio.h>
#include "curses/curses.h"
#include "vehicle.h"

static int screen_row;
static int screen_col;

//initialization
void enable_draw()
{
	initscr();
	getmaxyx(stdscr, screen_row, screen_col);
}

//get rows and columns count
void get_shape(int *row, int *col)
{
	*row = screen_row;
	*col = screen_col;
}

void drow_carts(cart *head)
{
	while(head)
	{
		mvprintw( head -> pos.y, head -> pos.x, "*" );
		head = head -> next;
	}
}

void draw_pumpkins(struct position *pumpkins, int pumpkins_count)
{
	for(int i = 0; i < pumpkins_count; i++)
	{
		mvprintw( pumpkins[i].y, pumpkins[i].x, "@" );
	}
}
void printLevel(int pos_y, int pos_x, int pumpkins_eaten){
    mvprintw(pos_y, pos_x, "%d", pumpkins_eaten); //Вывод количества съеденных тыкв
    
}
void draw_clear_field()
{
	clear();
	
	for(int i = 0; i < screen_col; i++)
	{
		mvprintw( 0, i, "#" );
	}
	for(int i = 0; i < screen_col; i++)
	{
		mvprintw( screen_row - 1, i, "#" );
	}
	for(int i = 0; i < screen_row; i++)
	{
		mvprintw( i, 0, "#" );
	}
	for(int i = 0; i < screen_row; i++)
	{
		mvprintw( i, screen_col - 1, "#" );
	}
}

//close curses
void disable_draw()
{
	endwin(); // завершение работы с ncurses
}
