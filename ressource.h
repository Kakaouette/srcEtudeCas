#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <SDL_image.h>


typedef struct Ressource{
    SDL_Rect* image;
    /// int valeur;
    char vue;
    char pass;
    char rendu;
    char position[2];
}Ressource;


#endif // RESSOURCE_H
