#ifndef CASE_H
#define CASE_H

#include <SDL_image.h>
#include "sprite.h"

typedef struct Case{
        SDL_Rect *image;
        char type;
}Case;

typedef enum Type{//passer type de case quon veut au generateur: genMap([3,10],...) -> 3 case libre et 10 infranchisable (faire corespondance avec lenum type
	libre,
	infranchissable
	// perte de ressource, etc...
}Type;


#endif // CASE_H
