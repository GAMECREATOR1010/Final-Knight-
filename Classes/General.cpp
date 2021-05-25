#include "General.h"

Vec2 ChangeDir()
{
	int i = rand() % 4;
	if (i == 0)
		return Vec2(1, 0);
	else if (i == 1)
		return Vec2(0, 1);
	else if (i == 2)
		return Vec2(-1, 0);
	else
		return Vec2(0, -1);
}


