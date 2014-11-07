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
J1 = joueur.newJoueur(); // Aucune idée.
Case*[][] map;
ressource*[] ressources;
execution(); // Appellé depuis le main. Créé affichage/joueur/etc... // options à ajouter en argument
};
