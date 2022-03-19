#include "algorithms.h"

void distance(const vector<int> fs, const vector<int> aps, int s, vector<int>& dist)
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
