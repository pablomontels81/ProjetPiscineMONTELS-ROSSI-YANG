#ifndef POIDSTT_H_INCLUDED
#define POIDSTT_H_INCLUDED

class PoidsTT
{
    public:
        ///constructeur qui re�oit en params les donn�es du sommet
        PoidsTT(float,float,bool);
        float getPoids1() const;
        float getPoids2() const;
        ~PoidsTT();

    protected:

    private:

        /// Donn�es sp�cifiques du Poids
        float Poids1;
        float Poids2;
        bool F_P;
};

#endif // POIDSTT_H_INCLUDED
