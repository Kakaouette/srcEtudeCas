#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Jeu.h"
const int NB_CASE_X = 20;
const int NB_CASE_Y = 15;
//attributs de la feuille de sprites
const int SPRITE_WIDTH = 32;
const int SPRITE_HEIGHT = 32;
//nombre dimage: 512/32=16, 16*16

void pause();

int main(int argc, char *argv[])
{

    //attributs de l'écran
    const int SCREEN_WIDTH = NB_CASE_X*SPRITE_WIDTH;//640
    const int SCREEN_HEIGHT = NB_CASE_Y*SPRITE_HEIGHT;//480
    const int SCREEN_BPP = 32;

    SDL_Surface *ecran = NULL; //screen

    SDL_Init(SDL_INIT_VIDEO);


    ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); //afficher fenetre
    SDL_WM_SetCaption("La cueillette", NULL); //titre de la fenetre
    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre

    /**Initialisation du jeu*/
    Jeu *game;
    //genTerrain(game->map);
    //genObjet(3, game);
    /**Affichage*/
    Uint8 typeEvent=0;
    SDL_Event event;
    while(typeEvent!=SDL_QUIT){
        afficher(ecran, game);
        do{
            SDL_WaitEvent(&event);
            typeEvent = event.type;
        }while(typeEvent!=SDL_KEYDOWN && typeEvent!=SDL_QUIT);
    }

    //pause();

    SDL_Quit(); //Arrêt de la SDL

    return 0;
}

void pause(){ // Mise en pause du programme
    int continuer = 1;
    SDL_Event event;

    while (continuer)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                continuer = 0;
        }
    }
}

