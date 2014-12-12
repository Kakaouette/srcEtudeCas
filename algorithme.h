#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "etatPosition.h"

Arrete** algorithmeChemin(Joueur *joueur, Ressource **ressources, int nbRessources, const Case*** carte, char nbCases[2]);
void calculChemin(char A[2], char B[2], const Case*** carte, char nbCases[2], int actuel, int *meilleur, char*** chemin, char** meilleurChemin);
Arrete** cheminPlusCourt(Arrete** tabArretes, EtatPosition** etatPositions, int nbArretes, int nbRessources);
Arrete** ordonnerChemin(Arrete** chemin, int taille);

char comparePosition(char *positionA, char *positionB);
char testPosition(char position[2], const Case*** carte, char nbCases[2], int actuel, char** chemin, char direction);

Arrete** trierArretes(Arrete **tab, int nbArretes, Arrete *aRanger);
char comparerArrete(Arrete* premiere, Arrete* deuxieme);

char* inverserChemin(char* chemin, char taille);
Arrete* inverserArrete(Arrete* arrete);

char arreteValide(EtatPosition** etatPositions, int nbPositions, int idxA, int idxB, Arrete** chemin, int tailleChemin);
char estChaine(EtatPosition* posExtremite, EtatPosition* posActuelle, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int nb);
char chaine(EtatPosition* B, EtatPosition* A, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int tailleChemin);

void reallocChemin(char*** chemin, int actuel);
void remplirChemin(char posX, char posY, char* cheminActuel, char direction);
Arrete* copieArrete(Arrete* arrete);
Arrete** copieChemin(Arrete** chemin, int taille);

#endif // ALGORITHME_H
