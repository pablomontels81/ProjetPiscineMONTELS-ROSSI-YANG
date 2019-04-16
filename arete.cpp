#include <iostream>
#include <queue>
#include <stack>
#include<unordered_map>
#include<unordered_set>
#include "arete.h"

Arete::Arete(std::string id,float cout1,float cout2,double S1,double S2):m_id{id},m_cout1{cout1},m_cout2{cout2},m_sommetdepart{S1},m_sommetarrive{S2}
{
}

void Arete::afficherDataArete() const
{
    std::cout<<"    "<<m_id<<" : "<<"("<<m_sommetdepart<<","<<m_sommetarrive<<")"<<std::endl;
    std::cout<<"       "<<"poids 1 : "<<m_cout1<<",  poids 2 : "<<m_cout2<<std::endl;
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
