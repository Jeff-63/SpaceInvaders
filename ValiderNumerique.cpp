#include "ValiderNumerique.h"
#include <iostream>
using namespace std;

int validerNumerique()
{
	int valeur;
	cin >> valeur;
	while (cin.fail() || cin.peek() != 10)
	{
		cin.clear();
		cin.ignore(512, '\n');
		cout << "ERREUR : entrez un nombre s'il vous plait..." << endl;
		cout << "Essayez a nouveau : ";
		cin >> valeur;
	}

	return valeur;
}