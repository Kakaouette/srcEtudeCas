#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "joueur.h"

char * remplirChemin(char A, char B, char *C, char D);
void testChemin(char A[2], char B[2], const Case*** carte, char nbCases[2], int actuel, int *meilleur, char** chemin, char** meilleurChemin, char direction);
void calculChemin(char A[2], char B[2], const Case*** carte, char nbCases[2], int actuel, int *meilleur, char** chemin, char** meilleurChemin);

long newPosition(char coordonnee[2]);
char evaluerPosition(char coordonnee[2], long etatPosition);

Arrete** trierArretes(Arrete* (*tab), int nbArretes, Arrete *aRanger);
Arrete** trierChemin(Arrete* (*tab), int nbArretes);

Arrete** algorithmeChemin(Joueur *joueur, Ressource* (*ressources), int nbRessources, const Case*** carte, char nbCases[2]);

#endif // ALGORITHME_H
