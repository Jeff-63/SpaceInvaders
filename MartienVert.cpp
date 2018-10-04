#include "MartienVert.h"

MartienVert::MartienVert() :ExtraTerrestre(visuelMartienVert, scoreMartienVert)
{
	jiggle = true;
}

void MartienVert::jiggleExtraTerrestre()
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
