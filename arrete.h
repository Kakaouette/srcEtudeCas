#ifndef ARRETE_H
#define ARRETE_H

#include "Case.h"

/**
 * \struct Arrete
 * \brief Objet repr�sentant un arc entre un point A et un point B.
 * \brief Contient les coordonn�es de A et B, le chemin C et la distance totale D.
 *
 */
typedef struct Arrete{
    char A[2];
    char B[2];
    char* C; // Chaine de caract�re contenant les directions du chemin (H,B,G,D respectivement Haut, Bas, Gauche, Droite).
    char D;
}Arrete;

Arrete* newArrete(char A[2], char B[2], const Case*** carte, char nbCases[2]);

#endif // ARRETE_H
