#include "algorithms.h"

void distance(const vector<int>& fs, const vector<int>& aps, int s, vector<int>& dist)
{
   int n = aps[0];
   int it, iit; ///@todo - Que faire avec ça?
   vector<int> fa; //file d'attente
   fa.reserve(n+1);
   int t = 0 , q = 1, p = 1, d = 0;
   fa[1] = s;

   //Par défaut l'infini vaut -1
   for(int i=1; i <= n; ++i)
   {
       dist[i] = -1;
   }

   while(t < q) //Tant que la file d'attente n'est pas vide
   {
       ++d;
       q = p;
       while(t < q)
       {
           ++t;
           s = fa[t];
           it = aps[s];
           iit = fs[it];
       }
   }
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
    vector<int> rangT;
    rang(rangT, FS, APS);

    cout<<"Rang : "<<endl;
    cout<<"APS : ";
    for(unsigned i = 0 ; i < APS.size(); i++)
        cout<<APS[i];
    cout<<"FS : ";
    for(unsigned i = 0 ; i < FS.size(); i++)
        cout<<FS[i];
    for(unsigned i = 0 ; i < rangT.size(); i++)
         cout<<rangT[i];
}
