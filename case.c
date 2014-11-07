#include <string.h>

enum Type{
	libre, infranchissable // ,etc...
};

struct Case { // Majuscule ! sinon c'est la merde !
std::string image; // Addr image
Type type; //
// Case*[4] entourage; // Plus facile pour l'algo ! (gauche-droite-haut-bas)
}; // Pour �viter d'�crire toujours "struct _Case" !
