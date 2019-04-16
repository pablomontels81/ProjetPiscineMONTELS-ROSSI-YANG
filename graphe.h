#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en mémoire
        //format du fichier ordre/liste des sommets/taille/liste des arêtes
        graphe(std::string,std::string);
        ~graphe();
        void afficher() const;
        std::unordered_map<std::string,float> trieCroissant () ;
        void Kruskal () const;

    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::unordered_map<std::string,Sommet*> m_sommets;//stockée dans une map (clé=id du sommet, valeur= pointeur sur le sommet)
        std::unordered_map<std::string,Arete*> m_aretes;
};

#endif // GRAPHE_H
