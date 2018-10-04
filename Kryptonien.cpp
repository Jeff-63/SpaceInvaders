#include "Kryptonien.h"

Kryptonien::Kryptonien() :ExtraTerrestre(visuelKryptonien, scoreKryptonien)
{
	jiggle = true;
}

void Kryptonien::jiggleExtraTerrestre()
{
	removeExtraTerrestre();

	if (jiggle)
	{
		if (coord.getPositionX() > 1)
		{
			coord.setPositionX(coord.getPositionX() - 1);
		}
	}
	else
	{
		if (coord.getPositionX() < 41)
		{
			coord.setPositionX(coord.getPositionX() + 1);
		}
	}

	jiggle = !jiggle;

	putExtraTerrestre();
}