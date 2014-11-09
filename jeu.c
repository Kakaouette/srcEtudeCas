
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

void execution(){} // Appell� depuis le main. Cr�� affichage/joueur/etc... // options a ajouter en argument


void new_Game(Jeu* game){
    int i;
    game->map = malloc(NB_CASE_X * sizeof(*game->map));
    for (i=0 ; i < NB_CASE_X ; i++){
        game->map[i] = malloc(NB_CASE_Y * sizeof(**game->map));//(sizeof(SDL_Rect)+3*sizeof(char))
    }
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
