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

bool MainWindow::verifieDistance()
{
    return false;
}

bool MainWindow::verifieRang()
{
    return false;
}
bool MainWindow::verifieTarjan()
{
    return false;
}
bool MainWindow::verifieOrdonnancement()
{
    return false;
}
bool MainWindow::verifieDijkstra()
{
    return false;
}
bool MainWindow::verifieDantzig()
{
    return false;
}
bool MainWindow::verifieKruskal()
{
    return false;
}
bool MainWindow::verifiePruferEncode()
{
    return false;
}
bool MainWindow::verifiePruferDecode()
{
    return false;
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
    menuS = new menuSaisie();
    menuS->show();
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
        vector<vector<int>> mat_dist = d_g.englobe_Distance();
}

void MainWindow::onClick_Rang()
{
    if(verifieRang())
    {
        vector<int> rang = d_g.englobe_Rang();
        d_vue.metAJourGraphe();
    }
}

void MainWindow::onClick_Tarjan()
{
    if(verifieTarjan())
    {
        d_vue.metAJourGraphe();
    }

}
void MainWindow::onClick_Ordonnancement()
{
    if(verifieOrdonnancement())
    {
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Dijkstra()
{
    if(verifieDijkstra())
    {
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Dantzig()
{
    if(verifieDantzig())
    {
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Kruskal()
{
    if(verifieKruskal())
    {
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Prufer_encode()
{
    if(verifiePruferEncode())
    {
        d_vue.metAJourGraphe();
    }
}
void MainWindow::onClick_Prufer_decode()
{
    if(verifiePruferDecode())
    {
        d_vue.metAJourGraphe();
    }
}
