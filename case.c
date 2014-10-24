

enum Type{
	libre, infranchissable // perte de ressource, etc...
};

struct Case { // Majuscule ! sinon c'est la merde !
string image; // Addr image
Type type; //
// Case*[4] entourage; // Plus facile pour l'algo ! (gauche-droite-haut-bas)
}Case; // Pour éviter d'écrire toujours "struct _Case" !
