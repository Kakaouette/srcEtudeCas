#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <SDL_image.h>
#include "arrete.h"


typedef struct Ressource{
    Sprite *image;
    /// int valeur;
    char vue; // Pour la definition des arretes
    char rendu; // Pour le tri : passe une fois
    char pass; // Pour le tri : passe deux fois (elimine)
    char position[2];
}Ressource;


#endif // RESSOURCE_H
