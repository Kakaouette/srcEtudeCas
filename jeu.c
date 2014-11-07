void resetRessources(Ressource*[] ressources){
    int i;
    for(i = 0 ; i < ressources.length ; i++){
        ressources[i].vue = 0;
        ressources[i].pass = 0;
        ressources[i].rendu = 0;
    }
}

struct Jeu{
Joueur J1 = joueur.newJoueur(); // Aucune id�e.
Case* map[][];
Ressource* ressources[];
execution(); // Appell� depuis le main. Cr�� affichage/joueur/etc... // options � ajouter en argument
};
