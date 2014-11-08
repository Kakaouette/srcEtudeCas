#ifndef JEU_H
#define JEU_H

#include "Case.h"
#include "ressource.h"

typedef struct Jeu{
    Case* **map;//[NB_CASE_X][NB_CASE_Y];
    //Joueur J1 = joueur.newJoueur(); // Aucune id�e.
    Ressource* ressources[];
    //execution(); // Appell� depuis le main. Cr�� affichage/joueur/etc... // options a ajouter en argument
}Jeu;

void new_Game(Jeu* game);
void free_Jeu(Jeu *game);

#endif // JEU_H
