#include <iostream>
#include"graphe.h"

int main()
{
    //Déclaration des vecteurs de type Arete allant prendre le vecteur d'Arete trié
    graphe g("broadway.txt","broadway_weights_0.txt");
    graphe h("broadway.txt","broadway_weights_0.txt");

    ///Lancement Du Kruskal Sur Base du Cout 1
    //Trie Croissant Cout 1
    g.triCout1();
    g.Kruskalcout1();

    ///Lancement Du Kruskal Sur Base du Cout 2
    //Trie Croissant Cout 2
    h.triCout2();
    h.Kruskalcout2();


}

