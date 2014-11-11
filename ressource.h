#ifndef RESSOURCE_H
#define RESSOURCE_H

#include <SDL_image.h>


typedef struct Ressource{
    SDL_Rect* image;
    /// int valeur;
    char position[2];//?choisir mettre ressource sur case ou mettre position dans ressource?
    int vue;
    int pass;
    int rendu;
}Ressource;


#endif // RESSOURCE_H
