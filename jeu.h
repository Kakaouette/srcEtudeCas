#ifndef JEU_H
#define JEU_H

#include "algorithme.h"


typedef struct Jeu{
    const Case** (*map); //le const s'applique à la valeur pointée
    int nbCaseX;
    int nbCaseY;
    Joueur J1;// = joueur.newJoueur(); // Aucune id�e.
    Ressource* (*ressources);//tableauDeResourceParType[ressourceType0[position[x,y],...], ressourceType1,...]
    int nbRessource;
}Jeu;

void execution();


typedef struct Option{
    int nbCaseX;
    int nbCaseY;
    int nbCaseLibre;
    int nbRessource;
    Sprite *sprite;
}Option;


void new_Game(Jeu *game, Option *defaut);
void free_Jeu(Jeu *game);

void genTerrain(Jeu *game, int nbCaseLibreVoulu);
void genDepartArrivee(Jeu *game);
void genObjet(Jeu *game);

//Prototype random
int rand_a_b(int a, int b);

#endif // JEU_H
