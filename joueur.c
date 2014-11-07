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

struct joueur{ // Accès à "map" pour accéder aux cases sans garder le truc en fond
short depart[2];
short arrivee[2];
string image;
short position[2] ;
ressource*[] score;
//int[nombreTypeRessource] score; // 0-banane, 1-fraise, 2-orange, etc... #define fraise 0 // #define ptsFraise 1 (ou 5) ?
/*
// "Constructeur" !
Voir exempleConstructeur.txt
*/
char jouer(); // Un tour
deplacement();
joueur newJoueur();
}joueur;

struct Joueur *nouveauJoueur (size_t sz) {
    // Try to allocate vector structure.

    struct Vector *retVal = malloc (sizeof (struct Vector));
    if (retval == NULL)
        return NULL;

    // Try to allocate vector data, free structure if fail.

    retVal->data = malloc (sz * sizeof (double));
    if (retVal->data == NULL) {
        free (retVal);
        return NULL;
    }

    // Set size and return.

    retVal->size = sz;
    return retVal;
}

void delVector (struct Vector *vector) {
    // Can safely assume vector is NULL or fully built.

    if (vector != NULL) {
        free (vector->data);
        free (vector);
    }
}

