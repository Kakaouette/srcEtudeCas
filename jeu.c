
#include "Case.h"
#include "Jeu.h"


/*void resetRessources(Ressource* ressources[]){
    int i;
    for(i = 0 ; i < ressources.length ; i++){
        ressources[i]->vue = 0;
        ressources[i]->pass = 0;
        ressources[i]->rendu = 0;
    }
}*/

void execution(){} // Appell� depuis le main. Cr�� affichage/joueur/etc... // options a ajouter en argument


static Case** casesTemp;
static Ressource* ressourcesTemp;

void new_Game(Jeu* game){
    //allocation temp
    int i;
    casesTemp = malloc(game->nbCaseX * sizeof(*casesTemp));
    for (i=0 ; i < game->nbCaseX ; i++){
        casesTemp[i] = malloc(game->nbCaseY * sizeof(**casesTemp));
    }
    ressourcesTemp = malloc(game->nbRessource * sizeof(*ressourcesTemp));
    //allocation map
    game->map = malloc(game->nbCaseX * sizeof(*game->map));
    for (i=0 ; i < game->nbCaseX ; i++){
        game->map[i] = malloc(game->nbCaseY * sizeof(**game->map));
    }
    //allocation ressources
    game->ressources = malloc(game->nbRessource* sizeof(Ressource));
    //initialisation map
    int j;
    for (i=0; i<game->nbCaseX;i++){
        for (j=0; j<game->nbCaseY;j++){
            casesTemp[i][j].depart = 0;
            casesTemp[i][j].arrivee = 0;
            game->map[i][j] = &casesTemp[i][j];
        }
    }
    //initialisation ressources
    for (j=0; j<game->nbRessource;j++){
        game->ressources[j] = &ressourcesTemp[j];
    }
}
void free_Jeu(Jeu *game){
    int i;
    // Libération mémoire des temp
    for (i=0; i<game->nbCaseX; i++)
    {
        free(casesTemp[i]);
    }
    free(casesTemp);
    free(ressourcesTemp);
    // Libération mémoire map
    for (i=0; i<game->nbCaseX; i++)
    {
        free (game->map[i]);
    }
    free(game->map);
    // Libération mémoire ressources
    free(game->ressources);
}
