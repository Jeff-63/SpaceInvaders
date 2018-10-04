#pragma once
#include "Laser.h"
class TableauLaser
{
public:
	TableauLaser();
	~TableauLaser();
	void ajouter(Laser *laser);
	Laser** getTabLasers();
	int getNbLasers();

private:
	int nbMaxElements;
	int nbElements;
	Laser **tableauLaser;
};