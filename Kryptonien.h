#pragma once
#include "ExtraTerrestre.h"
#include "TypeExtraTerrestre.h"
class Kryptonien : public ExtraTerrestre
{
	bool jiggle;

public:
	static const int visuelKryptonien = 86;
	static const int scoreKryptonien = 50;
	Kryptonien();
	void jiggleExtraTerrestre();
};