#include "place.h"
#include <stdbool.h>
#include "dir.h"

bool equalPositions(struct position a, struct position b)
{
	return (a.x == b.x) && (a.y == b.y);
}

position get_next_position(position current, Direction dir)
{
	switch(dir)
	{
		case direction_forward:
			current.y -= 1;
			break;
		case direction_back:
			current.y += 1;
			break;
		case direction_left:
			current.x -= 1;
			break;
		case direction_right:
			current.x += 1;
			break;
	}
	return current;
}
