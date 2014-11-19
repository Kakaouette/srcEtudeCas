#ifndef ALGORITHME_H
#define ALGORITHME_H

#include "arrete.h"
#include "joueur.h"

long newPosition(char coordonnee[2]);
char evaluerPosition(char coordonnee[2], long etatPosition);

Arrete** trierArretes(Arrete* (*tab), int nbArretes, Arrete *aRanger);
Arrete** trierChemin(Arrete* (*tab), int nbArretes);

Arrete** algorithmeSansContrainte(Joueur *joueur, Ressource* (*ressources), int nbRessources);

#endif // ALGORITHME_H
