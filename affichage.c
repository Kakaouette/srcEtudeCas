#include <SDL.h>
#include <SDL_image.h>
#include <time.h>
#include "Case.c"

struct affichage{
affichage(); // appellé pour générer le tout (ajouter argument pour plus d'options)
genTerrain();
genDepartArrivee();
genObjet();
};

void Afficher(SDL_Surface * ecran)
{
    //attributs de la feuille de sprites
    const int SHEET_WIDTH = 512;
    const int SHEET_HEIGHT = 512;
    const int SPRITE_WIDTH = 32;
    const int SPRITE_HEIGHT = 32;
    //nombre dimage: 512/32=16, 16*16

    //attributs de l'écran
    const int SCREEN_WIDTH = 20*SPRITE_WIDTH;//640
    const int SCREEN_HEIGHT = 15*SPRITE_HEIGHT;//480
    const int SCREEN_BPP = 32;

    //Les surfaces
    SDL_Surface *textures = NULL;
    //Les différentes parties de la feuille de sprites qui vont être blittés
    SDL_Rect clip[ 4 ];
    //clipping
    //On coupe la partie en haut à gauche (premier sprite)
    clip[ 0 ].x = 0*SPRITE_WIDTH; //0->15
    clip[ 0 ].y = 0*SPRITE_HEIGHT;
    clip[ 0 ].w = SPRITE_WIDTH;
    clip[ 0 ].h = SPRITE_HEIGHT;

    //herbe
    clip[ 1 ].x = 15*SPRITE_WIDTH;
    clip[ 1 ].y = 1*SPRITE_HEIGHT;
    clip[ 1 ].w = SPRITE_WIDTH;
    clip[ 1 ].h = SPRITE_HEIGHT;

    //gems
    clip[ 3 ].x = 10*SPRITE_WIDTH;
    clip[ 3 ].y = 9*SPRITE_HEIGHT;
    clip[ 3 ].w = SPRITE_WIDTH;
    clip[ 3 ].h = SPRITE_HEIGHT;

    Case c;
    c.image = clip[1];

    textures = IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png"); //load le tileset


    //On applique les sprites sur l'écran
    apply_surface( 0, 0, textures, ecran, &clip[ 0 ] );
    apply_surface( 1*SPRITE_WIDTH, 1*SPRITE_HEIGHT, textures, ecran, &clip[ 3 ] ); //0->(SCREEN_WIDTH/SPRITE_WIDTH)-1
    int i,j;
    //On applique les sprites sur l'écran
    for (i=0;i<SPRITE_WIDTH;i++){
        for (j=0;j<SPRITE_HEIGHT;j++){
            apply_surface( i*SPRITE_WIDTH, j*SPRITE_HEIGHT, textures, ecran, &c.image ); //0->(SCREEN_WIDTH/SPRITE_WIDTH)-1
        }
    }


    SDL_Flip(ecran); // Mise à jour de l'écran

    SDL_FreeSurface(textures); // On libère la surface
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip )//clip = NULL
{
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}

int rand_a_b(int a, int b){
    return rand()%(b-a) +a;
}

genTerrain(){
    int nbCaseLibreVoulu = 10;
    int nbCaseTake = 0;

    //put que d obs
    for (int i=0; i<20; i++){
        for (int j=0; j<15; j++){
            map[i][j]->type = Type.infranchissable; //rendre la case infranchissable
        }
    }

    //generation chemin coherent
    //case de depart au hasard
    srand(time(NULL)); // initialisation de rand
	int	dX = rand_a_b(0,20);
	int	dY = rand_a_b(0,15);
	map[dX][dY]->type = Type.libre //rendre la case libre

    int dX2, dY2

    do
        //take une case autour au hasard
        do
            do
                dX2 = dX + rand_a_b(-1,1);
            while(dX2<0 || dX2>20)
            do
                dY2 = dY + rand_a_b(-1,1);
            while(dY2<0 || dY2>15)
            //while case pas dans terrain
        while(map[dX2][dY2]->type = Type.libre)
        //while case dej take (contain(caseChemin, caseij))
        dX = dX2;
        dY = dY2;
        map[dX][dY]->type = Type.libre //rendre la case libre
        nbCaseTake += 1;
    while(nbCaseTake < nbCaseLibreVoulu) //nb de case accessible voulu

    //pb boucle infini si case sauto bloque
}

genDepartArrivee(){

    bool depart = false;
    bool arrivee = false;

    srand(time(NULL)); // initialisation de rand
    int	dX, dY
    while(depart == false or arrivee == false){
        //case au hasard
        dX = rand_a_b(0,20);
        dY = rand_a_b(0,15);

        if (map[dX][dY]->type == Type.libre){ //si case libre
            if (depart){
                map[dX][dY]->depart = 1;
                depart = true;
            }else{
                map[dX][dY]->arrivee = 1;
                arrivee = true;
            }
        }
    }
}

genObjet(){
    int nbRessourceVoulu = 2
  while(nbRessource pas attein){
    random i 0->50
    random j 0->50
    if (map[i][j] interrain){
      map.ressource(i,j)
    }
  }
}
