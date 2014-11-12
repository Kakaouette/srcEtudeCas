#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Jeu.h"
#include "affichage.h"

extern const SDL_Rect araignee;
extern const SDL_Rect squelette;
extern const SDL_Rect persoV2;

int main(int argc, char *argv[])
{
    srand(time(NULL)); // initialisation de rand
    /**Initialisation du jeu*/
    Jeu jeu;
    SDL_Surface *ecran = NULL; //screen
    SDL_Event event;

    //attributs de l'écran
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    const int SCREEN_BPP = 32;


    SDL_Init(SDL_INIT_VIDEO);


    char choix = 0;
    int tempsActuel, tempsPrecedent;
    char anciennePosition[2], dplJoueur[2];

    do{
        /**Initialisation du jeu*/
        jeu.nbCaseX = 20;//.nbCaseX =50//fullscreen
        jeu.nbCaseY = 15;//.nbCaseY =28//fullscreen
        jeu.nbRessource = 3;
        new_Game(&jeu);// allocation + initialisation
        /**Initialisation ecran*/
        SCREEN_WIDTH = jeu.nbCaseX*SPRITE_WIDTH;
        SCREEN_HEIGHT = jeu.nbCaseY*SPRITE_HEIGHT;
        ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); //afficher fenetre
        SDL_WM_SetCaption("La cueillette", NULL); //titre de la fenetre
        SDL_WM_SetIcon(IMG_Load("Image/sac.png"), NULL); //icon de la fenetre
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre
        /**Initialisation*/
        jeu.J1.image = &squelette; //choix du joueur//peut etre different a chaque partie //squelette
        genTerrain((jeu.nbCaseX*jeu.nbCaseY)/3,&jeu); //creation du terrain
        genObjet(jeu.nbRessource, &jeu);
        genDepartArrivee(&jeu);
        anciennePosition[0] = jeu.J1.position[0];
        anciennePosition[1] = jeu.J1.position[1];
        jeu.J1.orientation = bas;
        do{
            dplJoueur[0] = jeu.J1.position[0] - anciennePosition[0];
            dplJoueur[1] = jeu.J1.position[1] - anciennePosition[1];

            /**Affichage*/
            afficher(ecran, &jeu, dplJoueur);

            anciennePosition[0] = jeu.J1.position[0];
            anciennePosition[1] = jeu.J1.position[1];

            choix = gestionMenu(ecran, &jeu);

            //dpl joueur
            jeu.J1.position[0] = jeu.J1.position[0]+1;
        }while(choix!=1 && choix!=3); //&& game->J1.score[0] < nbRessource //ttes les ressources sont ramassees //fin de partie
        free_Jeu(&jeu); //désallocation
    }while (choix!=1); //rejouer

    SDL_Quit(); //Arrêt de la SDL

    return 0;
}

