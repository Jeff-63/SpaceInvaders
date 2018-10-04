#pragma once
#include "ExtraTerrestre.h"

class MartienVert : public ExtraTerrestre
{
	bool jiggle;

public:
	static const int visuelMartienVert = 42;
	static const int scoreMartienVert = 25;
	MartienVert();
	void jiggleExtraTerrestre();
};
