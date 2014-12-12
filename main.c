#include <stdio.h>
#include <stdlib.h>

#include <SDL.h>
#include <SDL_image.h>

#include "affichage.h"

extern  Sprite araignee; //const//enlevé pour permettre que le load des images ne soit fait quune fois
extern  Sprite squelette;
extern  Sprite farmer;
extern Sprite sprTerre;
extern Sprite sprHerbe;

extern  Case caseHerbe;
extern  Case caseTerre;

SDL_Rect* boutons;

int main(int argc, char *argv[])
{
    boutons = malloc(7 * sizeof(SDL_Rect));//allocation
    /**Déclaration des options de jeu*/
    Option opt;
    opt.nbJoueur = 1;
    opt.sprites = malloc(opt.nbJoueur * sizeof(Sprite));//allocation
    opt.sprites[0] = &araignee;
    opt.nbCaseX = 20;
    opt.nbCaseY = 15;
    opt.nbCaseLibre = (opt.nbCaseX*opt.nbCaseY)/3;
    opt.nbRessource = 0;//3

    /**Déclaration des options d'affichage*/
    OptionDAffichage optAffichage;
    optAffichage.origineMapX = 1;
    optAffichage.origineMapY = 1;
    optAffichage.contourAffichee = 1;
    optAffichage.automatique = 0;

    /**Déclaration des varables*/
    Jeu jeu;
    SDL_Surface *ecran = NULL; //screen

    //attributs de l'écran
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    const int SCREEN_BPP = 32;

    char choix = choixNull;


    srand(time(NULL)); // initialisation de rand
    SDL_Init(SDL_INIT_VIDEO);

    /**Pré-load des images*/
    araignee.image = IMG_Load(araignee.pathName);
    squelette.image = IMG_Load(squelette.pathName);
    farmer.image = IMG_Load(farmer.pathName);
    sprHerbe.image = IMG_Load(sprHerbe.pathName);
    sprTerre.image = IMG_Load(sprTerre.pathName);
    /**Load des sprites*/
    caseHerbe.sprite = &sprHerbe;
    caseTerre.sprite = &sprTerre;

    do{
        optAffichage.automatique = 0;
        /**Initialisation de la fenetre*/
        SCREEN_WIDTH = (opt.nbCaseX + 2*optAffichage.origineMapX)*SPRITE_WIDTH;
        SCREEN_HEIGHT = (opt.nbCaseY + 2*optAffichage.origineMapY)*SPRITE_HEIGHT;
        SDL_WM_SetCaption("La cueillette", NULL); //titre de la fenetre
        SDL_WM_SetIcon(IMG_Load("Image/sac.png"), NULL); //icone de la fenetre
        ecran = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_HWSURFACE); //afficher fenetre
        SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre
        /**Initialisation du jeu*/
        new_Game(&jeu, &opt);// allocation + initialisation
        genTerrain(&jeu,opt.nbCaseLibre); //creation du terrain
        genObjet(&jeu);
        genDepartArrivee(&jeu);


        char* anciennesPositions = malloc(2*jeu.nbPlayer * sizeof(char));
        int i=0;
        Arrete** *arretes = malloc(jeu.nbPlayer*sizeof(Arrete**));
        int* compteurArrete=malloc(jeu.nbPlayer*sizeof(int));;
        for (i=0 ; i < jeu.nbPlayer ; i++){
            arretes[i] = malloc((jeu.nbRessource + 1) * sizeof(Arrete*));
        }
        int cases[2] = {jeu.nbCaseX, jeu.nbCaseY};
        for (i=0; i<jeu.nbPlayer; i++){
            anciennesPositions[0+i*2] = jeu.players[i]->position[0];
            anciennesPositions[1+i*2] = jeu.players[i]->position[1];
            compteurArrete[i]=0;
            arretes[i] = algorithmeChemin(jeu.players[i], jeu.ressources, jeu.nbRessource, jeu.map, cases);
        }

        /**Affichage du jeu de départ*/
        affichageInitial(&optAffichage, ecran, &jeu);

        int nbArrete = jeu.nbRessource + 1;

        do{
            if(i+1<jeu.nbPlayer){i++;}else{i=0;}
            choix = gestionEvent(&optAffichage, ecran, &jeu, jeu.players[i], &opt);
            if (choix == play || choix == choixNull){
                jeu.nbTourPassee++;
                if (compteurArrete[i] < nbArrete){
                    char result = jouerTour(&jeu, jeu.players[i], arretes[i][compteurArrete[i]]);
                    if (result == 'F'){compteurArrete[i]++;}
                }
                ///Affichage///
                char anciennePosition[2] = {anciennesPositions[0+i*2], anciennesPositions[1+i*2]};
                afficherDpl(&optAffichage, ecran, &jeu, jeu.players[i], anciennePosition, 250);

                anciennesPositions[0+i*2] = jeu.players[i]->position[0];
                anciennesPositions[1+i*2] = jeu.players[i]->position[1];

                if (jeu.players[i]->position[0] == jeu.players[i]->arrivee[0]
                    && jeu.players[i]->position[1] == jeu.players[i]->arrivee[1] && jeu.nbRessource == 0){ //ttes les ressources sont ramassees
                    choix = victoire;
                }
            }
        }while(choix!=quitter && choix!=rejouer && choix!=victoire); //fin de partie

        if (choix==victoire){
            SDL_Color gold = {255,215,0};
            char affichageVictory[13] = "Victoire!";
            if (jeu.nbPlayer>1){sprintf(affichageVictory, "Victoire J%d!", i+1);} //ajout du char joueur
            apply_text(ecran->w/2-96, 128, affichageVictory, ecran, "Fonts/OCRAStd.otf", 32, gold);

            choix = gestionMenu(&optAffichage, ecran, &jeu, &opt);
        } //fin de partie: voulez vous rejouer

        free_Jeu(&jeu); //désallocation
    }while (choix!=quitter); //rejouer

    SDL_Quit(); //Arrêt de la SDL


    // On libère les surface
    SDL_FreeSurface(araignee.image);
    SDL_FreeSurface(squelette.image);
    SDL_FreeSurface(farmer.image);
    SDL_FreeSurface(sprHerbe.image);
    SDL_FreeSurface(sprTerre.image);

    //liberation memoire
    free(opt.sprites);
    opt.sprites = NULL;
    free(boutons);
    boutons = NULL;

    return 0;
}

