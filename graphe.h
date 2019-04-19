#ifndef GRAPHE_H
#define GRAPHE_H

#include <string>
#include <unordered_map>
#include "sommet.h"
#include "arete.h"
#include"PoidsTT.h"
#include"svgfile.h"

class graphe
{
public:
    ///constructeur qui charge le graphe en mémoire
    //format du fichier ordre/liste des sommets/taille/liste des arêtes
    graphe(std::string,std::string);
    ~graphe();
    void afficher() const;
    void Pareto();
    void dessinerGraphe(Svgfile &svgout,std::string texte) const;
    void dessiner_Combinaison_Pareto(Svgfile &fichier_pareto) ;
    std::vector<Arete*> Prim(int num);
    void dessinerCheminPrim(Svgfile &svgout);
    std::vector<Arete*> triPoids(int poid);
    //std::vector<Arete*> triCout2();
    int eulerien(std::set<Sommet*> vec);
    void EnumerationBinaire() ;
    //void Kruskal();
    std::string changement_float (float val);


protected:

private:
    /// Le réseau est constitué d'une collection de sommets
    std::vector<Sommet*> m_sommets;//stockée dans un vecteur (pointeur sur le sommet)
    std::vector<Arete*> m_aretes;//stockée dans un vecteur (pointeur sur l'arête)
    std::vector<std::vector<bool>> m_vecteur_test_pareto;
    std::vector<PoidsTT*> m_PoidsTT;
    std::set<PoidsTT*>m_PoidsTT_Post_Pareto;
    int m_nbCout;
};
#endif // GRAPHE_H
