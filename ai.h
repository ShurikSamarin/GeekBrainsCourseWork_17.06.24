#include "vehicle.h"
#include "place.h"
#include "dir.h"

void add_random_dron(bool try_get_free_pos(position *pos));

void update_drons(void move_dron(cart *head, Direction dir));

void clean_drons();

void draw_drons(void drow_carts(cart *head));

bool contain_dron(struct position pos);
