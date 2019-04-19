#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "arete.h"

Arete::Arete(std::string id,std::vector<float>poid,std::string S1,std::string S2):m_id{id},m_poids{poid},m_sommetdepart{S1},m_sommetarrive{S2}
{
}

void Arete::afficherDataArete() const
{
    std::cout<<"    "<<m_id<<" : "<<"("<<m_sommetdepart<<","<<m_sommetarrive<<")"<<std::endl;
    std::cout << "Vous avez la possibilite de choisir " << m_poids.size() << " poids differents" << std::endl;
    std::cout << "Choississez de la valeur 0 a la valeur " << m_poids.size()-1 << " pour le poids" << std::endl;
    for (int i = 0; i < m_poids.size(); ++i)
    {
       std::cout<<"       "<<"poids" << i << ": "<<m_poids[i]<<std::endl;
    }

}

void Arete::dessinerChemin(Svgfile &fichier, std::vector<Sommet*> m_sommets, int dec)
{
    //sommet depart et sommet arrive
   double x_sd, y_sd, x_sa, y_sa, total_x, total_y;
   for (size_t i = 0; i<m_sommets.size();++i) // parcour le vecteur sommets
   {
       if (m_sommets[i]->getId() == m_sommetdepart) // condition correpdanec des id
       {
           x_sd = m_sommets[i]->getX();
           y_sd = m_sommets[i]->getY();
       }
       if (m_sommets[i]->getId() == m_sommetarrive) // Pareil
       {
           x_sa = m_sommets[i]->getX();
           y_sa = m_sommets[i]->getY();
       }
   }
    total_x = x_sd+x_sa;
    total_y = y_sd+y_sa;

    fichier.addLine(x_sd+800, y_sd + dec, x_sa+800, y_sa + dec, "red");
    fichier.addText((total_x/2)+800, (total_y/2) + dec, m_id, "green");

}


void Arete::dessinerGraphe(Svgfile &fichier, std::vector<Sommet*> m_sommets)
{
    //sommet depart et sommet arrive
   double x_sd, y_sd, x_sa, y_sa, total_x, total_y;
   for (size_t i = 0; i<m_sommets.size();++i) // parcour le vecteur sommets
   {
       if (m_sommets[i]->getId()==m_sommetdepart) // condition correpdanec des id
       {
           x_sd = m_sommets[i]->getX();
           y_sd = m_sommets[i]->getY();
       }
       if (m_sommets[i]->getId()==m_sommetarrive) // Pareil
       {
           x_sa = m_sommets[i]->getX();
           y_sa = m_sommets[i]->getY();
       }
   }
    total_x = x_sd+x_sa;
    total_y = y_sd+y_sa;

    fichier.addLine(x_sd+100, y_sd, x_sa+100, y_sa, "black");
    fichier.addText((total_x/2)+100, (total_y/2), m_id, "green");
}


void Arete::afficherIDArete() const{


    std::cout<<"   "<<m_id<<std::endl;
}

Arete::~Arete()
{
    //dtor
}

float Arete::getPoids(int poid) const
{
            return m_poids[poid];
}

/*float Arete::getCout2() const
{
            return m_cout2;
}*/
std::string Arete::getS1()
{
    return m_sommetdepart;
}
std::string Arete::getS2() const
{
    return m_sommetarrive;
}

std::string Arete::getId()
{
     return m_id;
}

void Arete::setMarq(bool marq)
{
    m_marq=marq;
}

bool Arete::getMarq()
{
    return m_marq;
}
