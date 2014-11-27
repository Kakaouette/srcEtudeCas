#include "algorithme.h"

#define X 0
#define Y 1
#define etatPositionX (etatPosition&0xFF)
#define etatPositionY ((etatPosition>>8)&0xFF)
#define etatPositionFlag ((etatPosition>>16)&0xFF)


void calculChemin(char A[2], char B[2], Case*** carte, int actuel, int *meilleur, char*** chemin, char** meilleurChemin){
    /// Le "*meilleur" est a verifier
    // Limitation de l execution si on ne trouve pas de chemin plus court on abandonne
    if( (actuel >= *meilleur) && (*meilleur != 0) ){
        return;
    }
    // Rendu a l objectif on remplace les valeurs de meilleur distance et chemin
    if( (A[X] == B[X]) && (A[Y] == B[Y]) ){
        *meilleur = actuel;
        int i;
        *meilleurChemin = realloc(*meilleurChemin, sizeof(char)*actuel);
        for(i = 0 ; i < actuel ; i++){
            *meilleurChemin[i] = *chemin[i][2];
        }
        return;
    }
    /// chemin[]{X,Y,Sens}
    /// meilleurChemin{Sens}
    char directions[3] = {'X', 'X', *chemin[actuel]};
    *chemin = realloc(*chemin, sizeof(char)*(actuel+1));
    *chemin[actuel] = malloc(sizeof(char)*3);
    /// essaie d'aller vers case X suivante.
    if(A[X]<B[X] && *chemin[actuel-1][2]!='G'){
        directions[X] = 'D';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(carte[A[X]+1][A[Y]]->type!=infranchissable){
            *chemin[actuel]= {A[X],A[Y],'D'};
            calculChemin({A[X]+1,A[Y]}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        } else {
            /// Sinon, chemin = NULLL;
            *chemin[actuel][2] = NULL;
        }
    } else if (A[X]>B[X] && *chemin[actuel-1][2]!='D'){
        directions[X] = 'G';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(carte[A[X]-1][A[Y]]->type!=infranchissable){
            *chemin[actuel]= {A[X],A[Y],'G'};
            calculChemin({A[X]-1,A[Y]}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        } else {
            /// Sinon, chemin = NULLL;
            *chemin[actuel][2] = NULL;
        }
    } else {
        *chemin[actuel] = NULL;
    }
    /// essaie d'aller vers case Y suivante.
    if(A[Y]<B[Y] && *chemin[actuel-1][2]!='B'){
        directions[Y] = 'H';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(carte[A[X]][A[Y]-1]->type!=infranchissable){
            *chemin[actuel] = {A[X],A[Y],'H'};
            calculChemin({A[X],A[Y]-1}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        } else {
            /// Sinon, chemin = NULLL;
            *chemin[actuel][2] = NULL;
        }
    } else if (A[Y]>B[Y] && *chemin[actuel-1][2]!='H'){
        directions[Y] = 'B';
        /// Si ok, Appelle algo depuis la nouvelle case avec actuel++.
        if(carte[A[X]][A[Y]+1]->type!=infranchissable){
            *chemin[actuel] = {A[X],A[Y],'B'};
            calculChemin({A[X],A[Y]+1}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        } else {
            /// Sinon, chemin = NULLL;
            *chemin[actuel][2] = NULL;
        }
    }
    if(*chemin[actuel][2] == NULL){
        char direction = 'G';
        if(!directionExiste && (carte[A[X]-1][A[Y]]->type!=infranchissable)){
            *chemin[actuel] = {A[X],A[Y],'G'};
            calculChemin({A[X]-1,A[Y]}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        }
        direction = 'D';
        if(!directionExiste && (carte[A[X]+1][A[Y]]->type!=infranchissable)){
            *chemin[actuel] = {A[X],A[Y],'D'};
            calculChemin({A[X]+1,A[Y]}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        }
        direction = 'B';
        if(!directionExiste && (carte[A[X]][A[Y]+1]->type!=infranchissable)){
            *chemin[actuel] = {A[X],A[Y],'B'};
            calculChemin({A[X],A[Y]+1}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        }
        direction = 'H';
        if(!directionExiste && (carte[A[X]][A[Y]-1]->type!=infranchissable)){
            *chemin[actuel] = {A[X],A[Y],'H'};
            calculChemin({A[X],A[Y]-1}, B, carte, actuel+1, meilleur, chemin, meilleurChemin);
        }
    }
    /// Si arretes[0] et [1] sont NULL, calcul avec 3eme possibilite (pas de demi-tour)
    /// /// Si arretes[3] = NULL retour NULL (Sauf cas depart qui autorise 4eme possibilite).
    /// Sinon Retourne l'arrete avec D meilleure valeur.
}

long newPosition(char coordonnee[2]){
    long position = coordonnee[X] + (coordonnee[Y] << 8);
    return position;
}

/**
    Evalue une position en comparaison avec un etat pour definir s'il s'agit
    de l'etat correspondant a cette position.
    Retourne 0 si correspondance et flag a 0.
    Retourne 1 si correspondance et flag a 1.
    Retourne 2 si correspondance et flag a 2.
    Retourne N si non correspondance.
*/
char evaluerPosition(char coordonnee[2], long etatPosition){
    if((coordonnee[X] == etatPositionX) &&
       (coordonnee[Y] == etatPositionY)){
        if(etatPositionFlag==0){
            return '0';
        } else if (etatPositionFlag==1){
            return '1';
        } else {
            return '2';
        }
    } else {
        return 'N';
    }
}

/**
    Ajoute l'arrete donnee au tableau, a la position
    correspondante pour garder un tableau ordonne selon
    la distance des arretes.
*/
Arrete** trierArretes(Arrete* (*tab), int nbArretes, Arrete *aRanger){
    ///memset();
    short i, j;
    for(i = 0 ; i < nbArretes ; i++){
        if(tab[i]==0){
            tab[i] = aRanger;
            break;
        }
        if((tab[i]->D)<(aRanger->D)){
            for(j = i; j < nbArretes ; j++){
                if(tab[i]==0){
                    tab[i] = aRanger;
                    break;
                }
                Arrete* temp = temp = tab[i];
                tab[i] = aRanger;
            }
            break;
        }
    }
    return tab;
}

/**
    Tri le tableau du chemin pour mettre dans l'ordre depuis l'arrete
    avec la position du joueur a l'arrete avec l'arrivee.
*/
Arrete** trierChemin(Arrete* (*tab), int nbArretes){
    int i, j, k;
    Arrete* arreteTemp = malloc(sizeof(Arrete));
    // boucle pour trouver l'arrete suivante, la placer a la suite
    // et continuer jusqu'a avoir range l'arbre.
    for(i = 1 ; i < nbArretes ; i++){
        for(j = i ; j < nbArretes ; j++){
            if(comparerArrete(tab[i-1], tab[j])=='O'){
                if(comparerArrete(tab[i-1], tab[j])=='I'){
                    inverserPoints(tab[j]); // Inversion pour que le chemin soit toujours A -> B
                }
                for(k = j ; k > i ; k--){
                    arreteTemp = tab[k-1];
                    tab[k-1] = tab[k];
                    tab[k] = arreteTemp;
                }
            }
        }
    }
    free(arreteTemp);
    return tab;
}

/**
    Algorithme de resolution du chemin le plus court.
    Algorithme base sur la Theorie des Graphes.
    Retourne un tableau d'Arretes ordonnees, correspondant au chemin
    a effectuer.
*/
Arrete** algorithmeSansContrainte(Joueur *joueur, Ressource* (*ressources), int nbRessources){
    // Tableau final avec les arretes a retourner
    Arrete* (*chemin);
    chemin = malloc((nbRessources+1) * sizeof(Arrete*));
    // Pas de ressources : on va directement au point d'arrivee.
    if(nbRessources == 0){
        chemin[0] = newArrete(joueur->position, joueur->arrivee);
        return chemin;
    }

    int i, j, A, B, E, avance;
    // Nombre total d'arretes possibles.
    int nbArretes = (nbRessources * (nbRessources-1))/2 + nbRessources*2;
    // Allocation tableau avec toutes les arretes possibles
    Arrete* (*tabArretes);
    tabArretes = malloc(nbArretes * sizeof(Arrete*));
    // Tableau de long contenant la position X et Y d'un point et le flag associe
    // Par octet de poids fort a faible : rien-flag-posY-posX
    long* etatPosition;
    etatPosition = malloc((nbRessources+2) * sizeof(long));
    etatPosition[0] = newPosition(joueur->position);
    etatPosition[1] = newPosition(joueur->arrivee);

    // Ajout des arretes liées au joueur et au point d'arrivee
    for(i = 0 ; i < nbRessources ; i++){
        // Ajout de l'arrete avec le joueur
        Arrete* arreteJoueur = newArrete(joueur->position, ressources[i]->position);
        trierArretes(tabArretes, nbArretes, arreteJoueur);
        // Ajout de l'arrete avec le point d'arrivee
        Arrete* arreteArrivee = newArrete(joueur->arrivee, ressources[i]->position);
        trierArretes(tabArretes, nbArretes, arreteArrivee);
    }

    // Ajout des arretes entre ressources
    for(i = 0 ; i < nbRessources ; i++){
        etatPosition[i+2] = ressources[i]->position[X] + (ressources[i]->position[Y] << 8);
        // On cherche la table en partant de i+1 pour parcourir
        // les autres ressources non parcourues precedemment
        for(j = i+1 ; j < nbRessources ; j++){
            Arrete* arreteRessource = newArrete(ressources[i]->position, ressources[j]->position);
            trierArretes(tabArretes, nbArretes, arreteRessource);
        }
    }


    // Enfin, on parcours le tableau pour definir le chemin le plus cours
    avance = 0;
    for(i = 0 ; i < nbArretes ; i++){
        A = 0; B = 0;
        // On regarde chaque point pour regarder l'état du point
        // et éviter les boucles.
        for(j = 0 ; j < (nbRessources+2) ; j++){
            // On vérifie l'état du point A
            E = evaluerPosition(tabArretes[i]->A, etatPosition[j]);
            if(E=='0'){
                A = j;
                if(B!=0){break;}
            } else if(E=='1'){
                A = j + 0x0100;
                if(B!=0){break;}
            } else if(E=='2'){
                A = j + 0x0200; break;
            }
            // On vérifie l'état du point B
            E = evaluerPosition(tabArretes[i]->A, etatPosition[j]);
            if(E=='0'){
                B = j;
                if(A!=0){break;}
            } else if(E=='1'){
                B = j + 0x0100;
                if(A!=0){break;}
            } else if(E=='2'){
                B = j + 0x0200; break;
            }
        }
        if(((A&0xFF00)!=0x0200) && ((B&0xFF00)!=0x0200)){
            chemin[avance] = tabArretes[i];
            avance++;
            etatPosition[A&0xFF]+= 0x010000;
            etatPosition[B&0xFF]+= 0x010000;
        }
    }

    Arrete* arreteTemp = malloc(sizeof(Arrete));
    // Boucle pour retrouver le point de depart et le placer au debut.
    for(i = 0 ; i < nbArretes ; i++){
        if((chemin[i]->A[0] == joueur->position[0]) &&
           (chemin[i]->A[1] == joueur->position[1])){
            for(j = i ; j > 0 ; j--){
                arreteTemp = chemin[j-1];
                chemin[j-1] = chemin[j];
                chemin[j] = arreteTemp;
            }
            break;
        }
    }
    free(arreteTemp);

    // Tri du reste du chemin.
    trierChemin(chemin, nbRessources+1);
    ///!!! Free des elements avant ou juste free du tableau direct ?
    for(i = 0 ; i < nbArretes ; i++){
        free(tabArretes[i]);
    }
    free(tabArretes);
    free(etatPosition);
    return chemin;
}

