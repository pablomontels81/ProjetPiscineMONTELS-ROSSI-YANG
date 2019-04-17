#include <fstream>
#include <iostream>
#include <sstream>
#include "graphe.h"

#include "algorithm"

graphe::graphe(std::string nomFichierSommets,std::string nomFichierPoids)
{
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
    for (int i=0; i<ordre; ++i)
    {
        ifsSommet>>id;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>x;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>y;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
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

    for (int i=0; i<taille1; i++)
    {
        ifsSommet>>id;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet1;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsSommet>>sommet2;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>Tampon;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>cout1;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        ifsPoids>>cout2;
        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_aretes.push_back(new Arete{id,cout1,cout2,sommet1,sommet2});
        //prenne l'id du sommet et ajoute le voisin
        //prenne l'id du voisin et ajoute le sommet
        for (size_t j = 0; j<m_sommets.size(); ++j)
        {
            if (m_sommets[j]->getId()==sommet1)
            {
                m_sommets[j]->ajouterVoisin(sommet2);
            }

            if (m_sommets[j]->getId()==sommet2)
            {
                m_sommets[j]->ajouterVoisin(sommet1);
                //std::cout<< "Voisin du" << j << "est " << sommet1 << std::endl;
            }
        }
    }

}

void graphe::Primcout1(Svgfile &svgout)
{
    //svgout.addGrid();
    std::vector<Arete*> graphe_prim;
    std::set<std::string> sommets_marques;

    /*for (auto a:m_aretes)
    {
        a->afficherIDArete();
    }*/

    ///TRI///

    triCout1();

    /*std::cout << "TRIER:" << std::endl;
    for (auto a:m_aretes)
    {
        a->afficherIDArete();
    }*/

    ///DEBUT PRIM///

    ///PREMIERE ARETE///
    graphe_prim.push_back(m_aretes[0]);
    m_aretes[0]->setMarq(true);
    int tamp0 = stoi(m_aretes[0]->getS1());
    int tamp00 = stoi(m_aretes[0]->getS2());
    m_sommets[tamp0]->setMarq(true);
    m_sommets[tamp00]->setMarq(true);

    ///LES AUTRES///

    int tamp1, tamp2;
    int stop = 0;
    int top = m_aretes.size();
    for (int i = 0; i<(m_sommets.size()-2); i++)
    {
        for (int j = 0; j<top; ++j)
        {
            if (m_aretes[j]->getMarq()!=true && stop==0)
            {
                tamp1 = stoi(m_aretes[j]->getS1());
                tamp2 = stoi(m_aretes[j]->getS2());

                if (m_sommets[tamp1]->getMarq()!= true && m_sommets[tamp2]->getMarq()== true)
                {
                   m_sommets[tamp1]->setMarq(true);
                   m_aretes[j]->setMarq(true);
                   graphe_prim.push_back(m_aretes[j]);
                   stop=1;
                }

                else if (m_sommets[tamp1]->getMarq()== true && m_sommets[tamp2]->getMarq()!= true)
                {
                    m_sommets[tamp2]->setMarq(true);
                    m_aretes[j]->setMarq(true);
                    graphe_prim.push_back(m_aretes[j]);
                    stop=1;
                }
            }
        }
        stop =0;
    }

    ///AFFICHAGE

    std::cout<<"Resultat Prim : Arbre couvrant de Poids Minimum: "<<std::endl;
    for (auto elemAretePrim : graphe_prim)
    {
        elemAretePrim->afficherIDArete();
    }
    for (auto elemAretePrim : graphe_prim)
    {
        elemAretePrim->dessinerChemin(svgout,m_sommets);
    }
    for (auto elemAretePrim : m_sommets)
    {
        elemAretePrim->dessinerSommetC(svgout);
    }
}

void graphe::afficher() const
{
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

}

void graphe::dessiner(Svgfile &svgout) const
{
    for (auto elemSommet : m_sommets)
    {
        elemSommet->dessinerSommet(svgout);
    }
    for (auto elemArete : m_aretes)
    {
        elemArete->dessinerGraphe(svgout,m_sommets);
    }
}

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

int graphe::eulerien(std::set <Sommet*> vec)
{
    int compt=0; //sert à compter le nbre de sommets paires
    int re=0;
    for(auto v : vec) //parcourt les sommets
    {

        compt+= v->Paire(); //regarde si les sommets sont paires grâce aux nbres de sommets voisins
    }

    if (compt == vec.size()) //tous les sommets sont paires
    {
        re = 2; //cycle
    }
    if (compt==(m_sommets.size()-2)) //2 sommets impaires : chaine
    {
        re = 1;
    }
    else
    {
        re  = 0;//pas eulerien
    }

    return re;
}

/*void graphe::Kruskal()
{
    Svgfile svgout;
    svgout.addGrid();
    std::vector<Arete*> graphe_kruskal;
    std::set<Sommet*> sommets_marques;

    for (auto a:m_aretes)
    {
        a->afficherIDArete();
    }

    ///TRI///
    triCout1();
    std::cout << "TRIER:" << std::endl;
    for (auto a:m_aretes)
    {
        a->afficherIDArete();
    }

    ///DEBUT KRUSKAL

    int taille = (m_sommets.size()-1);
    std::cout << "TAILLE " << taille << std::endl;
    int cmpt = 0;
    int val = 0;
    int marq;

    ///TEST KRUSKAL 1///

    for (auto a : m_aretes)
    {
        //si elem_arete_en_cours->getS1()==sommets_marques->getId()
        //auto test1 = std::find(sommets_marques->getId().begin(), sommets_marques->getId().end(), elem_arete_en_cours->getS1());
        //auto test2 = std::find(sommets_marques->getId().begin(), sommets_marques->getId().end(), elem_arete_en_cours->getS2());

        if (taille!=cmpt)
        {
            if(val==0)
            {
                //pour savoir si cycle ou pas, cycle retourne 2 donc  nous = 0
                for (int i = 0; i<m_sommets.size(); i++)
                {
                    std::string id_S1 = a->getS1();
                    std::string id_S2 = a->getS2();

                    //recupere les deux sommets qui correspodent au id pour avoir des types sommets
                    if (id_S1 == m_sommets[i]->getId()) ///et s'il na pas deja ete marque
                    {
                        sommets_marques.insert(m_sommets[i]);
                        //m_sommets[i]->afficherVoisins();
                    }

                    if (id_S2 == m_sommets[i]->getId()) ///et s'il na pas deja ete marque
                    {
                        sommets_marques.insert(m_sommets[i]);
                        m_sommets[i]->afficherVoisins(); //set enleve std::set< > (vector.begin,)  .insert custom predica lambda
                    }
                    val=eulerien(sommets_marques);
                }
                graphe_kruskal.push_back(a);
                cmpt = cmpt + 1;
                std::cout << "        cmpt = " << cmpt << std::endl;


            }
        }


    }
    for (auto s : sommets_marques)
    {
        s->afficherData();
    }

    std::cout << "VALEUR EULE " << val << std::endl;

    ///TEST KRUSKAL 2 ///

    std::string sommet1;
    std::string sommet2;
    int num1, num2, marq1, marq2;
    int cmpt = 0;
    int retiens;
    int taille = (m_sommets.size()-1);

    for (size_t i = 0; i< m_aretes.size(); ++i)
    {
        if(taille!=cmpt)
        {
            sommet1 = m_aretes[i]->getS1();
            num1 = std::stoi(sommet1);

            sommet2 = m_aretes[i]->getS2();
            num2 = std::stoi(sommet2);

            marq1 = sommets_marques[num1];
            marq2 = sommets_marques[num2];

            ///recuperer les indices du sommets_marques
            if (marq1 != marq2)
            {
                graphe_kruskal.push_back(m_aretes[i]);
                cmpt = cmpt + 1;
                for (int j = 0; j<sommets_marques.size(); j++)
                {
                }

                std::cout << "TAB TOUR " << i<< ":" << std::endl;
                for (auto s:sommets_marques)
                {
                    std::cout<< s << std::endl;
                }
            }
        }
    }

    ///TEST KRUSKAL 3 ///
    for (auto elem_arete_en_cours : m_aretes)
    {
        auto test1 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS1());
        auto test2 = std::find(sommets_marques.begin(), sommets_marques.end(), elem_arete_en_cours->getS2());
        if (
            (test1 == sommets_marques.end())&&(test2 == sommets_marques.end())
            ||
            (test1 != sommets_marques.end())&&(test2 == sommets_marques.end())
            ||
            (test1 == sommets_marques.end())&&(test2 != sommets_marques.end())
            //rajouter que cela ne doit pas faire de cycle si on ajoute les nouveaux sommets->regarder les voisins -> donc creer les voisins de mon sommet
        )
        {
            sommets_marques.push_back(elem_arete_en_cours->getS1());
            sommets_marques.push_back(elem_arete_en_cours->getS2());
            graphe_kruskal.push_back(elem_arete_en_cours);
        }
    }
    std::cout<<"Resultat Kruskal : Arbre couvrant de Poids Minimum: "<<std::endl;
    for (auto elemAreteKruskal : graphe_kruskal)
    {
        elemAreteKruskal->afficherIDArete();
    }

}*/


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
    //std::cout<<"Taille Du Graphe : "<<taille<<std::endl;
    //std::cout<<"Nbre de Combinaison : "<<NbreMaxCombinaison<<std::endl;

    for (int i=0; i<taille; i++)
    {
        vecteur_valeur_conversion.push_back(pow(2,i));
    }
    /*
    for (auto elemValeurConversion : vecteur_valeur_conversion)
    {
        std::cout<<elemValeurConversion<<std::endl;
    }
    */
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
                    //Test_Connexite++;
                }
                else
                {
                    NbreAMettreBinaire=NbreAMettreBinaire;
                    vecteur_temporaire.push_back(0);
                    //if (Test_Connexite = (ordre-1))
                    //{
                    //    Test_Connexite=Test_Connexite;
                    //}
                    //else
                    //{
                    //    Test_Connexite=0;
                    //}
                }

            }

        }while (rest == 0);//Condition de Sortie pour obtenir notre nombre binaire
        //Test Ajout de la Combinaison Binaire SSI Nbre Aretes = Ordre - 1
        if (Compteur_Nbre_Arete == (ordre-1)/*&&(Test_Connexite != (ordre-1))*/)
        {
            vecteur_enumeration_binaire.push_back(vecteur_temporaire);
        }
        vecteur_temporaire.clear();
    }
    /*
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
    */
    /*
    float CoutTT_Poids1_Binaire, CoutTT_Poids2_Binaire;
    for (auto elem_colonne : vecteur_enumeration_binaire)
    {
        for (auto elem_ligne : elem_colonne)
        {
            CoutTT_Poids1_Binaire = CoutTT_Poids1_Binaire + ( elem_ligne * m_aretes[taille-elem_ligne] )
        }
    }
    */

}



graphe::~graphe()
{
    //dtor
}
