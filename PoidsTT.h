#ifndef POIDSTT_H_INCLUDED
#define POIDSTT_H_INCLUDED

class PoidsTT
{
    public:
        ///constructeur qui reçoit en params les données du sommet
        PoidsTT(float,float,bool);
        float getPoids1() const;
        float getPoids2() const;
        ~PoidsTT();

    protected:

    private:

        /// Données spécifiques du Poids
        float Poids1;
        float Poids2;
        bool F_P;
};

#endif // POIDSTT_H_INCLUDED
