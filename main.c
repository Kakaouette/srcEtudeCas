#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "affichage.h"

extern  Sprite araignee; //const//enlev� pour permettre que le load des images ne soit fait quune fois
extern  Sprite squelette;
extern  Sprite farmer;
extern Sprite sprTerre;
extern Sprite sprHerbe;

extern  Case caseHerbe;
extern  Case caseTerre;

SDL_Rect* boutons;

int main(int argc, char *argv[])
{
    boutons = malloc(6 * sizeof(SDL_Rect));//allocation
    /**D�claration des options de jeu*/
    Option opt;
    opt.sprite = &araignee;
    opt.nbCaseX = 20;
    opt.nbCaseY = 15;
    opt.nbCaseLibre = (opt.nbCaseX*opt.nbCaseY)/3;
    opt.nbRessource = 3;

    /**D�claration des options d'affichage*/
    OptionDAffichage optAffichage;
    optAffichage.origineMapX = 1;
    optAffichage.origineMapY = 1;
    optAffichage.contourAffichee = 1;

    /**D�claration des varables*/
    Jeu jeu;
    SDL_Surface *ecran = NULL; //screen

    //attributs de l'�cran
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    const int SCREEN_BPP = 32;

    char choix = choixNull;
    char anciennePosition[2];


    srand(time(NULL)); // initialisation de rand
    SDL_Init(SDL_INIT_VIDEO);

    /**Pr�-load des images*/
    araignee.image = IMG_Load(araignee.pathName);
    squelette.image = IMG_Load(squelette.pathName);
    farmer.image = IMG_Load(farmer.pathName);
    sprHerbe.image = IMG_Load(sprHerbe.pathName);
    sprTerre.image = IMG_Load(sprTerre.pathName);
    /**Load des sprites*/
    caseHerbe.sprite = &sprHerbe;
    caseTerre.sprite = &sprTerre;

    do{
        /**Initialisation de la fenetre*/
        SCREEN_WIDTH = (opt.nbCaseX + 2*optAffichage.origineMapX)*SPRITE_WIDTH;
        SCREEN_HEIGHT = (opt.nbCaseY + 2*optAffichage.origineMapY)*SPRITE_HEIGHT;
        SDL_WM_SetCaption("La cueillette", NULL); //titre de la fenetre
        SDL_WM_SetIcon(IMG_Load("Image/sac.png"), NULL); //icone de la fenetre
        ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); //afficher fenetre
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre
        /**Initialisation du jeu*/
        new_Game(&jeu, &opt);// allocation + initialisation
        jeu.J1.sprite = opt.sprite; //choix de l'apparence du joueur
        genTerrain(&jeu,opt.nbCaseLibre); //creation du terrain
        genObjet(&jeu);
        genDepartArrivee(&jeu);
        anciennePosition[0] = jeu.J1.position[0];
        anciennePosition[1] = jeu.J1.position[1];
        jeu.J1.orientation = bas;

        /**Affichage du jeu de d�part*/
        affichageInitial(&optAffichage, ecran, &jeu);

        int cases[2] = {jeu.nbCaseX, jeu.nbCaseY};
        Arrete** arretes = algorithmeChemin(&jeu.J1, &jeu.ressources, &jeu.nbRessource, jeu.map, cases);
        int i = 0;

       do{
            choix = gestionEvent(&optAffichage, ecran, &jeu, &opt);
            if (choix == play || choix == choixNull){

                if (i < jeu.nbRessource + 1){
                    char result = jouerTour(&jeu, &jeu.J1, arretes[i]);
                    if (result == 'F'){i++;}
                }

                /**Affichage*/
                afficherDpl(&optAffichage, ecran, &jeu, anciennePosition, 250);

                anciennePosition[0] = jeu.J1.position[0];
                anciennePosition[1] = jeu.J1.position[1];

            }

        if (jeu.J1.position[0] == jeu.J1.arrivee[0]
                    && jeu.J1.position[1] == jeu.J1.arrivee[1]){//&& game->J1.sac[0] == nbRessource || game->nbRessource == 0 //ttes les ressources sont ramassees
                    choix = victoire;
                }

        }while(choix!=quitter && choix!=rejouer && choix!=victoire); //fin de partie

        if (choix==victoire){
            SDL_Color gold = {255,215,0};
            apply_text(ecran->w/2-96, 128, "Victoire!", ecran, "Fonts/OCRAStd.otf", 32, gold);

            choix = gestionMenu(&optAffichage, ecran, &jeu, &opt);
        } //fin de partie: voulez vous rejouer

        free_Jeu(&jeu); //d�sallocation
    }while (choix!=quitter); //rejouer

    SDL_Quit(); //Arr�t de la SDL

    // On lib�re les surface
    SDL_FreeSurface(araignee.image);
    SDL_FreeSurface(squelette.image);
    SDL_FreeSurface(farmer.image);
    SDL_FreeSurface(sprHerbe.image);
    SDL_FreeSurface(sprTerre.image);

    //liberation memoire
    free(boutons);
    boutons = NULL;

    return 0;
}

