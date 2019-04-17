#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "arete.h"

Arete::Arete(std::string id,float cout1,float cout2,std::string S1,std::string S2):m_id{id},m_cout1{cout1},m_cout2{cout2},m_sommetdepart{S1},m_sommetarrive{S2}
{
}

void Arete::afficherDataArete() const
{
    std::cout<<"    "<<m_id<<" : "<<"("<<m_sommetdepart<<","<<m_sommetarrive<<")"<<std::endl;
    std::cout<<"       "<<"poids 1 : "<<m_cout1<<",  poids 2 : "<<m_cout2<<std::endl;
}

void Arete::dessinerChemin(Svgfile &fichier, std::vector<Sommet*> m_sommets)
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

    fichier.addLine(x_sd+800, y_sd, x_sa+800, y_sa, "red");
    fichier.addText((total_x/2)+800, (total_y/2), m_id, "green");

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

float Arete::getCout1() const
{
            return m_cout1;
}

float Arete::getCout2() const
{
            return m_cout2;
}
std::string Arete::getS1()
{
    return m_sommetdepart;
}
std::string Arete::getS2() const
{
    return m_sommetarrive;
}

void Arete::setMarq(bool marq)
{
    m_marq=marq;
}

bool Arete::getMarq()
{
    return m_marq;
}
