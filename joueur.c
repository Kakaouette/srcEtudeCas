#include <string.h>
#include <math.h>
#include "jeu.h"

#define X 0
#define Y 1

/**
 * Gère le déplacement d'une case :
 * Retourne 'T' si le joueur tombe sur une ressource, 'F' sinon
 * Place le joueur sur la case
 *
 * @param ressources    liste des ressources
 * @param nbRessource   nombre total de ressources
 * @param player        joueur actif
 * @param depl          sens de déplacement (H/B/G/D)
 * @return char
 */
char deplacement(Ressource* *ressources, int nbRessource, Joueur* player, char depl) { //Une case
    int i, j;

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
            player->sac[0]++;
            for (j = i; j < nbRessource - 1; j++) {
                ressources[j] = ressources[j + 1];
            }
            return 'T';
        }
    }
    return 'F';
}

/**
 * Vérifie si la case suivante est libre et si elle est dans les limtes de la carte
 * Retourne 1 si la case est valide, 0 sinon
 * 
 * @param map       carte des cases
 * @param nbCase    dimensions de la carte
 * @param position  coordonnées de la nouvelle case
 * @param depl      sens de déplacement (H/B/G/D)
 * @return int
 */
int testDeplacement(const Case*** map, int nbCase[2], char position[2], char depl) { //Une case
    char new_x = position[X];
    char new_y = position[Y];

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

    if (new_x >= 0 && new_x < nbCase[X] && new_y >= 0 && new_y < nbCase[Y]){
        if(map[new_x][new_y]->type != infranchissable) {
            return 1;
        } else {
            return 0;
        }
    } else {
        return 0;
    }
}
