#ifndef JOUEUR_H
#define JOUEUR_H


#include "ressource.h"

typedef struct Joueur { // Acc�s � "map" pour acc�der aux cases sans garder le truc en fond
    char arrivee[2];
    Sprite* sprite;
    char orientation;
    char position[2];
    int nbRessources;
    //Peut-on initialiser un tableau sans taille ?
    Ressource* sac[];//int score[nombreTypeRessource];
}Joueur;

typedef enum Orientation{
    bas,
    gauche,
    droite,
    haut
}Orientation;

#endif // JOUEUR_H
