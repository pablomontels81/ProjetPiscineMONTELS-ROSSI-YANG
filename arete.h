#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


class Arete
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        Arete(std::string,float,float,double,double);
        //void ajouterArete(const Arete*);
        void afficherDataArete() const;
        /*
        void afficherVoisinsPondere() const;
        ///m�thode de parcours en largeur du graphe � partir du sommet
        ///renvoie les pr�d�cesseurs sous forme d'une map (cl�=id du sommet,valeur=id de son pr�d�cesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///m�thode de parcours en profondeur du graphe � partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///m�thode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC() const;
        */
        ~Arete();

    protected:

    private:

        /// Donn�es sp�cifiques du sommet
        std::string m_id; // Identifiant
        float m_cout1, m_cout2; // Poids de l'ar�te
        double m_sommetdepart, m_sommetarrive; //Sommet d�part et arriv�e

};

#endif // ARETE_H_INCLUDED
