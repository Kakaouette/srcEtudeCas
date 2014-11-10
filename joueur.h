#ifndef JOUEUR_H
#define JOUEUR_H

#include <SDL_image.h>
#include "ressource.h"

typedef struct Joueur { // Acc�s � "map" pour acc�der aux cases sans garder le truc en fond
    int depart[2];
    int arrivee[2];
    SDL_Rect* image;
    int position[2];
    Ressource* score[];
    //int score[nombreTypeRessource]; // 0-banane, 1-fraise, 2-orange, etc... #define fraise 0 // #define ptsFraise 1 (ou 5) ?
/*
// "Constructeur" !
Voir exempleConstructeur.txt
*/
}Joueur;

#endif // JOUEUR_H
