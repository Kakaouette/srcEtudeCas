#include "joueur.h"

#include <string.h>
#include <math.h>

#define X 0
#define Y 1

char jouer(); // Un tour (pour le mode deux joueurs)

/**
 * Gère le déplacement d'une case :
 * Retourne -2 si la case est infranchissable
 * Retourne -1 si la case est libre
 * Retourne le numéro d'une ressource dans la liste des ressources si la case contient une ressource
 * Place le joueur sur la case si elle n'est pas infranchissable
 *
 * @param game      jeu
 * @param player    joueur
 * @param x         abscisse d'arrivée
 * @param y         ordonnée d'arrivée
 * @return int
 */
short deplacement(Ressource** ressources, Case*** map, int nbRessource, Joueur* player, short x, short y) { //Une case
    short depx = x - player->position[0];
    short depy = y - player->position[1];
    short sign;
    int i;
    size_t size;
    Case* nextCase;
    if (abs(depy) > abs(depx)) {
        if (depy != 0) {
            sign = depy/abs(depy);
            nextCase = map[player->position[X]][player->position[Y] + sign];
            switch (nextCase->type) {
                case libre :
                    player->position[Y] += sign;
                    for (i = 0; i < nbRessource; i++) {
                        if (player->position[X] == ressources[i]->position[X] &&
                                player->position[Y] == ressources[i]->position[Y]) {
                            player->sac[player->nbRessources] = ressources[i];
                            free(ressources[i]);
                            nbRessource--;
                            return i;
                        }
                    }
                    return 0;

                case infranchissable :
                    return -1;
            }
        }
    } else {
        if (depx != 0) {
            sign = depx/abs(depx);
            nextCase = map[player->position[X] + sign][player->position[Y]];
            switch (nextCase->type) {
                case libre :
                    player->position[X] += sign;
                    for (i = 0; i < nbRessource; i++) {
                        if (player->position[X] == ressources[i]->position[X] &&
                                player->position[Y] == ressources[i]->position[Y]) {
                            player->sac[player->nbRessources] = ressources[i];
                            free(ressources[i]);
                            nbRessource--;
                            return i;
                        }
                    }
                    return 0;

                case infranchissable :
                    return -1;
            }
        }
    }
}

//Essai d'itinéraire sans contraintes, 0% de garantie de fonctionnement
//pas encore fini
/*
void algorithme() {
    Jeu* game;
    Ressource* objectif;
    Joueur* player;
    short depl;
    while (player->position[X] != objectif->position[X] || player->position[Y] != objectif->position[Y]) {
        depl = deplacement(game, player, objectif->position[X], objectif->position[Y]);
    }
}*/
