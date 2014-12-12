#include "etatPosition.h"

/**
 * \fn EtatPosition* newPosition(char coordonnee[2], char JoueurOuArrivee)
 * \brief Fonction de création d'un EtatPosition.
 *
 * \param coordonnee Coordonnées de la position.
 * \param flag Etat du flag à l'initialisation.
 * \return Retourne un pointeur sur l'EtatPosition créé.
 */
EtatPosition* newPosition(char coordonnee[2], char flag){
    EtatPosition* position = (EtatPosition*)malloc(sizeof(EtatPosition));
    position->posX = coordonnee[0];
    position->posY = coordonnee[1];
    position->flagAvance = flag;
    position->flagVerif = 0;
    return position;
}

/**
 * \fn char evaluerPosition(char coordonnee[2], EtatPosition* etatPosition)
 * \brief Fonction d'évaluation d'un EtatPosition
 *
 * \param coordonnee Coordonnées de la position.
 * \param etatPosition Etat à évaluer.
 * \return Retourne la valeur du flag si la position correspond, sinon retourne N. Retourne E si flag invalide.
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

/**
 * \fn char indexEtat(char position[2], EtatPosition** tabEtats, int nbPositions)
 * \brief Fonction de recherche de l'index d'une position.
 *
 * \param position Coordonnées de la position.
 * \param tabEtats Liste des EtatPosition.
 * \param nbPositions Nombre d'EtatPosition.
 * \return Retourne l'index de la position dans le tableau, sinon -1.
 */
char indexEtat(char position[2], EtatPosition** tabEtats, int nbPositions){
    int i;
    for(i = 0 ; i < nbPositions ; i++){
        if( evaluerPosition(position, tabEtats[i]) != 'N'){
            return i;
        }
    }
    return -1;
}

/**
 * \fn EtatPosition* getEtatPosition(char position[2], EtatPosition** tabEtats, int nbPositions)
 * \brief Fonction de recherche de l'EtatPosition correspondant à une position.
 *
 * \param position Coordonnées de la position.
 * \param tabEtats Liste des EtatPosition.
 * \param nbPositions Nombre d'EtatPosition.
 * \return Retourne un pointeur sur l'EtatPosition correspondant, sinon NULL.
 */
EtatPosition* getEtatPosition(char position[2], EtatPosition** tabEtats, int nbPositions){
    int i;
    for(i = 0 ; i < nbPositions ; i++){
        if(position[0]==tabEtats[i]->posX && position[1]==tabEtats[i]->posY){
            return tabEtats[i];
        }
    }
    return NULL;
}

/**
 * \fn char comparerEtats(EtatPosition* etatA, EtatPosition* etatB)
 * \brief Fonction de comparaison des coordonnées de deux EtatPosition.
 *
 * \param etatA EtatPosition A.
 * \param etatB EtatPosition B.
 * \return Retourne 1 s'ils ont la même position, sinon 0.
 */
char comparerEtats(EtatPosition* etatA, EtatPosition* etatB){
    if( (etatA->posX == etatB->posX) && (etatA->posY == etatB->posY) ){
        return 1;
    } else {
        return 0;
    }
}

/**
 * \fn void resetFlag(EtatPosition** tabEtats, int nbPositions)
 * \brief Fonction de remise à zéro des flagVerif dans une liste d'EtatPosition
 *
 * \param tabEtats Liste des EtatPosition.
 * \param nbPositions Nombre d'EtatPosition.
 */
void resetFlag(EtatPosition** tabEtats, int nbPositions){
    int i;
    for(i = 0 ; i < nbPositions ; i++){
        tabEtats[i]->flagVerif = 0;
    }
}
