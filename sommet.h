#ifndef SOMMET_H_INCLUDED
#define SOMMET_H_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include"svgfile.h"
#include"util.h"


class Sommet
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Sommet(std::string,double,double);
        void ajouterVoisin(std::string);
        void afficherData() const;
        void afficherVoisins();
        void dessinerSommet(Svgfile &fichier);
        void dessinerSommetC(Svgfile &fichier, int dec);
        void dessinerT(Svgfile &fichier);
        ///m�thode de parcours en largeur du graphe � partir du sommet
        ///renvoie les pr�d�cesseurs sous forme d'une map (cl�=id du sommet,valeur=id de son pr�d�cesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///m�thode de parcours en profondeur du graphe � partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///m�thode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC() const;
        double getX();
        double getY();
        std::string getId();
        int Paire();
        bool getMarq();
        void setMarq(bool marq);
        ~Sommet();

    protected:

    private:
        /// Voisinage : liste d'adjacence
        std::vector<std::string> m_voisins;

        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        double m_x, m_y; // Position
        bool m_marq = false;

};


#endif // SOMMET_H_INCLUDED
