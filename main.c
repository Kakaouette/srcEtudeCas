#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "affichage.h"

extern const Sprite araignee;
extern const Sprite squelette;
extern const Sprite farmer;

SDL_Rect* boutons;

int main(int argc, char *argv[])
{
    boutons = malloc(6 * sizeof(SDL_Rect));//allocation
    /**Déclaration des options*/
    Option opt;
    opt.sprite = &araignee;
    opt.nbCaseX = 20;
    opt.nbCaseY = 15;
    opt.nbRessource = 3;

    /**Déclaration des varables*/
    Jeu jeu;
    SDL_Surface *ecran = NULL; //screen

    //attributs de l'écran
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    const int SCREEN_BPP = 32;

    char choix = choixNull;
    char anciennePosition[2], dplJoueur[2];


    srand(time(NULL)); // initialisation de rand
    SDL_Init(SDL_INIT_VIDEO);



    do{
        /**Initialisation de la fenetre*/
        SCREEN_WIDTH = opt.nbCaseX*SPRITE_WIDTH;
        SCREEN_HEIGHT = opt.nbCaseY*SPRITE_HEIGHT;
        SDL_WM_SetCaption("La cueillette", NULL); //titre de la fenetre
        SDL_WM_SetIcon(IMG_Load("Image/sac.png"), NULL); //icone de la fenetre
        ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); //afficher fenetre
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre
        /**Initialisation du jeu*/
        new_Game(&jeu, &opt);// allocation + initialisation
        jeu.J1.sprite = opt.sprite; //choix de l'apparence du joueur
        genTerrain(&jeu,(jeu.nbCaseX*jeu.nbCaseY)/3); //creation du terrain
        genObjet(&jeu);
        genDepartArrivee(&jeu);
        anciennePosition[0] = jeu.J1.position[0];
        anciennePosition[1] = jeu.J1.position[1];
        jeu.J1.orientation = bas;
        do{
            dplJoueur[0] = jeu.J1.position[0] - anciennePosition[0];
            dplJoueur[1] = jeu.J1.position[1] - anciennePosition[1];

            /**Affichage*/
            afficher(ecran, &jeu, dplJoueur, 500);

            anciennePosition[0] = jeu.J1.position[0];
            anciennePosition[1] = jeu.J1.position[1];

            choix = gestionEvent(ecran, &jeu, &opt);

            /**Déplacement du joueur*/

        }while(choix!=quitter && choix!=rejouer); //&& game->J1.score[0] < nbRessource //ttes les ressources sont ramassees //fin de partie

        if (choix!=quitter && choix!=rejouer){choix = gestionMenu(ecran, &jeu);} //fin de partie: voulez vous rejouer
        free_Jeu(&jeu); //désallocation
    }while (choix!=quitter); //rejouer

    SDL_Quit(); //Arrêt de la SDL


    //liberation memoire
    free(boutons);
    boutons = NULL;

    return 0;
}

