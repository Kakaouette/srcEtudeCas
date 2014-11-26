#include <string.h>
#include <math.h>
#include "jeu.h"

#define X 0
#define Y 1

char jouer(Jeu *game, Joueur *player, Arrete *arrete) { // Un tour (pour le mode deux joueurs)
    int i;

    short result = deplacement(game->ressources, game->map, game->nbRessource, player, arrete->C[0]);
    if (result != -1) {
        game->nbRessource--;
    }

    for (i = 0; i < arrete->D - 1; i++) {
        arrete->C[i] = arrete->C[i + 1];
    }
    free(arrete->C[arrete->D - 1]);
    arrete->D--;
}

/**
 * Gère le déplacement d'une case :
 * Retourne -1 si la case est libre
 * Retourne le numéro d'une ressource dans la liste des ressources si la case contient une ressource
 * Place le joueur sur la case
 *
 * @param ressources    liste des ressources
 * @param map           carte des cases
 * @param nbRessource   nombre total de ressources
 * @param player        joueur actif
 * @param depl          sens de déplacement (H/B/G/D)
 * @return short
 */
short deplacement(Ressource* *ressources, const Case*** map, int nbRessource, Joueur* player, char depl) { //Une case
    int i;

    switch (depl) {
        case 'H':
            player->position[Y]--;
            break;

        case 'B':
            player->position[Y]++;
            break;

        case 'G':
            player->position[X]--;
            break;

        case 'D':
            player->position[X]++;
            break;
    }

    for (i = 0; i < nbRessource; i++) {
        if (player->position[X] == ressources[i]->position[X] && player->position[Y] == ressources[i]->position[Y]) {
            player->sac[i]++;
            free(ressources[i]);
            return i;
        }
    }
    return -1;
}

//Fonction test qui ne déplace pas le joueur, renvoie juste le résultat
short testDeplacement(Ressource* *ressources, const Case*** map, int nbRessource, Joueur* player, char depl) { //Une case
    int i;
    char new_x = player->position[X];
    char new_y = player->position[Y];

    switch (depl) {
        case 'H':
            new_y--;
            break;

        case 'B':
            new_y++;
            break;

        case 'G':
            new_x--;
            break;

        case 'D':
            new_x++;
            break;
    }

    for (i = 0; i < nbRessource; i++) {
        if (new_x == ressources[i]->position[X] && new_y == ressources[i]->position[Y]) {
            player->sac[i]++;
            free(ressources[i]);
            return i;
        }
    }
    return -1;
}
