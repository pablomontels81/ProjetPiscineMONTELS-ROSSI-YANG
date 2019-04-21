#include <iostream>
#include"graphe.h"
#include"arete.h"
#include"svgfile.h"

int main()
{
    Svgfile svgout;
    Svgfile out("Pareto.svg");

    std::vector<bool>test;
    test.push_back(0);
    test.push_back(1);
    test.push_back(1);
    test.push_back(0);
    test.push_back(1);
    //Déclaration des vecteurs de type Arete allant prendre le vecteur d'Arete trié
    graphe g0("broadway.txt","broadway_weights_0.txt");
    graphe g1("triville.txt","triville_weights_0.txt");
    graphe g2("cubetown.txt","cubetown_weights_0.txt");
    graphe g3("manhattan.txt","manhattan_weights_0.txt");
    graphe g4("antoine.txt","antoine_weights_0.txt"); //test pour verifier si cc marche



    //g0.afficher();
    //g0.dessinerGraphe(svgout,"Graphe");
    //g0.dessinerCheminPrim(svgout); //0 pour poids 0


    g0.EnumerationBinairePareto();
    g0.Pareto();
    g0.dessiner_Combinaison_Pareto(out);

    //std::cout << g0.Dijkstra(test,0);

    //int ncc=g4.rechercher_afficherToutesCC();
    //std::cout << "NBRE CC : " << ncc << std::endl;

    //system("PAUSE");
    //g1.dessiner_Combinaison_Pareto();

    /*
    int choix;

    //std::cout<<"Choix ?";
    //std::cin>>choix;

    if(choix==1)
    {

    g0.afficher();
    g0.dessinerGraphe(svgout,"Graphe de Broadway");
    g0.dessinerCheminPrim(svgout); //0 pour poids 0
    //g.EnumerationBinaire();
    //g.afficher_Kruskal();

    }
    if(choix==2)
    {

    g1.afficher();
    g1.dessinerGraphe(svgout,"Graphe de Triville");
    g1.dessinerCheminPrim(svgout); //0 pour poids 0

    }

    if(choix==3)
    {

    g2.afficher();
    g2.dessinerGraphe(svgout,"Graphe de Cubetown");
    g2.dessinerCheminPrim(svgout); //0 pour poids 0

    }

    if(choix==4)
    {

    g3.afficher();
    g3.dessinerGraphe(svgout,"Graphe de Manhattan");
    g3.dessinerCheminPrim(svgout,0); //0 pour poids 0

    }*/

    return 0;
}

