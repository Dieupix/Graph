#include "application.h"

using std::cout;
using std::cin;

application::application()
{}

void application::load()
{
    int choix;
    do {
        std::cout<<"> 1. Via FS/APS ?"<<std::endl;
        std::cout<<"> 2. Via la matrice ?"<<std::endl;
        std::cout<<"> 3. Via un fichier ?"<<std::endl;
        std::cout<<"> 4. Via la position des arretes ?"<<std::endl;
        std::cin>>choix;
    }while(choix < 0 || choix > 3);

    switch(choix)
    {
        case 1: FSandAPS();
                break;
        case 2: matrice();
                break;
        case 3: fichier();
                break; //A FAIRE
    }
}

void application::FSandAPS()
{
        int n, m;
        vector<int> APS;
        vector<int> FS;
        vector<vector<int>> p;
        cout<<"Entrez le nombre de sommets du graphe : ";
        cin>>n;

        APS.resize(n+1);
        APS[0] = n;

        cout<<"Entrez le nombre d'arcs du graphe : ";
        cin>>m;

        FS.resize(n+m+1);
        FS[0] = n+m;

        p.resize(n+1);
        for(int i = 1; i <= n; i++)
        {
            p[i].resize(n+1);
        }

        for(int i = 1; i <= n; i++)
        {
            for(int j = 1; j <= n; j++)
            {
                p[i][j] = -1;
            }
        }

        int k = 0;
        int ns;
        for(int i = 1; i <= n; i++)
        {
            APS[i] = k+1;
            cout<<"Donner le nombre de successeurs du sommet "<<i<<" : ";
            cin>>ns;
            cout<<"Donner a cote de chaque successeur de "<<ns<<" le poids de l'arc correspondant : \n";
            for(int j = 1; j <= ns; j++)
            {
                int s;
                do{
                   cin>>s;
                }while(s > n);
                s = FS[++k];
                cin>>p[i][FS[k]];
            }
            FS[++k] = 0;
        }
        d_graphe.setFSandAPS(FS, APS);
        d_graphe.setCout(p);
}

void application::matrice()
{
    bool choixOriente;
    do{
        std::cout<<"S'agit-il d'un graphe oriente ? (1 = oui/0 = non)";
        std::cin>>choixOriente;
    }while(choixOriente != 1 && choixOriente != 0);

    int tailleMatrice;
    std::cout<<"Nombre de noeud : ";
    std::cin>>tailleMatrice;

    int nbArcs;
    std::cout<<"Nombre d'arcs : ";
    std::cin>>nbArcs;

    vector<vector<int>> Matrice(tailleMatrice+1);

    Matrice[0].push_back(tailleMatrice);
    Matrice[1].push_back(nbArcs);

    for(int i = 1; i <= tailleMatrice; i++)
    {
        Matrice[0][i] = 0;
    }

    for(int i = 1; i < tailleMatrice; i++)
    {
        Matrice[i].resize(tailleMatrice+1);
    }
    for(int i = 1; i <= tailleMatrice; i++)
    {
        for(int j = 1; j <= tailleMatrice; j++)
        {
            std::cout<<"Case n°["<<i<<"]["<<j<<"]";
            std::cin>>Matrice[i][j];
        }
    }
    d_graphe.setMatrice(Matrice);
    d_graphe.setOriente(choixOriente);
}

void application::fichier()
{

}
