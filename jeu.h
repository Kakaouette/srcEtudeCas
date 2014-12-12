#ifndef JEU_H
#define JEU_H

#include "algorithme.h"


/**
 * \struct Jeu
 * \brief Toutes les données d'un jeu
 *
 * case: la carte
 * nbCaseX, nbCaseY: nombre de case
 * players: les joueurs dans un tableau
 * ressources: les ressources dans un tableau
 */
typedef struct Jeu{
    const Case** (*map); //le const s'applique à la valeur pointée
    int nbCaseX;
    int nbCaseY;
    Joueur* (*players);
    int nbPlayer;
    Ressource* (*ressources);//tableauDeResourceParType[ressourceType0[position[x,y],...], ressourceType1,...]
    int nbRessource;
}Jeu;

void execution();
char jouerTour(Jeu*, Joueur*, Arrete*);

/**
 * \struct Option
 * \brief Les options de jeu
 *
 * sprites: l'apparence de chaque joueur dans un tableau
 */
typedef struct Option{
    int nbCaseX;
    int nbCaseY;
    int nbCaseLibre;
    int nbRessource;
    int nbJoueur;
    Sprite* *sprites;
}Option;


void new_Game(Jeu *game, Option *defaut);
void free_Jeu(Jeu *game);

void genTerrain(Jeu *game, int nbCaseLibreVoulu);
void genDepartArrivee(Jeu *game);
void genObjet(Jeu *game);

//Prototype random
int rand_a_b(int a, int b);

#endif // JEU_H
