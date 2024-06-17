#define PUMPKINS_BUFFER 20
#ifndef PUMPKINS_H
#define PUMPKINS_H

extern int pumpkins_eaten;

#include "place.h"
#include <stdbool.h>
#include <unistd.h>

extern struct position pumpkins[PUMPKINS_BUFFER];

extern int pumpkins_count;

bool contain_pumpkin(struct position pos);

void add_rand_pumpkins(bool try_get_free_pos(position *pos));

void update_pumpkins(bool try_get_free_pos(position *pos));

void remove_pumpkin(position pos);

bool try_get_closest_pumpkin(position pos, position *result);

void printLevel();

#endif // PUMPKINS_H
