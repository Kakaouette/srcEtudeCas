struct affichage{
affichage(); // appellé pour générer le tout (ajouter argument pour plus d'options)
genTerrain();
genDepartArrivee();
genObjet();
};

genTerrain(){
  int x=0;
  for (int i=0; i<50; i++){
    for (int j=0; j<50; j++){
      map[x] = Case(i,j);
      x++;
    }
  }
}
