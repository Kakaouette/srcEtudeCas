#define nombreTypeRessource 1
#define X 0
#define Y 1
#define positionX position[X]
#define positionY position[Y]
#define positionX(x) position[X] = x
#define positionY(y) position[Y] = y

struct joueur{ // Accès à "map" pour accéder aux cases sans garder le truc en fond
int[2] depart;
int[2] arrivee;
string image;
int[2] position;
ressource*[] score;
//int[nombreTypeRessource] score; // 0-banane, 1-fraise, 2-orange, etc... #define fraise 0 // #define ptsFraise 1 (ou 5) ?
/*
// "Constructeur" !
Voir exempleConstructeur.txt
*/
char jouer(); // Un tour
deplacement();
algorithme();
joueur newJoueur();
}joueur;
