#include "joueur.h"

#include <string.h>
#include <math.h>
#include "case.h"
#include "arrete.h"

// X et Y pour une meilleure lecture
#define X 0 // X pour l'abscisse position[X] premier element du tableau
#define Y 1 // Y pour l'ordonnee position[Y] second element du tableau

///!!! On donne la map en parametre. Mais chez moi y'a un probleme
///!!! il me donne "type incomplet" sur tableau à deux dimensions.
///!!! Envisager Case*** (ouais c'est moche), ou include de jeu ?
short deplacement(Joueur* player, Case**(* map), short x, short y) { //Une case
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

void trier(Arrete* (*tab), int nbArretes, Arrete *aRanger){
    ///memset();
    short i, j;
    Arrete* temp;
    for(i = 0 ; i < nbArretes ; i++){
        if(tab[i]==0){
            tab[i] = aRanger;
            break;
        }
        if((tab[i]->D)<(aRanger->D)){
            for(j = i; j < nbArretes ; j++){
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
}

void trierChemin(Arrete* (*tab), int nbArretes){

}
/*
//allocation map
    game->map = malloc(game->nbCaseX * sizeof(*game->map));
    for (i=0 ; i < game->nbCaseX ; i++){
        game->map[i] = malloc(game->nbCaseY * sizeof(**game->map));
    }
    //allocation ressources
    game->ressources = malloc(game->nbRessource* sizeof(Ressource));
*/
void algorithmeSansContrainte(Joueur *joueur, Ressource* (*ressources), int nbRessources){
    // Pas de ressources : on va directement au point d'arrivee.
    if(nbRessources == 0){
        ///deplacement(joueur, /*?*/, joueur->arrivee[X], joueur->arrivee[Y]);
        return;
    }
    // Nombre d'arretes total pour la taille tableau.
    int nbArretes = (nbRessources * (nbRessources-1))/2 + nbRessources*2;
    // Allocation tableau d'Arrete
    Arrete* (*tabArretes);
    tabArretes = malloc(nbArretes * sizeof(*Arrete));
    int i,j;
    // Ajout des arretes liées au joueur et au point d'arrivee
    for(i = 0, i < nbRessources, i++){
        // Ajout de l'arrete avec le joueur
        Arrete* arreteJoueur = malloc(sizeof(Arrete));
        arreteJoueur->A = joueur->position; // Point A (Joueur)
        arreteJoueur->B = ressources[i]->position; // Point B (Ressource)
        // Distance : |(Xb-Xa)+(Yb-Ya)|
        arreteJoueur->D = abs((arreteJoueur->B[X]-arreteJoueur->A[X])+(arreteJoueur->B[Y]-arreteJoueur->A[Y]));
        trier(tabArretes, nbArretes, arreteJoueur);
        // Ajout de l'arrete avec le point d'arrivee
        Arrete* arreteArrivee = malloc(sizeof(Arrete));
        arreteArrivee->A = joueur->arrivee; // Point A (Joueur)
        arreteArrivee->B = ressources[i]->position; // Point B (Ressource)
        // Distance : |(Xb-Xa)+(Yb-Ya)|
        arreteArrivee->D = abs((arreteArrivee->B[X]-arreteArrivee->A[X])+(arreteArrivee->B[Y]-arreteArrivee->A[Y]));
        trier(tabArretes, nbArretes, arreteArrivee);
    }
    // Ajout des arretes entre ressoruces
    for(i = 0, i < nbRessources, i++){
        // On cherche la table en partant de i+1 pour parcourir
        // les autres ressources non parcourues precedemment
        for(j = i+1, j < nbRessources, j++){
            Arrete* arreteRessource = malloc(sizeof(Arrete));
            arreteRessource->A = ressources[i]->position; // Point A (Ressource i)
            arreteRessource->B = ressources[j]->position; // Point B (Ressource j)
            // Distance : |(Xb-Xa)+(Yb-Ya)|
            arreteRessource->D = abs((arreteRessource->B[X]-arreteRessource->A[X])+(arreteRessource->B[Y]-arreteRessource->A[Y]));
            trier(tabArretes, nbArretes, arreteRessource);
        }
    }
    // Tableau final avec les arretes selectionnees
    Arrete* (*chemin);
    chemin = malloc((nbRessources+1) * sizeof(*Arrete));
    // Enfin, on parcours le tableau pour definir le chemin le plus cours
    for(i = 0 ; i < nbArretes ; i++){

    }
};

char jouer(); // Un tour (pour le mode deux joueurs)

void algorithme() {
    Ressource* objectif;
    Joueur* player;
    int depy = objectif->position[Y] - player->position[Y];
    int depx = objectif->position[X] - player->position[X];
    int dep = abs(depx) + abs(depy);
}
