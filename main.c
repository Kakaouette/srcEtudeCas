#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "Jeu.h"
#include "affichage.h"

SDL_Rect decoupage(int x, int y);
extern const SDL_Rect perso;
extern const SDL_Rect persoV2;
extern const SDL_Rect gems;

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
    new_Game(&jeu);// allocation + initialisation

    int nbRessource = 3, j;
    Ressource r[nbRessource];
    jeu.ressources = malloc(nbRessource* sizeof(Ressource));//allocation
    //initialisation
    for (j=0; j<nbRessource;j++){
        jeu.ressources[j] = &r[j];
        jeu.ressources[j]->image = &gems;
    }

    char choix = 0;
    SDL_Event event;
    int tempsActuel, tempsPrecedent;
    char anciennePosition[2], dplJoueur[2];

    do{
        /**Initialisation*/
        jeu.J1.image = &perso; //choix du joueur//peut etre different a chaque partie
        genTerrain((NB_CASE_X*NB_CASE_Y)/3,jeu.map); //creation du terrain
        genObjet(nbRessource, &jeu);
        genDepartArrivee(&jeu);
        anciennePosition[0] = jeu.J1.position[0];
        anciennePosition[1] = jeu.J1.position[1];
        jeu.J1.orientation = bas;
        do{
            dplJoueur[0] = jeu.J1.position[0] - anciennePosition[0];
            dplJoueur[1] = jeu.J1.position[1] - anciennePosition[1];

            /**Affichage*/
            afficher(ecran, &jeu, nbRessource, dplJoueur);

            anciennePosition[0] = jeu.J1.position[0];
            anciennePosition[1] = jeu.J1.position[1];

            choix = gestionMenu(ecran, &jeu, nbRessource);

            //dpl joueur
            jeu.J1.position[0] = jeu.J1.position[0]+1;
        }while(choix!=1 && choix!=3); //&& game->J1.score[0] < nbRessource //ttes les ressources sont ramassees //fin de partie
    }while (choix!=1); //rejouer

    free_Jeu(&jeu); //désallocation
    SDL_Quit(); //Arrêt de la SDL

    return 0;
}

