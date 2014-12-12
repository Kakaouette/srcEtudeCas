#include "arrete.h"

#define X 0
#define Y 1

/**
 * \fn Arrete* newArrete(char A[2], char B[2], const Case*** carte, char nbCases[2])
 * \brief Fonction de cr�ation d'une Arrete. Alloue la m�moire et calcul le meilleur
 * \brief chemin possible entre le point A et le point B.
 *
 * \param A Point A, d�part.
 * \param B Point B, arriv�e.
 * \param carte Ensemble des cases de la carte (n�cessaire pour le calcul du chemin).
 * \param nbCases Nombre de cases en X et en Y.
 * \return Retourne un pointeur sur l'Arrete cr��e.
 */
Arrete* newArrete(char A[2], char B[2], const Case*** carte, char nbCases[2]){
    // Cr�ation de l'Arrete.
    Arrete *arrete = malloc(sizeof(Arrete));
    // Initialisation de A.
    arrete->A[X] = A[X];
    arrete->A[Y] = A[Y];
    // Initialisation de B.
    arrete->B[X] = B[X];
    arrete->B[Y] = B[Y];

    int meilleur = 0;
    // ALLOC : Allocation temporaire pour le meilleur chemin.
        char** meilleurChemin = (char**)malloc(sizeof(char*));
    // ALLOC : Allocation temporaire pour le calcul du chemin.
        char*** chemin = (char***)malloc(sizeof(char**));
        *chemin = (char**)malloc(sizeof(char*)*0);
    // Calcul du chemin.
    calculChemin(A, B, carte, nbCases, 0, &meilleur, chemin, meilleurChemin);
    // FREE : lib�ration m�moire de l'allocation pour le calcul du chemin.
        free(*chemin);
        free(chemin);
    // Initialisation du chemin.
    arrete->C = (char*)malloc(sizeof(char)*meilleur);
    int i;
    for(i = 0 ; i < meilleur ; i++){
        (arrete->C)[i] = (*meilleurChemin)[i];
    }
    // FREE : lib�ration m�moire de l'allocation pour le meilleur chemin.
        free(*meilleurChemin);
        free(meilleurChemin);
    // Initialisation de D.
    arrete->D = meilleur;

    return arrete;
}
