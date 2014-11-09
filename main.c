#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Jeu.h"

SDL_Rect decoupage(int x, int y);

const int NB_CASE_X = 20;
const int NB_CASE_Y = 15;
//attributs de la feuille de sprites
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 32;
//nombre dimage: 512/32=16, 16*16

void pause();

int main(int argc, char *argv[])
{
    srand(time(NULL)); // initialisation de rand
    //attributs de l'écran
    const int SCREEN_WIDTH = NB_CASE_X*SPRITE_WIDTH;//640
    const int SCREEN_HEIGHT = NB_CASE_Y*SPRITE_HEIGHT;//480
    const int SCREEN_BPP = 32;

    SDL_Surface *ecran = NULL; //screen

    SDL_Init(SDL_INIT_VIDEO);


    ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); //afficher fenetre
    SDL_WM_SetCaption("La cueillette", NULL); //titre de la fenetre
    SDL_WM_SetIcon(IMG_Load("Image/sac.png"), NULL); //icon de la fenetre
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre

    /**Initialisation du jeu*/
    Jeu jeu;
    Jeu *game = &jeu;
    new_Game(game);// allocation
    //initialisation
    int i,j;
    Case cs[NB_CASE_X][NB_CASE_Y];


    for (i=0; i<NB_CASE_X;i++){
        for (j=0; j<NB_CASE_Y;j++){
            cs[i][j].depart = 0;
            cs[i][j].arrivee = 0;
            game->map[i][j] = &cs[i][j];
        }
    }

    SDL_Rect perso = decoupage(10,12);
    game->J1.image = &perso;


    SDL_Rect gems = decoupage(10,9);

    int nbRessource = 3;
    Ressource r[nbRessource];
    game->ressources = malloc(nbRessource * sizeof(*game->ressources));//allocation
    //initialisation
    for (j=0; j<nbRessource;j++){
        game->ressources[j] = &r[j];
        game->ressources[j]->image = &gems;
    }


    genTerrain((NB_CASE_X*NB_CASE_Y)/3,game->map);//creation du terrain
    genObjet(nbRessource, game);
    genDepartArrivee(game->map, game);
    /**Affichage*/
    Uint8 typeEvent=0;
    SDL_Event event;
    int tempsActuel = 0, tempsPrecedent = 0;
    while(typeEvent!=SDL_QUIT){
        afficher(ecran, game, nbRessource);
        do{
            tempsActuel = SDL_GetTicks();
            SDL_WaitEvent(&event);
            typeEvent = event.type;
            if (tempsActuel - tempsPrecedent >= 100){ // Si 100 ms au moins se sont écoulées
                tempsPrecedent = tempsActuel; //maj tempsPrecedent
                break;
            }
        }while(typeEvent!=SDL_KEYDOWN && typeEvent!=SDL_QUIT);


        //dpl joueur
    }

    SDL_Quit(); //Arrêt de la SDL

    return 0;
}

