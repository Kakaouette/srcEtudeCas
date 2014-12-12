#include "algorithme.h"

#define X 0
#define Y 1
#define directionExiste ((directions[0]==direction)||(directions[1]==direction)||(directions[2]==direction))

/**
 * \fn Arrete** algorithmeChemin(Joueur *joueur, Ressource **ressources, int nbRessources, const Case*** carte, char nbCases[2])
 * \brief Fonction principale de l'algorithme. Liste les Arrete existantes et cherche le chemin le plus court
 * \brief entre le joueur et l'arrivée, en passant par chacune des ressources.
 *
 * \param joueur Joueur pour lequel on calcule.
 * \param ressources Liste des ressources disponibles.
 * \param nbRessources Nombre de ressources.
 * \param carte Ensemble des cases.
 * \param nbCases Nombre de cases en X et Y.
 * \return Retourne le tableau du chemin ordonné.
 */
Arrete** algorithmeChemin(Joueur *joueur, Ressource **ressources, int nbRessources, const Case*** carte, char nbCases[2]){
    // Pas de ressources : on va directement au point d'arrivee.
    if(nbRessources == 0){
        // Création du chemin à retourner.
        Arrete **cheminSimple = malloc(sizeof(Arrete*));
        // Création de l'Arrete unique.
        cheminSimple[0] = newArrete(joueur->position, joueur->arrivee, carte, nbCases);
        return cheminSimple;
    }

    int i, j;
    // Nombre total d'Arrete à créer.
    int nbArretes = (nbRessources * (nbRessources+3))/2;
    // ALLOC : Tableau avec toutes les Arrete possibles.
        Arrete **tabArretes = (Arrete**)calloc(nbArretes, sizeof(Arrete*));
    // ALLOC : Liste des EtatPosition pour chaque point existant.
        EtatPosition** etatPositions = (EtatPosition**)malloc((nbRessources+2) * sizeof(EtatPosition*));
    // Les EtatPosition à l'index 0 et 1 correspondent respectivement à la position et l'arrivée du joueur.
    etatPositions[0] = newPosition(joueur->position, 1);
    etatPositions[1] = newPosition(joueur->arrivee, 1);

    // Ajout des arretes liées au joueur et au point d'arrivee.
    for(i = 0 ; i < nbRessources ; i++){
        // ALLOC : Arrete entre la position du joueur et la ressource.
            Arrete* arreteJoueur = newArrete(joueur->position, ressources[i]->position, carte, nbCases);
        // Ajout de l'Arrete le tableau, ordonné croissant par distance.
        tabArretes = trierArretes(tabArretes, nbArretes, arreteJoueur);
        // ALLOC : Arrete entre l'arrivée et la ressource.
            Arrete* arreteArrivee = newArrete(ressources[i]->position, joueur->arrivee, carte, nbCases);
        // Ajout de l'Arrete le tableau, ordonné croissant par distance.
        tabArretes = trierArretes(tabArretes, nbArretes, arreteArrivee);
    }

    // Ajout des arretes entre ressources.
    for(i = 0 ; i < nbRessources ; i++){
        // EtatPosition lié à cette ressource.
        etatPositions[i+2] = newPosition(ressources[i]->position, 0);
        // On cherche la table en partant de i+1 pour parcourir
        // les autres ressources non parcourues precedemment.
        for(j = i+1 ; j < nbRessources ; j++){
            // ALLOC : Arrete entre la position du joueur et la ressource.
                Arrete* arreteRessource = newArrete(ressources[i]->position, ressources[j]->position, carte, nbCases);
            // Ajout de l'Arrete le tableau, ordonné croissant par distance.
            tabArretes = trierArretes(tabArretes, nbArretes, arreteRessource);
        }
    }

    // Récupération de la combinaison d'Arrete correspondant le chemin le plus court.
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

    // Tri du reste du chemin pour mettre les Arrete dans l'ordre de parcours.
    chemin = ordonnerChemin(chemin, nbRessources+1);
    // ALLOC : Copie du chemin vers un nouvel espace mémoire
        chemin = copieChemin(chemin, nbRessources+1);
    // FREE : Libération mémoire des Arrete du tableau contenant toutes les Arrete.
        for(i = 0 ; i < nbArretes ; i++){
            free(tabArretes[i]);
        }
    // FREE : Libération mémoire du grand tableau d'Arrete.
        free(tabArretes);
    // FREE : Libération mémoire des EtatPosition
        for(i = 0 ; i < nbRessources+2 ; i++){
            free(etatPositions[i]);
        }
    // FREE : Libération du tableau d'EtatPosition
        free(etatPositions);

    return chemin;
}

/**
 * \fn void calculChemin(char A[2], char B[2], const Case*** carte, char nbCases[2], int actuel, int *meilleur, char*** chemin, char** meilleurChemin)
 * \brief Fonction de calcul du chemin valide le plus court d'un point A à un point B.
 *
 * \param A Position actuelle.
 * \param B Position cible.
 * \param carte Ensemble des cases.
 * \param nbCases Nombre de cases en X et Y.
 * \param actuel Avancée actuelle du chemin.
 * \param meilleur Distance la plus courte trouvée.
 * \param chemin Chemin actuel.
 * \param meilleurChemin Meilleur chemin trouvé.
 */
void calculChemin(char A[2], char B[2], const Case*** carte, char nbCases[2],
                  int actuel, int *meilleur, char*** chemin, char** meilleurChemin){
    // Limitation de l execution si on ne trouve pas de chemin plus court on abandonne
    if( (actuel >= (*meilleur)) && ((*meilleur) != 0) ){
        return;
    }
    // Rendu a l objectif on remplace les valeurs de meilleur distance et chemin
    if(comparePosition(A, B)){
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
    // chemin[]{X,Y,Sens}
    // meilleurChemin{Sens}
    reallocChemin(chemin, actuel);
    //(*chemin) = realloc((*chemin), sizeof(char*)*(actuel+1));
    (*chemin)[actuel] = (char*)calloc(3, sizeof(char)); // {posX,posY,direction}
    char directions[3] = {'X', 'X', 'X'};
    // essaie d'aller vers case X suivante.
    if(actuel>0){
        directions[2] = (*chemin)[actuel-1][2];
    }
    if(A[X]<B[X] && directions[2]!='G'){
        directions[0] = 'D';
        // Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testPosition(A, carte, nbCases, actuel, (*chemin), directions[0])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[0]);
            char Abis[2] = {A[X]+1,A[Y]};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    } else if (A[X]>B[X] && directions[2]!='D'){
        directions[0] = 'G';
        // Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testPosition(A, carte, nbCases, actuel, (*chemin), directions[0])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[0]);
            char Abis[2] = {A[X]-1,A[Y]};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    }
    // essaie d'aller vers case Y suivante.
    if(A[Y]>B[Y] && directions[2]!='B'){
        directions[1] = 'H';
        // Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testPosition(A, carte, nbCases, actuel, (*chemin), directions[1])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[1]);
            char Abis[2] = {A[X],A[Y]-1};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    } else if (A[Y]<B[Y] && directions[2]!='H'){
        directions[1] = 'B';
        // Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(testPosition(A, carte, nbCases, actuel, (*chemin), directions[1])){
            remplirChemin(A[X], A[Y], (*chemin)[actuel], directions[1]);
            char Abis[2] = {A[X],A[Y]+1};
            calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
        }
    }
    char direction = 'G';
    if(!directionExiste && testPosition(A, carte, nbCases, actuel, (*chemin), direction)){
        remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
        char Abis[2] = {A[X]-1,A[Y]};
        calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
    }
    direction = 'D';
    if(!directionExiste && testPosition(A, carte, nbCases, actuel, (*chemin), direction)){
        remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
        char Abis[2] = {A[X]+1,A[Y]};
        calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
    }
    direction = 'B';
    if(!directionExiste && testPosition(A, carte, nbCases, actuel, (*chemin), direction)){
        remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
        char Abis[2] = {A[X],A[Y]+1};
        calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
    }
    direction = 'H';
    if(!directionExiste && testPosition(A, carte, nbCases, actuel, (*chemin), direction)){
        remplirChemin(A[X], A[Y], (*chemin)[actuel], direction);
        char Abis[2] = {A[X],A[Y]-1};
        calculChemin(Abis, B, carte, nbCases, actuel+1, meilleur, chemin, meilleurChemin);
    }
    free((*chemin)[actuel]);
    return;
}

/**
 * \fn void reallocChemin(char*** chemin, int actuel)
 * \brief Fonction de reallocation du chemin.
 *
 * \param chemin Pointeur du tableau à modifier.
 * \param actuel Taille actuelle du chemin et donc du tableau.
 */
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

/**
 * \fn void remplirChemin(char posX, char posY, char* cheminActuel, char direction)
 * \brief Fonction de remplissage d'une ligne du chemin.
 *
 * \param posX Position X à ajouter.
 * \param posY Position Y à ajouter.
 * \param cheminActuel Ligne actuelle à remplir.
 * \param direction Direction à ajouter (H/B/G/D)
 */
void remplirChemin(char posX, char posY, char* cheminActuel, char direction){
    cheminActuel[0] = posX;
    cheminActuel[1] = posY;
    cheminActuel[2] = direction;
}

/**
 * \fn char comparePosition(char *positionA, char *positionB)
 * \brief Fonction de comparaison de deux positions.
 *
 * \param positionA Position A à comparer.
 * \param positionB Position B à comparer.
 * \return 1 si positions identiques, sinon 0.
 */
char comparePosition(char *positionA, char *positionB){
    if((positionA[0] == positionB[0]) && (positionA[1] == positionB[1])){
        return 1;
    } else {
        return 0;
    }
}

/**
 * \fn char testPosition(char position[2], const Case*** carte, char nbCases[2], int actuel, char** chemin, char direction)
 * \brief Fonction de test d'une position (Case) cible. Vérifie que la Case est franchissable
 * \brief et qu'elle n'a pas été franchie dans le chemin actuel (boucle).
 *
 * \param position Position actuelle.
 * \param carte Ensemble des cases.
 * \param nbCases Nombre de cases en X et Y.
 * \param actuel Avancée actuelle du chemin.
 * \param chemin Chemin actuel.
 * \param direction Direction dans laquelle on souhaite se déplacer.
 * \return 1 si déplacement valide dans cette direction, sinon 0.
 */
char testPosition(char position[2], const Case*** carte, char nbCases[2],
                int actuel, char** chemin, char direction){
    int i;
    char nouvellePosition[2];
    nouvellePosition[X] = position[X];
    nouvellePosition[Y] = position[Y];
    switch (direction) {
        case 'H':
            nouvellePosition[Y]--; break;
        case 'B':
            nouvellePosition[Y]++; break;
        case 'G':
            nouvellePosition[X]--; break;
        case 'D':
            nouvellePosition[X]++; break;
    }
    // Test la case cible
    if(testDeplacement(carte, nbCases, position, direction)){
        // Test que la case n'est pas déjà présente dans le chemin
        for(i = 0 ; i < actuel ; i++){
            if(comparePosition(nouvellePosition, chemin[i])){
                return 0;
            }
        }
        return 1;
    } else {
        return 0;
    }
}

/**
 * \fn Arrete** trierArretes(Arrete **tab, int nbArretes, Arrete *aRanger)
 * \brief Fonction de trie des Arrete selon leur distance.
 *
 * \param tab Tableau d'Arrete.
 * \param nbArretes Nombre d'Arrete du tableau.
 * \param aRanger Arrete à ranger dans le tableau.
 * \return Retourne le tableau avec la nouvelle Arrete.
 */
Arrete** trierArretes(Arrete **tab, int nbArretes, Arrete *aRanger){
    int i, j;
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
 * \fn char comparerArrete(Arrete* premiere, Arrete* deuxieme)
 * \brief Fonction de comparaison du suivi de deux Arrete.
 * \brief Compare si le point B de la premiere correspond au point
 * \brief A de la seconde.
 *
 * \param premiere Premiere Arrete à comparer.
 * \param deuxieme Deuxieme Arrete à comparer.
 * \return Retourne O si les Arrete se suivent, sinon N.
 */
char comparerArrete(Arrete* premiere, Arrete* deuxieme){
    if(premiere->B[0]==deuxieme->A[0] &&
       premiere->B[1]==deuxieme->A[1] ){
        return 'O';
   } else if(premiere->B[0]==deuxieme->B[0] &&
             premiere->B[1]==deuxieme->B[1] ){
        deuxieme = inverserArrete(deuxieme);
        return 'O';
   } else {
       return 'N';
   }
}

/**
 * \fn char* inverserChemin(char* chemin, char taille)
 * \brief Fonction d'inversion du chemin d'une Arrete.
 *
 * \param chemin Chemin à inverser.
 * \param taille Taille du chemin à inverser.
 * \return Retourne le nouveau chemin.
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
 * \fn Arrete* inverserArrete(Arrete* arrete)
 * \brief Fonction d'inversion des points et du chemin d'une Arrete.
 *
 * \param arrete Arrete à inverser.
 * \return Retourne l'Arrete inversée.
 */
Arrete* inverserArrete(Arrete* arrete){
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
 * \fn Arrete** ordonnerChemin(Arrete** chemin, int taille)
 * \brief Fonction de rangement du chemin du point de départ à l'arrivée.
 *
 * \param chemin Chemin à ordonner.
 * \param taille Taille du chemin.
 * \return Retourne le tableau du chemin ordonné.
 */
Arrete** ordonnerChemin(Arrete** chemin, int taille){
    int i, j;
    // boucle pour trouver l'arrete suivante, la placer a la suite
    // et continuer jusqu'a avoir range l'arbre.
    for(i = 1 ; i < taille ; i++){
        for(j = i ; j < taille ; j++){
            if(comparerArrete(chemin[i-1], chemin[j])=='O'){
                Arrete* arreteTemp = chemin[i];
                chemin[i] = chemin[j];
                chemin[j] = arreteTemp;
            }
        }
    }
    return chemin;
}

/**
 * \fn char chaine(EtatPosition* B, EtatPosition* A, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int tailleChemin)
 * \brief Fonction de recherche d'une chaine entre A et B dans un chemin d'Arrete.
 *
 * \param B Etat du point B.
 * \param A Etat du point A.
 * \param etatPositions Liste des points et leurs états.
 * \param chemin Chemin d'Arrete.
 * \param nbPositions Nombre de points.
 * \param tailleChemin Taille du chemin.
 * \return Retourne 1 s'il existe un chemin entre A et B, sinon 0.
 */
char chaine(EtatPosition* B, EtatPosition* A, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int tailleChemin){
    if( comparerEtats(A, B) ){ // Si on est rendu au point cible il y a une chaine
        return 1;
    }
    int i;
    for(i = 0 ; i < tailleChemin ; i++){
        if( (evaluerPosition(chemin[i]->A, A) != 'N') &&
            (getEtatPosition(chemin[i]->B, etatPositions, nbPositions)->flagVerif == 0) ){ // Arrete A -> B
            A->flagVerif = 1;
            return chaine(B, getEtatPosition(chemin[i]->B, etatPositions, nbPositions), etatPositions, chemin, nbPositions, tailleChemin);
        }
        if( (evaluerPosition(chemin[i]->B, A) != 'N') &&
            (getEtatPosition(chemin[i]->A, etatPositions, nbPositions)->flagVerif == 0) ){ // Arrete B -> A
            A->flagVerif = 1;
            return chaine(B, getEtatPosition(chemin[i]->A, etatPositions, nbPositions), etatPositions, chemin, nbPositions, tailleChemin);
        }
    }
    // Aucune arrete trouvee. Pas de chaine.
    return 0;
}

/**
 * \fn char estChaine(EtatPosition* posExtremite, EtatPosition* posActuelle, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int tailleChemin)
 * \brief Fonction d'appel de recherche d'une chaine entre A et B dans un chemin d'Arrete. Remet à zéro les flags après recherche.
 *
 * \param posExtremite Etat du point cible.
 * \param posActuelle Etat du point d'origine.
 * \param etatPositions Liste des points et leurs états.
 * \param chemin Chemin d'Arrete.
 * \param nbPositions Nombre de points.
 * \param tailleChemin Taille du chemin.
 * \return Retourne 1 s'il existe un chemin entre l'origine et la cible, sinon 0.
 */
char estChaine(EtatPosition* posExtremite, EtatPosition* posActuelle, EtatPosition** etatPositions, Arrete** chemin, int nbPositions, int nb){
    char ret = chaine(posExtremite, posActuelle, etatPositions, chemin, nbPositions, nb);
    resetFlag(etatPositions, nbPositions);
    return ret;
}

/**
 * \fn char arreteValide(EtatPosition** etatPositions, int nbPositions, int j, int k, Arrete** chemin, int nb)
 * \brief Fonction de vérification de la validité d'une Arrete : aucune fermeture du chemin sans inclure tous les points.
 *
 * \param etatPositions Liste des points et leurs états.
 * \param nbPositions Nombre de points.
 * \param idxA Index de l'état du point A de l'Arrete.
 * \param idxB Index de l'état du point B de l'Arrete.
 * \param chemin Chemin d'Arrete.
 * \param tailleChemin Taille du chemin.
 * \return Retourne 1 s'il existe un chemin entre l'origine et la cible, sinon 0.
 */
char arreteValide(EtatPosition** etatPositions, int nbPositions, int idxA, int idxB, Arrete** chemin, int tailleChemin){
    int i;
    if(idxA > 1 && idxB > 1) { // j et k sont des index de ressources on verifie les boucles
        for(i = 2 ; i < nbPositions ; i++){
            if(i != idxA && idxB != i){ // On analyse l'etat des autres ressources (le cas j<2 && k<2 est impossible)
                if((etatPositions[i]->flagAvance) < 2){ // S'il existe au moins une ressource libre
                    if( ( estChaine(etatPositions[0], etatPositions[idxA], etatPositions, chemin, nbPositions, tailleChemin) ||
                          estChaine(etatPositions[1], etatPositions[idxA], etatPositions, chemin, nbPositions, tailleChemin) )
                        && // Fermeture du chemin (chaque point de l'arrete fait une chaine jsuqu'à l'extemite
                        ( estChaine(etatPositions[0], etatPositions[idxB], etatPositions, chemin, nbPositions, tailleChemin) ||
                          estChaine(etatPositions[1], etatPositions[idxB], etatPositions, chemin, nbPositions, tailleChemin) ) ) {
                        return 0;
                    }  else {
                        return !estChaine(etatPositions[idxA], etatPositions[idxB], etatPositions, chemin, nbPositions, tailleChemin);
                    }
                }
            }
        }
        return !estChaine(etatPositions[idxA], etatPositions[idxB], etatPositions, chemin, nbPositions, tailleChemin);
    } else { // Au moins un des points est une extremite
        for(i = 2 ; i < nbPositions ; i++){
            if(i != idxA && idxB != i){ // On analyse l'etat des autres ressources (le cas j<2 && k<2 est impossible)
                if((etatPositions[i]->flagAvance) < 2){ // S'il existe au moins une ressource libre
                    if(idxA < 2) { // Si j est extremite on regarde que notre ressource (k) ne ferme pas le chemin
                        return !estChaine(etatPositions[!idxA], etatPositions[idxB], etatPositions, chemin, nbPositions, tailleChemin);
                    }
                    else { // Sinon on regarde que j ne ferme pas le chemin
                        return !estChaine(etatPositions[!idxB], etatPositions[idxA], etatPositions, chemin, nbPositions, tailleChemin);
                    }
                }
            }
        }
    }
    return 1;
}

/**
 * \fn Arrete** cheminPlusCourt(Arrete** tabArretes, EtatPosition** etatPositions, int nbArretes, int nbRessources)
 * \brief Fonction de recherche du chemin le plus court avec une liste donnée d'Arrete.
 *
 * \param tabArretes Liste totale des Arrete disponibles
 * \param etatPositions Liste des points et leurs états.
 * \param nbArretes Nombre total d'Arrete
 * \param nbRessources Nombre total de Ressource
 * \return Retourne la liste d'Arrete consitutant le chemin le plus court.
 */
Arrete** cheminPlusCourt(Arrete** tabArretes, EtatPosition** etatPositions, int nbArretes, int nbRessources){
    Arrete** chemin = (Arrete**)malloc(sizeof(Arrete*)*nbRessources+1);
    int i, j, k, tailleChemin =0;
    for(i = 0 ; i < nbArretes ; i++){ // Parcours  des arretes
        for(j=0; j < nbRessources+2;j++){ // Parcours des etats pour le point A
            if( ((tabArretes[i]->A[0]) == (etatPositions[j]->posX)) &&
                ((tabArretes[i]->A[1]) == (etatPositions[j]->posY)) ){
                for(k=0; k < nbRessources+2;k++){ // Parcours des etats pour le point B
                    if( ((tabArretes[i]->B[0]) == (etatPositions[k]->posX)) &&
                        ((tabArretes[i]->B[1]) == (etatPositions[k]->posY)) ){
                        if( ((etatPositions[j]->flagAvance) < 2) && ((etatPositions[k]->flagAvance) < 2)
                           && (arreteValide(etatPositions,nbRessources+2,j,k,chemin,tailleChemin)) ){
                            chemin[tailleChemin] = tabArretes[i]; tailleChemin++;
                            etatPositions[j]->flagAvance++;
                            etatPositions[k]->flagAvance++;
                            break;
                       }
                    }
                }
                break;
            }
        }
        if(tailleChemin > nbRessources)
            break;
    }
    return chemin;
}

/**
 * \fn Arrete* copieArrete(Arrete* arrete)
 * \brief Fonction de copie d'une Arrete vers une nouvelle adresse mémoire.
 *
 * \param arrete Arrete à copier.
 * \return Retourne un pointeur sur la nouvelle adresse.
 */
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

/**
 * \fn Arrete** copieChemin(Arrete** chemin, int taille)
 * \brief Fonction de copie d'un chemin et ses Arrete vers une nouvelle adresse mémoire.
 *
 * \param chemin Chemin à copier.
 * \param taille Taille du chemin à copier.
 * \return Retourne le nouveau chemin.
 */
Arrete** copieChemin(Arrete** chemin, int taille){
    Arrete** cheminRetour = (Arrete**)malloc(sizeof(Arrete*)*taille);
    int i;
    for(i = 0 ; i < taille ; i++){
        cheminRetour[i] = copieArrete(chemin[i]);
    }
    return cheminRetour;
}
