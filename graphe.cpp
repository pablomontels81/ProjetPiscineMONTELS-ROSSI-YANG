#include <fstream>
#include <iostream>
#include "graphe.h"
#include "algorithm"
#include "math.h"

///Fonction de récupération des DOnnées de l'Exercice (CONSTRUCTEUR)
graphe::graphe(std::string nomFichierSommets,std::string nomFichierPoids){
    //Ouverture FIchier Contenant les Poids
    std::ifstream ifsPoids{nomFichierPoids};
    if (!ifsPoids)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierPoids );
    //Ouverture Fichier Contenant les Sommets
    std::ifstream ifsSommet{nomFichierSommets};
    if (!ifsSommet)
        throw std::runtime_error( "Impossible d'ouvrir en lecture " + nomFichierSommets );

    int ordre;
    ifsSommet >> ordre;
    if ( ifsSommet.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string id;
    double x,y;
    //lecture des sommets
    for (int i=0; i<ordre; ++i){
        ifsSommet>>id; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>x; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>y; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_sommets.push_back(new Sommet{id,x,y});
    }

    int taille1,taille2, nbre;
    ifsPoids >> taille2 >> nbre;
    ifsSommet >> taille1;
    if (ifsPoids.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    if (ifsSommet.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    std::string Tampon;
    float cout1,cout2;
    std::string sommet1, sommet2;

    for (int i=0; i<taille1; i++){
        ifsSommet>>id; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet1; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>Tampon; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>cout1; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>cout2; if(ifsSommet.fail()) throw std::runtime_error("Probleme lecture données sommet");
        m_aretes.push_back(new Arete{id,cout1,cout2,sommet1,sommet2});
    }

}
///DESTRUCTEUR
graphe::~graphe()
{
    //dtor
}
/*
///Fonction de L'Algorithme de Prim pour les 2 pondérations
void graphe::Prim() const{
    std::vector<Arete*> graphe_Prim;
    std::vector
}
*/
///Fonction de l'Algorithme de Kruskal pour les 2 pondérations

void graphe::Kruskalcout1() const{
    std::vector<Arete*> graphe_kruskal;
    std::vector<std::string> sommets_marques;
    float CoutTT1;
    float CoutTT2;
    for (auto elem_arete_en_cours : m_aretes)
    {
        auto test1 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS1());
        auto test2 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS2());
        if ((test1 == sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 != sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 == sommets_marques.end())&&(test2 != sommets_marques.end())
            )
        {
            sommets_marques.push_back(elem_arete_en_cours->getS1());
            sommets_marques.push_back(elem_arete_en_cours->getS2());
            graphe_kruskal.push_back(elem_arete_en_cours);
        }
    }

    std::cout<<"Resultat Kruskal : Arbre couvrant de Poids Minimum en fonction du Cout 1: "<<std::endl;
    for (auto elemAreteKruskal : graphe_kruskal)
    {
        elemAreteKruskal->afficherIDArete();
    }
    for (auto elemCoutTT : graphe_kruskal)
    {
        CoutTT1=CoutTT1+elemCoutTT-> getCout1();
        CoutTT2=CoutTT2+elemCoutTT-> getCout2();
    }
    std::cout<<"Cout Total Du Kruskal [Cout1,Cout2]: [ "<<CoutTT1<<" , "<<CoutTT2<<" ]"<<std::endl;
}
void graphe::Kruskalcout2() const{
    std::vector<Arete*> graphe_kruskal;
    std::vector<std::string> sommets_marques;
    float CoutTT1;
    float CoutTT2;
    for (auto elem_arete_en_cours : m_aretes)
    {
        auto test1 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS1());
        auto test2 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS2());
        if ((test1 == sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 != sommets_marques.end())&&(test2 == sommets_marques.end())||
            (test1 == sommets_marques.end())&&(test2 != sommets_marques.end())
            )
        {
            sommets_marques.push_back(elem_arete_en_cours->getS1());
            sommets_marques.push_back(elem_arete_en_cours->getS2());
            graphe_kruskal.push_back(elem_arete_en_cours);
        }
    }
    std::cout<<"Resultat Kruskal : Arbre couvrant de Poids Minimum en fonction du Cout 2: "<<std::endl;
    for (auto elemAreteKruskal : graphe_kruskal)
    {
        elemAreteKruskal->afficherIDArete();
    }
    for (auto elemCoutTT : graphe_kruskal)
    {
        CoutTT1=CoutTT1+elemCoutTT-> getCout1();
        CoutTT2=CoutTT2+elemCoutTT-> getCout2();
    }
    std::cout<<"Cout Total Du Kruskal [Cout1,Cout2]: [ "<<CoutTT1<<" , "<<CoutTT2<<" ]"<<std::endl;
}
///Fonction d'Affichge des vecteurs de Sommets et d'Aretes de notre Graphe
void graphe::afficher() const{

    Svgfile svgout;

    std::cout<<"graphe : "<<std::endl;
    std::cout<<" ordre : "<<m_sommets.size()<<std::endl;
    std::cout<<"  sommet : "<<std::endl;
    for (auto elemSommet : m_sommets)
    {
        elemSommet->afficherData();
    }
    std::cout<<" taille : "<<m_aretes.size()<<std::endl;
    std::cout<<" arete : "<<std::endl;
    for (auto elemArete : m_aretes)
    {
        elemArete->afficherDataArete();
    }
    for (auto elemArete : m_aretes)
    {
        elemArete->dessinerArete(svgout,m_sommets);
    }
     for (auto elemSommet : m_sommets)
    {
        elemSommet->dessinerSommet(svgout);
    }

}
///Fonction de Trie Croissant des 2 Pondérations
std::vector<Arete*> graphe::triCout1()
{
    std::sort(m_aretes.begin(),m_aretes.end(),[](Arete* a1, Arete* a2)
    {
        return a1->getCout1() < a2->getCout1() ;
    });
}
std::vector<Arete*> graphe::triCout2()
{
    std::sort(m_aretes.begin(),m_aretes.end(),[](Arete* a1, Arete* a2)
    {
        return a1->getCout2() < a2->getCout2() ;
    });
}

///Fonction d'énumération binaire des 2^taille combinaisons
void graphe::EnumerationBinaire() const
{
    std::vector<std::vector<bool>> vecteur_enumeration_binaire;
    std::vector<int> vecteur_valeur_conversion;
    std::vector<std::vector<bool>> vecteur_enumeration_binaire_Trie1;
    std::vector<bool> vecteur_temporaire;
    double taille = m_aretes.size();
    int ordre = m_sommets.size();
    int valeur_comparaison;
    int rest;
    int NbreMaxCombinaison = pow(2,taille);
    int NbreAMettreBinaire;
    int Compteur_Nbre_Arete =0;
    int Test_Connexite =0;
    std::cout<<"Taille Du Graphe : "<<taille<<std::endl;
    std::cout<<"Nbre de Combinaison : "<<NbreMaxCombinaison<<std::endl;

    for (int i=0; i<taille; i++)
    {
        vecteur_valeur_conversion.push_back(pow(2,i));
    }
    for (auto elemValeurConversion : vecteur_valeur_conversion)
    {
        std::cout<<elemValeurConversion<<std::endl;
    }
    for (int Combinaison=0; Combinaison<NbreMaxCombinaison ;Combinaison++)
    {
        //Remise à zéro des variables de Test du Trie
        Compteur_Nbre_Arete = 0;
        Test_Connexite =0;
        NbreAMettreBinaire = Combinaison;
        do
        {
            for (int j=(taille-1); j>=0; j--)
            {
                if(NbreAMettreBinaire-pow(2,j) >= 0)
                {
                    NbreAMettreBinaire=NbreAMettreBinaire-pow(2,j);
                    vecteur_temporaire.push_back(1);
                    Compteur_Nbre_Arete++;
                    Test_Connexite++;
                }
                else
                {
                    NbreAMettreBinaire=NbreAMettreBinaire;
                    vecteur_temporaire.push_back(0);
                    if (Test_Connexite = (ordre-1))
                    {
                        Test_Connexite=Test_Connexite;
                    }
                    else
                    {
                        Test_Connexite=0;
                    }
                }

            }

        }while (rest == 0);//Condition de Sortie pour obtenir notre nombre binaire
        //Test Ajout de la Combinaison Binaire SSI Nbre Aretes = Ordre - 1
        if (Compteur_Nbre_Arete == (ordre-1)&&(Test_Connexite != (ordre-1)))
        {
            vecteur_enumeration_binaire.push_back(vecteur_temporaire);
        }
        vecteur_temporaire.clear();
    }

    for (auto elemColonne : vecteur_enumeration_binaire)
    {
        Compteur_Nbre_Arete = 0;
        for (auto elemLigne : elemColonne)
        {
            std::cout<<"  "<<elemLigne;
            if (elemLigne ==1)
                Compteur_Nbre_Arete=Compteur_Nbre_Arete+1;
        }
        std::cout<<"      Nbre de 1 : "<<Compteur_Nbre_Arete<<std::endl;
    }

    /*
    for (auto elemColonne : vecteur_enumeration_binaire)
    {
        for (auto elemLigne : elemColonne)
        {
            if (elemLigne == 1)
                Compteur_Nbre_Arete++;
        }
        if (Compteur_Nbre_Arete = (ordre-1))
        {

        }
    }
    */
}

