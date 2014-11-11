#ifndef AFFICHAGE_H
#define AFFICHAGE_H


#include <SDL_image.h>

//attributs de la feuille de sprites
#define SPRITE_WIDTH  32
#define SPRITE_HEIGHT  32

#define pathNameTileset  "Tiny32-Complete-Spritesheet-Repack3.png"
#define pathNameCharset  "Image/143-Farmer01-inaka.png"
#define pathNameCharsetYoda  "Image/Yoda.png"


typedef struct Sprite{
    SDL_Surface *charset; //ou :char* pathName;
    SDL_Rect* clip;
    char nbImageAnim;
}Sprite;

/*
    //attributs de la feuille de sprites
    const int SHEET_WIDTH = charset->w, SHEET_HEIGHT = charset->h;
    //nombre dimage: 512/32=16, 16*16
    int SPRITE_WIDTH=clip.w;
    int SPRITE_HEIGHT=clip.h;

    SDL_Surface *charset =  IMG_Load(pathNameCharset);
    SDL_Rect* clip = {0,0,charset.w/4,charset.h/4};
    Sprite perso = {charset, clip, 4}
    clip = {0,0,charset.w/perso.nbImageAnim,charset.h/4};

    SDL_Surface *tileset =  IMG_Load(pathNameTileset);
    SDL_Rect* clip = {15,1,SPRITE_WIDTH,SPRITE_HEIGHT};
    Sprite imgHerbe = {tileset, clip, 1}*/



/*//Image de case
const SDL_Rect herbe = {15*SPRITE_WIDTH,1*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
const SDL_Rect terre = {11*SPRITE_WIDTH,4*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};*/



#endif // AFFICHAGE_H
