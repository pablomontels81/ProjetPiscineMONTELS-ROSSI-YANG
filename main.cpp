#include <iostream>
#include"graphe.h"

int main()
{
    //Déclaration des vecteurs de type Arete allant prendre le vecteur d'Arete trié
    graphe g("triville.txt","triville_weights_0.txt");

    g.afficher();
    g.Primcout1();
    g.EnumerationBinaire();
    //g.afficher_Kruskal();

}

