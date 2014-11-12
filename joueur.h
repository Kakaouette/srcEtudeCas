#ifndef JOUEUR_H
#define JOUEUR_H


#include <SDL_image.h>
#include "ressource.h"

typedef struct Joueur { // Acc�s � "map" pour acc�der aux cases sans garder le truc en fond
    char arrivee[2];//?choisir mettre arrivee sur case ou position case arrivee sur joueur?
    SDL_Rect* image;
    char orientation;
    char position[2];
    Ressource* sac[];
    //int score[nombreTypeRessource]; // 0-banane, 1-fraise, 2-orange, etc... #define fraise 0 // #define ptsFraise 1 (ou 5) ?
}Joueur;

typedef enum Orientation{
    bas,
    gauche,
    droite,
    haut
}Orientation;

#endif // JOUEUR_H
