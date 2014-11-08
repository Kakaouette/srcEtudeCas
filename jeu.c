
#include <SDL_image.h>
#include "Case.h"
#include "Jeu.h"
#include "ressource.h"

extern const int NB_CASE_X;
extern const int NB_CASE_Y;

/*void resetRessources(Ressource* ressources[]){
    int i;
    for(i = 0 ; i < ressources.length ; i++){
        ressources[i]->vue = 0;
        ressources[i]->pass = 0;
        ressources[i]->rendu = 0;
    }
}*/


void new_Game(Jeu* game){
    int i;
    Case ** tableau;
    tableau = malloc(NB_CASE_X * sizeof(*tableau));//new Case* [NB_CASE_X];
    for (i=0 ; i < NB_CASE_X ; i++){
        tableau[i] = malloc(NB_CASE_Y * (sizeof(SDL_Rect)+3*sizeof(char)));//**tableau
    }
    game->map = tableau;
}

void free_Jeu(Jeu *game){
    int i;
    // Libération mémoire : tableau dynamique à 2 dimensions
    for (i=0; i<NB_CASE_X; i++)
    {
        free (game->map[i]);
    }
    free(game->map);
}
