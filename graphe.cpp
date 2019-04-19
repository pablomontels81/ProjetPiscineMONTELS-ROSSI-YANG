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
    if (ifsSommet.fail() )
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



    int taille1, taille2, nbre;
    ifsPoids >> taille2 >> nbre;
    ifsSommet >> taille1; //nbre d'aretes
    if (ifsPoids.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    if (ifsSommet.fail() )
        throw std::runtime_error("Probleme lecture ordre du graphe");
    m_nbCout = nbre;

    std::string Tampon;
    std::vector<float>poid(nbre);
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
        for(size_t z = 0; z<nbre; z++)
        {
            ifsPoids >> poid[z];
            if (ifsPoids.fail())
                throw std::runtime_error("Probleme lecture données sommet");
        }

        if(ifsSommet.fail())
            throw std::runtime_error("Probleme lecture données sommet");
        m_aretes.push_back(new Arete{id,poid,sommet1,sommet2});
        //prenne l'id du sommet et ajoute le voisin
        //prenne l'id du voisin et ajoute le sommet

        ///VOISINS

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

std::vector<Arete*> graphe::Prim(int num)
{
    //svgout.addGrid();

    std::vector<Arete*> graphe_prim;

    /*for (auto a:m_aretes)
    {
        a->afficherIDArete();
    }*/

    ///TRI///

    triPoids(num); //soit 0 ou 1
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
    for (size_t i = 0; i<(m_sommets.size()-2); i++)
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

    return graphe_prim;
}

void graphe::dessinerCheminPrim(Svgfile &svgout)
{

    std::vector<Arete*> graphe_prim1;

    std::vector<float> coup;



    for (int i=0; i<m_nbCout; i++)
    {
        for(int z=0; z<m_nbCout; ++z)
        {
            coup.push_back(0);
        }
        graphe_prim1 = Prim(i);

        std::cout<<"Resultat Prim : Arbre couvrant de Poids Minimum: "<<std::endl;
        for (auto elemAretePrim : graphe_prim1)
        {
            elemAretePrim->afficherIDArete();
        }

        for (auto elemAretePrim : graphe_prim1)
        {
            elemAretePrim->dessinerChemin(svgout,m_sommets,i*370);
        }
        for (auto elemAretePrim : m_sommets)
        {
            elemAretePrim->dessinerSommetC(svgout,i*370);
        }

        for(size_t j=0; j< graphe_prim1.size(); ++j)
        {
            if(graphe_prim1[j]->getMarq()==true)
            {
                for(int a=0; a<m_nbCout; ++a)
                {
                    coup[a] += graphe_prim1[j]->getPoids(a);
                }
            }
        }

        std::string poids;


        std::cout<< "(";
        for(int a=0; a<m_nbCout-1; ++a)
        {
            std::cout<<coup[a]<< ";";
            poids = changement_float(coup[a]) + ";" + poids;
        }
        std::cout << coup[m_nbCout-1] << ")" << std::endl;

        poids = poids + changement_float(coup[m_nbCout-1]);


        svgout.addText(800 , 100 + i*400,("(" + poids + ")"), "black");


        for (auto s : m_sommets)
        {
            s->setMarq(false);
        }

        for (auto a : m_aretes)
        {
            a->setMarq(false);
        }

        coup.clear();
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

void graphe::dessinerGraphe(Svgfile &svgout,std::string texte) const
{
    svgout.addText(600,50,texte,"balck");

    for (auto elemSommet : m_sommets)
    {
        elemSommet->dessinerSommet(svgout);

    }
    for (auto elemArete : m_aretes)
    {
        elemArete->dessinerGraphe(svgout,m_sommets);
    }
}

std::vector<Arete*> graphe::triPoids(int poid)
{
    std::sort(m_aretes.begin(),m_aretes.end(),[poid](Arete* a1, Arete* a2)
    {
        return a1->getPoids(poid) < a2->getPoids(poid) ;
    });
}

/*std::vector<Arete*> graphe::triCout2()
{
    std::sort(m_aretes.begin(),m_aretes.end(),[](Arete* a1, Arete* a2)
    {
        return a1->getCout2() < a2->getCout2() ;
    });
}*/

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

///Fonction d'énumération binaire des 2^taille combinaisons

void graphe::dessiner_Combinaison_Pareto(Svgfile &svgout) const
{

    //Récupération des ID des Aretes a Dessiner
    std::vector<std::string> m_vecteur_aretes_pareto;
    for (int Num_Colonne = 0; Num_Colonne<m_vecteur_test_pareto.size(); Num_Colonne++)
    {
        m_vecteur_aretes_pareto.clear();
        for (int Num_Ligne = 0; Num_Ligne<m_aretes.size(); Num_Ligne++)
        {
            if ( m_vecteur_test_pareto[Num_Colonne][Num_Ligne] == 1)
            {
                m_vecteur_aretes_pareto.push_back(m_aretes[Num_Ligne]->getId());
            }

            ///Place là l'affichage !!!!!!///


        }
    }
}


///Fonction d'énumération binaire des 2^taille combinaisons
void graphe::EnumerationBinaire()
{
    std::vector<std::vector<bool>> vecteur_enumeration_binaire;
    std::vector<int> vecteur_valeur_conversion;
    std::vector<bool> vecteur_temporaire;
    std::set<std::string> vecteur_sommet_parcourus;
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
    ///Trie Ordre 1
    for (int Combinaison=0; Combinaison<NbreMaxCombinaison ;Combinaison++)
    {
        //Remise à zéro des variables de Test du Trie
        vecteur_sommet_parcourus.clear();
        Compteur_Nbre_Arete = 0;
        Test_Connexite =0;
        NbreAMettreBinaire = Combinaison;
        do
        {
            //Re-Initialisation du vecteur
            //vecteur_sommet_parcourus.erase();
            for (int j=(taille-1); j>=0; j--)
            {
                if(NbreAMettreBinaire-pow(2,j) >= 0)
                {
                    NbreAMettreBinaire=NbreAMettreBinaire-pow(2,j);
                    vecteur_temporaire.push_back(1);
                    //vecteur_sommet_parcourus.push_back(m_aretes[j]->getS1());
                    //vecteur_sommet_parcourus.push_back(m_aretes[j]->getS2());
                    Compteur_Nbre_Arete++;
                    /*
                    if (Test_Connexite == ((ordre-1)-1))
                    {
                        Test_Connexite = Test_Connexite;
                    }
                    else
                    {
                        Test_Connexite = 0;
                    }
                    */
                }
                else
                {
                    NbreAMettreBinaire=NbreAMettreBinaire;
                    vecteur_temporaire.push_back(0);
                    /*Test_Connexite++;*/
                }

            }

        }while (rest == 0);//Condition de Sortie pour obtenir notre nombre binaire
        //Test Ajout de la Combinaison Binaire SSI Nbre Aretes = Ordre - 1

        if (Compteur_Nbre_Arete == (ordre-1))
        {
            vecteur_enumeration_binaire.push_back(vecteur_temporaire);
        }
        vecteur_temporaire.clear();
    }
    ///Trie Ordre 2
    for (int Num_Colonne = 0; Num_Colonne<vecteur_enumeration_binaire.size(); Num_Colonne++)
    {
        float cout1=0, cout2=0;
        Compteur_Nbre_Arete = 0;
        //system("PAUSE");
        vecteur_sommet_parcourus.clear();
        for (int Num_Ligne = 0; Num_Ligne<m_aretes.size(); Num_Ligne++)
        {
            std::cout<<"  "<<vecteur_enumeration_binaire[Num_Colonne][Num_Ligne];
            if ( vecteur_enumeration_binaire[Num_Colonne][Num_Ligne] == 1)
            {
                vecteur_sommet_parcourus.insert(m_aretes[Num_Ligne]->getS1());
                vecteur_sommet_parcourus.insert(m_aretes[Num_Ligne]->getS2());
                cout1 += m_aretes[Num_Ligne]->getPoids(1);
                cout2 += m_aretes[Num_Ligne]->getPoids(2);
            }

        }
        std::cout<<"      Nbre de Sommets Parcourus : "<<vecteur_sommet_parcourus.size()<<std::endl;
        //Condition de Connexité
        if (vecteur_sommet_parcourus.size() == ordre)
        {
            //Insertion des Combinaisons Valables à mon vecteur
            m_vecteur_test_pareto.push_back(vecteur_enumeration_binaire[Num_Colonne]);
            //Insertion des Poids Totaux Pour la Pondération 1 et 2 à mon vecteur dedié
            m_PoidsTT.push_back(new PoidsTT{cout1,cout2,false});

        }
    }

    ///Boucle d'Affichage

    for (auto elemColonne : m_vecteur_test_pareto)
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

}



void graphe::Pareto()
{
    ///1. Trie Croissant
    PoidsTT* Valeur_Test_Debut;
    PoidsTT* Valeur_Test_Fin;
    //float Valeur_Test_Debut, Valeur_Test_Fin;
    std::sort(m_PoidsTT.begin(), m_PoidsTT.end(), [](PoidsTT* a, PoidsTT* b) {
        return a->getPoids1() > b->getPoids2();
    });
    do
    {
        ///1.1 Récupération Des Premiers Couples Comme Valeur De Base
        Valeur_Test_Debut = m_PoidsTT.front();//1ere Valeur Du Vecteur
        m_PoidsTT.erase(m_PoidsTT.begin());
        Valeur_Test_Fin = m_PoidsTT.front();//2eme Valeur Du Vecteur

        ///Ajout Au Vecteur Final de mes bons Vecteurs (valeur TRUE)
        m_PoidsTT_Post_Pareto.push_back(new PoidsTT {Valeur_Test_Debut->getPoids1(),Valeur_Test_Debut->getPoids2(),true});
        m_PoidsTT_Post_Pareto.push_back(new PoidsTT {Valeur_Test_Fin->getPoids1(),Valeur_Test_Fin->getPoids2(),true});

        ///Boucle Pour Enlever les solutions dominées (en elevant dans la boucle la valeur qui nous sert de TEST
        for (int elem = 1; elem < m_PoidsTT.size(); elem ++)
        {
            if (
                (m_PoidsTT[elem]->getPoids1() > Valeur_Test_Fin->getPoids1())&& //Le Poids1 de la combinaisons et supérieur que ma valeur de Test
                ( (m_PoidsTT[elem]->getPoids2() > Valeur_Test_Fin->getPoids2()) && (m_PoidsTT[elem]->getPoids2() < Valeur_Test_Debut->getPoids2()) )
                )
            {
                ///Ajout Au Vecteur Final de mes Vecteurs dominés(valeur FALSE)
                m_PoidsTT_Post_Pareto.push_back(new PoidsTT {m_PoidsTT[elem]->getPoids1(),m_PoidsTT[elem]->getPoids2(),false});
                ///Suppression des ces Vecteurs dominés de mon vecteur
                m_PoidsTT.erase(m_PoidsTT.begin()+elem);
            }
        }
    }
    while (m_PoidsTT.size() != 0);



}




std::string graphe::changement_float(float val)
{
    std::ostringstream o;
    o << val;
    return o.str();
}



graphe::~graphe()
{
    //dtor
}
