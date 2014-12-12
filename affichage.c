#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <time.h>
#include <math.h>

#include "affichage.h"

//declaration des images//Les différentes parties de la feuille de sprites qui vont être blittés
Sprite sprTerre = {.pathName = pathNameTileset, .clip = {11*SPRITE_WIDTH,4*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}, .nbImageAnim = 1};
Sprite sprHerbe = {.pathName = pathNameTileset, .clip = {15*SPRITE_WIDTH,1*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}, .nbImageAnim = 1};
const Sprite gems = {.pathName = pathNameTileset, .clip = {10*SPRITE_WIDTH,9*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}, .nbImageAnim = 1};
const SDL_Rect imgArrivee = {4*SPRITE_WIDTH,4*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};//8,13
const SDL_Rect contourMap = {4*SPRITE_WIDTH,5*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT};//4,5//7,7

 Sprite araignee = {.pathName = pathNameTileset,.clip = {9*SPRITE_WIDTH,12*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}, .nbImageAnim = 3};
 Sprite squelette = {.pathName = pathNameTileset,.clip = {6*SPRITE_WIDTH,8*SPRITE_HEIGHT, SPRITE_WIDTH, SPRITE_HEIGHT}, .nbImageAnim = 3};
//{pathNameCharset, 0,0,charset.w/4,charset.h/4,4}
 Sprite farmer = {.pathName = "Image/143-Farmer01-inaka.png", .clip = {0*SPRITE_WIDTH,0*(192/4), SPRITE_WIDTH, (192/4)}, .nbImageAnim = 4};
 Sprite yoda = {.pathName = "Image/Yoda.png", .clip = {0*SPRITE_WIDTH,0*(192/4), SPRITE_WIDTH, (192/4)}, .nbImageAnim = 4};

extern SDL_Rect* boutons;

/**
 * \fn void affichageInitial(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game)
 * \brief affichage complet du jeu
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu qu'on veut afficher
 */
void affichageInitial(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game){
    ///Déclaration des variables///
    int i=0;


    SDL_FillRect(ecran, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre
    ///On applique les sprites sur l'écran///
        ///affichage map///
        afficherMap(optAffichage, ecran, game);
        ///affichage ressources///
        afficherRessources(optAffichage, ecran, game);
        ///affichage perso///
        for (i=0; i<game->nbPlayer; i++){ //pour chaque joueur
            SDL_Surface *charset =  game->players[i]->sprite->image; //IMG_Load(game->J1.sprite->pathName); //load le charset

            //orientation perso
            SDL_Rect clip = game->players[i]->sprite->clip;
            clip.y += game->players[i]->orientation * game->players[i]->sprite->clip.h;
            clip.x = game->players[i]->sprite->clip.x;

            apply_surface((game->players[i]->position[0] + optAffichage->origineMapX)*SPRITE_WIDTH, (game->players[i]->position[1] + optAffichage->origineMapY)*SPRITE_HEIGHT-game->players[i]->sprite->clip.h+SPRITE_HEIGHT, charset, ecran, &clip);
        }
        ///affichage score///
        afficherScore(ecran, game);

        ///affichage monde flottant///
        if (optAffichage->contourAffichee == 1){
            afficherContourMap(optAffichage, ecran, game);
        }

        SDL_Flip(ecran); // Mise à jour de l'écran
}
/**
 * \fn void afficherDpl(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Joueur* player, char anciennePosition[2], int vitesse)
 * \brief affichage du deplacement d'un joueur, la nouvelle position du joueur est donné dans sa structure par le parametre position[2]
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu qu'on veut afficher
 * \param player Le joueur qui se deplace
 * \param anciennePosition[2] La position du joueur avant son deplacement
 * \param vitesse Nombre de milliseconde que la fonction met pour deplacer le joueur
 */
void afficherDpl(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Joueur* player, char anciennePosition[2], int vitesse){
    ///Déclaration des variables///
    SDL_Surface *charset =  player->sprite->image; //IMG_Load(game->J1.sprite->pathName); //load le charset
    char i,x,y;
    int tempsActuel, tempsPrecedent;
    SDL_Event event;

    //orientation perso
    ///Déplacement du joueur///
    char dplJoueur[2];
    dplJoueur[0] = player->position[0] - anciennePosition[0];
    dplJoueur[1] = player->position[1] - anciennePosition[1];

    SDL_Rect clip = player->sprite->clip;
    if(dplJoueur[0]!=0){//1:d:+2, -1:g:+1
        player->orientation = (1+dplJoueur[0])/2+1;
    }else if(dplJoueur[1]!=0){//1:b:0, -1:h:3
        player->orientation = (1-dplJoueur[1])*3/2;
    }
    clip.y += player->orientation * player->sprite->clip.h;

    ///On applique les sprites sur l'écran///
    int nbImageAnim = player->sprite->nbImageAnim;
    for (i=1; i<=nbImageAnim; i++){
        ///affichage map///(clipping)
        for (y=0;y<=player->sprite->clip.h/SPRITE_HEIGHT;y++){//add: arrondir au nb superieur
                for(x=-(player->sprite->clip.w/(2*SPRITE_WIDTH)-1/2);x<=player->sprite->clip.w/(2*SPRITE_WIDTH)-1/2;x++){//add: arrondir au nb superieur
                    afficherCase(optAffichage, ecran, game,  anciennePosition[0]+x, anciennePosition[1]-y);
                    afficherCase(optAffichage, ecran, game,  player->position[0]+x, player->position[1]-y);
                }
        }


        //effacement de laffichage du background precedent//marche uniquement en monde flottant... -> generaliser
        //utilisé pour rafrechir score et img perso qui depasse des case de la map
        SDL_Surface *background = SDL_CreateRGBSurface(SDL_HWSURFACE, ecran->w, SPRITE_HEIGHT, 32, 0, 0, 0, 0);
        SDL_FillRect(background, NULL, SDL_MapRGB(ecran->format, 119, 181, 254)); //couleur de fond de la fenetre
        apply_surface(optAffichage->origineMapX-1, optAffichage->origineMapY-1, background, ecran, NULL);

        ///affichage ressources///
        afficherRessources(optAffichage, ecran, game);
        ///affichage perso///
        //changement clip
        if (dplJoueur[0]!=0 || dplJoueur[1]!=0){
            clip.x = player->sprite->clip.x+i*SPRITE_WIDTH;
            if(i==nbImageAnim){clip.x = player->sprite->clip.x;}
        }
        apply_surface((anciennePosition[0]*nbImageAnim+dplJoueur[0]*i)*SPRITE_WIDTH/nbImageAnim+SPRITE_WIDTH/2-player->sprite->clip.w/2 + optAffichage->origineMapX*SPRITE_WIDTH, (anciennePosition[1]*nbImageAnim+dplJoueur[1]*i)*SPRITE_HEIGHT/nbImageAnim-player->sprite->clip.h+SPRITE_HEIGHT + optAffichage->origineMapY*SPRITE_HEIGHT, charset, ecran, &clip);
        ///affichage score///
        afficherScore(ecran, game);

        SDL_Flip(ecran); // Mise à jour de l'écran

        ///Temporisation///
        tempsPrecedent = SDL_GetTicks();
        do{
            SDL_PollEvent(&event);
            tempsActuel = SDL_GetTicks();
        }while(tempsActuel - tempsPrecedent < vitesse/nbImageAnim); //dpl fini en "vitesse" ms
    }

}

/**
 * \fn void afficherMap(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game)
 * \brief gère l'affichage de la carte du jeu
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu où est la carte qu'on veut afficher
 */
void afficherMap(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game){
    char y,x;
    for (y=0;y<game->nbCaseY;y++){
        for (x=0;x<game->nbCaseX;x++){
            afficherCase(optAffichage, ecran, game, x, y); //ralentissement du au reload de la surface texture
        }
    }
}
/**
 * \fn void afficherCase(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, int x, int y)
 * \brief gère l'affichage d'une case de la carte du jeu celon sa position sur la carte
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu où est la carte qui contient la case qu'on veut afficher
 * \param x Position x de la case sur la carte
 * \param y Position y de la case sur la carte
 */
void afficherCase(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, int x, int y){
    SDL_Surface *textures; //IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png"); //load le tileset
    SDL_Color white = {255,255,255};
    char affichageCase[3]="A";
    if (x>=0 && x<game->nbCaseX && y>=0 && y<game->nbCaseY){ //demande daffichage des cases si elles existe
        textures = game->map[x][y]->sprite->image;

        apply_surface((x + optAffichage->origineMapX)*SPRITE_WIDTH, (y + optAffichage->origineMapY)*SPRITE_HEIGHT, textures, ecran, &game->map[x][y]->sprite->clip); //0->(SCREEN_WIDTH/SPRITE_WIDTH)-1

        /**affichage case d'arrivee*/
        int i;
        for (i=0; i<game->nbPlayer; i++){ //multi joueur
            if(game->players[i]->arrivee[0] == x && game->players[i]->arrivee[1] == y){
                textures = IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png");
                apply_surface((x + optAffichage->origineMapX)*SPRITE_WIDTH, (y + optAffichage->origineMapY)*SPRITE_HEIGHT, textures, ecran, &imgArrivee);
                rectangle((x + optAffichage->origineMapX)*SPRITE_WIDTH,(y + optAffichage->origineMapY)*SPRITE_HEIGHT,SPRITE_WIDTH, SPRITE_HEIGHT, white, ecran); //contour de la case
                if (game->nbPlayer>1){sprintf(affichageCase, "%s%d", affichageCase, i+1);} //ajout du char joueur
                apply_text((x + optAffichage->origineMapX)*SPRITE_WIDTH, (y + optAffichage->origineMapY)*SPRITE_HEIGHT, affichageCase, ecran, "Fonts/OCRAStd.otf", 20, white);
                SDL_FreeSurface(textures); // On libère la surface
            }
        }
    }
}
/**
 * \fn void afficherScore(SDL_Surface *ecran, Jeu *game)
 * \brief gère l'affichage du score
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu où est le joueur dont on veut afficher le score
 */
void afficherScore(SDL_Surface *ecran, Jeu *game){
    SDL_Color white = {255,255,255};
    int i;
    for (i=0; i<game->nbPlayer; i++){ //multi joueur
        char affichageScore[20] = "Score";
        if (game->nbPlayer>1){sprintf(affichageScore, "%s J%d", affichageScore, i+1);} //ajout du char joueur
        int score = game->players[i]->sac[0];
        sprintf(affichageScore, "%s: %d", affichageScore,score); //ajout du char score
        apply_text(SPRITE_WIDTH/4 + i*(32 + 192), SPRITE_HEIGHT/4, affichageScore, ecran, "Fonts/OCRAStd.otf", 20, white);
    }
}
/**
 * \fn void afficherRessources(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game)
 * \brief gère l'affichage des ressources
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu où sont les ressources qu'on veut afficher
 */
void afficherRessources(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game){
    SDL_Surface *textures; //load le tileset;
    int i;
    for (i=0; i < game->nbRessource; i++){
        if (game->ressources[i] !=NULL){
            textures =  IMG_Load(game->ressources[i]->image->pathName); //load le tileset
            apply_surface((game->ressources[i]->position[0] + optAffichage->origineMapX)*SPRITE_WIDTH, (game->ressources[i]->position[1] + optAffichage->origineMapY)*SPRITE_HEIGHT, textures, ecran, &game->ressources[i]->image->clip);
            SDL_FreeSurface(textures); //On libère la surface
        }
   }
}

/**
 * \fn void afficherContourMap(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game)
 * \brief affiche le contour de la carte
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu qu'on veut afficher
 */
void afficherContourMap(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game){
    SDL_Surface *textures =  IMG_Load("Tiny32-Complete-Spritesheet-Repack3.png"); //load le tileset
    char y = game->nbCaseY-1,x;
    for (x=0;x<game->nbCaseX;x++){
        apply_surface((x+optAffichage->origineMapX)*SPRITE_WIDTH, (y+optAffichage->origineMapY +1)*SPRITE_HEIGHT, textures, ecran, &contourMap); //0->(SCREEN_WIDTH/SPRITE_WIDTH)-1
    }
    SDL_FreeSurface(textures); // On libère la surface
}

/**
 * \fn SDL_Rect* afficherMenuRejouer(SDL_Surface *ecran)
 * \brief affiche un menu avec les options rejouer, quitter et option
 *
 * \param optAffichage Les options d'affichage
 * \return un tableau de SDL_Rect, chaque case contient les position et taille d'un des boutons
 */
SDL_Rect* afficherMenuRejouer(SDL_Surface *ecran){
    /**Déclaration des variables*/
    SDL_Surface *texte, *popup;
    int popWidth = 32*4, popHeight = 32*3/2, marge = 32/4;
    SDL_Color white = {255,255,255};

    TTF_Init(); //Démarrage de SDL_ttf
    TTF_Font *police = TTF_OpenFont("Fonts/OCRAStd.otf", 20); //Charger la police

    /**Bouton rejouer*/
    popup = SDL_CreateRGBSurface(SDL_HWSURFACE, popWidth, popHeight, 32, 0, 0, 0, 0);
    rectangle(0,0,popup->w, popup->h, white, popup); //contour de la case
    texte = TTF_RenderText_Blended(police, "Rejouer", white);
    apply_surface(popup->w/2-texte->w/2, popup->h/2-texte->h/2, texte, popup, NULL);
    apply_surface(ecran->w/2-(popup->w*2+marge)/2, ecran->h/2-popup->h/2, popup, ecran, NULL);
    //position du bouton
    boutons[0].x = ecran->w/2-(popWidth*2+marge)/2;
    boutons[0].y = ecran->h/2-popup->h/2;
    boutons[0].w = popup->w;
    boutons[0].h = popup->h;

    /**Bouton option*/
    popup = SDL_CreateRGBSurface(SDL_HWSURFACE, popWidth, popHeight, 32, 0, 0, 0, 0);
    rectangle(0,0,popup->w, popup->h, white, popup); //contour de la case
    texte = TTF_RenderText_Blended(police, "Option", white);
    apply_surface(16, 16, texte, popup, NULL);
    apply_surface(0, 0, popup, ecran, NULL);
    //position du bouton
    boutons[1].x = 0;
    boutons[1].y = 0;
    boutons[1].w = popup->w;
    boutons[1].h = popup->h;

    /**Bouton quitter*/
    popup = SDL_CreateRGBSurface(SDL_HWSURFACE, popWidth, popHeight, 32, 0, 0, 0, 0);
    rectangle(0,0,popup->w, popup->h, white, popup); //contour de la case
    texte = TTF_RenderText_Blended(police, "Quitter", white);
    apply_surface(popup->w/2-texte->w/2, popup->h/2-texte->h/2, texte, popup, NULL);
    apply_surface((ecran->w/2-(popup->w*2+marge)/2)+marge+popup->w, ecran->h/2-popup->h/2, popup, ecran, NULL);
    //position du bouton
    boutons[2].x = (ecran->w/2-(popup->w*2+marge)/2)+marge+popup->w;
    boutons[2].y = ecran->h/2-popup->h/2;
    boutons[2].w = popup->w;
    boutons[2].h = popup->h;

    TTF_CloseFont(police); //Fermer la police
    SDL_FreeSurface(texte); // On libère la surface
    SDL_FreeSurface(popup); // On libère la surface
    TTF_Quit(); //Arrêt de SDL_ttf

    SDL_Flip(ecran); // Mise à jour de l'écran

    return boutons;
}
/**
 * \fn SDL_Rect* afficherMenuOption(SDL_Surface *ecran, Option *opt, int joueurSelect)
 * \brief affiche un menu avec les options rejouer, quitter et option
 *
 * \param optAffichage Les options d'affichage
 * \param opt Les options de jeu
 * \param joueurSelect Le numero du joueur selectionné pour la modification de sont apparence
 * \return un tableau de SDL_Rect, chaque case contient les position et taille d'un des boutons
 */
SDL_Rect* afficherMenuOption(SDL_Surface *ecran, Option *opt, int joueurSelect){//add: choix nb case libre, mode de jeu
    /**Déclaration des variables*/
    SDL_Surface *texte;
    int popWidth = ecran->w, popHeight = ecran->h, marge = 32/4;
    SDL_Color white = {255,255,255};

    /**Zone menu*/
    SDL_Surface *popup = SDL_CreateRGBSurface(SDL_HWSURFACE, popWidth, popHeight, 32, 0, 0, 0, 0);
    rectangle(0,0,popup->w, popup->h, white, popup); //contour de la surface
    apply_surface(0, 0,popup, ecran, NULL);

    TTF_Init(); //Démarrage de SDL_ttf
    TTF_Font *police;

    /**Titre*/
    police = TTF_OpenFont("Fonts/OCRAStd.otf", 20); //Charger la police
    texte = TTF_RenderText_Blended(police, "Option", white);
    apply_surface(16, 16, texte, ecran, NULL);

    police = TTF_OpenFont("Fonts/OCRAStd.otf", 16); //Charger la police

    /**Zone nombre de joueurs*/
    int firstMarge = 16 + texte->w + marge;
    int positionX = firstMarge;
    int positionY = 16+texte->h +4* marge;
    char affichageNb[21+3+1] = "Nombre de joueurs: ";
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    positionX +=texte->w+marge;
    sprintf(affichageNb, "%d",opt->nbJoueur);
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    //position du bouton
    boutons[6].x = positionX;
    boutons[6].y = positionY;
    boutons[6].w = texte->w;
    boutons[6].h = texte->h;

    /**Zone apparence du joueur*/
    positionX = firstMarge;
    positionY += texte->h + 2*marge;
    texte = TTF_RenderText_Blended(police, "Apparence du joueur: ", white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    //btn player
    if (opt->nbJoueur>1){
        int i=0;
        boutons = realloc(boutons, (7 + opt->nbJoueur) * sizeof(SDL_Rect));//reallocation
        for (i=0; i<opt->nbJoueur; i++){
            positionX +=texte->w+marge;
            sprintf(affichageNb, "J%d",i+1); //ajout du char score
            texte = TTF_RenderText_Blended(police, affichageNb, white);
            apply_surface(positionX, positionY, texte, ecran, NULL);
            //position du bouton
            boutons[i+7].x = positionX;
            boutons[i+7].y = positionY;
            boutons[i+7].w = texte->w;
            boutons[i+7].h = texte->h;
            //affichage du joueur selectionné
            if (joueurSelect == i){
                rectangle(boutons[i+7].x,boutons[i+7].y,boutons[i+7].w, boutons[i+7].h, white, ecran); //contour de la case
            }
        }
    }
    //image charset
    positionX = firstMarge;
    positionY += texte->h + 2*marge;
    SDL_Surface *charset =  IMG_Load(araignee.pathName); //load le charset
    apply_surface(positionX, positionY, charset, ecran, &araignee.clip);
    //position du bouton
    boutons[0].x = positionX;
    boutons[0].y = positionY;
    boutons[0].w = charset->w/16;
    boutons[0].h = charset->h/16;
    //image charset
    positionX += araignee.clip.w+marge;
    charset =  IMG_Load(squelette.pathName); //load le charset
    apply_surface(positionX, positionY, charset, ecran, &squelette.clip);
    //position du bouton
    boutons[1].x = positionX;
    boutons[1].y = positionY;
    boutons[1].w = charset->w/16;
    boutons[1].h = charset->h/16;
    //image charset
    positionX += squelette.clip.w+marge;
    charset =  IMG_Load(farmer.pathName); //load le charset
    apply_surface(positionX, positionY, charset, ecran, &farmer.clip);
    //position du bouton
    boutons[2].x = positionX;
    boutons[2].y = positionY;
    boutons[2].w = charset->w/farmer.nbImageAnim;
    boutons[2].h = charset->h/4;

    //affichage de l'apparence selectionné
    if (opt->sprites[joueurSelect] == &araignee){
        rectangle(boutons[0].x,boutons[0].y,boutons[0].w, boutons[0].h, white, ecran); //contour de la case
    }else if (opt->sprites[joueurSelect] == &squelette){
        rectangle(boutons[1].x,boutons[1].y,boutons[1].w, boutons[1].h, white, ecran); //contour de la case
    }else if (opt->sprites[joueurSelect] == &farmer){
        rectangle(boutons[2].x,boutons[2].y,boutons[2].w, boutons[2].h, white, ecran); //contour de la case
    }

    /**Zone nombre de ressources*/
    positionX = firstMarge;
    positionY += charset->h/4 + 2*marge;
    sprintf(affichageNb, "Nombre de ressources: ");
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    positionX +=texte->w+marge;
    sprintf(affichageNb, "%d",opt->nbRessource); //ajout du char score
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    //position du bouton
    boutons[3].x = positionX;
    boutons[3].y = positionY;
    boutons[3].w = texte->w;
    boutons[3].h = texte->h;

    /**Zone taille de la map*/
    positionX = firstMarge;
    positionY += texte->h + 2*marge;
    texte = TTF_RenderText_Blended(police, "Taille de la map X: ", white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    positionX +=texte->w+marge;
    sprintf(affichageNb, "%d", opt->nbCaseX); //ajout du char score
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    //position du bouton
    boutons[4].x = positionX;
    boutons[4].y = positionY;
    boutons[4].w = texte->w;
    boutons[4].h = texte->h;
    positionX +=texte->w+marge;
    sprintf(affichageNb, "Y: ");//3+2
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    positionX +=texte->w+marge;
    sprintf(affichageNb, "%d",opt->nbCaseY); //ajout du char score
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(positionX, positionY, texte, ecran, NULL);
    //position du bouton
    boutons[5].x = positionX;
    boutons[5].y = positionY;
    boutons[5].w = texte->w;
    boutons[5].h = texte->h;


    TTF_CloseFont(police); //Fermer la police
    SDL_FreeSurface(texte); // On libère la surface
    SDL_FreeSurface(popup); // On libère la surface
    TTF_Quit(); //Arrêt de SDL_ttf

    SDL_Flip(ecran); // Mise à jour de l'écran

    return boutons;
}

/**
 * \fn char gestionEvent(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Joueur* player, Option *opt)
 * \brief gère les interaction avec lutilisateur a travers le clavier
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu dont on veut gerer levenement
 * \param player Le joueur dont c'est le tour
 * \param opt Les options de jeu
 * \return l'action demandé par lutilisateur
 */
char gestionEvent(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Joueur* player, Option *opt){
    /**Déclaration des variables*/
    char choix = choixNull;
    SDL_Event event;
    int tempsPrecedent = SDL_GetTicks();
    int tempsActuel;

    do{
        if(optAffichage->automatique == 0){
            SDL_WaitEvent(&event);
        }else{
            //temporisation
            SDL_PollEvent(&event);
            tempsActuel = SDL_GetTicks();
        }
        if (event.type == SDL_KEYDOWN){
                    Arrete aTemp;
                    aTemp.C = (char*)malloc(sizeof(char)*1);
            switch(event.key.keysym.sym){
                case SDLK_ESCAPE:
                    choix = gestionMenu(optAffichage, ecran, game, opt);
                    break;
                case SDLK_r:
                    choix = rejouer;
                    break;
                case SDLK_p:
                    choix = automatique;
                    optAffichage->automatique = 1;
                    break;
                case SDLK_UP:
                    //player->position[1] -= 1;
                    aTemp.C[0] = 'H';
                    aTemp.D = 1;
                    jouerTour(game, player, &aTemp);
                    break;
                case SDLK_DOWN:
                    //player->position[1] += 1;
                    aTemp.C[0] = 'B';
                    aTemp.D = 1;
                    jouerTour(game, player, &aTemp);
                    break;
                case SDLK_LEFT:
                    //player->position[0] -= 1;
                    aTemp.C[0] = 'G';
                    aTemp.D = 1;
                    jouerTour(game, player, &aTemp);
                    break;
                case SDLK_RIGHT:
                    //player->position[0] += 1;
                    aTemp.C[0] = 'D';
                    aTemp.D = 1;
                    jouerTour(game, player, &aTemp);
                    break;
                default:
                    break;
            }
            if (event.key.keysym.sym != SDLK_ESCAPE && event.key.keysym.sym != SDLK_r){choix = play;} //key autre que escape et "r"
            if(optAffichage->automatique == 1 && choix==NULL){choix=play;}
        }else if (event.type == SDL_QUIT){choix = quitter;} //fermer
    }while((choix==choixNull) && (optAffichage->automatique == 0||(optAffichage->automatique == 1 && tempsActuel - tempsPrecedent < 250)));

    return choix;
}
/**
 * \fn char gestionMenu(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Option *opt)
 * \brief gère les interaction avec lutilisateur pour le menu de pause
 *
 * \param optAffichage Les options d'affichage
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param game Le jeu dont on veut gerer levenement
 * \param opt Les options de jeu
 * \return l'action demandé par lutilisateur
 */
char gestionMenu(OptionDAffichage *optAffichage, SDL_Surface *ecran, Jeu *game, Option *opt){
    /**Déclaration des variables*/
    SDL_Surface *ancienEcran = SDL_DisplayFormatAlpha(ecran);


    char choix = choixNull;
    SDL_Event event;

    boutons = afficherMenuRejouer(ecran);
    do{SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym){
                    case SDLK_ESCAPE: // Appui sur la touche Echap
                        choix = 4;
                        break;
                    case SDLK_KP_ENTER:
                        choix = 4;
                        break;
                    case SDLK_RETURN:
                        choix = 4;
                        break;
                    case SDLK_a://clavier qwerty
                        choix = quitter;
                        break;
                    case SDLK_r:
                        choix = rejouer;
                        break;
                    case SDLK_o:
                        gestionMenuOption(ecran,opt);
                        boutons = afficherMenuRejouer(ecran);//reinitialiser boutons
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (event.button.button == SDL_BUTTON_LEFT){
                    if(event.button.x>=boutons[0].x && event.button.x<=boutons[0].x+boutons[0].w && event.button.y>=boutons[0].y && event.button.y<=boutons[0].y+boutons[0].h){
                        choix = rejouer;
                    }else if(event.button.x>=boutons[1].x && event.button.x<=boutons[1].x+boutons[1].w && event.button.y>=boutons[1].y && event.button.y<=boutons[1].y+boutons[1].h){
                        gestionMenuOption(ecran,opt);
                        boutons = afficherMenuRejouer(ecran);//reinitialiser boutons
                    }else if(event.button.x>=boutons[2].x && event.button.x<=boutons[2].x+boutons[2].w && event.button.y>=boutons[2].y && event.button.y<=boutons[2].y+boutons[2].h){
                        choix = quitter;
                    }else{//clic en dehors d boutons
                        choix = 4;
                    }
                }
                break;
            default:
                break;
        }
    }while(choix==choixNull);
    if(choix!=rejouer){
        apply_surface(0,0,ancienEcran,ecran,NULL);//enlever menu de lecran
        SDL_Flip(ecran); // Mise à jour de l'écran
    }

    SDL_FreeSurface(ancienEcran);
    return choix;
}
/**
 * \fn void gestionMenuOption(SDL_Surface *ecran, Option *opt)
 * \brief gère les interaction avec lutilisateur pour le menu option
 *
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param opt Les options de jeu
 */
void gestionMenuOption(SDL_Surface *ecran, Option *opt){
    ///Déclaration des variables
    SDL_Surface *ancienEcran = SDL_DisplayFormatAlpha(ecran);
    char choix = choixNull;
    SDL_Color white = {255,255,255};
    Uint32 whiteRect = {255,255,255};
    SDL_Event event;
    int apparenceActive=0;
    boutons = afficherMenuOption(ecran, opt, apparenceActive);
    int i;

    do{SDL_WaitEvent(&event);
                    switch(event.type){
                        case SDL_KEYDOWN:
                            switch (event.key.keysym.sym){
                                case SDLK_ESCAPE: // Appui sur la touche Echap
                                    choix = 4;
                                    break;
                                case SDLK_KP_ENTER:
                                    choix = 4;
                                    break;
                                case SDLK_RETURN:
                                    choix = 4;
                                    break;
                                case SDLK_r:
                                    choix = rejouer;
                                    break;
                                case SDLK_o:
                                    choix = 4;
                                    break;
                                default:
                                    break;
                            }
                            break;
                        case SDL_MOUSEBUTTONUP:
                            if (event.button.button == SDL_BUTTON_LEFT){
                                if(event.button.x>=boutons[0].x && event.button.x<=boutons[0].x+boutons[0].w && event.button.y>=boutons[0].y && event.button.y<=boutons[0].y+boutons[0].h){
                                    opt->sprites[apparenceActive] = &araignee;
                                    afficherMenuOption(ecran, opt, apparenceActive);
                                }else if(event.button.x>=boutons[1].x && event.button.x<=boutons[1].x+boutons[1].w && event.button.y>=boutons[1].y && event.button.y<=boutons[1].y+boutons[1].h){
                                    opt->sprites[apparenceActive] = &squelette;
                                    afficherMenuOption(ecran, opt, apparenceActive);
                                }else if(event.button.x>=boutons[2].x && event.button.x<=boutons[2].x+boutons[2].w && event.button.y>=boutons[2].y && event.button.y<=boutons[2].y+boutons[2].h){
                                    opt->sprites[apparenceActive] = &farmer;
                                    afficherMenuOption(ecran, opt, apparenceActive);
                                }else if(event.button.x>=boutons[3].x && event.button.x<=boutons[3].x+boutons[3].w && event.button.y>=boutons[3].y && event.button.y<=boutons[3].y+boutons[3].h){
                                    opt->nbRessource = gestionTextBox(opt->nbRessource, ecran, boutons[3], opt->nbCaseLibre);
                                }else if(event.button.x>=boutons[4].x && event.button.x<=boutons[4].x+boutons[4].w && event.button.y>=boutons[4].y && event.button.y<=boutons[4].y+boutons[4].h){
                                    opt->nbCaseX = gestionTextBox(opt->nbCaseX, ecran, boutons[4], 50);
                                    opt->nbCaseLibre = (opt->nbCaseX*opt->nbCaseY)/3;
                                }else if(event.button.x>=boutons[5].x && event.button.x<=boutons[5].x+boutons[5].w && event.button.y>=boutons[5].y && event.button.y<=boutons[5].y+boutons[5].h){
                                    opt->nbCaseY = gestionTextBox(opt->nbCaseY, ecran, boutons[5], 28);
                                    opt->nbCaseLibre = (opt->nbCaseX*opt->nbCaseY)/3;
                                }else if(event.button.x>=0 && event.button.x<=32*4 && event.button.y>=0 && event.button.y<=32*3/2){//clic sur le titre "Option"
                                    choix=4;
                                }else if(event.button.x>=boutons[6].x && event.button.x<=boutons[6].x+boutons[6].w && event.button.y>=boutons[6].y && event.button.y<=boutons[6].y+boutons[6].h){
                                    int ancienNbJoueur = opt->nbJoueur;
                                    opt->nbJoueur = gestionTextBox(opt->nbJoueur, ecran, boutons[6], 9);
                                    afficherMenuOption(ecran, opt, apparenceActive);
                                    opt->sprites = realloc(opt->sprites, opt->nbJoueur * sizeof(Sprite));//reallocation
                                    for(i=ancienNbJoueur;i<opt->nbJoueur;i++){
                                        opt->sprites[i]=&farmer;
                                    }
                                }else if (opt->nbJoueur>1){
                                    for(i=0;i<opt->nbJoueur;i++){
                                        if(event.button.x>=boutons[i+7].x && event.button.x<=boutons[i+7].x+boutons[i+7].w && event.button.y>=boutons[i+7].y && event.button.y<=boutons[i+7].y+boutons[i+7].h){
                                            apparenceActive = i;
                                            afficherMenuOption(ecran, opt, apparenceActive);
                                            break;
                                        }
                                    }
                                }
                            }
                            break;
                        case SDL_MOUSEMOTION:
                            for(i=0;i<7;i++){
                                if(event.button.x>=boutons[i].x && event.button.x<=boutons[i].x+boutons[i].w && event.button.y>=boutons[i].y && event.button.y<=boutons[i].y+boutons[i].h){
                                    rectangle(boutons[i].x,boutons[i].y,boutons[i].w, boutons[i].h, white, ecran); //contour de la case
                                    SDL_Flip(ecran); // Mise à jour de l'écran
                                    break;
                                }
                            }
                            if (i==7){
                                if (opt->nbJoueur>1){
                                    for(i=0;i<opt->nbJoueur;i++){
                                        if(event.button.x>=boutons[i+7].x && event.button.x<=boutons[i+7].x+boutons[i+7].w && event.button.y>=boutons[i+7].y && event.button.y<=boutons[i+7].y+boutons[i+7].h){
                                            rectangle(boutons[i+7].x,boutons[i+7].y,boutons[i+7].w, boutons[i+7].h, white, ecran); //contour de la case
                                            SDL_Flip(ecran); // Mise à jour de l'écran
                                            break;
                                        }
                                    }
                                    if (i==opt->nbJoueur){afficherMenuOption(ecran, opt, apparenceActive);}
                                }else{
                                    afficherMenuOption(ecran, opt, apparenceActive);
                                }
                            }
                            break;
                        default:
                            break;
                    }

        }while(choix==choixNull);

        apply_surface(0,0,ancienEcran,ecran,NULL);//enlever menu de lecran
        SDL_Flip(ecran); // Mise à jour de l'écran

    SDL_FreeSurface(ancienEcran);
}
/**
 * \fn int gestionTextBox(int value, SDL_Surface *ecran, SDL_Rect zone, int limite)
 * \brief gère les interaction avec lutilisateur pour la modifiation et laffichage d'un nombre
 *
 * \param value La valeur initiale
 * \param ecran La surface sur laquelle on veut l'afficher
 * \param zone L'endroit où on veut afficher le nombre
 * \param limite Valeur maximum que peut prendre le nombre
 * \return la nouvelle valeur
 */
int gestionTextBox(int value, SDL_Surface *ecran, SDL_Rect zone, int limite){
    /**Déclaration des variables*/
    SDL_Color white = {255,255,255};
    SDL_Color black = {0,0,0};
    SDL_Surface *texte, *popup;
    char valide = 0;
    char affichageNb[3] = "";

    TTF_Init(); //Démarrage de SDL_ttf
    TTF_Font *police = TTF_OpenFont("Fonts/OCRAStd.otf", 16); //Charger la police
    SDL_Event event;


    do{
        /**Affichage de la valeur modifié*/
        sprintf(affichageNb, "%d",value); //convertion int -> string
        texte = TTF_RenderText_Blended(police, affichageNb, black);
        popup = SDL_CreateRGBSurface(SDL_HWSURFACE, texte->w, texte->h, 32, 0,0,0,0); //maj taille popup
        SDL_FillRect(popup, NULL, SDL_MapRGB(popup->format, 255, 255, 255)); //couleur de fond de la fenetre
        apply_surface(0, 0, texte, popup, NULL);
        apply_surface(zone.x, zone.y,popup, ecran, NULL);
        SDL_Flip(ecran); // Mise à jour de l'écran

        /**Modification de la valeur*/
        SDL_WaitEvent(&event);
        if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym){
                case SDLK_KP0:
                    value = value*10 + 0;
                    break;
                case SDLK_KP1:
                    value = value*10 + 1;
                    break;
                case SDLK_KP2:
                    value = value*10 + 2;
                    break;
                case SDLK_KP3:
                    value = value*10 + 3;
                    break;
                case SDLK_KP4:
                    value = value*10 + 4;
                    break;
                case SDLK_KP5:
                    value = value*10 + 5;
                    break;
                case SDLK_KP6:
                    value = value*10 + 6;
                    break;
                case SDLK_KP7:
                    value = value*10 + 7;
                    break;
                case SDLK_KP8:
                    value = value*10 + 8;
                    break;
                case SDLK_KP9:
                    value = value*10 + 9;
                    break;
                case SDLK_BACKSPACE:
                    value = (value - value%10) / 10;
                    break;
                case SDLK_KP_ENTER: //validation
                    valide = 1;
                    break;
                case SDLK_RETURN: //validation
                    valide = 1;
                    break;
                default:
                    break;
            }
            if (value>limite){
                value = limite;
            }else if(value/1000>0){//limite laffichage a 3 chiffre
                value = (value - value%10) / 10;
            }
        }

        /**Masquage de l'ancienne valeur*/
        SDL_FillRect(popup, NULL, SDL_MapRGB(popup->format, 0, 0, 0)); //couleur de fond de la fenetre
        apply_surface(zone.x, zone.y,popup, ecran, NULL);
    }while(valide == 0);

    sprintf(affichageNb, "%d",value); //ajout du char score
    texte = TTF_RenderText_Blended(police, affichageNb, white);
    apply_surface(0, 0, texte, popup, NULL);
    apply_surface(zone.x, zone.y,popup, ecran, NULL);
    SDL_Flip(ecran); // Mise à jour de l'écran

    TTF_CloseFont(police); //Fermer la police
    SDL_FreeSurface(texte); // On libère la surface
    SDL_FreeSurface(popup); // On libère la surface
    TTF_Quit(); //Arrêt de SDL_ttf

    return value;//renvoie la nouvelle valeur
}


//Dessin
/**
 * \fn void ligneHorizontale(int x, int y, int width, Uint32 couleur, SDL_Surface *surface)
 * \brief affiche une ligne horizontale
 *
 * \param x Position x
 * \param y Position y
 * \param width Longueur de la ligne
 * \param couleur Couleur de la ligne
 * \param surface La surface sur laquelle on veut l'afficher
 */
void ligneHorizontale(int x, int y, int width, Uint32 couleur, SDL_Surface *surface){
  SDL_Rect rectTemp = {x,y,width,1};
  SDL_FillRect(surface, &rectTemp, couleur);
}
/**
 * \fn void ligneVerticale(int x, int y, int height, Uint32 couleur, SDL_Surface *surface)
 * \brief affiche une ligne verticale
 *
 * \param x Position x
 * \param y Position y
 * \param height Longueur de la ligne
 * \param couleur Couleur de la ligne
 * \param surface La surface sur laquelle on veut l'afficher
 */
void ligneVerticale(int x, int y, int height, Uint32 couleur, SDL_Surface *surface){
  SDL_Rect rectTemp = {x,y,1,height};
  SDL_FillRect(surface, &rectTemp, couleur);
}
/**
 * \fn void rectangle(int x, int y, int width, int height, Uint32 couleur, SDL_Surface *surface)
 * \brief affiche un rectangle
 *
 * \param x Position x
 * \param y Position y
 * \param width Longueur du rectangle
 * \param height Largeur du rectangle
 * \param couleur Couleur du rectangle
 * \param surface La surface sur laquelle on veut l'afficher
 */
void rectangle(int x, int y, int width, int height, Uint32 couleur, SDL_Surface *surface){
    ligneHorizontale(x, y, width, couleur, surface);
    ligneHorizontale(x, y + height - 1, width, couleur, surface);
    ligneVerticale(x, y + 1, height - 2, couleur, surface);
    ligneVerticale(x + width - 1, y + 1, height - 2, couleur, surface);
}
/**
 * \fn void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip)
 * \brief affiche une image
 *
 * \param x Position x
 * \param y Position y
 * \param source La surface qu'on veut afficher
 * \param destination La surface sur laquelle on veut l'afficher
 * \param clip Coontient la taille et position sur la surface qu'on veut afficher de la partie qu'on veut afficher
 */
void apply_surface(int x, int y, SDL_Surface *source, SDL_Surface *destination, SDL_Rect *clip){
    SDL_Rect offset = {.x = x, .y = y};

    //On blitte la surface
    SDL_BlitSurface(source, clip, destination, &offset);
}
/**
 * \fn void apply_text(int x, int y, char* txt, SDL_Surface *destination, char* filePolice, int taille, SDL_Color couleur)
 * \brief affiche un texte
 *
 * \param x Position x
 * \param y Position y
 * \param txt Le tetx a afficher
 * \param destination La surface sur laquelle on veut l'afficher
 * \param filePolice La police qu'on veut pour le texte
 * \param taille La taille qu'on veut pour le texte
 * \param couleur Couleur du texte
 */
void apply_text(int x, int y, char* txt, SDL_Surface *destination, char* filePolice, int taille, SDL_Color couleur){
    TTF_Init(); //Démarrage de SDL_ttf
    TTF_Font *police = TTF_OpenFont(filePolice, taille); //Charger la police
    SDL_Surface *texte = TTF_RenderText_Blended(police, txt, couleur); //creer la surface correspondant au texte
    apply_surface(x, y, texte, destination, NULL);
    SDL_FreeSurface(texte); // On libère la surface
    TTF_CloseFont(police); //Fermer la police
    TTF_Quit(); //Arrêt de SDL_ttf
}
