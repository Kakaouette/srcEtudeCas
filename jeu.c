#include "Jeu.h"
#include "Case.h"


extern const Case caseHerbe;
extern const Case caseTerre;
extern const SDL_Rect gems;


void resetRessources(Jeu *game){
    int i;
    for(i = 0 ; i < game->nbRessource ; i++){
        game->ressources[i]->vue = 0;
        game->ressources[i]->pass = 0;
        game->ressources[i]->rendu = 0;
    }
}

void execution(){} // Appell� depuis le main. Cr�� affichage/joueur/etc... // options a ajouter en argument

static Ressource* ressourcesTemp;

void new_Game(Jeu *game, Option *defaut){
    game->nbCaseX = defaut->nbCaseX;//.nbCaseX =50//fullscreen
    game->nbCaseY = defaut->nbCaseY;//.nbCaseY =28//fullscreen
    game->nbRessource = defaut->nbRessource; //add: verif que sa ne depasse pas le nb de cases libre

    //allocation temp
    ressourcesTemp = malloc(game->nbRessource * sizeof(*ressourcesTemp));
    //allocation map
    int i;
    game->map = malloc(game->nbCaseX * sizeof(*game->map));
    for (i=0 ; i < game->nbCaseX ; i++){
        game->map[i] = malloc(game->nbCaseY * sizeof(**game->map));
    }
    //allocation ressources
    game->ressources = malloc(game->nbRessource * sizeof(Ressource));
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
}
void free_Jeu(Jeu *game){
    int i;
    // Libération mémoire des temp
    free(ressourcesTemp);
    ressourcesTemp = NULL;
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
}


void genTerrain(Jeu *game, int nbCaseLibreVoulu){
    int nbCaseTake = 0;

    char i,j;

    for (i=0; i<game->nbCaseX; i++){
        for (j=0; j<game->nbCaseY; j++){
            //initialisation
            game->map[i][j] = &caseHerbe;//pointe sur une case infranchissable
        }
    }
    //generation chemin coherent
    //case de depart au hasard
	char dX = rand_a_b(0,game->nbCaseX);
	char dY = rand_a_b(0,game->nbCaseY);
	game->map[dX][dY] = &caseTerre;//pointe sur une case libre
    nbCaseTake ++;

        char xx,yy,nb, nbAnc;
    do{//take une case autour au hasard
        do{
        nb=0;
        for (xx = -1; xx <= 1; xx++) {
			yy = abs(xx)-1;
			if (((dX + xx)>=0) && ((dX + xx)<game->nbCaseX) && ((dY + yy)>=0) && ((dY + yy)<game->nbCaseY)) {
			    if(game->map[dX + xx][dY + yy]->type != libre){
                    nb++;
			    }
			}
			yy = 1 - abs(xx);
			if (yy != abs(xx)-1 && (dX + xx)>=0 && (dX + xx)<game->nbCaseX && (dY + yy)>=0 && (dY + yy)<game->nbCaseY) {
			    if(game->map[dX + xx][dY + yy]->type != libre){
                    nb++;
			    }
			}
		}
        nbAnc = nb;
		if(nbAnc == 0){
            do{
                dX = rand_a_b(0,game->nbCaseX);
                dY = rand_a_b(0,game->nbCaseY);

            }while(game->map[dX][dY]->type != libre);
		}
        }while(nbAnc == 0);

        char q[nbAnc][2];
        //case valide a coté de la case depart
        for ( xx = -1; xx <= 1; xx++) {
			yy = abs(xx)-1;
			if ((dX + xx)>=0 && (dX + xx)<game->nbCaseX && (dY + yy)>=0 && (dY + yy)<game->nbCaseY) {
			    if(game->map[dX + xx][dY + yy]->type != libre){

			    nb--;
			    q[nb][0] = dX + xx;
			    q[nb][1] = dY + yy;
			    }
			}
			yy = 1 - abs(xx);
			if (yy != abs(xx)-1 && (dX + xx)>=0 && (dX + xx)<game->nbCaseX && (dY + yy)>=0 && (dY + yy)<game->nbCaseY) {
			    if(game->map[dX + xx][dY + yy]->type != libre){

			    nb--;
			    q[nb][0] = dX + xx;
			    q[nb][1] = dY + yy;
			    }
			}
		}

        char index = rand_a_b(0,nbAnc);
        dX = q[index][0];
        dY = q[index][1];
        game->map[dX][dY] = &caseTerre;
        nbCaseTake ++;
    }while(nbCaseTake < nbCaseLibreVoulu); //nb de case accessible voulu
}
void genDepartArrivee(Jeu *game){

    char depart = 0, arrivee = 0; //bool existe pas en c, c dla merde

    char	dX, dY;
    do{
        //case au hasard
        dX = rand_a_b(0,game->nbCaseX);
        dY = rand_a_b(0,game->nbCaseY);

        if (game->map[dX][dY]->type == libre){ //si case libre
            if (depart == 0){
                game->J1.position[0] = dX;
                game->J1.position[1] = dY;
                depart = 1;
            }else{
                game->J1.arrivee[0] = dX;
                game->J1.arrivee[1] = dY;
                arrivee = 1;
            }
        }
    }while(depart == 0 || arrivee == 0);
}
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
        }while(game->map[x][y]->type != libre || dejaRessource);

        game->ressources[nbCaseTake]->position[0]=x;
        game->ressources[nbCaseTake]->position[1]=y;
        game->ressources[nbCaseTake]->image = &gems;
        nbCaseTake++;
    }
}


//Random
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
