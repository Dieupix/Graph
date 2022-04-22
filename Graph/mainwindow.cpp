#include "mainwindow.h"
#include<iostream>

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow{parent}, d_g{widgetGraph()}, d_vue{this}
{
    d_vue.creeInterface();
    d_vue.metAJourGraphe();

    connect(&d_vue, &vue::OrienteeChange, this, &MainWindow::onCheck_OrienteeChange);
    connect(&d_vue, &vue::A_des_PoidsChange, this, &MainWindow::onCheck_A_des_PoidsChange);
    connect(&d_vue, &vue::FsAps_MatAdjChange, this, &MainWindow::onCheck_FsAps_MatAdjChange);

    connect(&d_vue, &vue::Quitter, this, &MainWindow::close);
    connect(&d_vue, &vue::Charger, this, &MainWindow::charge);
    connect(&d_vue, &vue::Saisie, this, &MainWindow::saisie);
    connect(&d_vue, &vue::Ajout, this, &MainWindow::ajoute);
    connect(&d_vue, &vue::Suppression, this, &MainWindow::supprime);

    connect(&d_vue, &vue::AlgorithmeSelectionneDistance, this, &MainWindow::onClick_Distance);
    connect(&d_vue, &vue::AlgorithmeSelectionneRang, this, &MainWindow::onClick_Rang);
    connect(&d_vue, &vue::AlgorithmeSelectionneTarjan, this, &MainWindow::onClick_Tarjan);
    connect(&d_vue, &vue::AlgorithmeSelectionneOrdonnancement, this, &MainWindow::onClick_Ordonnancement);
    connect(&d_vue, &vue::AlgorithmeSelectionneDijkstra, this, &MainWindow::onClick_Dijkstra);
    connect(&d_vue, &vue::AlgorithmeSelectionneDantzig, this, &MainWindow::onClick_Dantzig);
    connect(&d_vue, &vue::AlgorithmeSelectionneKruskal, this, &MainWindow::onClick_Kruskal);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferEncode, this, &MainWindow::onClick_Prufer_encode);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferDecode, this, &MainWindow::onClick_Prufer_decode);
}
bool MainWindow::verifieFS_APS_NonVide()
{
    if(d_g.getFs().size() == 0 || d_g.getAps().size() == 0)
    {
        return false;
    }
    return true;
}
bool MainWindow::verifieMatrice_NonVide()
{
    vector<vector<int>> mat = d_g.getMatrice();
    if(mat.size() == 0)
        return false;
    else if(mat[0].size() != 2)
    {
        return false;
    }
    else
    {
        unsigned size = mat[1].size();
        for(unsigned i = 2 ; i < mat.size() ; ++i)
        {
            if(mat[i].size() != size)
                return false;
        }
        return true;
    }
}
bool MainWindow::verifieDistance()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return verifieFS_APS_NonVide() || verifieMatrice_NonVide();
}

bool MainWindow::verifieRang()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return verifieFS_APS_NonVide() || verifieMatrice_NonVide();
}
bool MainWindow::verifieTarjan()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return verifieFS_APS_NonVide() || verifieMatrice_NonVide();
}
bool MainWindow::verifieOrdonnancement(const vector<int>& duree_taches)
{
    //Il faut que fs et aps soit initialisé.
    //Il faut que duree_taches soit correctement initisalisé et saisie
    if(d_g.getUsingFSandAPS())
    {
        if(verifieFS_APS_NonVide())
        {
            int n = d_g.getAps()[0];
            return (duree_taches[0] != n);
        }
        return false;
    }
    else
    {
        if(verifieMatrice_NonVide())
        {
            int n = d_g.getMatrice()[0][0];
            return(duree_taches[0] != n);
        }
        return false;
    }
}
bool MainWindow::verifieDijkstra(int sommet_depart)
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    //Il faut que le cout soit correct, qu'il ne contienne pas de cout < 0
    if(d_g.getUsingFSandAPS())
    {
        if(verifieFS_APS_NonVide())
        {
            bool sommet_correct = true;
            bool couts_correct = true;
            if(sommet_depart <= 0 || sommet_depart > d_g.getAps()[0])
                sommet_correct = false;
            else
            {
                vector<vector<int>> couts = d_g.getCouts();
                if(couts[0][0] != d_g.getAps()[0] || couts[0][1] != (d_g.getFs()[0] - d_g.getAps()[0]))
                    couts_correct = false;
                else
                {
                    for(unsigned i = 1 ; i < couts.size() ; ++i)
                        for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                            if(couts[i][j] < 0)
                                couts_correct = false;
                }
            }
            return sommet_correct && couts_correct;
        }
        return false;
    }
    else
    {
        if(verifieMatrice_NonVide())
        {
            bool sommet_correct = true;
            bool couts_correct = true;
            int n = d_g.getMatrice()[0][0];
            int m = d_g.getMatrice()[0][1];
            if(sommet_depart <= 0 || sommet_depart > n)
                sommet_correct = false;
            else
            {
                vector<vector<int>> couts = d_g.getCouts();
                if(couts[0][0] != n || couts[0][1] != m)
                    couts_correct = false;
                else
                {
                    for(unsigned i = 1 ; i < couts.size() ; ++i)
                        for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                            if(couts[i][j] < 0)
                                couts_correct = false;
                }
            }
            return sommet_correct && couts_correct;
        }
        return false;
    }


}
bool MainWindow::verifieDantzig()
{
    //Il faut que le cout soit bien initialisé ou la matrice.
    if(d_g.getUsingFSandAPS())
    {
        if(verifieFS_APS_NonVide())
        {
            bool cout_correct = true;
            vector<vector<int>> couts = d_g.getCouts();
            if(couts[0][0] != d_g.getAps()[0] || couts[0][1] != (d_g.getFs()[0] - d_g.getAps()[0]))
                cout_correct = false;
            return cout_correct;
        }
        return false;
    }
    else
    {
       if(verifieMatrice_NonVide())
       {
           bool cout_correct = true;
           int n = d_g.getMatrice()[0][0];
           int m = d_g.getMatrice()[0][1];
           vector<vector<int>> couts = d_g.getCouts();
           if(couts[0][0] != n || couts[0][1] != m)
               cout_correct = false;
           return cout_correct;
       }
       return false;
    }
}
bool MainWindow::verifieKruskal()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return verifieFS_APS_NonVide() || verifieMatrice_NonVide();
}
bool MainWindow::verifiePruferEncode()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return verifieFS_APS_NonVide() || verifieMatrice_NonVide();
}
bool MainWindow::verifiePruferDecode(const vector<int>& p)
{
    bool p_correct = true;
    unsigned m = p[0];
    if(m != p.size())
        p_correct = false;
    else
    {
        for(unsigned i = 1 ; i < m ; ++i)
            if(p[i] <= 0 || p[i] > (int)m+2)
                return p_correct = false;
    }
    return p_correct;
}

void MainWindow::charge()
{
    //Chargement d'un widgetGraph
    //Ajouter un istream
    //d_g.loadFrom();
}

void MainWindow::saisie()
{
    //Saisie d'un widgetGraph
    //Ajouter un ostream
    //d_g.save();
}
void MainWindow::ajoute()
{
    //Ajoute un noeud
}
void MainWindow::supprime()
{
    //Supprime un noeud
}
void MainWindow::onCheck_OrienteeChange(bool estoriente)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe();
}
void MainWindow::onCheck_A_des_PoidsChange(bool a_des_poids)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe();
}
void MainWindow::onCheck_FsAps_MatAdjChange(bool fs_aps_utilise)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe();
}



void MainWindow::onClick_Distance()
{
    if(verifieDistance())
    {
        vector<vector<int>> mat_dist = d_g.englobe_Distance();
    }//retourner la matrice
}

void MainWindow::onClick_Rang()
{
    if(verifieRang())
    {
        vector<int> rang = d_g.englobe_Rang();
    }//retourner le rang
}

void MainWindow::onClick_Tarjan()
{
    if(verifieTarjan())
    {
        widgetGraph wg = d_g.englobe_Tarjan();
        d_vue.metAJourGraphe();
    }

}
void MainWindow::onClick_Ordonnancement()
{
    vector<int> duree_taches;
    if(verifieOrdonnancement(duree_taches))
    {
        widgetGraph wg = d_g.englobe_Ordonnancement(duree_taches);
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Dijkstra()
{
    int sommet_depart = 1;//A faire saisir
    vector<int> d, pr;
    if(verifieDijkstra(sommet_depart))
    {
        d_g.englobe_Dijkstra(sommet_depart,d,pr);
    }//Retourner d et pr
}
void MainWindow::onClick_Dantzig()
{
    if(verifieDantzig())
    {
        d_g.englobe_Dantzig();
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Kruskal()
{
    if(verifieKruskal())
    {
        d_g.englobe_Kruskal();
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Prufer_encode()
{
    if(verifiePruferEncode())
    {
        vector<int> p = d_g.englobe_Prufer_encode();
    }
    //retourner p
}
void MainWindow::onClick_Prufer_decode()
{
    vector<int> p; //A faire saisir
    if(verifiePruferDecode(p))
    {
        widgetGraph wg = d_g.englobe_Prufer_decode(p);
        d_vue.metAJourGraphe();
    }
}
