struct affichage{
affichage(); // appellé pour générer le tout (ajouter argument pour plus d'options)
genTerrain();
genDepartArrivee();
genObjet();
};

affichage(){
  for (int i=0; i<50; i++){
    for (int j=0; j<50; j++){
      //afficher map[i][j]
        //afficher map[i][j]->case->image
    }
  }
}

genTerrain(){
  obs = Case(img, type);
  chemin = Case(img, type);
  
  //generation chemin coherent
    //case de depart au hasard
    //do
      //take une case autour au hasard
        //if case dans terrain (i<50 and j<50) and pas case dej take (contain(caseChemin, caseij))
        //else le faire pour une autre case
    //while(nb de case accessible voulu)
  //completer trou par obs
  
  for (int i=0; i<50; i++){
    for (int j=0; j<50; j++){
      if (is in terrain and not chemin)
        map[i][j] = obs;
    }
  }
}

genDepartArrivee(){
  while(d = null and a = null){
    random case
    if (case not obs){
      if (d=null){
        d=case
      }else{
        a=case
      }
    }
  }  
}

genObjet(){
  while(nbRessource pas attein){
    random i 0->50
    random j 0->50
    if (map[i][j] interrain){
      map.ressource(i,j)
    }
  }
}
