#include "LaserET.h"
#include <iostream>

void LaserET::moveLaser()
{
	removeLaser();
	if (coord.getPositionY() < 41)
	{
		coord.setPositionY(coord.getPositionY() + 1);
		putLaser();
	}
	else
		isAlive = false;
}
void LaserET::startLaser(int x, int  y)
{
	coord.setPositionX(x);
	coord.setPositionY(y);
	putLaser();
	isAlive = true;
}