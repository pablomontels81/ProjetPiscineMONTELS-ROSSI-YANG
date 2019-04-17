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
        void dessiner(Svgfile &svgout) const;
        void Primcout1(Svgfile &svgout);
        std::vector<Arete*> triCout1();
        std::vector<Arete*> triCout2();
        int eulerien(std::set<Sommet*> vec);
        void EnumerationBinaire() const;
        //void Kruskal();


    protected:

    private:
        /// Le réseau est constitué d'une collection de sommets
        std::vector<Sommet*> m_sommets;//stockée dans un vecteur (pointeur sur le sommet)
        std::vector<Arete*> m_aretes;//stockée dans un vecteur (pointeur sur l'arête)
};

#endif // GRAPHE_H
