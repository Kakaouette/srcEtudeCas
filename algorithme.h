#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "joueur.h"

void calculChemin(char A[2], char B[2], Case*** carte, int actuel, int *meilleur, char*** chemin, char** meilleurChemin){

long newPosition(char coordonnee[2]);
char evaluerPosition(char coordonnee[2], long etatPosition);

Arrete** trierArretes(Arrete* (*tab), int nbArretes, Arrete *aRanger);
Arrete** trierChemin(Arrete* (*tab), int nbArretes);

Arrete** algorithmeSansContrainte(Joueur *joueur, Ressource* (*ressources), int nbRessources);

#endif // ALGORITHME_H
