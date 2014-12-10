#include "etatPosition.h"

/**
    Cree une position avec les octets : 0x0FYX
    avec X = position en X
         Y = position en Y
         F = Flag
    Flag = 0 si la position n'a jamais ete visitee
    Flag = 1 si la position a ete visitee une fois
    Flag = 2 si la position n'est plus disponible (venu et parti)
    On met à 1 s'il s'agit du depart ou de l'arrivee
    puisqu'on ne veut passer qu'une fois par ces points.
*/
EtatPosition* newPosition(char coordonnee[2], char JoueurOuArrivee){
    EtatPosition* position = (EtatPosition*)malloc(sizeof(EtatPosition));
    if(JoueurOuArrivee){
        position->flagAvance = 1;
    } else {
        position->flagAvance = 0;
    }
    position->posX = coordonnee[0];
    position->posY = coordonnee[1];
    position->flagVerif = 0;
    return position;
}

/**
    Evalue une position en comparaison avec un etat pour definir s'il s'agit
    de l'etat correspondant a cette position.
    Retourne 0 si correspondance et flagAvance a 0.
    Retourne 1 si correspondance et flagAvance a 1.
    Retourne 2 si correspondance et flagAvance a 2.
    Retourne N si non correspondance.
    Retourne E si flagAvance invalide.
*/
char evaluerPosition(char coordonnee[2], EtatPosition* etatPosition){
    if((coordonnee[0] == etatPosition->posX) &&
       (coordonnee[1] == etatPosition->posY)){
        if(etatPosition->flagAvance == 0){
            return '0';
        } else if (etatPosition->flagAvance == 1){
            return '1';
        } else if (etatPosition->flagAvance == 2){
            return '2';
        } else {
            return 'E';
        }
    } else {
        return 'N';
    }
}

char indexEtat(char position[2], EtatPosition** tabEtats, int nbPositions){
    int i;
    for(i = 0 ; i < nbPositions ; i++){
        if( evaluerPosition(position, tabEtats[i]) != 'N'){
            return i;
        }
    }
    return -1;
}

EtatPosition* getEtatPosition(char position[2], EtatPosition** tabEtats, int nbPositions){
    int i;
    for(i = 0 ; i < nbPositions ; i++){
        if(position[0]==tabEtats[i]->posX && position[1]==tabEtats[i]->posY){
            return tabEtats[i];
        }
    }
    return NULL;
}

char comparerEtats(EtatPosition* etatA, EtatPosition* etatB){
    if( (etatA->posX == etatB->posX) && (etatA->posY == etatB->posY) ){
        return 1;
    } else {
        return 0;
    }
}

void resetFlag(EtatPosition** tabEtats, int nbPositions){
    int i;
    for(i = 0 ; i < nbPositions ; i++){
        tabEtats[i]->flagVerif = 0;
    }
}
