#ifndef JEU_H
#define JEU_H

#include "Case.h"
#include "ressource.h"
#include "joueur.h"


typedef struct Jeu{
    Case** (*map);
    int nbCaseX;
    int nbCaseY;
    Joueur J1;// = joueur.newJoueur(); // Aucune id�e.
    Ressource* (*ressources);//?choisir 1:mettre ressource sur case ou 2:mettre position dans ressource?->1:enlever tableau de ressource
    int nbRessource;
}Jeu;

void execution();

void new_Game(Jeu* game);
void free_Jeu(Jeu *game);

#endif // JEU_H
