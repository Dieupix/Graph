#include "application.h"

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
        case 3: break; //A FAIRE
        case 4: arete();
                break;
    }
}

void application::FSandAPS()
{
    bool choixOriente;
    do{
        std::cout<<"S'agit-il d'un graphe oriente ? (1 = oui/0 = non)";
        std::cin>>choixOriente;
    }while(choixOriente != 1 && choixOriente != 0);

    int FSsize;
    std::cout<<"Taille de FS : ";
    std::cin>>FSsize;

    int APSsize;
    std::cout<<"Taille de APS : ";
    std::cin>>APSsize;

    vector<int> FS(FSsize);
    for(int i = 0; i < FSsize; i++)
    {
        std::cout<<"Case de FS n°"<<i;
        std::cin>>FS[i];
    }

    vector<int> APS(APSsize);
    for(int i = 0; i < APSsize; i++)
    {
        std::cout<<"Case de APS n°"<<i;
        std::cin>>APS[i];
    }
    d_graphe.setFSandAPS(FS,APS);
    d_graphe.setOriente(choixOriente);
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

    vector<vector<int>> Matrice(tailleMatrice);
    for(int i = 0; i < tailleMatrice; i++)
    {
        for(int j = 0; j < tailleMatrice; j++)
        {
            std::cout<<"Case n°["<<i<<"]["<<j<<"]";
            std::cin>>Matrice[i][j];
        }
    }
    d_graphe.setMatrice(Matrice);
    d_graphe.setOriente(choixOriente);
}

void application::arete()
{
    int nbSommet;
    int nbArete;
    std::cout<<"Donnez le nombre de sommets : ";
    std::cin>>nbSommet;

    do{
        std::cout<<"Donnez le nombre d'aretes : ";
        std::cin>>nbArete;
    }while(nbArete < nbSommet);


}
