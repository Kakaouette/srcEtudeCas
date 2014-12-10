#include "arrete.h"

#define X 0
#define Y 1

/**
    Retourne un pointeur d'arrete avec les points A, B et
    la distance calculee entre les deux points.
*/
Arrete* newArrete(char A[2], char B[2], const Case*** carte, char nbCases[2]){
    Arrete *arrete = malloc(sizeof(Arrete));
    arrete->A[X] = A[X];
    arrete->A[Y] = A[Y];
    arrete->B[X] = B[X];
    arrete->B[Y] = B[Y];
    int meilleur = 0;
    char*** chemin = (char***)malloc(sizeof(char**));
    *chemin = (char**)malloc(sizeof(char*)*0);
    char** meilleurChemin = (char**)malloc(sizeof(char*));
    calculChemin(A, B, carte, nbCases, 0, &meilleur, chemin, meilleurChemin);
    int i;
    arrete->C = (char*)malloc(sizeof(char)*meilleur);
    for(i = 0 ; i < meilleur ; i++){
        (arrete->C)[i] = (*meilleurChemin)[i];
    }
    free(*chemin);
    free(chemin);
    free(*meilleurChemin);
    free(meilleurChemin);
    arrete->D = meilleur;
    /// Ajouter C pour chemin et appeler fonction definissant chemin plus court quand contrainte
    ///arrete->C = calculChemin(A,B);
    return arrete;
}
