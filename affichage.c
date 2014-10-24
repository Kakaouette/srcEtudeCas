struct affichage{
affichage(); // appellé pour générer le tout (ajouter argument pour plus d'options)
genTerrain();
genDepartArrivee();
genObjet();
};

genTerrain(){
  obs = Case(img, type);
  chemin = Case(img, type);
  
  //generation chemin coherent
    //case de depart au hasard
    //do
      //take une case autour au hasard
        //if case dans terrain (i<50 and j<50) and pas case dej take (contain(caseChemin, caseij))
    //while(nb de case accessible voulu)
  //completer trou par obs
  
  for (int i=0; i<50; i++){
    for (int j=0; j<50; j++){
      map[i][j] = obs;
    }
  }
}
