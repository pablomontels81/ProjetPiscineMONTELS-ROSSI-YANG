#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include"sommet.h"
#include"svgfile.h"
#include"util.h"


class Arete
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Arete(std::string,float,float,std::string,std::string);
        //void ajouterArete(const Arete*);
        void afficherDataArete() const;
        void afficherIDArete() const;
        float getCout1() const;
        float getCout2() const;
        std::string getS1();
        std::string getS2() const;
        void dessinerArete(Svgfile &fichier, std::vector<Sommet*> m_sommets);
        void dessinerChemin(Svgfile &fichier, std::vector<Sommet*> m_sommets);
        void setMarq(bool marq);
        bool getMarq();
        /*
        void afficherVoisinsPondere() const;
        ///méthode de parcours en largeur du graphe à partir du sommet
        ///renvoie les prédécesseurs sous forme d'une map (clé=id du sommet,valeur=id de son prédécesseur)
        std::unordered_map<std::string,std::string> parcoursBFS() const;
         ///méthode de parcours en profondeur du graphe à partir du sommet
        std::unordered_map<std::string,std::string> parcoursDFS() const;
        ///méthode qui recherche la composante connexe du sommet
        ///renvoie la liste des ids des sommets de la composante
        std::unordered_set<std::string> rechercherCC() const;
        */
        ~Arete();

    protected:

    private:

        /// Données spécifiques du sommet
        std::string m_id; // Identifiant
        float m_cout1, m_cout2; // Poids de l'arête
        std::vector<Sommet*> m_sommets;
        std::string m_sommetdepart, m_sommetarrive;
        bool m_marq = false; //Sommet départ et arrivée

};

#endif // ARETE_H_INCLUDED
