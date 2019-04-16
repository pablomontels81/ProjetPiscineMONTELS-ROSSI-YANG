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
        void afficherGrapheTrieCroissant() const;
        std::vector<Arete*> trieCroissantCout1 () ;
        std::vector<Arete*> trieCroissantCout2() ;
        void Kruskal () const;

    protected:

    private:
        /// Le r�seau est constitu� d'une collection de sommets
        std::vector<Sommet*> m_sommets;//stock�e dans un vecteur (pointeur sur le sommet)
        std::vector<Arete*> m_aretes;//stock�e dans un vecteur (pointeur sur l'ar�te)
};

#endif // GRAPHE_H
