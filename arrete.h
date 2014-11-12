#ifndef ARRETE_H
#define ARRETE_H

typedef struct Arrete Arrete;

/**
    Arrete : une arrete represente l'arc entre
    un point A et un point B. Une arrete est representee
    par les coordonnees du point A, du point B, et la distance
    relative entre les deux points et le parcours correspondant
    sous la forme d'une chaine de caractere.
*/
struct Arrete{
    char A[2]; // Coordonnees point A
    char B[2]; // Coordonnees point B
    char D; // Distance entre A et B //?= nb de case dans chemin parcouru?
    //string C; // Chemin, parcous à effectuer de A vers B (inverser la lecture pour B vers A).
};

#endif // ARRETE_H
