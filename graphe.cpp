#include <fstream>
#include <iostream>
#include "graphe.h"


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
    std::string sommet1, sommet2;

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
void graphe::afficher() const{

    Svgfile svgout;
    svgout.addGrid();

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
    for (auto elemArete : m_aretes)
    {
        elemArete->dessinerArete(svgout,m_sommets);
    }
    for (auto elemSommet : m_sommets)
    {
        elemSommet->dessinerSommet(svgout);
    }

}
/*
void graphe::afficherGrapheTrieCroissant() const{
    std::cout<<"
}*/

std::vector<Arete*> graphe::trieCroissantCout1()
{
    std::sort(m_aretes.begin(),m_aretes.end(),[](Arete* a1, Arete* a2)
    {
        return a1->getCout1() < a2->getCout1() ;
    });
}
std::vector<Arete*> graphe::trieCroissantCout2()
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

