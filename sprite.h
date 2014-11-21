#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_image.h>

typedef struct Sprite{
    char* pathName;//SDL_Surface *charset; //ou :char* pathName;
    SDL_Rect clip;
    char nbImageAnim;
}Sprite;

#endif // SPRITE_H
