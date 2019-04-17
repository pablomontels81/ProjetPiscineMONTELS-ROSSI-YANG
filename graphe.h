#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"

class graphe
{
    public:
        ///constructeur qui charge le graphe en m�moire
        //format du fichier ordre/liste des sommets/taille/liste des ar�tes
        graphe(std::string,std::string);
        ~graphe();
        void afficher() const;
        void EnumerationBinaire() const;
        void afficher_Kruskal() const;
        void Kruskalcout1() const;
        void Kruskalcout2() const;
        std::vector<Arete*> triCout1();
        std::vector<Arete*> triCout2();
        void afficherGrapheTrieCroissantCout1() const;
        void afficherGrapheTrieCroissantCout2() const;
        //std::vector<Arete*> Kruskal() const;
        void Prim() const;


    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Sommet*> m_sommets;//stock�e dans un vecteur (pointeur sur le sommet)
        std::vector<Arete*> m_aretes;//stock�e dans un vecteur (pointeur sur l'ar�te)
};

#endif // GRAPHE_H
