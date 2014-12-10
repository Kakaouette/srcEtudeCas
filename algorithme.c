#include "algorithme.h"

#define X 0
#define Y 1
#define directionExiste ((directions[0]==direction)||(directions[1]==direction)||(directions[2]==direction))

void reallocChemin(char*** chemin, int actuel){
    char** cheminBis = (char**)malloc(sizeof(char*)*actuel);
    int i;
    for(i = 0 ; i < actuel ; i++){
        cheminBis[i] = (char*)calloc(3, sizeof(char));
        cheminBis[i][0] = (*chemin)[i][0];
        cheminBis[i][1] = (*chemin)[i][1];
        cheminBis[i][2] = (*chemin)[i][2];
        free((*chemin)[i]);
    }
    free(*chemin);
    (*chemin) = (char**)malloc(sizeof(char*)*(actuel+1));
    for(i = 0 ; i < actuel ; i++){
        (*chemin)[i] = (char*)calloc(3, sizeof(char));
        (*chemin)[i][0] = cheminBis[i][0];
        (*chemin)[i][1] = cheminBis[i][1];
        (*chemin)[i][2] = cheminBis[i][2];
        free(cheminBis[i]);
    }
    free(cheminBis);
}

void remplirChemin(char posX, char posY, char* cheminActuel, char direction){
    cheminActuel[0] = posX;
    cheminActuel[1] = posY;
    cheminActuel[2] = direction;
}

char testChemin(char position[2], const Case*** carte, char nbCases[2],
                int actuel, char** chemin, char direction){
    int i;
    // Test la case cible
    if(testDeplacement(carte, nbCases, position, direction)){
        // Test que la case n'est pas déjà présente dans le chemin
        for(i = 0 ; i < actuel ; i++){
            if((position[X] == chemin[i][X]) && (position[Y] == chemin[i][Y])){
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

void calculChemin(char A[2], char B[2], const Case*** carte, char nbCases[2],
                  int actuel, int *meilleur, char*** chemin, char** meilleurChemin){
    // Limitation de l execution si on ne trouve pas de chemin plus court on abandonne
    if( (actuel >= (*meilleur)) && ((*meilleur) != 0) ){
        return;
    }
    // Rendu a l objectif on remplace les valeurs de meilleur distance et chemin
    if( (A[X] == B[X]) && (A[Y] == B[Y]) ){
        *meilleur = actuel;
        int i;
        free(*meilleurChemin);
        *meilleurChemin = (char*)malloc(sizeof(char)*(*meilleur));
        for(i = 0 ; i < (*meilleur) ; i++){
            (*meilleurChemin)[i] = (*chemin)[i][2];
        }
        if(actuel>0){
            (*chemin)[actuel-1][2] = 'X';
        }
        return;
    }
    /// chemin[]{X,Y,Sens}
    /// meilleurChemin{Sens}
    reallocChemin(chemin, actuel);
    //(*chemin) = realloc((*chemin), sizeof(char*)*(actuel+1));
    (*chemin)[actuel] = (char*)calloc(3, sizeof(char)); // {posX,posY,direction}
    (*chemin)[actuel][2] = 'X';
    char directions[3] = {'X', 'X', 'X'};
    /// essaie d'aller vers case X suivante.
    if(actuel>0){
        directions[2] = (*chemin)[actuel-1][2];
    }
    if(A[X]<B[X] && directions[2]!='G'){
        directions[0] = 'D';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testChemin(A, carte, nbCases, actuel, (*chemin), directions[0])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[0]);
            char Abis[2] = {A[X]+1,A[Y]};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    } else if (A[X]>B[X] && directions[2]!='D'){
        directions[0] = 'G';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testChemin(A, carte, nbCases, actuel, (*chemin), directions[0])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[0]);
            char Abis[2] = {A[X]-1,A[Y]};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    }
    /// essaie d'aller vers case Y suivante.
    if(A[Y]>B[Y] && directions[2]!='B'){
        directions[1] = 'H';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testChemin(A, carte, nbCases, actuel, (*chemin), directions[1])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[1]);
            char Abis[2] = {A[X],A[Y]-1};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    } else if (A[Y]<B[Y] && directions[2]!='H'){
        directions[1] = 'B';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testChemin(A, carte, nbCases, actuel, (*chemin), directions[1])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[1]);
            char Abis[2] = {A[X],A[Y]+1};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    }
    if((*chemin)[actuel][2] == 'X'){
        char direction = 'G';
        if(!directionExiste && testChemin(A, carte, nbCases, actuel, (*chemin), direction)){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
            char Abis[2] = {A[X]-1,A[Y]};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
        direction = 'D';
        if(!directionExiste && testChemin(A, carte, nbCases, actuel, (*chemin), direction)){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
            char Abis[2] = {A[X]+1,A[Y]};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
        direction = 'B';
        if(!directionExiste && testChemin(A, carte, nbCases, actuel, (*chemin), direction)){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
            char Abis[2] = {A[X],A[Y]+1};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
        direction = 'H';
        if(!directionExiste && testChemin(A, carte, nbCases, actuel, (*chemin), direction)){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
            char Abis[2] = {A[X],A[Y]-1};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    }
    // Aucune direction n'a offert de solution : on remplace la valeur precedente
    // du tableau pour que le chemin reste "invalide"
    // On verifie en plus qu'il ne s'agit pas du point de depart (Si c'est le cas il y a un probleme)
    if((*chemin)[actuel][2]=='X' && actuel>0){
        (*chemin)[actuel-1][2] = 'X';
    }
    free((*chemin)[actuel]);
    return;
}

/**
    Ajoute l'arrete donnee au tableau, a la position
    correspondante pour garder un tableau ordonne selon
    la distance des arretes.
*/
Arrete** trierArretes(Arrete **tab, int nbArretes, Arrete *aRanger){
    ///memset();
    short i, j;
    for(i = 0 ; i < nbArretes ; i++){
        if(tab[i]==0){
            tab[i] = aRanger;
            break;
        }
        if((tab[i]->D)>(aRanger->D)){
            for(j = i; j < nbArretes ; j++){
                if(tab[j]==0){
                    tab[j] = aRanger;
                    break;
                }
                Arrete* temp = tab[j];
                tab[j] = aRanger;
                aRanger = temp;
            }
            break;
        }
    }
    return tab;
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

/**
    Inverse le contenu du chemin (Ordre et direction)
*/
char* inverserChemin(char* chemin, char taille){
    char* nouveauChemin = (char*)calloc(taille, sizeof(char));
    int i;
    for(i = 0 ; i < taille ; i++){
        switch(chemin[taille-1-i]){
            case 'B' :
                nouveauChemin[i] = 'H';break;
            case 'H' :
                nouveauChemin[i] = 'B';break;
            case 'D' :
                nouveauChemin[i] = 'G';break;
            case 'G' :
                nouveauChemin[i] = 'D';break;
        }
    }
    free(chemin);
    return nouveauChemin;
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

    arrete->C = inverserChemin(arrete->C, arrete->D);

    return arrete;
}

/**
    Tri le tableau du chemin pour mettre dans l'ordre depuis l'arrete
    avec la position du joueur a l'arrete avec l'arrivee.
*/
Arrete** trierChemin(Arrete** tab, int nbArretes){
    int i, j, k;
    char rappel = 0;
    // boucle pour trouver l'arrete suivante, la placer a la suite
    // et continuer jusqu'a avoir range l'arbre.
    for(i = 1 ; i < nbArretes ; i++){
        for(j = i ; j < nbArretes ; j++){
            if(comparerArrete(tab[i-1], tab[j])=='I'){
                inverserPoints(tab[j]); // Inversion pour que le chemin soit toujours A -> B
            }
            if(comparerArrete(tab[i-1], tab[j])=='O'){
                Arrete* arreteTemp = tab[i];
                tab[i] = tab[j];
                tab[j] = arreteTemp;
            }
        }
    }
    return tab;
}

/**
    Algorithme de resolution du chemin le plus court.
    Algorithme base sur la Theorie des Graphes.
    Retourne un tableau d'Arretes ordonnees, correspondant au chemin
    a effectuer.
*/
Arrete** algorithmeChemin(Joueur *joueur, Ressource **ressources, int nbRessources, const Case*** carte, char nbCases[2]){
    // Pas de ressources : on va directement au point d'arrivee.
    if(nbRessources == 0){
        // Tableau final avec les arretes a retourner
        Arrete **cheminSimple;
        cheminSimple = malloc(sizeof(Arrete*));
        cheminSimple[0] = newArrete(joueur->position, joueur->arrivee, carte, nbCases);
        return cheminSimple;
    }

    int i, j;
    // Nombre total d'arretes possibles.
    //int nbArretes = (nbRessources * (nbRessources-1))/2 + nbRessources*2;
    int nbArretes = (nbRessources * (nbRessources+3))/2;
    // Allocation tableau avec toutes les arretes possibles
    Arrete **tabArretes;
    tabArretes = (Arrete**)calloc(nbArretes, sizeof(Arrete*));
    for(i = 0 ; i < nbArretes ; i++){
        tabArretes[i] = 0;
    }
    // Tableau de long contenant la position X et Y d'un point et le flag associe
    // Par octet de poids fort a faible : rien-flag-posY-posX
    EtatPosition** etatPositions = (EtatPosition**)malloc((nbRessources+2) * sizeof(EtatPosition*));
    etatPositions[0] = newPosition(joueur->position, 1);
    etatPositions[1] = newPosition(joueur->arrivee, 1);

    // Ajout des arretes liées au joueur et au point d'arrivee
    for(i = 0 ; i < nbRessources ; i++){
        // Ajout de l'arrete avec le joueur
        Arrete* arreteJoueur = newArrete(joueur->position, ressources[i]->position, carte, nbCases);
        trierArretes(tabArretes, nbArretes, arreteJoueur);
        // Ajout de l'arrete avec le point d'arrivee
        Arrete* arreteArrivee = newArrete(ressources[i]->position, joueur->arrivee, carte, nbCases);
        trierArretes(tabArretes, nbArretes, arreteArrivee);
    }

    // Ajout des arretes entre ressources
    for(i = 0 ; i < nbRessources ; i++){
        etatPositions[i+2] = newPosition(ressources[i]->position, 0);
        // On cherche la table en partant de i+1 pour parcourir
        // les autres ressources non parcourues precedemment
        for(j = i+1 ; j < nbRessources ; j++){
            Arrete* arreteRessource = newArrete(ressources[i]->position, ressources[j]->position, carte, nbCases);
            trierArretes(tabArretes, nbArretes, arreteRessource);
        }
    }

    Arrete** chemin = cheminPlusCourt(tabArretes, etatPositions, nbArretes, nbRessources);

    // Boucle pour retrouver le point de depart et le placer au debut.
    for(i = 0 ; i < nbRessources+1 ; i++){
        if( (chemin[i]->A[0] == joueur->position[0]) &&
            (chemin[i]->A[1] == joueur->position[1]) ){
            Arrete* arreteTemp;
            arreteTemp = chemin[0];
            chemin[0] = chemin[i];
            chemin[i] = arreteTemp;
            break;
        }
    }

    // Tri du reste du chemin.

    chemin = trierChemin(chemin, nbRessources+1);

    chemin = copieChemin(chemin, nbRessources+1);
    ///!!! Free des elements avant ou juste free du tableau direct ?
    for(i = 0 ; i < nbArretes ; i++){
        free(tabArretes[i]);
    }
    free(tabArretes);
    for(i = 0 ; i < nbRessources+2 ; i++){
        free(etatPositions[i]);
    }
    free(etatPositions);
    //free(chemin);
    return chemin;
}

/**
    Retourne 1 s'il existe une boucle entre le point d'index j et le point d'index k
    dans le chemin actuel.
*/
char boucle(EtatPosition** etatPositions, int nbPositions, int j, int k, Arrete** chemin, int nb){
    int i;
    for(i = 0 ; i < nb ; i++){
        if( (evaluerPosition(chemin[i]->A, etatPositions[j]) != 'N') && // Arrete A -> B
            (getEtatPosition(chemin[i]->B, etatPositions, nbPositions)->flagVerif == 0) ){ // point cible qui n'a pas deja ete vu (eviter de boucler sur la meme arrete
            if( evaluerPosition(chemin[i]->B, etatPositions[k]) != 'N'){ // On retrouve k sur le point cible, c'est une boucle.
               return 1;
            } else { // Sinon on regarde le point suivant
                etatPositions[j]->flagVerif = 1;
                return boucle(etatPositions, nbPositions, indexEtat(chemin[i]->B, etatPositions, nbPositions), k, chemin, nb);
            }
        }
        if( (evaluerPosition(chemin[i]->B, etatPositions[j]) != 'N') && // Arrete B -> A
            (getEtatPosition(chemin[i]->A, etatPositions, nbPositions)->flagVerif == 0) ){ // point qui n'a pas deja ete vu
            if( evaluerPosition(chemin[i]->A, etatPositions[k]) != 'N' ){ // On retrouve k sur le point cible, c'est une boucle.
               return 1;
            } else { // Sinon on regarde le point suivant
                etatPositions[j]->flagVerif = 1;
                return boucle(etatPositions, nbPositions, indexEtat(chemin[i]->A, etatPositions, nbPositions), k, chemin, nb);
            }
        }
    }
    return 0;
}

/**
    Retourne 1 s'il existe un chemin entre le point actuel et l'extremite donnee
*/
char chaine(EtatPosition* posExtremite, EtatPosition* posActuel, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int nb){
    if( comparerEtats(posActuel, posExtremite) ){ // Si on est rendu au point cible il y a une chaine
        return 1;
    }
    int i;
    for(i = 0 ; i < nb ; i++){
        if( (evaluerPosition(chemin[i]->A, posActuel) != 'N') &&
            (getEtatPosition(chemin[i]->B, etatPositions, nbPositions)->flagVerif == 0) ){ // Arrete A -> B
            posActuel->flagVerif = 1;
            return chaine(posExtremite, getEtatPosition(chemin[i]->B, etatPositions, nbPositions), etatPositions, chemin, nbPositions, nb);
        }
        if( (evaluerPosition(chemin[i]->B, posActuel) != 'N') &&
            (getEtatPosition(chemin[i]->A, etatPositions, nbPositions)->flagVerif == 0) ){ // Arrete B -> A
            posActuel->flagVerif = 1;
            return chaine(posExtremite, getEtatPosition(chemin[i]->A, etatPositions, nbPositions), etatPositions, chemin, nbPositions, nb);
        }
    }
    // Aucune arrete trouvee. Pas de chaine.
    return 0;
}

char estBoucle(EtatPosition** etatPositions, int nbPositions, int j, int k, Arrete** chemin, int nb){
    char ret = boucle(etatPositions,nbPositions,j,k,chemin,nb);
    resetFlag(etatPositions, nbPositions);
    return ret;
}

char estChaine(EtatPosition* posExtremite, EtatPosition* posActuel, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int nb){
    char ret = chaine(posExtremite, posActuel, etatPositions, chemin, nbPositions, nb);
    resetFlag(etatPositions, nbPositions);
    return ret;
}

/**
    Retourne 1 si l'arrete entre le point a l'index j et le point a l'index k est valide
    => Verifie que l'arrete n'implique pas de boucle ou de fermeture du chemin
*/
char arreteValide(EtatPosition** etatPositions, int nbPositions, int j, int k, Arrete** chemin, int nb){
    int i;
    if(j > 1 && k > 1) { // j et k sont des index de ressources on verifie les boucles
        for(i = 2 ; i < nbPositions ; i++){
            if(i != j && k != i){ // On analyse l'etat des autres ressources (le cas j<2 && k<2 est impossible)
                if((etatPositions[i]->flagAvance) < 2){ // S'il existe au moins une ressource libre
                    if( ( estChaine(etatPositions[0], etatPositions[j], etatPositions, chemin, nbPositions, nb) ||
                          estChaine(etatPositions[1], etatPositions[j], etatPositions, chemin, nbPositions, nb) )
                        && // Fermeture du chemin (chaque point de l'arrete fait une chaine jsuqu'à l'extemite
                        ( estChaine(etatPositions[0], etatPositions[k], etatPositions, chemin, nbPositions, nb) ||
                          estChaine(etatPositions[1], etatPositions[k], etatPositions, chemin, nbPositions, nb) ) ) {
                        return 0;
                    }  else {
                        return !estBoucle(etatPositions,nbPositions,j,k,chemin,nb);
                    }
                }
            }
        }
        return !estBoucle(etatPositions,nbPositions,j,k,chemin,nb);
    } else { // Au moins un des points est une extremite
        for(i = 2 ; i < nbPositions ; i++){
            if(i != j && k != i){ // On analyse l'etat des autres ressources (le cas j<2 && k<2 est impossible)
                if((etatPositions[i]->flagAvance) < 2){ // S'il existe au moins une ressource libre
                    if(j < 2) { // Si j est extremite on regarde que notre ressource (k) ne ferme pas le chemin
                        return !estChaine(etatPositions[!j], etatPositions[k], etatPositions, chemin, nbPositions, nb);
                    }
                    else { // Sinon on regarde que j ne ferme pas le chemin
                        return !estChaine(etatPositions[!k], etatPositions[j], etatPositions, chemin, nbPositions, nb);
                    }
                }
            }
        }
    }
    return 1;
}

Arrete** cheminPlusCourt(Arrete** tabArretes, EtatPosition** etatPositions, int nbArretes, int nbRessources){
    Arrete** chemin = (Arrete**)malloc(sizeof(Arrete*)*nbRessources+1);
    int i, j, k, nb =0;
    for(i = 0 ; i < nbArretes ; i++){ // Parcours  des arretes
        for(j=0; j < nbRessources+2;j++){ // Parcours des etats pour le point A
            if( ((tabArretes[i]->A[0]) == (etatPositions[j]->posX)) &&
                ((tabArretes[i]->A[1]) == (etatPositions[j]->posY)) ){
                for(k=0; k < nbRessources+2;k++){ // Parcours des etats pour le point B
                    if( ((tabArretes[i]->B[0]) == (etatPositions[k]->posX)) &&
                        ((tabArretes[i]->B[1]) == (etatPositions[k]->posY)) ){
                        if( ((etatPositions[j]->flagAvance) < 2) && ((etatPositions[k]->flagAvance) < 2)
                           && (arreteValide(etatPositions,nbRessources+2,j,k,chemin,nb)) ){
                            chemin[nb] = tabArretes[i];nb++;
                            etatPositions[j]->flagAvance++;
                            etatPositions[k]->flagAvance++;
                            break;
                       }
                    }
                }
                break;
            }
        }
        if(nb > nbRessources)
            break;
    }
    return chemin;
}

Arrete* copieArrete(Arrete* arrete){
    Arrete* arreteRetour = (Arrete*)malloc(sizeof(Arrete));
    arreteRetour->A[0] = arrete->A[0];
    arreteRetour->A[1] = arrete->A[1];
    arreteRetour->B[0] = arrete->B[0];
    arreteRetour->B[1] = arrete->B[1];
    arreteRetour->D = arrete->D;
    arreteRetour->C = (char*)malloc(sizeof(char)*(arreteRetour->D));
    int i;
    for(i = 0 ; i < arrete->D ; i++){
        arreteRetour->C[i] = arrete->C[i];
    }
    return arreteRetour;
}

Arrete** copieChemin(Arrete** chemin, int size){
    Arrete** cheminRetour = (Arrete**)malloc(sizeof(Arrete*)*size);
    int i, j;
    for(i = 0 ; i < size ; i++){
        cheminRetour[i] = copieArrete(chemin[i]);
    }
    return cheminRetour;
}
