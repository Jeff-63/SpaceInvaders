#include "UIKit.h"
#include <conio.h>
#include <iostream>
#include <time.h>
#include "MartienVert.h"
#include "Kryptonien.h"
#include "Infestateur.h"
#include "LaserET.h"
#include "Vaisseau.h"
#include "Laser.h"
#include "Menu.h"
#include "Regles.h"
#include "TableauLaser.h"

void afficherTerrain(int nbLignes, int nbColonnes);
char recupererTouche();
void afficherLaser(Laser** &tabLaser, int nbLaser, string type);
void jiggleExtraTerrestres(ExtraTerrestre** &tabExtraTerrestres);
void testerCollision(ExtraTerrestre** &tabExtraTerrestres, Laser** &tabLaser, int nbLaser);
void majTabMartiens(ExtraTerrestre** &tabExtraTerrestres);
bool testerJoueurMeurt(Vaisseau* joueur, Laser** tabLaserET, int nbLaser);;
void playFireSound();
void playGameOverSound();
void playWinSound();
int getIndiceET();
void setTimersByDifficulte(int &timerJiggleExtraTerrestres, int &timerTireET, int difficulte);
char recommencer();
void loseGame();
void winGame();

void main()
{
	srand(time(NULL));
	const int NB_LIGNES = 41;
	const int NB_COLONES = 41;
	const int REGLES = 50;
	const int COMMENCER = 49;
	const int QUITTER = 48;
	const int TIMER_ADD_MARTIEN = 80;
	const int TIMER_ADD_KRYPTONIEN = 500;
	const int TIMER_ADD_INFESTATEUR = 1000;
	int limiteTimerTireET;
	int limiteTimerJiggleExtraTerrestre;
	int choixOption;
	bool continuer;
	bool gagne;
	char touche;
	

	do
	{
		system("cls");
		afficherMenu();
		choixOption = selectionnerOptionMenu();
		if (choixOption == REGLES)
			afficherRegles();
	} while (choixOption != QUITTER && choixOption != COMMENCER);
	if (choixOption == COMMENCER)
	{
		do
		{
			system("cls");
			afficherNiveauDifficulte();
			int niveauDifficulte = selectionnerNiveauDifficulte();
			setTimersByDifficulte(limiteTimerJiggleExtraTerrestre, limiteTimerTireET, niveauDifficulte);
			system("cls");

			PlaySound(NULL, 0, 0);
			afficherTerrain(NB_LIGNES, NB_COLONES);
			gagne = false;
			continuer = false;
			touche = NULL;
			bool joueurEnVie = true;
			int timerAddExtraTerrestre = TIMER_ADD_MARTIEN - 1;
			int timerJiggleExtraTerrestres = limiteTimerJiggleExtraTerrestre;
			int timerTireET = limiteTimerTireET;
			setTimersByDifficulte(limiteTimerJiggleExtraTerrestre, limiteTimerTireET, 2);
			ExtraTerrestre::resetNombreExtraTerrestre();
			Vaisseau *joueur = new Vaisseau();
			ExtraTerrestre **tabExtraTerrestre = new ExtraTerrestre*[15];
			TableauLaser lasersJoueur;
			TableauLaser lasersET;
			while (ExtraTerrestre::getNombreExtraTerrestre() < 15 && !gagne  && joueurEnVie)
			{
				timerAddExtraTerrestre++;
				timerJiggleExtraTerrestres++;
				if (timerAddExtraTerrestre >= TIMER_ADD_INFESTATEUR)
				{
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre()] = new Infestateur();
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre()]->resetExtraTerrestre();
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre() - 1]->putExtraTerrestre();

					timerAddExtraTerrestre = 0;
				}
				if (timerAddExtraTerrestre == TIMER_ADD_MARTIEN || timerAddExtraTerrestre == TIMER_ADD_MARTIEN * 2 || timerAddExtraTerrestre == TIMER_ADD_MARTIEN * 4 || timerAddExtraTerrestre == TIMER_ADD_MARTIEN * 6 || timerAddExtraTerrestre == TIMER_ADD_MARTIEN * 8 || timerAddExtraTerrestre == TIMER_ADD_MARTIEN * 10)
				{
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre()] = new MartienVert();
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre()]->resetExtraTerrestre();
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre() - 1]->putExtraTerrestre();
				}
				if (timerAddExtraTerrestre == TIMER_ADD_KRYPTONIEN)
				{
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre()] = new Kryptonien();
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre()]->resetExtraTerrestre();
					tabExtraTerrestre[ExtraTerrestre::getNombreExtraTerrestre() - 1]->putExtraTerrestre();
				}

				timerTireET++;
				if (timerTireET >= limiteTimerTireET)
				{
					int i = getIndiceET();
					playFireSound();
					LaserET *laserET = new LaserET;
					laserET->coord.setPositionX(tabExtraTerrestre[i]->coord.getPositionX());
					laserET->coord.setPositionY(tabExtraTerrestre[i]->coord.getPositionY());
					laserET->isAlive = false;
					lasersET.ajouter(laserET);

					timerTireET = 0;
				}

				touche = recupererTouche();
				if (touche != -1)
				{
					if (touche == ' ')
					{
						playFireSound();
						Laser *laser = new Laser;
						laser->coord.setPositionX(joueur->coord.getPositionX());
						laser->isAlive = false;
						lasersJoueur.ajouter(laser);
					}

					if (joueur->coord.getPositionX() > 1 && joueur->coord.getPositionX() < NB_COLONES - 1)
					{
						joueur->modifierPosition(touche);
					}
					else if (joueur->coord.getPositionX() == 1)
					{
						if (touche == 'l')
						{
							joueur->modifierPosition(touche);
						}
					}
					else if (joueur->coord.getPositionX() == NB_COLONES - 1)
					{
						if (touche == 'k')
						{
							joueur->modifierPosition(touche);
						}
					}
				}

				Laser ** tabLaser = lasersJoueur.getTabLasers();
				afficherLaser(tabLaser, lasersJoueur.getNbLasers(), "joueur");

				Laser ** tabLaserET = lasersET.getTabLasers();
				afficherLaser(tabLaserET, lasersET.getNbLasers(), "ET");

				if (timerJiggleExtraTerrestres >= limiteTimerJiggleExtraTerrestre)
				{
					jiggleExtraTerrestres(tabExtraTerrestre);
					timerJiggleExtraTerrestres = 0;
				}
				Sleep(20);

				joueurEnVie = testerJoueurMeurt(joueur, tabLaserET, lasersET.getNbLasers());
				if(joueurEnVie)
				{
					testerCollision(tabExtraTerrestre, tabLaser, lasersJoueur.getNbLasers());
				}

				if (ExtraTerrestre::getNombreExtraTerrestre() == 0)
					gagne = true;
			}

			system("cls");
			if (gagne)
			{
				winGame();
			}
			else
			{
				loseGame();
			}
			if (recommencer() == 'O')
				continuer = true;
		}while (continuer);
	}
}

/*
Tâche: afficher le contour du terrain
Paramètres: le nombre de lignes et de colonnes du terrain rectangulaire
*/
void afficherTerrain(int nbLignes, int nbColonnes)
{
	UIKit::setDimensionFenetre(0, 0, nbColonnes + 90, nbLignes + 2);
	UIKit::cadre(0, 0, nbColonnes, nbLignes, 10);
	UIKit::curseurVisible(false);
}

char recupererTouche()
{
	if (_kbhit() == NULL)
	{
		return -1;
	}
	else
	{
		char caractere = _getch();
		if ((toupper(caractere) == 'K') || (toupper(caractere) == 'L') || (caractere == ' '))
		{
			return tolower(caractere);
		}
		else
			return -1;
	}
}

void playFireSound() {
	PlaySound("shoot.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}

void playGameOverSound() {
	PlaySound("lose.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}

void playWinSound() {
	PlaySound("win.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}

void afficherLaser(Laser** &tabLaser, int nbLaser, string type)
{
	for (int i = 0; i < nbLaser; i++)
	{
		if (tabLaser[i] != NULL)
		{
			if (!tabLaser[i]->isAlive)
			{
				if (type == "joueur")
				{
					tabLaser[i]->startLaser(tabLaser[i]->coord.getPositionX());
				}
				else if (type == "ET")
				{
					((LaserET*)tabLaser[i])->startLaser(tabLaser[i]->coord.getPositionX(), tabLaser[i]->coord.getPositionY());
				}
			}
			else if (tabLaser[i]->coord.getPositionY() > 1 && tabLaser[i]->coord.getPositionY() < 40)
			{
				if (type == "joueur")
				{
					tabLaser[i]->moveLaser();
				}
				else if (type == "ET")
				{
					((LaserET*)tabLaser[i])->moveLaser();
				}
			}
			else
			{
				tabLaser[i]->killLaser();
				delete tabLaser[i];
				tabLaser[i] = NULL;
			}
		}
	}
}

void jiggleExtraTerrestres(ExtraTerrestre** &tabExtraTerrestres)
{
	for (int i = 0; i < ExtraTerrestre::getNombreExtraTerrestre(); i++)
	{
		if (tabExtraTerrestres[i] != NULL)
		{
			if (tabExtraTerrestres[i]->ajouterPoints() == MartienVert::scoreMartienVert)
				((MartienVert*)tabExtraTerrestres[i])->jiggleExtraTerrestre();
			else if (tabExtraTerrestres[i]->ajouterPoints() == Kryptonien::scoreKryptonien)
				((Kryptonien*)tabExtraTerrestres[i])->jiggleExtraTerrestre();
			else if (tabExtraTerrestres[i]->ajouterPoints() == Infestateur::scoreInfestateur)
				((Infestateur*)tabExtraTerrestres[i])->jiggleExtraTerrestre();
		}

	}
}

void majTabMartiens(ExtraTerrestre** &tabExtraTerrestres)
{
	int nbElementValide = ExtraTerrestre::getNombreExtraTerrestre() - 1;

	ExtraTerrestre **tabTemp = new ExtraTerrestre*[15];
	int indiceCourantTemp = 0;
	for (int i = 0; i < ExtraTerrestre::getNombreExtraTerrestre(); i++)
	{
		if (tabExtraTerrestres[i] != NULL)
		{
			tabTemp[indiceCourantTemp] = tabExtraTerrestres[i];
			indiceCourantTemp++;
		}
	}

	delete[] tabExtraTerrestres;
	tabExtraTerrestres = tabTemp;
	ExtraTerrestre::reduireNombreExtraTerrestre();

}

void testerCollision(ExtraTerrestre** &tabExtraTerrestres, Laser** &tabLaser, int nbLaser)
{
	bool collision = false;
	for (int i = 0; i < nbLaser && !collision; i++)
	{
		if (tabLaser[i] != NULL)
		{
			for (int j = 0; j < ExtraTerrestre::getNombreExtraTerrestre() && !collision; j++)
			{
				if (tabExtraTerrestres[j] != NULL)
				{
					if ((tabLaser[i]->coord.getPositionX() == tabExtraTerrestres[j]->coord.getPositionX()) && (tabLaser[i]->coord.getPositionY() == tabExtraTerrestres[j]->coord.getPositionY()))
					{
						collision = true;
						tabExtraTerrestres[j]->removeExtraTerrestre();
						tabExtraTerrestres[j] = NULL;
						majTabMartiens(tabExtraTerrestres);
					}
				}
			}
		}
	}
}

bool testerJoueurMeurt(Vaisseau* joueur, Laser** tabLaserET, int nbLaser)
{
	for (int j = 0; j < nbLaser; j++)
	{
		if (tabLaserET[j] != NULL)
		{
			if ((joueur->coord.getPositionX() == tabLaserET[j]->coord.getPositionX()) && (tabLaserET[j]->coord.getPositionY() == joueur->coord.getPositionY()))
			{
				return false;
			}
		}
	}
	return true;
}

int getIndiceET()
{
	int indice;

	indice = rand() % ExtraTerrestre::getNombreExtraTerrestre();

	return indice;
}

void setTimersByDifficulte(int &timerJiggleExtraTerrestres, int &timerTireET, int difficulte)
{
	switch (difficulte)
	{
	case 49:
		timerJiggleExtraTerrestres = 10;
		timerTireET = 200;
		break;
	case 50:
		timerJiggleExtraTerrestres = 5;
		timerTireET = 100;
		break;
	case 51:
		timerJiggleExtraTerrestres = 2;
		timerTireET = 25;
		break;
	}
}

char recommencer()
{
	cout << "			Voulez-vous faire une autre partie ? (O/N) " << endl;

	char choix;
	do
	{
		choix = toupper(_getch());
	} while ((choix != 'O') && (choix != 'N'));
	return choix;

}

void loseGame()
{
	UIKit::color(12);
	playGameOverSound();
	std::cout << "____     ___                      ___                             " << std::endl;
	std::cout << "`MM(     )M'                      `MM                             " << std::endl;
	std::cout << " `MM.    d'                        MM                             " << std::endl;
	std::cout << "  `MM.  d' _____  ___   ___        MM   _____     ____     ____   " << std::endl;
	std::cout << "   `MM d' 6MMMMMb `MM    MM        MM  6MMMMMb   6MMMMb\  6MMMMb  " << std::endl;
	std::cout << "    `MM' 6M'   `Mb MM    MM        MM 6M'   `Mb MM'    ` 6M'  `Mb " << std::endl;
	std::cout << "     MM  MM     MM MM    MM        MM MM     MM YM.      MM    MM " << std::endl;
	std::cout << "     MM  MM     MM MM    MM        MM MM     MM  YMMMMb  MMMMMMMM " << std::endl;
	std::cout << "     MM  MM     MM MM    MM        MM MM     MM      `Mb MM       " << std::endl;
	std::cout << "     MM  YM.   ,M9 YM.   MM        MM YM.   ,M9 L    ,MM YM    d9 " << std::endl;
	std::cout << "    _MM_  YMMMMM9   YMMM9MM_      _MM_ YMMMMM9  MYMMMM9   YMMMM9  " << std::endl << std::endl << std::endl;

}

void winGame()
{
	UIKit::color(12);
	playWinSound();
	std::cout << "oooooo   oooo                            oooooo   oooooo     oooo  o8o              " << std::endl;
	std::cout << " `888.   .8'                              `888.    `888.     .8'                    " << std::endl;
	std::cout << "  `888. .8'    .ooooo.  oooo  oooo         `888.   .8888.   .8'   oooo  ooo. .oo.   " << std::endl;
	std::cout << "   `888.8'    d88' `88b `888  `888          `888  .8'`888. .8'    `888  `888P'Y88b  " << std::endl;
	std::cout << "    `888'     888   888  888   888           `888.8'  `888.8'      888   888   888  " << std::endl;
	std::cout << "     888      888   888  888   888            `888'    `888'       888   888   888  " << std::endl;
	std::cout << "    o888o     `Y8bod8P'  `V88V'V8P'            `8'      `8'       o888o o888o o888o " << std::endl << std::endl << std::endl;

}

