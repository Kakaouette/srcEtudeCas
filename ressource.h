#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <SDL_image.h>

typedef struct Ressource{
    SDL_Rect* image;
    /// int valeur;
    int position[2];
    int vue;
    int pass;
    int rendu;
}Ressource;


#endif // RESSOURCE_H
