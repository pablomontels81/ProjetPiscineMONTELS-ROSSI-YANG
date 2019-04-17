#include <iostream>
#include"graphe.h"

int main()
{
    //Déclaration des vecteurs de type Arete allant prendre le vecteur d'Arete trié
    graphe g("broadway.txt","broadway_weights_0.txt");

    g.EnumerationBinaire();
    //g.triCout1();

    //g.afficher();

    //g.Kruskalcout1();

    //g.afficher_Kruskal();


}

