#ifndef JOUEUR_H
#define JOUEUR_H


#include "ressource.h"

typedef struct Joueur {
    char arrivee[2];
    Sprite* sprite;
    char orientation;
    char position[2];
    Ressource** sac;//int score[nombreTypeRessource];
    int nbRessources;
}Joueur;

typedef enum Orientation{
    bas,
    gauche,
    droite,
    haut
}Orientation;

#endif // JOUEUR_H
