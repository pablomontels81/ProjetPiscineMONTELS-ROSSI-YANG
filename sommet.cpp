#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"


Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}

void Sommet::ajouterVoisin(const Sommet* voisin)
{
    m_voisins.push_back(voisin);
}

void Sommet::afficherVoisins()
{
    for(auto v:m_voisins)
    {
        std::cout << v << std::endl;
    }
}

void Sommet::afficherData() const
{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
}

void Sommet::dessinerSommetC(Svgfile &fichier, int dec)
{
    fichier.addDisk(m_x+800, m_y + dec,5, "black");
    fichier.addText(m_x+810, m_y-10 + dec, m_id, "violet");
}

void Sommet::dessinerSommet(Svgfile &fichier)
{
    fichier.addDisk(m_x+100, m_y,5, "red");
    fichier.addText(m_x+110, m_y-10, m_id, "violet");
}

void Sommet::dessinerT(Svgfile &fichier)
{
    fichier.addText(m_x+500,m_y+200,"Graphe test","black");
}


double Sommet::getX()
{
     return m_x;
}

double Sommet::getY()
{
   return m_y;
}

float Sommet::getPoids()
{
     return m_poid;
}

float Sommet::setPoids(float poid)
{
    m_poid = poid;
}


std::string Sommet::getId()
{
     return m_id;
}

int Sommet::Paire()
{
    int nbr;

    if(m_voisins.size() %2 == 0) //si paire
    {
        nbr = 1;
    }
    else // sinon impaire
    {
        nbr = 0;
    }
    return nbr;
}

bool Sommet::getMarq()
{
    return m_marq;
}

void Sommet::setMarq(bool marq)
{
   m_marq = marq;
}

Sommet::~Sommet()
{
    //dtor
}

/// on fait du recursif ///
std::unordered_set<std::string> Sommet::rechercherCC(std::unordered_set<std::string> &cc) const
{
    cc.insert(m_id); //on ajoute l'identifiant
    //std::cout << "    " << m_id; //on l'affiche
    for(const auto &test : m_voisins) //on parcourt les voisins
    {
        if(cc.count(test->m_id) == 0) //si pas marqué on relance le programme
        {
            test->rechercherCC(cc);
        }
    }

    return cc;
}
