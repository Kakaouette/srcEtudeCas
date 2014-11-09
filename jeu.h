#ifndef JEU_H
#define JEU_H

#include "Case.h"
#include "ressource.h"
#include "joueur.h"

extern const int NB_CASE_X;
extern const int NB_CASE_Y;

typedef struct Jeu{
    Case** (*map);//[NB_CASE_X][NB_CASE_Y];
    Joueur J1;// = joueur.newJoueur(); // Aucune id�e.
    Ressource* (*ressources);
}Jeu;

void execution();
void new_Game(Jeu* game);
void free_Jeu(Jeu *game);

#endif // JEU_H
