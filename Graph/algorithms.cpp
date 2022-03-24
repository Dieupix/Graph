#include "algorithms.h"

void descente_largeur(int r,const vector<int>& fs, const vector<int>& aps, vector<int>& dist)
{
    int nb_sommets = aps[0];
    int i = 0;
    int j = 1;
    int k = 0;
    int ifin;
    int s;
    int t;
    int it;
    //int* fil = new int[nb_sommets+1];
    vector<int> fil(nb_sommets+1);
    fil[0] = nb_sommets;
    dist.resize(nb_sommets+1);
    dist[0] = nb_sommets;
    fil[1] = r;

    for(int h = 1 ; h <= nb_sommets ; ++h)
    {
        dist[h] = -1;
    }
    dist[r] = 0;

    while(i<j) //Tq la file d'attente n'est pas vide
    {
        ++k;
        ifin = j;
        while(i<ifin) //On parcourt le bloc courant
        {
            ++i;
            s = fil[i];
            it = aps[s];
            t = fs[it];
            while(t>0) //On parcourt tous les successeurs de chaque sommet du bloc courant
            {
                if(dist[t] == -1) //Si le successeur du sommet courant n'est pas encore marqué
                {
                    ++j;
                    fil[j] = t; //On le place dans le bloc suivant en préparation et on lui affecte la distance courante
                    dist[t] = dist[fil[i]]+1;//dist[t] = k;//Variante : dist[t] = dist[fil[i]]+1;
                }
                t = fs[++it];
            }
        }
    }
}
void Mat_distance(const vector<int>& FS, const vector<int>& APS, vector<vector<int>>& matriceDistance)
{
    int n = APS[0];
    matriceDistance.resize(n+1);
    for(int r = 1 ; r <= n ; r++)
    {
        descente_largeur(r,FS,APS,matriceDistance[r]);
    }
    matriceDistance[0][0] = n;
}

void empiler (int x, vector<int>& pilch)
{
    pilch[x] = pilch[0];
    pilch[0] = x;
}

void demi_degre_interieur(const vector<int>& FS, const vector<int>& APS, vector<int> &DDI)
{
    DDI.resize(APS[0] + 1);
    DDI[0] = APS[0];
    for(int i = 1; i <= APS[0]; ++i)
    {
        DDI[i] = 0;
    }
    for(int i = 1; i < FS[0]; ++i)
    {
        if(FS[i] != 0)
            DDI[FS[i]]++;
    }
}

void rang(vector<int>& rang, const vector<int>& fs, const vector<int>& aps)
{
        int n = aps[0];
        int s,rangActuel,h,t;
        rang.resize(n+1);
        vector<int> pilch(n+1);
        vector<int> prem(n+1);

        vector<int> ddi;
        demi_degre_interieur(fs, aps, ddi);

        //Initialisation à -1
        pilch[0] = 0;
        for(s = 1; s <= n; s++)
        {
            rang[s] = -1; // n : nombre de sommets de G represente l'infini
            if (ddi[s] == 0)
                empiler(s,pilch);
        }

        rangActuel = -1;
        s = pilch[0];
        prem[0] = s;

        while (pilch[0] > 0)
        {
            rangActuel++;
            pilch[0] = 0;
            while (s > 0)
            {
                rang[s] = rangActuel;
                h = aps[s];
                t = fs[h];
                while (t > 0)
                    {
                    ddi[t]--;
                    if (ddi[t] == 0)
                        empiler(t,pilch);
                    h++;
                    t=fs[h];
                }
                s = pilch[s];
            }
            s = pilch[0];
            prem[rangActuel+1] = s;
        }
}

void rangToString(const vector<int>& FS, const vector<int>& APS)
{
    // ON VA PAS SE MENTIR MAIS C'EST PAAAAS VRAIMENT UN TO_STRING QUOI

    vector<int> rangT;
    rang(rangT, FS, APS);

    cout<<"Rang : "<<endl;
    cout<<"APS : ";
    for(unsigned i = 0 ; i < APS.size(); i++)
        cout<<APS[i]<<", ";
    cout << endl;
    cout<<"FS : ";
    for(unsigned i = 0 ; i < FS.size(); i++)
        cout<<FS[i]<<", ";
    cout << endl;
    cout << "RangT : ";
    for(unsigned i = 0 ; i < rangT.size(); i++)
         cout<<rangT[i]<<", ";
    cout << endl;
}
