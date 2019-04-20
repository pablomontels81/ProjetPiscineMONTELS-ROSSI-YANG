#include "PoidsTT.h"

PoidsTT::PoidsTT(float P1,float P2,bool F_P):Poids1{P1},Poids2{P2},F_P{F_P}
{
}
PoidsTT::~PoidsTT()
{
    //dtor
}
float PoidsTT::getPoids1() const
{
    return Poids1;
}

float PoidsTT::getPoids2() const
{
    return Poids2;
}

bool PoidsTT::getBool() const
{
    return F_P;
}
