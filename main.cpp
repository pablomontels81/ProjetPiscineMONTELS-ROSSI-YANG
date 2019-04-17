#include <iostream>
#include"graphe.h"
#include"svgfile.h"

int main()
{
    Svgfile svgout;

    //Déclaration des vecteurs de type Arete allant prendre le vecteur d'Arete trié
    graphe g("manhattan.txt","manhattan_weights_0.txt");

    g.afficher();
    g.dessiner(svgout);
    g.Primcout1(svgout);
    //g.EnumerationBinaire();
    //g.afficher_Kruskal();

    return 0;
}

