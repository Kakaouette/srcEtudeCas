#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include <math.h>

#include "Jeu.h"
#include "Case.h"
#include "ressource.h"
extern const int NB_CASE_X;
extern const int NB_CASE_Y;
extern const int SPRITE_WIDTH;
extern const int SPRITE_HEIGHT;


SDL_Rect decoupage(int x, int y){

    SDL_Rect clip;

    //clipping
    clip.x = x*SPRITE_WIDTH; //0->15
    clip.y = y*SPRITE_HEIGHT;
    clip.w = SPRITE_WIDTH;
    clip.h = SPRITE_HEIGHT;
    return clip;
}

void afficher(SDL_Surface * ecran, Jeu * game)
{
    //attributs de la feuille de sprites
    const int SHEET_WIDTH = 512, SHEET_HEIGHT = 512;
    //nombre dimage: 512/32=16, 16*16

    //attributs de l'écran
    const int SCREEN_WIDTH = NB_CASE_X*SPRITE_WIDTH;//640
    const int SCREEN_HEIGHT = NB_CASE_Y*SPRITE_HEIGHT;//480
    const int SCREEN_BPP = 32;

    //Les surfaces
    SDL_Surface *textures = NULL;
    textures = IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png"); //load le tileset
    //Les différentes parties de la feuille de sprites qui vont être blittés
    SDL_Rect terre = decoupage(11, 4);
    SDL_Rect herbe = decoupage(15, 1);
    SDL_Rect perso = decoupage(10,12);
    SDL_Rect gems = decoupage(10,9);


    Case cs[NB_CASE_X][NB_CASE_Y];
    Case* c[NB_CASE_X][NB_CASE_Y];

    int i,j;

    for (i=0; i<NB_CASE_X;i++){
        for (j=0; j<NB_CASE_Y;j++){
            //cs[i][j].type = libre;
            c[i][j]=&cs[i][j];
        }
    }



    int y,x;
    /**On applique les sprites sur l'écran*/

    /**affichage map*/
    for (y=0;y<NB_CASE_Y;y++){
        for (x=0;x<NB_CASE_X;x++){
            if (c[x][y]->type == libre){
                c[x][y]->image = &terre;
            }else{
                c[x][y]->image = &herbe;
            } //remplacer "c" par "game->map"
            apply_surface( x*SPRITE_WIDTH, y*SPRITE_HEIGHT, textures, ecran, c[x][y]->image ); //0->(SCREEN_WIDTH/SPRITE_WIDTH)-1
        }
    }
    /**affichage perso*/
    //apply_surface( p1->i*SPRITE_WIDTH, p1->j*SPRITE_HEIGHT, textures, ecran, &p1->image );


    SDL_Flip(ecran); // Mise à jour de l'écran

    SDL_FreeSurface(textures); // On libère la surface
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip ){
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}

int rand_a_b(int a, int b){
    return rand() % (b - a) + a;
}

void genTerrain(Case* map[][NB_CASE_Y]){
    int nbCaseLibreVoulu = 1/3*(NB_CASE_X*NB_CASE_Y);
    int nbCaseTake = 0;

    int i,j;

    for (i=0; i<20; i++){
        for (j=0; j<15; j++){
            map[i][j]->type = infranchissable; //rendre la case infranchissable
        }
    }
    //generation chemin coherent
    //case de depart au hasard
    srand(time(NULL)); // initialisation de rand
	int	dX = rand_a_b(0,20);
	int	dY = rand_a_b(0,15);
	map[dX][dY]->type = libre; //rendre la case libre
    nbCaseTake ++;

        int xx,yy,nb, nbAnc;
    do{//take une case autour au hasard
        do{
        nb=0;
        for (xx = -1; xx <= 1; xx++) {
			yy = abs(xx)-1;
			if (((dX + xx)>=0) && ((dX + xx)<20) && ((dY + yy)>=0) && ((dY + yy)<15)) {
			    if(map[dX + xx][dY + yy]->type != libre){
                    nb++;
			    }
			}
			yy = 1 - abs(xx);
			if (yy != abs(xx)-1 && (dX + xx)>=0 && (dX + xx)<20 && (dY + yy)>=0 && (dY + yy)<15) {
			    if(map[dX + xx][dY + yy]->type != libre){
                    nb++;
			    }
			}
		}
        nbAnc = nb;
		if(nbAnc == 0){
            do{
                dX = rand_a_b(0,20);
                dY = rand_a_b(0,15);

            }while(map[dX][dY]->type != libre);
		}
        }while(nbAnc == 0);

        int q[nbAnc][2];
        //case valide a coté de la case depart
        for ( xx = -1; xx <= 1; xx++) {
			yy = abs(xx)-1;
			if ((dX + xx)>=0 && (dX + xx)<20 && (dY + yy)>=0 && (dY + yy)<15) {
			    if(map[dX + xx][dY + yy]->type != libre){

			    nb--;
			    q[nb][0] = dX + xx;
			    q[nb][1] = dY + yy;
			    }
			}
			yy = 1 - abs(xx);
			if (yy != abs(xx)-1 && (dX + xx)>=0 && (dX + xx)<20 && (dY + yy)>=0 && (dY + yy)<15) {
			    if(map[dX + xx][dY + yy]->type != libre){

			    nb--;
			    q[nb][0] = dX + xx;
			    q[nb][1] = dY + yy;
			    }
			}
		}

        int index = rand_a_b(0,nbAnc);
        dX = q[index][0];
        dY = q[index][1];
        map[dX][dY]->type = libre; //rendre la case libre
        nbCaseTake ++;
    }while(nbCaseTake < nbCaseLibreVoulu); //nb de case accessible voulu
}

void genDepartArrivee(Case* map[][NB_CASE_Y]){

    char depart = 0, arrivee = 0; //bool existe pas en c, c dla merde

    srand(time(NULL)); // initialisation de rand
    int	dX, dY;
    do{
        //case au hasard
        dX = rand_a_b(0,NB_CASE_X);
        dY = rand_a_b(0,NB_CASE_Y);

        if (map[dX][dY]->type == libre){ //si case libre
            if (depart){
                map[dX][dY]->depart = pow(2,0);
                depart = 1;
            }else{
                map[dX][dY]->arrivee = pow(2,0);
                arrivee = 1;
            }
        }
    }while(depart == 0 || arrivee == 0);
}

void genObjet(int nbRessourceVoulu, Jeu * game){
    int nbCaseTake = 0;
    srand(time(NULL)); // initialisation de rand

    int x,y;

    while(nbCaseTake < nbRessourceVoulu){
        do{
            x= rand_a_b(0,NB_CASE_X);
            y= rand_a_b(0,NB_CASE_Y);
        }while(game->map[x][y]->type != libre);
        game->ressources[nbCaseTake]->position[0]=x;
        game->ressources[nbCaseTake]->position[1]=y;
        nbCaseTake++;
    }//pb pas de verif si case deja une ressource
}
