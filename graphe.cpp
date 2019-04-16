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
        m_sommets.insert({id,new Sommet{id,x,y}});
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
        m_aretes.insert({id,new Arete{id,cout1,cout2,sommet1,sommet2}});
    }

}
void graphe::afficher() const{
    std::cout<<"graphe : "<<std::endl;
    std::cout<<" ordre "<<m_sommets.size()<<std::endl;
    for (auto elemSommet : m_sommets)
    {
        std::cout<<" sommet : "<<std::endl;
        elemSommet.second->afficherData();
    }
    std::cout<<" taille "<<m_aretes.size()<<std::endl;
    for (auto elemArete : m_aretes)
    {
        std::cout<<" arete : "<<std::endl;
        elemArete.second->afficherDataArete();
    }
}

std::unordered_map<std::string,float> graphe::trieCroissant()
{
    std::sort(m_aretes.begin(),m_aretes.end(),fonction_comparaison_cout1())
}

graphe::~graphe()
{
    //dtor
}

bool fonction_comparaison_cout1(std::pair<int,Arete> n1, std::pair<int,Arete> n2)
{
    return n1.second.m_cout1 < n2.second.m_cout1;
}
