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
    std::cout<<m_id<<"  "<<m_sommetdepart<<"  "<<m_sommetarrive<<std::endl;
    std::cout<<m_cout1<<"  "<<m_cout2<<std::endl;
}

Arete::~Arete()
{
    //dtor
}
