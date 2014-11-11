#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <math.h>

#include "Jeu.h"
#include "Case.h"
#include "ressource.h"
#include "affichage.h"
extern Case cs[NB_CASE_X][NB_CASE_Y];

//declaration des images//Les différentes parties de la feuille de sprites qui vont être blittés
const SDL_Rect perso = {9*SPRITE_WIDTH,12*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};//6,8
const SDL_Rect persoV2 = {0*SPRITE_WIDTH,0*SPRITE_HEIGHT, SPRITE_WIDTH, 48};
const SDL_Rect terre = {11*SPRITE_WIDTH,4*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
const SDL_Rect imgHerbe = {15*SPRITE_WIDTH,1*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
const SDL_Rect gems = {10*SPRITE_WIDTH,9*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};
const SDL_Rect imgArrivee = {4*SPRITE_WIDTH,4*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};//8,13



void afficher(SDL_Surface * ecran, Jeu * game, int nbRessource, char dplJoueur[2]){
    //Les surfaces
    SDL_Surface *charset =  IMG_Load(pathNameTileset); //load le charset//Image/Yoda.png

    //orientation perso
    SDL_Rect clip = *game->J1.image;
    if(dplJoueur[0]!=0){//1:d:+2, -1:g:+1
        game->J1.orientation = (1+dplJoueur[0])/2+1;
    }else if(dplJoueur[1]!=0){//1:b:0, -1:h:3
        game->J1.orientation = (1-dplJoueur[1])*2/3;
    }
    clip.y = clip.y + game->J1.orientation*SPRITE_HEIGHT; //SPRITE_HEIGHT remplacer par taille dun sprite dans limage(modulable)

    char y;
    int tempsActuel, tempsPrecedent;
    SDL_Event event;
    /**On applique les sprites sur l'écran*/
    int nbImageAnim = 3;
    for (y=1; y<=nbImageAnim; y++){
        /**affichage map*/
        afficherMap(ecran, game->map);
        /**affichage ressources*/
        afficherRessources(ecran, game->ressources, nbRessource);
        /**affichage perso*/
        //changement clip
        if (dplJoueur[0]!=0 || dplJoueur[1]!=0){
            clip.x = game->J1.image->x+y*SPRITE_WIDTH;
            if(y==nbImageAnim){clip.x = game->J1.image->x;}
        }
        apply_surface((game->J1.position[0]*nbImageAnim+dplJoueur[0]*(y-nbImageAnim))*SPRITE_WIDTH/nbImageAnim, (game->J1.position[1]*nbImageAnim+dplJoueur[1]*(y-nbImageAnim))*SPRITE_HEIGHT/nbImageAnim-game->J1.image->h+SPRITE_HEIGHT, charset, ecran, &clip);
        /**affichage score*/
        afficherScore(ecran, game);

        SDL_Flip(ecran); // Mise à jour de l'écran
        tempsPrecedent = SDL_GetTicks();
        do{
                SDL_PollEvent(&event);
                tempsActuel = SDL_GetTicks();
        }while(tempsActuel - tempsPrecedent < 500/nbImageAnim); //dpl fini en 500 ms
    }

    SDL_Flip(ecran); // Mise à jour de l'écran

    SDL_FreeSurface(charset); // On libère la surface
}
void afficherMap(SDL_Surface * ecran, Case** (*map)){
    TTF_Init(); //Démarrage de SDL_ttf
    SDL_Surface *textures =  IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png"); //load le tileset
    SDL_Color white = {255,255,255};
    TTF_Font *police = TTF_OpenFont("Fonts/OCRAStd.otf", 20); //Charger la police
    SDL_Surface* texte;
    char y,x;
    for (y=0;y<NB_CASE_Y;y++){
        for (x=0;x<NB_CASE_X;x++){
            if (map[x][y]->type == libre){
                map[x][y]->image = &terre;
            }else if (map[x][y]->type == infranchissable){
                map[x][y]->image = &imgHerbe;
            }
            apply_surface(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, textures, ecran, map[x][y]->image); //0->(SCREEN_WIDTH/SPRITE_WIDTH)-1
            /**affichage case d'arrivee*/
            if(map[x][y]->arrivee == pow(2,0)){
                apply_surface(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, textures, ecran, &imgArrivee);
                rectangle(x*SPRITE_WIDTH,y*SPRITE_HEIGHT,SPRITE_WIDTH, SPRITE_HEIGHT, white, ecran); //contour de la case
                texte = TTF_RenderText_Blended(police, "A", white);
                apply_surface(x*SPRITE_WIDTH, y*SPRITE_HEIGHT, texte, ecran, NULL);
            }
        }
    }
    TTF_CloseFont(police); //Fermer la police
    SDL_FreeSurface(texte); // On libère la surface
    TTF_Quit(); //Arrêt de SDL_ttf
    SDL_FreeSurface(textures); // On libère la surface
}
void afficherScore(SDL_Surface * ecran, Jeu * game){
    TTF_Init(); //Démarrage de SDL_ttf
    TTF_Font *police = TTF_OpenFont("Fonts/OCRAStd.otf", 20); //Charger la policevoid
    SDL_Color black = {0,0,0};
    SDL_Color white = {255,255,255};
    //TTF_SetFontOutline(police, 1);
    SDL_Surface* texte;
    char affichageScore[20] = "Score";
    //if (joueur.length>1){sprintf(affichageScore, "%s J%d", affichageScore, numJoueur);} //ajout du char joueur
    int score = 0;
    sprintf(affichageScore, "%s: %d", affichageScore,score); //ajout du char score
    texte = TTF_RenderText_Blended(police, affichageScore, white);
    apply_surface(SPRITE_WIDTH/4, SPRITE_HEIGHT/4, texte, ecran, NULL);
    TTF_CloseFont(police); //Fermer la police
    SDL_FreeSurface(texte); // On libère la surface
    TTF_Quit(); //Arrêt de SDL_ttf
}
void afficherRessources(SDL_Surface * ecran, Ressource* (*ressources), int nbRessource){
    SDL_Surface *textures =  IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png"); //load le tileset
    int x;
    for (x=0;x<nbRessource;x++){//sizeof(ressources)/sizeof(ressources[0])
        apply_surface(ressources[x]->position[0]*SPRITE_WIDTH, ressources[x]->position[1]*SPRITE_HEIGHT, textures, ecran, ressources[x]->image);
    }
    SDL_FreeSurface(textures); // On libère la surface
}

void afficherMenuRejouer(SDL_Surface * ecran){
    SDL_Color white = {255,255,255};
    int popWidth = 32*4;
    int popHeight = 32*3/2;
    int marge = 32/4;

    SDL_Surface* texte;
    SDL_Surface *popup = SDL_CreateRGBSurface(SDL_HWSURFACE, popWidth, popHeight, 32, 0, 0, 0, 0);
    rectangle(0,0,popup->w, popup->h, white, popup); //contour de la case
    TTF_Init(); //Démarrage de SDL_ttf
    TTF_Font *police = TTF_OpenFont("Fonts/OCRAStd.otf", 20); //Charger la police
    texte = TTF_RenderText_Blended(police, "Rejouer", white);
    apply_surface(popup->w/2-texte->w/2, popup->h/2-texte->h/2, texte, popup, NULL);
    apply_surface(ecran->w/2-(popup->w*2+marge)/2, ecran->h/2-popup->h/2, popup, ecran, NULL);

    popup = SDL_CreateRGBSurface(SDL_HWSURFACE, popWidth, popHeight, 32, 0, 0, 0, 0);
    rectangle(0,0,popup->w, popup->h, white, popup); //contour de la case
    texte = TTF_RenderText_Blended(police, "Quitter", white);
    apply_surface(popup->w/2-texte->w/2, popup->h/2-texte->h/2, texte, popup, NULL);
    apply_surface((ecran->w/2-(popup->w*2+marge)/2)+marge+popup->w, ecran->h/2-popup->h/2, popup, ecran, NULL);

    TTF_CloseFont(police); //Fermer la police
    SDL_FreeSurface(texte); // On libère la surface
    SDL_FreeSurface(popup); // On libère la surface
    TTF_Quit(); //Arrêt de SDL_ttf

    SDL_Flip(ecran); // Mise à jour de l'écran

}
char gestionMenu(SDL_Surface * ecran, Jeu * game, int nbRessource){
    char dplJoueur[2];
    char choix = 0;
    SDL_Event event;
        do{SDL_WaitEvent(&event);
            choix=0;
            if (event.type == SDL_KEYDOWN){
                if (event.key.keysym.sym == SDLK_ESCAPE){
                    afficherMenuRejouer(ecran);
                        do{SDL_WaitEvent(&event);
                            switch(event.type)
                            {
                                case SDL_KEYDOWN:
                                    switch (event.key.keysym.sym)
                                    {
                                        case SDLK_ESCAPE: // Appui sur la touche Echap
                                            choix = 4;
                                            break;
                                    }
                                    break;
                                case SDL_MOUSEBUTTONUP:
                                    if (event.button.button == SDL_BUTTON_LEFT){
                                        if(event.button.x>=ecran->w/2-(32*4*2+32/4)/2 && event.button.x<=ecran->w/2-(32*4*2+32/4)/2+32*4 && event.button.y>=ecran->h/2-32*3/2/2 && event.button.y<=ecran->h/2-32*3/2/2+32*3/2){
                                            choix = 3;
                                        }else if(event.button.x>=(ecran->w/2-(32*4*2+32/4)/2)+32/4+32*4 && event.button.x<=(ecran->w/2-(32*4*2+32/4)/2)+32/4+32*4+32*4 && event.button.y>=ecran->h/2-32*3/2/2 && event.button.y<=ecran->h/2-32*3/2/2+32*3/2){
                                            choix = 1;
                                        }
                                    }
                                    break;
                            }
                        }while(choix!=4 && choix!=1 && choix!=3);
                        if(choix!=3){dplJoueur[0] = 0;dplJoueur[1] = 0;afficher(ecran, game, nbRessource, dplJoueur);}

                }else if(event.key.keysym.sym == SDLK_r){choix = 3;}else{choix = 2;} //key autre que escape
            }else if (event.type == SDL_QUIT){choix = 1;} //fermer
        }while(choix!=1 && choix!=2 && choix!=3);

        //temporisation
        /*tempsPrecedent = SDL_GetTicks();
        do{
            SDL_PollEvent(&event);
            tempsActuel = SDL_GetTicks();
        }while(tempsActuel - tempsPrecedent < 1000); // Si 1000 ms au moins se sont écoulées*/
        return choix;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination, SDL_Rect* clip ){
    SDL_Rect offset;

    offset.x = x;
    offset.y = y;

    //On blitte la surface
    SDL_BlitSurface( source, clip, destination, &offset );
}


void genTerrain(int nbCaseLibreVoulu, Case** (*map)){
    int nbCaseTake = 0;

    char i,j;

    for (i=0; i<20; i++){
        for (j=0; j<15; j++){
            //initialisation
            map[i][j]->depart = 0;
            map[i][j]->arrivee = 0;
            map[i][j]->type = infranchissable; //rendre la case infranchissable
        }
    }
    //generation chemin coherent
    //case de depart au hasard
	char dX = rand_a_b(0,20);
	char dY = rand_a_b(0,15);
	map[dX][dY]->type = libre; //rendre la case libre
    nbCaseTake ++;

        char xx,yy,nb, nbAnc;
    do{//take une case autour au hasard
        do{
        nb=0;
        for (xx = -1; xx <= 1; xx++) {
			yy = abs(xx)-1;
			if (((dX + xx)>=0) && ((dX + xx)<20) && ((dY + yy)>=0) && ((dY + yy)<15)) {
			    if(map[dX + xx][dY + yy]->type != libre){
                    nb++;
			    }
			}
			yy = 1 - abs(xx);
			if (yy != abs(xx)-1 && (dX + xx)>=0 && (dX + xx)<20 && (dY + yy)>=0 && (dY + yy)<15) {
			    if(map[dX + xx][dY + yy]->type != libre){
                    nb++;
			    }
			}
		}
        nbAnc = nb;
		if(nbAnc == 0){
            do{
                dX = rand_a_b(0,20);
                dY = rand_a_b(0,15);

            }while(map[dX][dY]->type != libre);
		}
        }while(nbAnc == 0);

        char q[nbAnc][2];
        //case valide a coté de la case depart
        for ( xx = -1; xx <= 1; xx++) {
			yy = abs(xx)-1;
			if ((dX + xx)>=0 && (dX + xx)<20 && (dY + yy)>=0 && (dY + yy)<15) {
			    if(map[dX + xx][dY + yy]->type != libre){

			    nb--;
			    q[nb][0] = dX + xx;
			    q[nb][1] = dY + yy;
			    }
			}
			yy = 1 - abs(xx);
			if (yy != abs(xx)-1 && (dX + xx)>=0 && (dX + xx)<20 && (dY + yy)>=0 && (dY + yy)<15) {
			    if(map[dX + xx][dY + yy]->type != libre){

			    nb--;
			    q[nb][0] = dX + xx;
			    q[nb][1] = dY + yy;
			    }
			}
		}

        char index = rand_a_b(0,nbAnc);
        dX = q[index][0];
        dY = q[index][1];
        map[dX][dY]->type = libre; //rendre la case libre
        nbCaseTake ++;
    }while(nbCaseTake < nbCaseLibreVoulu); //nb de case accessible voulu
}
void genDepartArrivee(Jeu * game){

    char depart = 0, arrivee = 0; //bool existe pas en c, c dla merde

    char	dX, dY;
    do{
        //case au hasard
        dX = rand_a_b(0,NB_CASE_X);
        dY = rand_a_b(0,NB_CASE_Y);

        if (game->map[dX][dY]->type == libre){ //si case libre
            if (depart == 0){
                game->map[dX][dY]->depart = pow(2,0);

                game->J1.depart[0] = dX;
                game->J1.depart[1] = dY;
                game->J1.position[0] = dX;
                game->J1.position[1] = dY;
                depart = 1;
            }else{
                game->map[dX][dY]->arrivee = pow(2,0);
                game->J1.arrivee[0] = dX;
                game->J1.arrivee[1] = dY;
                arrivee = 1;
            }
        }
    }while(depart == 0 || arrivee == 0);
}
void genObjet(int nbRessourceVoulu, Jeu * game){
    int nbCaseTake = 0;

    char x,y;

    while(nbCaseTake < nbRessourceVoulu){
        do{
            x= rand_a_b(0,NB_CASE_X);
            y= rand_a_b(0,NB_CASE_Y);
        }while(game->map[x][y]->type != libre);
        //game->ressources[nbCaseTake]->image = &gems; //bug, naffiche rien
        game->ressources[nbCaseTake]->position[0]=x;
        game->ressources[nbCaseTake]->position[1]=y;
        nbCaseTake++;
    }//pb pas de verif si case deja une ressource
}


//Random
int rand_a_b(int a, int b){
    return rand() % (b - a) + a;
}
int* init_sans_doublons(int a, int b){
	int taille = b-a;
	int* resultat=malloc((taille)*sizeof (int));
	int i=0;
	// On remplit le tableau de manière à ce qu'il soit trié
	for(i = 0; i< taille; i++){
		resultat[i]=i+a;
	}
	return resultat;
}
void melanger(int* tableau, int taille){
	int i=0;
	int nombre_tire=0;
	int temp=0;

	for(i = 0; i< taille;i++){
		nombre_tire=rand_a_b(0,taille);
		// On échange les contenus des cases i et nombre_tire
		temp = tableau[i];
		tableau[i] = tableau[nombre_tire];
		tableau[nombre_tire]=temp;
	}
}

//Dessin
void ligneHorizontale(int x, int y, int width, Uint32 couleur, SDL_Surface* surface){
  SDL_Rect rectTemp = {x,y,width,1};
  SDL_FillRect(surface, &rectTemp, couleur);
}
void ligneVerticale(int x, int y, int height, Uint32 couleur, SDL_Surface* surface){
  SDL_Rect rectTemp = {x,y,1,height};
  SDL_FillRect(surface, &rectTemp, couleur);
}
void rectangle(int x, int y, int width, int height, Uint32 couleur, SDL_Surface* surface){
  ligneHorizontale(x, y, width, couleur, surface);
  ligneHorizontale(x, y + height - 1, width, couleur, surface);
  ligneVerticale(x, y + 1, height - 2, couleur, surface);
  ligneVerticale(x + width - 1, y + 1, height - 2, couleur, surface);
}
