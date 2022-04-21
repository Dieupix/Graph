#include "vue.h"
#include<QBoxLayout>
#include<QLabel>
#include<QMenu>
#include<QMenuBar>
#include<QPaintEvent>

#include "graphwidget.h"

vue::vue(QMainWindow* fenetre) : d_fenetre{fenetre}
{}

void vue::creeInterface()
{
    d_fenetre->setWindowTitle("Graphe");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    mainLayout->addWidget(new QLabel("Votre graphe :"), 0, Qt::AlignLeft);

    setMenu();
/*
    const vector<int> fs {6, 2, 3, 0, 3, 0, 0};
    const vector<int> aps {3, 1, 4, 6};
    Graph g(fs,aps);
    auto widGraph = new widgetGraph(g);
    mainLayout->addWidget(widGraph);*/

    // POUR AJOUTER LE GRAPH DANS LA VUE
    auto gwLayout = new QVBoxLayout();
    mainLayout->addLayout(gwLayout);

    GraphWidget* gw = new GraphWidget();
    gwLayout->addWidget(gw);
    gw->show();

    //gw->close();
}

void vue::setMenu()
{
    auto menuGraph = d_fenetre->menuBar()->addMenu("&Fichier");

    auto actionCharger = new QAction{"Charger"};
    actionCharger->setToolTip("Charger graph");
    menuGraph->addAction(actionCharger);

    auto actionSaisie = new QAction{"Saisie"};
    actionSaisie->setToolTip("Saisir graph");
    menuGraph->addAction(actionSaisie);

    menuGraph->addSeparator();

    auto actionAjout = new QAction{"Ajout Noeud"};
    actionAjout->setToolTip("Ajout Noeud");
    menuGraph->addAction(actionAjout);

    auto actionSupprimer = new QAction{"Supprimer Noeud"};
    actionSupprimer->setToolTip("Supprimer Noeud");
    menuGraph->addAction(actionSupprimer);

    menuGraph->addSeparator();

    auto actionQuitter = new QAction{"Quitter"};
    actionQuitter->setToolTip("Quitter application");
    menuGraph->addAction(actionQuitter);

    //MENU ALGO
    auto menuAlgo = d_fenetre->menuBar()->addMenu("&Algorithm");

    auto actionDistance = new QAction{"Distance"};
    actionDistance->setToolTip("Distance algorithme");
    menuAlgo->addAction(actionDistance);

    auto actionRang = new QAction{"Rang"};
    actionRang->setToolTip("Rang algorithme");
    menuAlgo->addAction(actionRang);

    auto actionTarjan = new QAction{"Tarjan"};
    actionTarjan->setToolTip("Tarjan algorithme");
    menuAlgo->addAction(actionTarjan);

    auto actionOrdonnancement = new QAction{"Ordonnancement"};
    actionOrdonnancement->setToolTip("Ordonnancement algorithme");
    menuAlgo->addAction(actionOrdonnancement);

    auto actionDijkstra = new QAction{"Dijkstra"};
    actionDijkstra->setToolTip("Dijkstra algorithme");
    menuAlgo->addAction(actionDijkstra);

    auto actionDantzig = new QAction{"Dantzig"};
    actionDantzig->setToolTip("Dantzig algorithme");
    menuAlgo->addAction(actionDantzig);

    auto actionKruskal = new QAction{"Kruskal"};
    actionKruskal->setToolTip("Kruskal algorithme");
    menuAlgo->addAction(actionKruskal);

    auto actionPrufer = new QAction{"Prufer"};
    actionPrufer->setToolTip("Prufer algorithme");
    menuAlgo->addAction(actionPrufer);
}

void vue::metAJourGraphe(const widgetGraph& g)
{

}

void vue::metAJourNoeud(const Noeud& n)
{

}

//Faire la suite...
