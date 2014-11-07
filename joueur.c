/*
long tab[20];
long arrete = 0x120A05;
trier(tab, arrete);
*/


long[] trier(long[] tab, long aRanger){
    memset();
    short i, j, temp;
    for(i = 0 ; i < tab.length ; i++){
        if(tab[i]==0){
            tab[i] = aRanger;
            break;
        }
        if((tab[i]&0xFF)<(aRanger&0xFF)){
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
    return tab;
}

void algorithmeSansContrainte(Joueur joueur, Ressource*[] ressources){

};

#define nombreTypeRessource 1
#define X 0
#define Y 1
#define positionX position[X]
#define positionY position[Y]
#define positionX(x) position[X] = x
#define positionY(y) position[Y] = y
#include <string.h>
#include <math.h>
struct Joueur{ // Acc�s � "map" pour acc�der aux cases sans garder le truc en fond
    int depart[2];
    int arrivee[2];
    std::string image;
    int position[2];
    Ressource* score[];
//int[nombreTypeRessource] score; // 0-banane, 1-fraise, 2-orange, etc... #define fraise 0 // #define ptsFraise 1 (ou 5) ?
/*
// "Constructeur" !
Voir exempleConstructeur.txt
*/
};
char jouer(); // Un tour (pour le mode deux joueurs)
int deplacement(Joueur* player, int x, int y) { //Une case
    int depx = x - player->position[X];
    int depy = y - player->position[Y];
    if (abs(depy) > abs(depx)) {
        if (depy != 0) {
            int sign = depy/abs(depy);
            Case* nextCase = jeu.map[player->position[X]][player->position[Y] + sign];
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
            int sign = depx/abs(depx);
            Case* nextCase = jeu.map[player->position[X] + sign][player->position[Y]];
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
Joueur* newJoueur() {

}
