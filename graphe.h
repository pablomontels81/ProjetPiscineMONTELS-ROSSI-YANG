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

    graphe(std::string,std::string);
    ~graphe();

    void afficher() const;
    void dessinerGraphe(Svgfile &svgout,std::string texte) const;

    std::vector<Arete*> Prim(int num);
    void dessinerCheminPrim(Svgfile &svgout);

    void triPoids(int poid);

    void Pareto();
    std::vector<std::vector<bool>> EnumerationBinairePareto();
    void dessiner_Combinaison_Pareto();

    float Dijkstra(std::vector<bool>arete,int sommetdep);
    float etape3(std::vector<bool>arete);
    std::vector<std::vector<bool>> EnumerationBinaireDij();
    void DijkstraTout();
    void dessiner_Dijkstra();

    std::string changement_float (float val);
    int rechercher_afficherToutesCC() const;
    void recupGraphe(std::vector<bool> arete);

    void recupGraphe_Dessine(std::vector<bool> arete, Svgfile &svgout);


protected:

private:
    /// Le r�seau est constitu� d'une collection de sommets
    std::vector<Sommet*> m_sommets;//stock�e dans un vecteur (pointeur sur le sommet)
    std::vector<Arete*> m_aretes;//stock�e dans un vecteur (pointeur sur l'ar�te)
    //std::vector<std::vector<bool>> m_vecteur_test_pareto;
    //std::vector<std::vector<bool>> m_vecteur_test_dij;
    std::vector<PoidsTT*> m_PoidsTT;
    std::set<PoidsTT*>m_PoidsTT_Post_Pareto;
    std::vector<PoidsTT*>m_PoidsTT_Post_Dij;
    int m_nbCout, m_ordre;
};
#endif // GRAPHE_H
