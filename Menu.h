#pragma once
#include "ValiderNumerique.h"
#include <iostream>
#include "UIKit.h"
#include "mmsystem.h" 
#pragma comment( lib, "winmm.lib" ) 
#include <conio.h>

void afficherMenu();
void afficherOptionsMenu();
void afficherNiveauDifficulte();
int selectionnerOptionMenu();
int selectionnerNiveauDifficulte();
void playMenuSound();
void setFenetreMenu();
void playBackgroundSound();