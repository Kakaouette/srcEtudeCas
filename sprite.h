#ifndef SPRITE_H
#define SPRITE_H

#include <SDL_image.h>

/**
 * \struct Sprite
 * \brief Toutes les données necessaire pour une image
 *
 * pathName: le chemin de limage
 * clip: la partie de limage quon veut
 * nbImageAnim: le nombre dimage pour un charset animé
 * image: limage chargé
 */
typedef struct Sprite{
    char* pathName;//SDL_Surface *charset; //ou :char* pathName;
    SDL_Rect clip;
    char nbImageAnim;
    SDL_Surface *image;
}Sprite;

#endif // SPRITE_H
