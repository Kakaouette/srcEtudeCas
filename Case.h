#ifndef CASE_H
#define CASE_H

#include <SDL_image.h>

typedef struct Case{
        /*Case(string image, char type, char depart, char arrivee, ressource* ressource):
        image(image), type(type), depart(depart), arrivee(arrivee), ressource(&ressource){};*/

        //string image;
        SDL_Rect* image;
        char type;
        char depart;
        char arrivee;
        //ressource *ressource;
}Case;

typedef enum Type{
	libre, infranchissable // perte de ressource, etc...
}Type;

typedef enum imageCase{
    terre,
    herbe
}imageCase;

#endif // CASE_H
