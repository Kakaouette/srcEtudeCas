#ifndef JOUEUR_H
#define JOUEUR_H


#include "ressource.h"

typedef struct Joueur { // Acc�s � "map" pour acc�der aux cases sans garder le truc en fond
    char arrivee[2];
    Sprite* sprite;
    char orientation;
    char position[2];
    int sac[1];
    int nbRessources;
}Joueur;

typedef enum Orientation{
    bas,
    gauche,
    droite,
    haut
}Orientation;

void deplacement(Ressource**, int, Joueur*, char);
int testDeplacement(const Case***, int[2], char[2], char);

#endif // JOUEUR_H
