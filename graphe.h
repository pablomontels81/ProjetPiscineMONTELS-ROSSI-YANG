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
    void EnumerationBinairePareto();
    void dessiner_Combinaison_Pareto(Svgfile &fichier_pareto);


    std::string changement_float (float val);
    int rechercher_afficherToutesCC() const;
    void recupGraphe(std::vector<bool> arete);


protected:

private:
    /// Le réseau est constitué d'une collection de sommets
    std::vector<Sommet*> m_sommets;//stockée dans un vecteur (pointeur sur le sommet)
    std::vector<Arete*> m_aretes;//stockée dans un vecteur (pointeur sur l'arête)
    std::vector<std::vector<bool>> m_vecteur_test_pareto;
    std::vector<std::vector<bool>> m_vecteur_test_dij;
    std::vector<PoidsTT*> m_PoidsTT;
    std::set<PoidsTT*>m_PoidsTT_Post_Pareto;
    std::vector<PoidsTT*>m_PoidsTT_Post_Dij;
    int m_nbCout, m_ordre;
};
#endif // GRAPHE_H
