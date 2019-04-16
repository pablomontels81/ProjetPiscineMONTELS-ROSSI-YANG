#include <iostream>
#include"graphe.h"

int main()
{
    std::vector<Arete*>
    graphe g("broadway.txt","broadway_weights_0.txt");
    g.afficher();

}

