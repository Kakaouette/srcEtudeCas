#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <SDL_image.h>
#include "arrete.h"


typedef struct Ressource{
    Sprite *image;
    /// int valeur;
    char position[2];
}Ressource;


#endif // RESSOURCE_H
