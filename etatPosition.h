#ifndef ETATPOSITION_H
#define ETATPOSITION_H

#include "joueur.h"

typedef struct EtatPosition{
    char posX;
    char posY;
    char flagAvance;
    char flagVerif;
}EtatPosition;

EtatPosition* newPosition(char coordonnee[2], char JoueurOuArrivee);
char indexEtat(char position[2], EtatPosition** tabEtats, int nbPositions);
char evaluerPosition(char coordonnee[2], EtatPosition* etatPositions);
char comparerEtats(EtatPosition* etatA, EtatPosition* etatB);
void resetFlag(EtatPosition** tabEtats, int nbPositions);
EtatPosition* getEtatPosition(char position[2], EtatPosition** tabEtats, int nbPositions);

#endif // ETATPOSITION_H
