void resetRessources(Ressource*[] ressources){
    int i;
    for(i = 0 ; i < ressources.length ; i++){
        ressources[i].vue = 0;
        ressources[i].pass = 0;
        ressources[i].rendu = 0;
    }
}

struct Jeu{
joueur J1;
J1 = joueur.newJoueur(); // Aucune id�e.
Case*[][] map;
ressource*[] ressources;
execution(); // Appell� depuis le main. Cr�� affichage/joueur/etc... // options � ajouter en argument
};
