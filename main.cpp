#include <iostream>
#include"graphe.h"

int main()
{
    //D�claration des vecteurs de type Arete allant prendre le vecteur d'Arete tri�
    graphe g("triville.txt","triville_weights_0.txt");

    g.afficher();
    g.Primcout1();
    g.EnumerationBinaire();
    //g.afficher_Kruskal();

}

