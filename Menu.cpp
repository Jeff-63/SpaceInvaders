#include "Menu.h"

const int COMMENCER_PARTIE = 1;
const int REGLES_JEU = 2;
const int QUITTER = 0;

void afficherMenu()
{
	setFenetreMenu();
	playMenuSound();
	std::cout << "			  oooooooo8 " << std::endl;
	std::cout << "			 888        ooooooooo     ooooooo    ooooooo    ooooooooo8 " << std::endl;
	std::cout << "			  888oooooo  888    888   ooooo888 888     888 888oooooo8  " << std::endl;
	std::cout << "			         888 888    888 888    888 888         888         " << std::endl;
	std::cout << "			 o88oooo888  888ooo88    88ooo88 8o  88ooo888    88oooo888 " << std::endl;
	std::cout << "			            o888                                           " << std::endl << std::endl << std::endl;
	std::cout << "			 ooooo                                       oooo" << std::endl ;
	std::cout << "			  888  oo oooooo oooo   oooo ooooooo    ooooo888  ooooooooo8 oo oooooo     oooooooo8" << std::endl;
	std::cout << "			  888   888   888 888   888  ooooo888 888    888 888oooooo8   888    888  888ooooooo" << std::endl;
	std::cout << "			  888   888   888  888 888 888    888 888    888 888          888                 888" << std::endl;
	std::cout << "			 o888o o888o o888o   888    88ooo88 8o  88ooo888o  88oooo888 o888o        88oooooo88" << std::endl << std::endl << std::endl;
                                                                        
	std::cout << "							 ooooo ooooo " << std::endl;
	std::cout << "							  888   888  " << std::endl;
	std::cout << "							  888   888  " << std::endl;
	std::cout << "							  888   888  " << std::endl;
	std::cout << "							 o888o o888o " << std::endl;

	Sleep(3800);
	afficherOptionsMenu();
}

void afficherOptionsMenu()
{
	playBackgroundSound();

	std::cout << std::endl << std::endl << "_______________________________________________________________________________________________________________________________________" << std::endl << std::endl << std::endl << std::endl;

	std::cout << "						 1 : Commencer Partie " << std::endl; 
	std::cout << "						 2 : Regles du jeu  " << std::endl;
	std::cout << "						 0 : Quitter" << std::endl;
}

void afficherNiveauDifficulte()
{
	UIKit::color(11);
	std::cout << std::endl << std::endl << "			Selectionner votre niveau de difficulte : " << std::endl << std::endl << std::endl << std::endl;

	std::cout << "					 1 : Facile " << std::endl;
	std::cout << "					 2 : Normale " << std::endl;
	std::cout << "					 3 : Difficile  " << std::endl;
}

int selectionnerOptionMenu()
{
	int choix;
	do
	{
		choix = _getch();
	} while ((choix != 48) && (choix != 49) && (choix != 50));
	return choix;

}

int selectionnerNiveauDifficulte()
{
	int choix;
	do
	{
		choix = _getch();
	} while ((choix != 49) && (choix != 50) && (choix != 51));
	return choix;

}

void playMenuSound() {
	PlaySound("spaceInvaders.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}

void playBackgroundSound() {
	PlaySound("background.wav", GetModuleHandle(NULL), SND_FILENAME | SND_ASYNC);
}

void setFenetreMenu()
{
	UIKit::setDimensionFenetre(0, 0, 132, 44);
	UIKit::color(11);
	UIKit::curseurVisible(false);
}