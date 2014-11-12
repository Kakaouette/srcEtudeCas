#ifndef CASE_H
#define CASE_H

#include <SDL_image.h>
#include "ressource.h"

typedef struct Case{
        SDL_Rect* image;
        char type;
        Ressource *ressource;//?choisir mettre ressource sur case ou mettre position dans ressource?
}Case;

typedef enum Type{
	libre,
	infranchissable
	// perte de ressource, etc...
}Type;


#endif // CASE_H
