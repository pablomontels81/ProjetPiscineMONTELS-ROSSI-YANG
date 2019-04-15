#ifndef ARETE_H_INCLUDED
#define ARETE_H_INCLUDED

#include <string>
#include <vector>
#include <unordered_map>
#include <unordered_set>


class Arete
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        Arete(std::string,float,float,double,double);
        //void ajouterArete(const Arete*);
        void afficherDataArete() const;
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
        double m_sommetdepart, m_sommetarrive; //Sommet départ et arrivée

};

#endif // ARETE_H_INCLUDED
