#include "arrete.h"

#define X 0
#define Y 1

/**
    Retourne un pointeur d'arrete avec les points A, B et
    la distance calculee entre les deux points.
*/
Arrete* newArrete(char A[2], char B[2]){
    Arrete *arrete = malloc(sizeof(Arrete));
    arrete->A[X] = A[X];
    arrete->A[Y] = A[Y];
    arrete->B[X] = B[X];
    arrete->B[Y] = B[Y];
    arrete->D = abs(B[X] - A[X]) + abs(B[Y] - A[Y]);
    /// Ajouter C pour hcemin et appeler fonction definissant chemin plus court quand contrainte
    return arrete;
}

/**
    Inverse les points A et B dans une arrete.
*/
Arrete* inverserPoints(Arrete* arrete){
    char temp;
    temp = arrete->A[0];
    arrete->A[0] = arrete->B[0];
    arrete->B[0] = temp;
    temp = arrete->A[1];
    arrete->A[1] = arrete->B[1];
    arrete->B[1] = temp;
    return arrete;
}
/**
    Compare le point B d'une premiere arrete avec les points A et B de la seconde.
    Retourne O pour Oui (1.B = 2.A), I pour Inverse (1.B = 2.B) et N pour Non.
*/
char comparerArrete(Arrete* premiere, Arrete* deuxieme){
    if(premiere->B[0]==deuxieme->A[0] &&
       premiere->B[1]==deuxieme->A[1] ){
        return 'O'; // O si
   } else if(premiere->B[0]==deuxieme->B[0] &&
             premiere->B[1]==deuxieme->B[1] ){
        return 'I';
   } else {
       return 'N';
   }
}
