#include <fstream>
#include <iostream>
#include "graphe.h"
#include "algorithm"

graphe::graphe(std::string nomFichierSommets,std::string nomFichierPoids){
    //Ouverture FIchier Contenant les Poids
    std::ifstream ifsPoids{nomFichierPoids};
    if (!ifsPoids)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierPoids );
    //Ouverture Fichier Contenant les Sommets
    std::ifstream ifsSommet{nomFichierSommets};
    if (!ifsSommet)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierSommets );

    int ordre;
    ifsSommet >> ordre;
    if ( ifsSommet.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifsSommet>>id; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>x; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>y; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    int taille1,taille2, nbre;
    ifsPoids >> taille2 >> nbre;
    ifsSommet >> taille1;
    if (ifsPoids.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    if (ifsSommet.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string Tampon;
    float cout1,cout2;
    double sommet1, sommet2;

    for (int i=0; i<taille1; i++){
        ifsSommet>>id; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet1; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>Tampon; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>cout1; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>cout2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_aretes.push_back(new Arete{id,cout1,cout2,sommet1,sommet2});
    }

}

void graphe::Kruskalcout1() const{
    std::vector<Arete*> graphe_kruskal;
    std::vector<double> sommets_marques;
    for (auto elem_arete_en_cours : m_aretes)
    {
        auto test1 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS1());
        auto test2 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS2());
        if ((test1 == sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 != sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 == sommets_marques.end())&&(test2 != sommets_marques.end())
            )
        {
            sommets_marques.push_back(elem_arete_en_cours->getS1());
            sommets_marques.push_back(elem_arete_en_cours->getS2());
            graphe_kruskal.push_back(elem_arete_en_cours);
        }
    }
    std::cout<<"Resultat Kruskal : Arbre couvrant de Poids Minimum: "<<std::endl;
    for (auto elemAreteKruskal : graphe_kruskal)
    {
        elemAreteKruskal->afficherIDArete();
    }

}
void graphe::Kruskalcout2() const{
    std::vector<Arete*> graphe_kruskal;
    std::vector<double> sommets_marques;
    for (auto elem_arete_en_cours : m_aretes)
    {
        auto test1 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS1());
        auto test2 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS2());
        if ((test1 == sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 != sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 == sommets_marques.end())&&(test2 != sommets_marques.end())
            )
        {
            sommets_marques.push_back(elem_arete_en_cours->getS1());
            sommets_marques.push_back(elem_arete_en_cours->getS2());
            graphe_kruskal.push_back(elem_arete_en_cours);
        }
    }
    std::cout<<"Resultat Kruskal : Arbre couvrant de Poids Minimum: "<<std::endl;
    for (auto elemAreteKruskal : graphe_kruskal)
    {
        elemAreteKruskal->afficherIDArete();
    }
}

void graphe::afficher() const{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<" ordre : "<<m_sommets.size()<<std::endl;
    std::cout<<"  sommet : "<<std::endl;
    for (auto elemSommet : m_sommets)
    {
        elemSommet->afficherData();
    }
    std::cout<<" taille : "<<m_aretes.size()<<std::endl;
    std::cout<<" arete : "<<std::endl;
    for (auto elemArete : m_aretes)
    {
        elemArete->afficherDataArete();
    }
}

std::vector<Arete*> graphe::triCout1()
{
    std::sort(m_aretes.begin(),m_aretes.end(),[](Arete* a1, Arete* a2)
    {
        return a1->getCout1() < a2->getCout1() ;
    });
}
std::vector<Arete*> graphe::triCout2()
{
    std::sort(m_aretes.begin(),m_aretes.end(),[](Arete* a1, Arete* a2)
    {
        return a1->getCout2() < a2->getCout2() ;
    });
}




graphe::~graphe()
{
    //dtor
}

