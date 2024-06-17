#include <stdio.h>
#include <stdlib.h>
#include "vehicle.h"
#include "dir.h"
#include "place.h"

//create first cart
cart* create_head(int pos_x, int pos_y)
{
	cart *head = calloc(1,sizeof(cart));
	head -> pos.x = pos_x;
	head -> pos.y = pos_y;
	return head;
}

void move_carts(cart *head, Direction dir)
{
	position target_pos = get_next_position(head -> pos, dir);
	
	position tmp_pos;
	cart *current_cart = head;
	while(current_cart)
	{
		tmp_pos = current_cart -> pos;
		current_cart -> pos = target_pos;
		target_pos = tmp_pos;
		current_cart = current_cart -> next;
	}
}

//search tail cart
static cart* get_last_cart(cart *current_cart)
{
	while(current_cart -> next)
	{
		current_cart = current_cart -> next;
	}
	return current_cart;
}

//add new cart to tail
void add_cart(cart *head)
{
	cart *last_cart = get_last_cart(head);
	cart *new_cart = calloc(1,sizeof(cart));
	last_cart -> next = new_cart;
	new_cart -> pos = last_cart -> pos;
}

void clean_carts(cart *head)
{
	cart *current = head;
	while(current)
	{
		cart *tmp = current -> next;
		free(current);
		current = tmp;
	}
	head = NULL;
}

bool contain_cart(cart *head, struct position pos)
{
	while(head)
	{
		if(equalPositions(head -> pos, pos))
		{
			return true;
		}
		head = head -> next;
	}
	return false;
}
