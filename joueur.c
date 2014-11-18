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

long newPosition(char coordonnee[2]){
    long position = coordonnee[X] + (coordonnee[Y] << 8);
    return position;
}

Arrete** trierArretes(Arrete* (*tab), int nbArretes, Arrete *aRanger){
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
    return tab;
}

Arrete** trierChemin(Arrete* (*tab), int nbArretes){
    int i, j, k;
    Arrete* arreteTemp = malloc(sizeof(Arrete));
    // boucle pour trouver l'arrete suivante, la placer a la suite
    // et continuer jusqu'a avoir range l'arbre.
    for(i = 1 ; i < nbArretes ; i++){
        for(j = i ; j < nbArretes ; j++){
            if(comparerArrete(tab[i-1], tab[j])=='O'){
                if(comparerArrete(tab[i-1], tab[j])=='I'){
                    inverserPoints(tab[j]); // Inversion pour que le chemin soit toujours A -> B
                }
                for(k = j ; k > i ; k--){
                    arreteTemp = tab[k-1];
                    tab[k-1] = tab[k];
                    tab[k] = arreteTemp;
                }
            }
        }
    }
    free(arreteTemp);
    return tab;
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
Arrete** algorithmeSansContrainte(Joueur *joueur, Ressource* (*ressources), int nbRessources){
    // Tableau final avec les arretes a retourner
    Arrete* (*chemin);
    chemin = malloc((nbRessources+1) * sizeof(Arrete*));
    // Pas de ressources : on va directement au point d'arrivee.
    if(nbRessources == 0){
        Arrete* arreteSimple = malloc(sizeof(Arrete));
        chemin[0] = arreteSimple;
        return chemin;
    }

    int i, j, A, B, avance;
    // Nombre total d'arretes possibles.
    int nbArretes = (nbRessources * (nbRessources-1))/2 + nbRessources*2;
    // Allocation tableau avec toutes les arretes possibles
    Arrete* (*tabArretes);
    tabArretes = malloc(nbArretes * sizeof(Arrete*));
    // Tableau de long contenant la position X et Y d'un point et le flag associe
    // Par octet de poids fort a faible : rien-flag-posY-posX
    long* etatPosition;
    etatPosition = malloc((nbRessources+2) * sizeof(long));
    etatPosition[0] = newPosition(joueur->position);
    etatPosition[1] = newPosition(joueur->arrivee);

    // Ajout des arretes liées au joueur et au point d'arrivee
    for(i = 0 ; i < nbRessources ; i++){
        // Ajout de l'arrete avec le joueur
        Arrete* arreteJoueur = newArrete(joueur->position, ressources[i]->position, c);
        trierArretes(tabArretes, nbArretes, arreteJoueur);
        // Ajout de l'arrete avec le point d'arrivee
        Arrete* arreteArrivee = newArrete(joueur->arrivee, ressources[i]->position, c);
        trierArretes(tabArretes, nbArretes, arreteArrivee);
    }

    // Ajout des arretes entre ressources
    for(i = 0 ; i < nbRessources ; i++){
        etatPosition[i+2] = ressources[i]->position[X] + (ressources[i]->position[Y] << 8);
        // On cherche la table en partant de i+1 pour parcourir
        // les autres ressources non parcourues precedemment
        for(j = i+1 ; j < nbRessources ; j++){
            Arrete* arreteRessource = newArrete(ressources[i], ressources[j]);
            trierArretes(tabArretes, nbArretes, arreteRessource);
        }
    }

    avance = 0;
    // Enfin, on parcours le tableau pour definir le chemin le plus cours
    for(i = 0 ; i < nbArretes ; i++){
        A = 0; B = 0;
        // On regarde chaque point pour regarder l'état du point
        // et éviter les boucles.
        for(j = 0 ; j < (nbRessources+2) ; j++){
            // On vérifie l'état du point A
            if((tabArretes[i]->A[X] == (etatPosition[j]&0xFF)) &&
               (tabArretes[i]->A[Y] == ((etatPosition[j]>>8)&0xFF))){
                if(((etatPosition[j]>>16)&0xFF)==0){
                    A = j;
                    if(B!=0){
                        break;
                    }
                } else if (((etatPosition[j]>>16)&0xFF)==1){
                    A = j + 0x0100;
                    if(B!=0){
                        break;
                    }
                } else {
                    A = j + 0x0200; break;
                }
            }
            // On vérifie l'état du point B
            if((tabArretes[i]->B[X] == (etatPosition[j]&0xFF)) &&
               (tabArretes[i]->B[Y] == ((etatPosition[j]>>8)&0xFF))){
                if(((etatPosition[j]>>16)&0xFF)==0){
                    B = j;
                    if(A!=0){
                        break;
                    }
                } else if (((etatPosition[j]>>16)&0xFF)==1){
                    B = j + 0x0100;
                    if(A!=0){
                        break;
                    }
                } else {
                    B = j + 0x0200; break;
                }
            }
        }
        if(((A&0xFF00)!=2) && ((B&0xFF00)!=2)){
            chemin[avance] = tabArretes[i];
            avance++;
            etatPosition[A&0xFF]+= 0x010000;
            etatPosition[B&0xFF]+= 0x010000;
        }
    }
    Arrete* arreteTemp = malloc(sizeof(Arrete));
    // Boucle pour retrouver le point de depart et le placer au debut.
    for(i = 0 ; i < nbArretes ; i++){
        if((chemin[i]->A[0] == joueur->position[0]) &&
           (chemin[i]->A[1] == joueur->position[1])){
            for(j = i ; j > 0 ; j--){
                arreteTemp = chemin[j-1];
                chemin[j-1] = chemin[j];
                chemin[j] = arreteTemp;
            }
            break;
        }
    }
    free(arreteTemp);
    trierChemin(chemin, nbRessources+1);
    ///!!! Free des elements avant ou juste free du tableau direct ?
    for(i = 0 ; i < nbArretes ; i++){
        free(tabArretes[i]);
    }
    free(tabArretes);
    free(etatPosition);
    return chemin;
};

char jouer(); // Un tour (pour le mode deux joueurs)

void algorithme() {
    Ressource* objectif;
    Joueur* player;
    int depy = objectif->position[Y] - player->position[Y];
    int depx = objectif->position[X] - player->position[X];
    int dep = abs(depx) + abs(depy);
}
