
#include "Case.h"
#include "Jeu.h"


Case cs[NB_CASE_X][NB_CASE_Y];

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
    // allocation
    int i;
    game->map = malloc(NB_CASE_X * sizeof(*game->map));
    for (i=0 ; i < NB_CASE_X ; i++){
        game->map[i] = malloc(NB_CASE_Y * sizeof(**game->map));
    }
    //initialisation
    int j;
    for (i=0; i<NB_CASE_X;i++){
        for (j=0; j<NB_CASE_Y;j++){
            cs[i][j].depart = 0;
            cs[i][j].arrivee = 0;
            game->map[i][j] = &cs[i][j];
        }
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

    free(game->ressources);
}
