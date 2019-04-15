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
        m_sommets.insert({id,new Sommet{id,x,y}});
    }

    int taille;
    ifsPoids >> taille;
    if (ifsPoids.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    if (ifsSommet.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");

    float cout1,cout2;
    double sommet1, sommet2;

    for (int i=0; i<taille; i++){
        ifsSommet>>id; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet1; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        /*
        ifsPoids>>id2; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture données arete");
        ifsPoids>>cout1; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture données arete");
        ifsPoids>>cout2; if(ifsPoids.fail()) throw std::runtime_error("Probleme lecture données arete");
        ifsSommet>>id2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données arete");
        ifsSommet>>sommet1; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données arete");
        ifsSommet>>sommet2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données arete");*/
        m_aretes.insert({id,new Arete{id,1.0,1.0,sommet1,sommet2}});
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

void graphe::parcoursBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursBFS();
}
void graphe::afficherBFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursBFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursBFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
void graphe::parcoursDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    l_pred=s0->parcoursDFS();
}
void graphe::afficherDFS(std::string id) const{
    Sommet*s0=(m_sommets.find(id))->second;
    std::unordered_map<std::string,std::string> l_pred;
    std::cout<<"parcoursDFS a partir de "<<id<<" :"<<std::endl;
    l_pred=s0->parcoursDFS();
    for(auto s:l_pred){
        std::cout<<s.first<<" <--- ";
        std::pair<std::string,std::string> pred=s;
        while(pred.second!=id){
            pred=*l_pred.find(pred.second);
            std::cout<<pred.first<<" <--- ";
        }
        std::cout<<id<<std::endl;
    }
}
int graphe::rechercher_afficherToutesCC() const{
    int i=0;
    std::cout<<"composantes connexes :"<<std::endl;
    std::cout<<"recherche et affichage de toutes les composantes connexes a coder"<<std::endl;
    return i;
}
graphe::~graphe()
{
    //dtor
}
