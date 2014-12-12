#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "etatPosition.h"

void reallocChemin(char*** chemin, int actuel);
void remplirChemin(char posX, char posY, char* tab, char direction);
char testPosition(char position[2], const Case*** carte, char nbCases[2], int actuel, char** chemin, char direction);
void calculChemin(char A[2], char B[2], const Case*** carte, char nbCases[2], int actuel, int *meilleur, char*** chemin, char** meilleurChemin);

Arrete* inverserArrete(Arrete* arrete);
char comparerArrete(Arrete* premiere, Arrete* deuxieme);

Arrete** trierArretes(Arrete* (*tab), int nbArretes, Arrete *aRanger);
Arrete** ordonnerChemin(Arrete* (*tab), int nbArretes);

Arrete** algorithmeChemin(Joueur *joueur, Ressource* (*ressources), int nbRessources, const Case*** carte, char nbCases[2]);
Arrete** cheminPlusCourt(Arrete** tabArretes, EtatPosition** etatPositions, int nbArretes, int nbRessources);
Arrete** copieChemin(Arrete** chemin, int size);
Arrete* copieArrete(Arrete* arrete);

#endif // ALGORITHME_H
