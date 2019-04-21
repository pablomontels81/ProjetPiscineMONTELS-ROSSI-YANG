#include <fstream>
#include <iostream>
#include <queue>
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
    m_ordre = ordre;
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
        for(int z = 0; z<nbre; z++)
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
                m_sommets[j]->ajouterVoisin(m_sommets[stoi(sommet2)]);
            }

            if (m_sommets[j]->getId()==sommet2)
            {
                m_sommets[j]->ajouterVoisin(m_sommets[stoi(sommet1)]);
            }
        }
    }

}

std::vector<Arete*> graphe::Prim(int num)
{
    std::vector<Arete*> graphe_prim;

    std::vector <Arete*> aretes = m_aretes;

    ///TRI///

    //triPoids(num);

    std::sort(aretes.begin(),aretes.end(),[num](Arete* a1, Arete* a2)
    {
        return a1->getPoids(num) < a2->getPoids(num) ;
    });

    ///DEBUT PRIM///

    ///PREMIERE ARETE///
    graphe_prim.push_back(aretes[0]);
    aretes[0]->setMarq(true);
    int tamp0 = stoi(aretes[0]->getS1());
    int tamp00 = stoi(aretes[0]->getS2());
    m_sommets[tamp0]->setMarq(true);
    m_sommets[tamp00]->setMarq(true);

    ///LES AUTRES///

    int tamp1, tamp2;
    int stop = 0;
    int top = aretes.size();
    for (size_t i = 0; i<(m_sommets.size()-2); i++)
    {
        for (int j = 0; j<top; ++j)
        {
            if (aretes[j]->getMarq()!=true && stop==0)
            {
                tamp1 = stoi(aretes[j]->getS1());
                tamp2 = stoi(aretes[j]->getS2());

                if (m_sommets[tamp1]->getMarq()!= true && m_sommets[tamp2]->getMarq()== true)
                {
                    m_sommets[tamp1]->setMarq(true);
                    aretes[j]->setMarq(true);
                    graphe_prim.push_back(aretes[j]);
                    stop=1;
                }

                else if (m_sommets[tamp1]->getMarq()== true && m_sommets[tamp2]->getMarq()!= true)
                {
                    m_sommets[tamp2]->setMarq(true);
                    aretes[j]->setMarq(true);
                    graphe_prim.push_back(aretes[j]);
                    stop=1;
                }

            }

        }
        stop =0;
    }

    return graphe_prim;
}

float graphe::Dijkstra(std::vector<bool>arete, int sommetdep)
{
    std::vector<int>m_dec;
    int m_marq;
    int compteur=0;
    float poidtt = 0;
    std::vector<Sommet*> sommets = m_sommets;
    std::vector<float> vecPoids;
    float poids;
    bool exist = false;
    int tamp1,tamp2,tampSommet,pred;

    for (int i = 0; i<m_ordre ; ++i)
    {
        sommets[i]->setMarq(false);
    }

    sommets[sommetdep]->setPoids(0);
    m_marq = sommetdep;
    sommets[sommetdep]->setMarq(true);

    for(size_t a = 0; a<m_sommets.size(); ++a)
    {
        do
        {
            for(size_t i =0; i<arete.size(); ++i)
            {
                tamp1 = stoi(m_aretes[i]->getS1()); ///changement de string en int
                tamp2 = stoi(m_aretes[i]->getS2());

                ///si arete marqué, aucun sommet marqué
                if(arete[i] == true && ((m_marq == tamp1)||(tamp2==m_marq))&& sommets[tamp1]->getMarq()!= sommets[tamp2]->getMarq())
                {
                    if (sommets[tamp1]->getMarq()!= true && sommets[tamp2]->getMarq()== true)
                    {
                        tampSommet = tamp1;///sommet selec pour devient decouvert
                        pred = tamp2; ///selecction du sommet précédent
                    }
                    if (sommets[tamp1]->getMarq()== true && sommets[tamp2]->getMarq()!= true)
                    {
                        tampSommet = tamp2;
                        pred = tamp1;
                    }
                    poids = sommets[pred]->getPoids() + m_aretes[i]->getPoids(1); ///valeur du poid
                    for(size_t j = 0; j< m_dec.size(); ++j) ///Parcour du vecteur dec
                    {
                        if(m_dec[j]==tampSommet) ///sommet selec est déja decc
                        {
                            if(poids<sommets[tampSommet]->getPoids())
                                sommets[tampSommet]->setPoids(poids);
                            exist=true; ///Sommet marqué
                        }
                    }
                    if(exist == false)
                    {
                        m_dec.push_back(tampSommet); ///ajout dans dec
                        sommets[tampSommet]->setPoids(poids);
                    }
                    exist=false;
                }
            }
            for(size_t j=0; j<m_dec.size(); ++j) ///parccour du dec pour ajoutet les poids
            {
                vecPoids.push_back(sommets[m_dec[j]]->getPoids());
            }
            std::sort(vecPoids.begin(),vecPoids.end(),[](float a1, float a2)
            {
                return a1 < a2 ;
            });
            for(size_t j=0; j<sommets.size(); ++j) ///parcour des sommets
            {
                if(sommets[j]->getPoids() == vecPoids[0] && sommets[j]->getMarq() == false) ///condition pour prendre le sommet avec poids minimum
                {
                    m_marq = j;
                    sommets[j]->setMarq(true); ///marq le sommet
                    compteur++;
                    for(size_t a =0; a<m_dec.size(); ++a)
                    {
                        if(m_dec[a] == j)
                        {
                            m_dec.erase(m_dec.begin()+a);///efface sommet qui est marqué
                        }
                    }
                    break;
                }
            }
            vecPoids.clear();

        }
        while(compteur != m_ordre-1);
    }

    for(int i = 0 ; i<m_ordre; ++i)
    {
        poidtt += sommets[i]->getPoids();
    }

    return poidtt;
}

float graphe::etape3(std::vector<bool>arete)
{
    float poidtt2 = 0;
    for(size_t i =0; i<arete.size(); ++i)
    {
        if(arete[i]==true)
        {
            poidtt2 += m_aretes[i]->getPoids(0);
        }
    }

    return poidtt2;
}

void graphe::DijkstraTout()
{
    Svgfile svgout ("etape3.svg");
    Svgfile svgout2 ("etape3_graphe.svg");

    std::vector<std::vector<bool>> vec = EnumerationBinaireDij();

    //std::cout << "TEST " << m_vecteur_test_dij[0][0] << std::endl;

    std::vector<bool>test;
    test.push_back(0);
    test.push_back(1);
    test.push_back(1);
    test.push_back(1);
    test.push_back(0);

    float poids = 0;
    float poids2 = 0;

    int x;
    int y;

    svgout.addLine(100,100,100,700,"black");
    svgout.addLine(100,700,1300,700,"black");

    svgout.addText(100,100,"cout 2","black");
    svgout.addText(1300,700,"cout 1","black");

    for (int j = 0; j<vec.size(); j++)
    {
        for (int i = 0; i < m_sommets.size(); ++i)
        {
            poids2 += Dijkstra(vec[j],i);
        }

        poids += etape3(vec[j]);
        std::cout << "*****POIDS du " << j << " : " << poids << " ; " << poids2 << std::endl;

        x = 10*poids;
        y = 1*poids2;

        svgout.addDisk(100+x,700-y,5,"red");
        svgout.addText(100+x,700-y,j,"black");

        poids = 0;
        poids2 = 0;


    }

    recupGraphe_Dessine(vec[0],svgout2);
}

void graphe::dessiner_Dijkstra()
{
    //je recuepere les valeurs des poids avec Dijkstra
    //
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


        svgout.addText(800, 100 + i*400,("(" + poids + ")"), "black");


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
    svgout.addText(600,50,texte,"black");

    for (auto elemSommet : m_sommets)
    {
        elemSommet->dessinerSommet(svgout);

    }
    for (auto elemArete : m_aretes)
    {
        elemArete->dessinerGraphe(svgout,m_sommets);
    }
}

void graphe::triPoids(int poid)
{
    std::sort(m_aretes.begin(),m_aretes.end(),[poid](Arete* a1, Arete* a2)
    {
        return a1->getPoids(poid) < a2->getPoids(poid) ;
    });
}

///Fonction d'énumération binaire des 2^taille combinaisons

void graphe::dessiner_Combinaison_Pareto()
{
    Svgfile fichier_pareto ("Pareto.svg");
    Svgfile fichier_graphe ("Graphe_Pareto.svg");
    std::vector<std::vector<bool>> m_vecteur_test_pareto = EnumerationBinairePareto();
    Pareto();

    fichier_pareto.addLine(100,700,1300,700,"black");
    fichier_pareto.addLine(100,100,100,700,"black");

    double x,y;
    for (auto elem_Pareto : m_PoidsTT_Post_Pareto)
    {
        //fichier_pareto.addGrid();
        x = 10*(double)elem_Pareto->getPoids1();
        y = 10*(double)elem_Pareto->getPoids2();
        if (elem_Pareto->getBool() != 0)
        {
            fichier_pareto.addDisk(100+x,700-y,5,"green");
        }
        else
        {
            fichier_pareto.addDisk(100+x,700-y,5,"red");
        }
        std::cout<<" [ "<<elem_Pareto->getPoids1()<<" , "<<elem_Pareto->getPoids2()<<" Favorable "<<elem_Pareto->getBool()<<std::endl;
    }


    /**boucle de dessin des graphes**/

    for (int i = 0; i < m_vecteur_test_pareto.size(); i++)
    {
        //std::cout << m_PoidsTT_Post_Pareto.size() << " TEST" << std::endl;
        //if(m_PoidsTT_Post_Pareto[i]->getBool() != 0)
        std::cout << "TEST DESSIN " << i << std::endl;
        recupGraphe_Dessine(m_vecteur_test_pareto[i], fichier_graphe);
    }
}



///Fonction d'énumération binaire des 2^taille combinaisons
std::vector<std::vector<bool>> graphe::EnumerationBinairePareto()
{
    Svgfile svgout("TEST.svg");
    std::vector<std::vector<bool>> vecteur_enumeration_binaire;
    std::vector<int> vecteur_valeur_conversion;
    std::vector<bool> vecteur_temporaire;
    std::vector<std::string> vecteur_sommet_parcourus;

    std::vector<std::vector<bool>> m_vecteur_test_pareto;

    size_t taille = m_aretes.size();
    size_t ordre = m_sommets.size();
    int rest =0;
    int NbreMaxCombinaison = pow(2,taille);
    int NbreAMettreBinaire;
    size_t Compteur_Nbre_Arete =0;
    //std::cout<<"Taille Du Graphe : "<<taille<<std::endl;
    //std::cout<<"Nbre de Combinaison : "<<NbreMaxCombinaison<<std::endl;

    for (size_t i=0; i<taille; i++)
    {
        vecteur_valeur_conversion.push_back(pow(2,i));
    }
    ///Trie Ordre 1
    for (int Combinaison=0; Combinaison<NbreMaxCombinaison ; Combinaison++)
    {
        //Remise à zéro des variables de Test du Trie
        vecteur_sommet_parcourus.clear();
        Compteur_Nbre_Arete = 0;
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
                }
                else
                {
                    NbreAMettreBinaire=NbreAMettreBinaire;
                    vecteur_temporaire.push_back(0);
                }

            }

        }

        while (rest != 0); //Condition de Sortie pour obtenir notre nombre binaire
        //Test Ajout de la Combinaison Binaire SSI Nbre Aretes = Ordre - 1

        if (Compteur_Nbre_Arete == (ordre-1))
        {
            recupGraphe(vecteur_temporaire);
            if(rechercher_afficherToutesCC() == 1)
                vecteur_enumeration_binaire.push_back(vecteur_temporaire);
        }
        ///on fait la deuxieme condition avec la connexite si conn
        vecteur_temporaire.clear();
    }
    ////////
    std::vector<float> coup;
    std::vector<std::string> m_vecteur_combinaison;
    for (size_t Num_Colonne = 0; Num_Colonne<vecteur_enumeration_binaire.size(); Num_Colonne++)
    {
        Compteur_Nbre_Arete = 0;

        float CoutTT1= 0, CoutTT2= 0;
        for (size_t Num_Ligne = 0; Num_Ligne < m_aretes.size(); Num_Ligne++)
        {
            if ( vecteur_enumeration_binaire[Num_Colonne][Num_Ligne] == 1)
            {
                auto result1 = std::find(vecteur_sommet_parcourus.begin(), vecteur_sommet_parcourus.end(), m_aretes[Num_Ligne]->getS1());
                auto result2 = std::find(vecteur_sommet_parcourus.begin(), vecteur_sommet_parcourus.end(), m_aretes[Num_Ligne]->getS2());
                if (result1 == vecteur_sommet_parcourus.end())
                {
                    vecteur_sommet_parcourus.push_back(m_aretes[Num_Ligne]->getS1());
                }
                if (result2 == vecteur_sommet_parcourus.end())
                {
                    vecteur_sommet_parcourus.push_back(m_aretes[Num_Ligne]->getS2());
                }
                CoutTT1 += m_aretes[Num_Ligne]->getPoids(0);
                CoutTT2 += m_aretes[Num_Ligne]->getPoids(1);
                m_vecteur_combinaison.push_back(m_aretes[Num_Ligne]->getId());
            }

        }
        //Condition de Connexité
        if (vecteur_sommet_parcourus.size() == ordre)
        {
            //Insertion des Combinaisons Valables à mon vecteur
            m_vecteur_test_pareto.push_back(vecteur_enumeration_binaire[Num_Colonne]);
            //Insertion des Poids Totaux Pour la Pondération 1 et 2 à mon vecteur dedié
            m_PoidsTT.push_back(new PoidsTT{CoutTT1,CoutTT2,false});

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

    return m_vecteur_test_pareto;
}



void graphe::Pareto()
{
    ///1. Trie Croissant
    PoidsTT* Valeur_Test1;
    PoidsTT* Valeur_Test2;

    std::sort(m_PoidsTT.begin(), m_PoidsTT.end(), [](PoidsTT* a, PoidsTT* b)
    {
        if (a->getPoids1() == b->getPoids1() && a->getPoids2() < b->getPoids2())
        {
            return a->getPoids1() > b->getPoids1();
        }
        return a->getPoids1() < b->getPoids1();
    });

    /*for (auto elem : m_PoidsTT)
    {
        system("PAUSE");
        std::cout<<" Nbre De Solution Pareto : "<<m_PoidsTT.size();
        std::cout<<" [ "<<elem->getPoids1()<<" , "<<elem->getPoids2()<<" ] "<<std::endl;
    }*/

    do
    {
        ///1.1 Récupération Des Premiers Couples Comme Valeur De Base
        Valeur_Test1 = m_PoidsTT.front();//1ere Valeur Du Vecteur
        m_PoidsTT.erase(m_PoidsTT.begin());
        Valeur_Test2 = m_PoidsTT.front();//2eme Valeur Du Vecteur
        ///Ajout Au Vecteur Final de mes bons Vecteurs (valeur TRUE)
        m_PoidsTT_Post_Pareto.insert(new PoidsTT {Valeur_Test1->getPoids1(),Valeur_Test1->getPoids2(),true});
        //m_PoidsTT_Post_Pareto.push_back(new PoidsTT {Valeur_Test1->getPoids1(),Valeur_Test1->getPoids2(),true});
        m_PoidsTT_Post_Pareto.insert(new PoidsTT {Valeur_Test2->getPoids1(),Valeur_Test2->getPoids2(),true});
        ///Boucle Pour Enlever les solutions dominées (en elevant dans la boucle la valeur qui nous sert de TEST
        for (size_t elem = 1; elem < m_PoidsTT.size(); elem ++)
        {
            if (//Le Poids1 de la combinaisons et supérieur que ma valeur de Test
                (m_PoidsTT[elem]->getPoids2() >= Valeur_Test2->getPoids2()||
                 m_PoidsTT[elem]->getPoids2() >= Valeur_Test1->getPoids2()
                )
            )
            {

                std::cout<<m_PoidsTT[elem]->getPoids1()<<"  ,  "<<m_PoidsTT[elem]->getPoids2()<<std::endl;
                ///Ajout Au Vecteur Final de mes Vecteurs dominés(valeur FALSE)
                m_PoidsTT_Post_Pareto.insert(new PoidsTT {m_PoidsTT[elem]->getPoids1(),m_PoidsTT[elem]->getPoids2(),false});
                ///Suppression des ces Vecteurs dominés de mon vecteur
                m_PoidsTT.erase(m_PoidsTT.begin()+elem);

            }
            {
                std::cout<<"TEST : "<<m_PoidsTT[elem]->getPoids1()<<"  ,  "<<m_PoidsTT[elem]->getPoids2()<<std::endl;
                ///Ajout Au Vecteur Final de mes Vecteurs dominés(valeur FALSE)
                m_PoidsTT_Post_Pareto.insert(new PoidsTT {m_PoidsTT[elem]->getPoids1(),m_PoidsTT[elem]->getPoids2(),false});
                ///Suppression des ces Vecteurs dominés de mon vecteur
                m_PoidsTT.erase(m_PoidsTT.begin()+elem);

            }
        }
    }
    while (m_PoidsTT.size() != 0);
}

std::vector<std::vector<bool>> graphe::EnumerationBinaireDij()
{
    //Svgfile svgout("TEST.svg");
    std::vector<std::vector<bool>> vecteur_enumeration_binaire;
    std::vector<int> vecteur_valeur_conversion;
    std::vector<bool> vecteur_temporaire;
    std::vector<std::string> vecteur_sommet_parcourus;

    std::vector<std::vector<bool>> m_vecteur_test_dij;

    size_t taille = m_aretes.size();
    size_t ordre = m_sommets.size();
    int rest =0;
    int NbreMaxCombinaison = pow(2,taille);
    int NbreAMettreBinaire;
    size_t Compteur_Nbre_Arete =0;
    //std::cout<<"Taille Du Graphe : "<<taille<<std::endl;
    //std::cout<<"Nbre de Combinaison : "<<NbreMaxCombinaison<<std::endl;

    for (size_t i=0; i<taille; i++)
    {
        vecteur_valeur_conversion.push_back(pow(2,i));
    }
    ///Trie Ordre 1
    for (int Combinaison=0; Combinaison<NbreMaxCombinaison ; Combinaison++)
    {
        //Remise à zéro des variables de Test du Trie
        vecteur_sommet_parcourus.clear();
        Compteur_Nbre_Arete = 0;
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
                }
                else
                {
                    NbreAMettreBinaire=NbreAMettreBinaire;
                    vecteur_temporaire.push_back(0);
                }

            }

        }

        while (rest != 0); //Condition de Sortie pour obtenir notre nombre binaire
        //Test Ajout de la Combinaison Binaire SSI Nbre Aretes = Ordre - 1

        if (Compteur_Nbre_Arete >= (ordre-1))
        {
            recupGraphe(vecteur_temporaire);
            if(rechercher_afficherToutesCC() == 1)
                vecteur_enumeration_binaire.push_back(vecteur_temporaire);
        }
        ///on fait la deuxieme condition avec la connexite si conn
        vecteur_temporaire.clear();
    }
    ////////
    std::vector<float> coup;
    std::vector<std::string> m_vecteur_combinaison;
    for (size_t Num_Colonne = 0; Num_Colonne<vecteur_enumeration_binaire.size(); Num_Colonne++)
    {
        Compteur_Nbre_Arete = 0;

        float CoutTT1= 0, CoutTT2= 0;
        for (size_t Num_Ligne = 0; Num_Ligne < m_aretes.size(); Num_Ligne++)
        {
            if ( vecteur_enumeration_binaire[Num_Colonne][Num_Ligne] == 1)
            {
                auto result1 = std::find(vecteur_sommet_parcourus.begin(), vecteur_sommet_parcourus.end(), m_aretes[Num_Ligne]->getS1());
                auto result2 = std::find(vecteur_sommet_parcourus.begin(), vecteur_sommet_parcourus.end(), m_aretes[Num_Ligne]->getS2());
                if (result1 == vecteur_sommet_parcourus.end())
                {
                    vecteur_sommet_parcourus.push_back(m_aretes[Num_Ligne]->getS1());
                }
                if (result2 == vecteur_sommet_parcourus.end())
                {
                    vecteur_sommet_parcourus.push_back(m_aretes[Num_Ligne]->getS2());
                }
                CoutTT1 += m_aretes[Num_Ligne]->getPoids(0);
                CoutTT2 += m_aretes[Num_Ligne]->getPoids(1);
                m_vecteur_combinaison.push_back(m_aretes[Num_Ligne]->getId());
            }

        }
        //Condition de Connexité
        if (vecteur_sommet_parcourus.size() == ordre)
        {
            //Insertion des Combinaisons Valables à mon vecteur
            m_vecteur_test_dij.push_back(vecteur_enumeration_binaire[Num_Colonne]);
            //Insertion des Poids Totaux Pour la Pondération 1 et 2 à mon vecteur dedié
            m_PoidsTT.push_back(new PoidsTT{CoutTT1,CoutTT2,false});

        }
    }

    ///Boucle d'Affichage

    for (auto elemColonne : m_vecteur_test_dij)
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

    return m_vecteur_test_dij;
}


std::string graphe::changement_float(float val)
{
    std::ostringstream o;
    o << val;
    return o.str();
}

void graphe::recupGraphe(std::vector<bool> arete)
{
    std::vector<Sommet*> sommets;
    for(size_t a=0; a<m_sommets.size(); ++a)
    {
        sommets.push_back(new Sommet{m_sommets[a]->getId(), m_sommets[a]->getX(),m_sommets[a]->getY()});
    }
    for(size_t a=0; a<m_aretes.size(); a++)
    {
        if(arete[a]==true)
        {
            sommets[std::stoi(m_aretes[a]->getS1())]->ajouterVoisin(sommets[std::stoi(m_aretes[a]->getS2())]);
            sommets[std::stoi(m_aretes[a]->getS2())]->ajouterVoisin(sommets[std::stoi(m_aretes[a]->getS1())]);
        }
    }
    m_sommets = sommets;
}


int graphe::rechercher_afficherToutesCC() const
{
    int i=0; ///compteur composantes connexes (cc)
    //std::cout<<"composantes connexes :"<<std::endl;
    std::unordered_set<std::string> cc; //stocke identifant cc dans un set

    for(const auto &test : m_sommets) //parcours les sommets
    {
        if (cc.count((test)->getId())== 0)//check si marqué ou pas
        {
            i++; ///ajoute car cc
            // std::cout<<"cc"<<i<<std::endl; //affiche numero cc
            (test)->rechercherCC(cc); //cherche tous les sommets de la cc
            //std::cout<<std::endl;
        }
    }
    return i;
}

void graphe::recupGraphe_Dessine(std::vector<bool> arete, Svgfile &svgout)
{
    std::vector<Sommet*> sommets;
    std::vector<Arete*> aretes;
    for(size_t a=0; a<m_sommets.size(); ++a)
    {
        sommets.push_back(new Sommet{m_sommets[a]->getId(), m_sommets[a]->getX(),m_sommets[a]->getY()});
    }
    for(size_t a=0; a<m_aretes.size(); a++)
    {
        if(arete[a]==true)
        {
            aretes.push_back(new Arete{m_aretes[a]->getId(), {m_aretes[a]->getPoids(0),m_aretes[a]->getPoids(1)}, m_aretes[a]->getS1(), m_aretes[a]->getS2()});
        }
    }

    for (int i = 0; i < sommets.size(); ++i)
    {
        sommets[i]->dessinerSommet(svgout);
    }

    for (int i = 0; i < aretes.size(); ++i)
    {
        aretes[i]->dessinerGraphe(svgout, sommets);
    }
}


graphe::~graphe()
{
    //dtor
}
