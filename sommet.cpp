#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "sommet.h"


Sommet::Sommet(std::string id,double x,double y):m_id{id},m_x{x},m_y{y}
{
}
void Sommet::ajouterVoisin(const Sommet* voisin){
    m_voisins.push_back(voisin);
}
void Sommet::afficherData() const{
     std::cout<<"    "<<m_id<<" : "<<"(x,y)=("<<m_x<<","<<m_y<<")"<<std::endl;
 }
void Sommet::dessinerSommet(Svgfile &fichier)
{
    fichier.addDisk(m_x, m_y,5, "black");
    fichier.addText(m_x+10, m_y-10, m_id, "violet");
}

double Sommet::getX()
{
     return m_x;
}

double Sommet::getY()
{
     return m_y;
}

std::string Sommet::getId()
{
     return m_id;
}

Sommet::~Sommet()
{
    //dtor
}
