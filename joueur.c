#include "joueur.h"

#include <string.h>
#include <math.h>
#include "case.h"
#include "arrete.h"

// X et Y pour une meilleure lecture
#define X 0 // X pour l'abscisse position[X] premier element du tableau
#define Y 1 // Y pour l'ordonnee position[Y] second element du tableau


void trier(Arrete* tab[], Arrete *aRanger){
    ///memset();
    //short i, j, temp;
    ///!!! Pas de "length" ou "size"
    /*for(i = 0 ; i < tab.length ; i++){
        if(tab[i]==0){
            tab[i] = aRanger;
            break;
        }
        if((tab[i]->D)<(aRanger->D)){
            for(j = i; j < tab.length ; j++){
                if(tab[i]==0){
                    tab[i] = aRanger;
                    break;
                }
                temp = tab[i];
                tab[i] = aRanger;
            }
            break;
        }
    }
    return tab;*/
}

void algorithmeSansContrainte(Joueur joueur, Ressource* ressources[]){

};

char jouer(); // Un tour (pour le mode deux joueurs)

///!!! On donne la map en parametre. Mais chez moi y'a un probleme
///!!! il me donne "type incomplet" sur tableau à deux dimensions.
///!!! Envisager Case*** (ouais c'est moche), ou include de jeu ?
short deplacement(Joueur* player, Case* map[], short x, short y) { //Une case
    short depx = x - player->position[0];
    short depy = y - player->position[1];
    if (abs(depy) > abs(depx)) {
        if (depy != 0) {
            short sign = depy/abs(depy);
            ///!!! "jeu" est inconnu, il faut donner la map ou le jeu en param
            Case* nextCase = NULL; //jeu.map[player->position[X]][player->position[Y] + sign];
            switch (nextCase->type) {
                case libre :
                    player->position[Y] += sign;
                    return 0;

    // Try to allocate vector data, free structure if fail.
                case infranchissable :
                    return 1;
            }
        }
    } else {
        if (depx != 0) {
            short sign = depx/abs(depx);
            ///!!! Meme souci "jeu" et "map"
            Case* nextCase = NULL;//jeu.map[player->position[X] + sign][player->position[Y]];
            switch (nextCase->type) {
                case libre :
                    player->position[X] += sign;
                    return 0;
                case infranchissable :
                    return 1;
            }
        }
    }
}

void algorithme() {
    Ressource* objectif;
    Joueur* player;
    int depy = objectif->position[Y] - player->position[Y];
    int depx = objectif->position[X] - player->position[X];
    int dep = abs(depx) + abs(depy);
}
