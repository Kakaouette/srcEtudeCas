#ifndef JOUEUR_H
#define JOUEUR_H


#include "ressource.h"

/**
 * \struct Joueur
 * \brief Toutes les données necessaire pour un joueur
 *
 * arrivee: position darrivée
 * sprite: image
 * orientation: orientation actuelle
 * position: position actuelle
 * sac: ressources ramassées
 */
typedef struct Joueur {
    char arrivee[2];
    Sprite* sprite;
    char orientation;
    char position[2];
    int sac[1];
    int nbRessources;
}Joueur;

/**
 * \enum Orientation
 * \brief Orientation dun joueur
 */
typedef enum Orientation{
    bas,
    gauche,
    droite,
    haut
}Orientation;

char deplacement(Ressource**, int, Joueur*, char);
int testDeplacement(const Case***, int[2], char[2], char);

#endif // JOUEUR_H
