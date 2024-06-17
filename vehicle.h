#ifndef CARTS_H
#define CARTS_H

#include "place.h"
#include "dir.h"

typedef struct cart
{
	position pos;
	struct cart *next;
}cart;

cart* create_head(int pos_x, int pos_y);

void add_cart(cart *head);

void clean_carts(cart *head);

void move_carts(cart *head, Direction dir);

bool contain_cart(cart *head, struct position pos);

#endif
