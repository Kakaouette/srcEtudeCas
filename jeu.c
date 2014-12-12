#include "Jeu.h"

extern  Sprite araignee; //const//enlevé pour permettre que le load des images ne soit fait quune fois
extern  Sprite squelette;
extern  Sprite farmer;
extern  Case caseHerbe;
extern  Case caseTerre;
extern const Sprite gems;

char jouerTour(Jeu *game, Joueur *player, Arrete *arrete) { // Un tour (pour le mode deux joueurs)
    int i;

    char ressource = deplacement(game->ressources, game->nbRessource, player, arrete->C[0]);

    if (ressource == 'T') {
        game->nbRessource--;
    }

    for (i = 0; i < arrete->D - 1; i++) {
        arrete->C[i] = arrete->C[i + 1];
    }
    //free(&arrete->C[arrete->D - 1]);
    arrete->D--;

    return (arrete->D == 0) ? 'F' : 'T';
}


void execution(){} // Appell� depuis le main. Cr�� affichage/joueur/etc... // options a ajouter en argument

static Ressource* ressourcesTemp;
static Joueur* playersTemp;

/**
 * \fn void new_Game(Jeu *game, Option *defaut)
 * \brief allocations memoire pour un jeu et initialisations
 *
 * \param game Le jeu dont on veux faire les allocations et initialisations
 * \param defaut Les options de jeu
 */
void new_Game(Jeu *game, Option *defaut){
    ///Initialisation des paramètres du jeu///
    game->nbCaseX = defaut->nbCaseX;//.nbCaseX =50//fullscreen
    game->nbCaseY = defaut->nbCaseY;//.nbCaseY =28//fullscreen
    game->nbRessource = defaut->nbRessource;
    game->nbPlayer = defaut->nbJoueur;
    game->nbTourPassee = 0;
    ///Allocations///
    //allocation temp
    ressourcesTemp = malloc(game->nbRessource * sizeof(*ressourcesTemp)); //sizeof(Ressource)
    playersTemp = malloc(game->nbPlayer * sizeof(*playersTemp)); //sizeof(Ressource)
    //allocation map
    int i;
    game->map = malloc(game->nbCaseX * sizeof(*game->map));
    for (i=0 ; i < game->nbCaseX ; i++){
        game->map[i] = malloc(game->nbCaseY * sizeof(**game->map));
    }
    //allocation ressources
    game->ressources = malloc(game->nbRessource * sizeof(Ressource*));
    //allocation joueurs
    game->players = malloc(game->nbPlayer * sizeof(Joueur*));
    ///Initialisations///
    //initialisation map
    int j;
    for (i=0; i<game->nbCaseX;i++){
        for (j=0; j<game->nbCaseY;j++){
            game->map[i][j] = NULL;
        }
    }
    //initialisation ressources
    for (j=0; j<game->nbRessource;j++){
        game->ressources[j] = &ressourcesTemp[j];
    }
    //initialisation joueurs
    for (j=0;j<game->nbPlayer;j++){
        game->players[j] = &playersTemp[j];
        game->players[j]->sprite = defaut->sprites[j]; //choix de l'apparence du joueur
        game->players[j]->orientation = bas;
        game->players[j]->sac[0]=0;
    }
}
/**
 * \fn void free_Jeu(Jeu *game)
 * \brief liberation de memoire pour un jeu
 *
 * \param game Le jeu dont on veut liberer la memoire
 */
void free_Jeu(Jeu *game){
    int i;
    // Libération mémoire des temp
    free(ressourcesTemp);
    ressourcesTemp = NULL;
    free(playersTemp);
    playersTemp = NULL;
    // Libération mémoire map
    for (i=0; i<game->nbCaseX; i++)
    {
        free (game->map[i]);
        game->map[i] = NULL;
    }
    free(game->map);
    game->map = NULL;
    // Libération mémoire ressources
    free(game->ressources);
    game->ressources = NULL;
    // Libération mémoire joueurs
    free(game->players);
    game->players = NULL;
}


/**
 * \fn void genTerrain(Jeu *game, int nbCaseLibreVoulu)
 * \brief genere la carte pour un jeu
 *
 * \param game Le jeu dont on veut generer la carte
 * \param nbCaseLibreVoulu Le nombre de cases libre que l'on veut sur la carte
 */
void genTerrain(Jeu *game, int nbCaseLibreVoulu){
    //Déclaration des variables
    int nbCaseTake = 0;
    char x,y;

    ///Initialisation des cases en infranchissable///
    for (x=0; x<game->nbCaseX; x++){
        for (y=0; y<game->nbCaseY; y++){
            game->map[x][y] = &caseHerbe;//pointe sur une case infranchissable
        }
    }
    ///generation chemin coherent///
    //case de depart
	char dX = rand_a_b(0,game->nbCaseX);
	char dY = rand_a_b(0,game->nbCaseY);
	game->map[dX][dY] = &caseTerre;//pointe sur une case libre
    nbCaseTake ++;

    do{
        //Déclaration des variables
        char nbCases;
        char** q;
        q = malloc(0 * sizeof(*q));

        //take une case autour au hasard
        do{//recherche du nb de case possible autour
            nbCases=0;
            for (x = -1; x <= 1; x++) {//recherche dans les 4 positions autour de la case de depart
                y = abs(x)-1;
                if (((dX + x)>=0) && ((dX + x)<game->nbCaseX) && ((dY + y)>=0) && ((dY + y)<game->nbCaseY)) {//in terrain
                    if(game->map[dX + x][dY + y]->type != libre){//is not alerady libre
                        nbCases++;
                        q = realloc(q, nbCases * sizeof(*q));//reallocation
                        q[nbCases-1] = malloc(2 * sizeof(**q));
                        //remplissage du tableau
                        q[nbCases-1][0] = dX + x;
                        q[nbCases-1][1] = dY + y;
                    }
                }
                y = 1 - abs(x);
                if (y != abs(x)-1 && (dX + x)>=0 && (dX + x)<game->nbCaseX && (dY + y)>=0 && (dY + y)<game->nbCaseY) {//in terrain
                    if(game->map[dX + x][dY + y]->type != libre){//is not alerady libre
                        nbCases++;
                        q = realloc(q, nbCases * sizeof(*q));//reallocation
                        q[nbCases-1] = malloc(2 * sizeof(**q));
                        //remplissage du tableau
                        q[nbCases-1][0] = dX + x;
                        q[nbCases-1][1] = dY + y;
                    }
                }
            }
            if(nbCases == 0){//aucune case non deja prise et dans le terrain
                do{//on selec une autre case libre
                    dX = rand_a_b(0,game->nbCaseX);
                    dY = rand_a_b(0,game->nbCaseY);
                }while(game->map[dX][dY]->type != libre);
            }
        }while(nbCases == 0);
        ///Choix de la case suivante///
        char index = rand_a_b(0,nbCases);
        dX = q[index][0];
        dY = q[index][1];
        game->map[dX][dY] = &caseTerre;
        nbCaseTake ++;

        free(q);
    }while(nbCaseTake < nbCaseLibreVoulu); //nb de case accessible voulu
}
/**
 * \fn void genDepartArrivee(Jeu *game)
 * \brief donne la position de depart et d'arriver pour les joueurs du jeu
 *
 * \param game Le jeu qui contient les joueur dont on veut initialiser les position
 */
void genDepartArrivee(Jeu *game){
    int j=0;
    for (j=0;j<game->nbPlayer;j++){//pour chaque joueur
        char depart = 0, arrivee = 0; //bool existe pas en c, c dla merde

        char dX, dY;
        do{
            //case au hasard
            dX = rand_a_b(0,game->nbCaseX);
            dY = rand_a_b(0,game->nbCaseY);

            if (game->map[dX][dY]->type == libre){ //si case libre
                if (depart == 0){
                    game->players[j]->position[0] = dX;
                    game->players[j]->position[1] = dY;
                    depart = 1;
                }else{
                    game->players[j]->arrivee[0] = dX;
                    game->players[j]->arrivee[1] = dY;
                    arrivee = 1;
                }
            }
        }while(depart == 0 || arrivee == 0);
    }
}
/**
 * \fn void genObjet(Jeu *game)
 * \brief donne une position aux ressource du jeu
 *
 * \param game Le jeu qui contient les ressources dont on veut generer la position
 */
void genObjet(Jeu *game){
    int nbRessourceVoulu = game->nbRessource;
    int nbCaseTake = 0, i;
    char x,y;

    char dejaRessource; //bool existe pas en c, c dla merde

    while(nbCaseTake < nbRessourceVoulu){
        do{
            x= rand_a_b(0,game->nbCaseX);
            y= rand_a_b(0,game->nbCaseY);

            if (game->map[x][y]->type == libre){
                dejaRessource = 0;
                //verif si pas deja une ressource
                for (i=0;i<game->nbRessource;i++){
                    if (game->ressources[i]->position[0] == x && game->ressources[i]->position[1] == y){
                        dejaRessource = 1;
                        break;
                    }
                }
            }
        }while(game->map[x][y]->type != libre || dejaRessource == 1);

        game->ressources[nbCaseTake]->position[0]=x;
        game->ressources[nbCaseTake]->position[1]=y;
        game->ressources[nbCaseTake]->image = &gems;
        nbCaseTake++;
    }
}


//Random
/**
 * \fn int rand_a_b(int a, int b)
 * \brief genere un nombre entier aleatoire entre a et b
 *
 * \param a Limite basse
 * \param b Limite haute
 * \return le nombre generé
 */
int rand_a_b(int a, int b){
    return rand() % (b - a) + a;
}
int* init_sans_doublons(int a, int b){
	int taille = b-a;
	int* resultat=malloc((taille)*sizeof (int));
	int i=0;
	// On remplit le tableau de manière à ce qu'il soit trié
	for(i = 0; i< taille; i++){
		resultat[i]=i+a;
	}
	return resultat;
}
void melanger(int* tableau, int taille){
	int i=0;
	int nombre_tire=0;
	int temp=0;

	for(i = 0; i< taille;i++){
		nombre_tire=rand_a_b(0,taille);
		// On échange les contenus des cases i et nombre_tire
		temp = tableau[i];
		tableau[i] = tableau[nombre_tire];
		tableau[nombre_tire]=temp;
	}
}
