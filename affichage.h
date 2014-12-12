#ifndef AFFICHAGE_H
#define AFFICHAGE_H


#include <SDL_image.h>
#include "jeu.h"

//attributs de la feuille de sprites
#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT  32

#define pathNameTileset  "Tiny32-Complete-Spritesheet-Repack3.png"


typedef enum fctMenu{
    choixNull,
    quitter,
    play,
    rejouer,
    quitterMenuRejouer,
    victoire,
    automatique
}fctMenu;
/*
    //attributs de la feuille de sprites
    const int SHEET_WIDTH = charset->w, SHEET_HEIGHT = charset->h;
    //nombre dimage: 512/32=16, 16*16
    int SPRITE_WIDTH=clip.w;
    int SPRITE_HEIGHT=clip.h;
*/

typedef struct OptionDAffichage{
    int origineMapX;
    int origineMapY;
    char contourAffichee;
    char automatique;
}OptionDAffichage;
//add contour (monde flottant): origine 1,1 /monde continu: origine 0,0


//Prototype affichage
void affichageInitial(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game);
void afficherDpl(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Joueur* player, char anciennePosition[2], int vitesse);
void afficher(SDL_Surface *ecran, Jeu *game, char anciennePosition[2], int vitesse);
void afficherMap(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game);
void afficherCase(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, int x, int y);
void afficherScore(SDL_Surface *ecran, Jeu *game);
void afficherRessources(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game);

void afficherContourMap(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game);

SDL_Rect* afficherMenuRejouer(SDL_Surface * ecran);
SDL_Rect* afficherMenuOption(SDL_Surface *ecran, Option *opt, int joueurSelect);

//Prototype gestion des menu
char gestionEvent(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Joueur* player, Option *opt);
char gestionMenu(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Option *opt);
void gestionMenuOption(SDL_Surface *ecran, Option *opt);
int gestionTextBox(int value, SDL_Surface* ecran, SDL_Rect zone, int limite);

//Prototype dessin
void ligneHorizontale(int x, int y, int width, Uint32 couleur, SDL_Surface *surface);
void ligneVerticale(int x, int y, int height, Uint32 couleur, SDL_Surface *surface);
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip );
void apply_text(int x, int y, char* txt, SDL_Surface *destination, char* filePolice, int taille, SDL_Color couleur);

#endif // AFFICHAGE_H
