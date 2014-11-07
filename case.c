//#include "Case.h"

#include <stdio.h>
#include <stdlib.h>
#include <SDL_image.h>

typedef struct Case Case;
struct Case{
        /*Case(string image, char type, char depart, char arrivee, ressource* ressource):
        image(image), type(type), depart(depart), arrivee(arrivee), ressource(&ressource){};*/

        //string image;
        SDL_Rect image;
        Type type;
        char depart;
        char arrivee;
        //ressource *ressource;
};

typedef enum Type Type;
enum Type{
	libre, infranchissable // perte de ressource, etc...
};

typedef enum imageCase imageCase;
enum imageCase{
    terre = "",
    herbe = ""
};
