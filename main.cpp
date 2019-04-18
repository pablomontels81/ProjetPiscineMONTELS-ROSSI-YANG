#include <iostream>
#include"graphe.h"
#include"arete.h"
#include"svgfile.h"

int main()
{
    Svgfile svgout;

    //Déclaration des vecteurs de type Arete allant prendre le vecteur d'Arete trié
    graphe g("triville.txt","triville_weights_0.txt");

    g.afficher();
    g.dessinerGraphe(svgout);
    g.dessinerCheminPrim(svgout,0); //0 pour poids 0
    //g.EnumerationBinaire();
    //g.afficher_Kruskal();

    return 0;
}

