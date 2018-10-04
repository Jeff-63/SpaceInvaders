#pragma once
#include "ExtraTerrestre.h"
#include "TypeExtraTerrestre.h"
class Infestateur : public ExtraTerrestre
{
	bool jiggle;

public:
	static const int visuelInfestateur = 176;
	static const int scoreInfestateur = 100;
	Infestateur();
	void jiggleExtraTerrestre();
};
