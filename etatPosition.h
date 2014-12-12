#ifndef ETATPOSITION_H
#define ETATPOSITION_H

#include "joueur.h"

/**
 * \struct EtatPosition
 * \brief Objet contenant des flags li�s � une position.
 *
 */
typedef struct EtatPosition{
    char posX;
    char posY;
    char flagAvance; // Flag pour l'�tat du point : 0, aucun lien ; 1, li� � une Arrete ; 2, li� � deux Arrete
    char flagVerif; // Flag pour l'�tat vu/non vu du point lors du calcul de chaines existantes
}EtatPosition;

EtatPosition* newPosition(char coordonnee[2], char flag);

char evaluerPosition(char coordonnee[2], EtatPosition* etatPosition);
char indexEtat(char position[2], EtatPosition** tabEtats, int nbPositions);
EtatPosition* getEtatPosition(char position[2], EtatPosition** tabEtats, int nbPositions);
char comparerEtats(EtatPosition* etatA, EtatPosition* etatB);
void resetFlag(EtatPosition** tabEtats, int nbPositions);


#endif // ETATPOSITION_H
