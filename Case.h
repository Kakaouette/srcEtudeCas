#ifndef CASE_H
#define CASE_H

#include <SDL_image.h>
#include "ressource.h"
SDL_Rect decoupage(int x, int y);

typedef struct Case{
        //string image;
        SDL_Rect* image;
        char type;
        char depart;
        char arrivee;
        Ressource *ressource;
}Case;

typedef enum Type{
	libre, infranchissable // perte de ressource, etc...
}Type;

typedef enum imageCase{
    terre,
    herbe
}imageCase;

    /*SDL_Rect imgHerbe = decoupage(15, 1);
    Case caseHerbe;
    caseHerbe.depart = 0;
    caseHerbe.arrivee = 0;
    caseHerbe.image = &imgHerbe;
    caseHerbe.type = infranchissable;*/

#endif // CASE_H
