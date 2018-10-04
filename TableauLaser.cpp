#include "TableauLaser.h"
#include <conio.h>
#include "UIKit.h"
#include <iostream>

TableauLaser::TableauLaser()
{
	this->nbElements = 0;
	this->nbMaxElements = 1;
	this->tableauLaser = new Laser*[this->nbMaxElements];
}

TableauLaser::~TableauLaser()
{
	for (int i = 0; i < this->nbElements; i++)
	{
		delete this->tableauLaser[i];
	}
	delete[] this->tableauLaser;
	this->tableauLaser = NULL;
}

void TableauLaser::ajouter(Laser *laser)
{
	if (this->nbElements == this->nbMaxElements)
	{
		this->nbMaxElements *= 2;
		Laser **tabTemp = new Laser*[this->nbMaxElements];
		for (int i = 0; i < this->nbElements; i++)
		{
			tabTemp[i] = this->tableauLaser[i];
		}

		delete[] this->tableauLaser;

		this->tableauLaser = tabTemp;
	}

	this->tableauLaser[this->nbElements] = laser;
	this->nbElements++;
}

int TableauLaser::getNbLasers()
{
	return this->nbElements;
}

Laser** TableauLaser::getTabLasers()
{
	return this->tableauLaser;
}
