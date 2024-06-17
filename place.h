#ifndef POSITION_H
#define POSITION_H

#include <stdbool.h>
#include "dir.h"

typedef struct position
{
	int x;
	int y;
}position;

bool equalPositions(struct position a, struct position b);

position get_next_position(position current, Direction dir);

#endif
