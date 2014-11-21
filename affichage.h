#ifndef AFFICHAGE_H
#define AFFICHAGE_H

#include "jeu.h"
#include <SDL_image.h>

//attributs de la feuille de sprites
#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT  32

#define pathNameTileset  "Tiny32-Complete-Spritesheet-Repack3.png"


typedef enum fctMenu{
    choixNull,
    quitter,
    play,
    rejouer,
    quitterMenuRejouer
}fctMenu;
/*
    //attributs de la feuille de sprites
    const int SHEET_WIDTH = charset->w, SHEET_HEIGHT = charset->h;
    //nombre dimage: 512/32=16, 16*16
    int SPRITE_WIDTH=clip.w;
    int SPRITE_HEIGHT=clip.h;
*/



SDL_Rect* afficherMenuRejouer(SDL_Surface * ecran);

int gestionTextBox(int value, SDL_Surface* ecran, SDL_Rect zone);


//Prototype dessin
void ligneHorizontale(int x, int y, int width, Uint32 couleur, SDL_Surface *surface);
void ligneVerticale(int x, int y, int height, Uint32 couleur, SDL_Surface *surface);
void apply_surface( int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip );
void apply_text(int x, int y, char* txt, SDL_Surface *destination, char* filePolice, int taille, SDL_Color couleur);

#endif // AFFICHAGE_H
