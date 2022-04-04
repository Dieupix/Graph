#include "algorithms.h"

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

void empiler (int x, vector<int>& pilch)
{
    pilch[x] = pilch[0];
    pilch[0] = x;
}

void fortconnexe(const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem)
{
    int n = APS[0], p = 0;

    cfc.clear();
    cfc.resize(n + 1);

    pilch.clear();
    pilch.resize(n + 1);

    pred.clear();
    pred.resize(n + 1, 0);

    prem.clear();
    prem.resize(n + 1);

    vector<int> tarj;
    tarj.reserve(n + 1);
    vector<bool> entarj(n + 1, true);
    vector<int> num(n + 1, 0);
    vector<int> ro(n + 1, 0);

    int k = 0;

    pilch[0] = 0;

    for(int s = 1; s <= n; ++s)
    {
        if(num[s] == 0)
        {
            traversee(s, p, k, FS, APS, cfc, pilch, pred, prem, tarj, entarj, num, ro);
        }
    }

    prem[0] = k;

    cout << "num:   "; printVector(num);
    cout << "ro:    "; printVector(ro);
}

void mat_distance(const vector<int>& FS, const vector<int>& APS, vector<vector<int>>& matriceDistance)
{
    int n = APS[0];
    matriceDistance.resize(n+1);
    for(int r = 1 ; r <= n ; r++)
    {
        descente_largeur(r,FS,APS,matriceDistance[r]);
    }
    matriceDistance[0][0] = n;
}

void printVector(const vector<int>& v)
{
    unsigned i = 0;
    cout << "[";
    for(i = 0; i < v.size() - 1; ++i)
    {
        cout << v[i] << ", ";
    }
    cout << v[i] << "]\n";
}

void Prufer_encode(vector<vector<int>> mat, vector<int>& p)
{
    unsigned n = mat[0][0];
    p.clear();
    p.resize(n-1);
    p[0] = n-2;

    for(unsigned i = 1; i <= n; ++i)
    {
        mat[i][0] = 0;
        for(unsigned j = 1; j <= n; ++j)
        {
            mat[i][0] += mat[i][j];
        }
    }

    for(unsigned k = 1; k <= n-2; ++k)
    {
        int i = 1, j = 1;
        while(mat[i][0] != 1) ++i;
        while(mat[i][j] != 1) ++j;

        p[k] = j;
        mat[i][j] = 0;
        mat[j][i] = 0;
        mat[i][0] = 0;
        --mat[j][0];
    }
}

void Prufer_decode(const vector<int>& p, vector<vector<int>>& mat)
{
    unsigned m = p[0], n = m + 2;
    vector<int> s(m + 3);

    mat.clear();
    mat.resize(n + 1);
    for(unsigned i = 0; i <= n; ++i) mat[i].resize(n + 1, 0);

    for(unsigned i = 1; i <= n; ++i) s[i] = 0;
    for(unsigned i = 1; i <= m; ++i) ++s[p[i]];

    for(unsigned i = 1; i <= m; ++i)
    {
        unsigned k = 1;
        while(s[k] != 0) ++k;

        mat[p[i]][k] = 1;
        mat[k][p[i]] = 1;

        s[k] = -1;
        --s[p[i]];
    }

    int k = -1;
    for(unsigned i = 1; i <= n; ++i)
    {
        if(s[i] == 0)
        {
            if(k == -1) k = i;
            else
            {
                mat[i][k] = 1;
                mat[k][i] = 1;
            }
        }
    }
}

void rang(vector<int>& rang, const vector<int>& fs, const vector<int>& aps)
{
        int n = aps[0];
        int s,rangActuel,h,t;
        rang.resize(n+1);
        vector<int> pilch(n+1);
        vector<int> prem(n+1);
        rang[0] = n;
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

void Tarjan(const vector<int>& FS, const vector<int>& APS)
{
    vector<int> cfc, pilch, pred, prem;
    fortconnexe(FS, APS, cfc, pilch, pred, prem);

    cout << "cfc:   "; printVector(cfc);
    cout << "pilch: "; printVector(pilch);
    cout << "pred:  "; printVector(pred);
    cout << "prem:  "; printVector(prem);
}

void traversee(int s, int& p, int& k, const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem, vector<int>& tarj, vector<bool>& entarj, vector<int>& num, vector<int>& ro)
{
    ++p;
    num[s] = p;
    ro[s] = p;

    tarj.push_back(s);
    //entarj[s] = true;

    int i = APS[s];
    int t = FS[i];
    while(t != 0)
    {
        if(num[t] == 0)
        {
            pred[t] = i;
            traversee(t, p, k, FS, APS, cfc, pilch, pred, prem, tarj, entarj, num, ro);
            if(ro[t] < ro[s]) ro[s] = ro[t];
            else if(num[t] < ro[s] and entarj[t]) ro[s] = num[t];
        }

        ++i;
        t = FS[i];
    }

    if(ro[s] == num[s]) ++k;

    int u = 0;
    do
    {
        u = tarj.back();
        tarj.pop_back();
        entarj[u] = false;
        empiler(u, pilch);
        cfc[u] = k;
    } while(u != s);

    prem[s] = pilch[0];
    pilch[0] = 0;
}

void Ordonnancement(const vector<int> file_pred, const vector<int> adr_prem_pred, const vector<int> duree_taches, vector<int>& file_pred_critique, vector<int>& adr_prem_pred_critique, vector<int>& longueur_critique)
{
    int n = adr_prem_pred[0];
    int m = file_pred[0];

    file_pred_critique.resize(m+1);
    adr_prem_pred_critique.resize(n+1);

    adr_prem_pred_critique[0] = n;

    longueur_critique.resize(n+1);
    longueur_critique[0] = n;

    int kc = 1; //Indice de la dernière place remplie dans fpc
    int t, lg; //la longueur lg de la tâche t
    longueur_critique[1] = 0;
    file_pred_critique[1] = 0; //Fin de la liste
    adr_prem_pred_critique[1] = 1;

    for(int s = 2 ; s <= n ; ++s)
    {
        //Calcul de lc[s] en fonction des prédecesseurs critiques de s
        longueur_critique[s] = 0;
        adr_prem_pred_critique[s] = kc+1; //Début de la liste des prédecesseurs critiques de s
        for(int k = adr_prem_pred[s] ; (t = file_pred[k]) != 0 ; ++k)
        {
            lg = longueur_critique[t] + duree_taches[t];
            if(lg >= longueur_critique[s])
            {
                if(lg > longueur_critique[s])
                {
                    longueur_critique[s] = lg; //Nouvelle lg candidate à être critique
                    kc = adr_prem_pred_critique[s] ;
                    file_pred_critique[kc] = t;
                }
                else //lg == lc[s]
                {
                    ++kc;
                    file_pred_critique[kc] = t;
                }
            }
        }
        ++kc;
        file_pred_critique[kc] = 0; //Fin de la liste des prédecesseurs critiques de s
    }
    file_pred_critique[0] = kc;
}


void englobe_ordonnancement(const vector<int>& fs, const vector<int>& aps)
{
    //@TODO Manu : transformer fs et aps en fp et app + cout en duree_taches
    //@TODO Manu : fpc et appc et lc devient un Graphe !
    vector<int> file_pred;
    vector<int> adr_prem_pred;
    vector<int> duree_taches;
    vector<int> file_pred_critique;
    vector<int> adr_prem_pred_critique;
    vector<int> longueur_critique;

    Ordonnancement(file_pred, adr_prem_pred, duree_taches, file_pred_critique, adr_prem_pred_critique, longueur_critique);
}




















