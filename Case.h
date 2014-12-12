#ifndef CASE_H
#define CASE_H

#include <SDL_image.h>
#include "sprite.h"

/**
 * \struct Case
 * \brief Toutes les données necessaire pour une case de la carte
 *
 * type: le type de la case (libre, infranchissable...)
 * sprite: limage de la case
 */
typedef struct Case{
        char type;
        Sprite* sprite;
}Case;

/**
 * \enum Type
 * \brief Type d'une case
 */
typedef enum Type{//passer type de case quon veut au generateur: genMap([3,10],...) -> 3 case libre et 10 infranchisable (faire corespondance avec lenum type
	libre,
	infranchissable
	// perte de ressource, etc...
}Type;


#endif // CASE_H
