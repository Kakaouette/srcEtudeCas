

enum Type{
	libre, infranchissable // ,etc... (perte de ressource)
};

struct Case { // Majuscule ! sinon c'est la merde !
string image; // Addr image
Type type; //
// Case*[4] entourage; // Plus facile pour l'algo ! (gauche-droite-haut-bas)
}Case; // Pour éviter d'écrire toujours "struct _Case" !
