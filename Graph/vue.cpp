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

    //MENU GRAPH
    auto menuGraph = d_fenetre->menuBar()->addMenu("&Fichier");

    auto actionCharger = new QAction{"Charger"};
    actionCharger->setToolTip("Charger graph");
    menuGraph->addAction(actionCharger);
    connect(actionCharger, &QAction::triggered, this, &vue::onCharger);

    auto actionSaisie = new QAction{"Saisie"};
    actionSaisie->setToolTip("Saisir graph");
    menuGraph->addAction(actionSaisie);
    connect(actionSaisie, &QAction::triggered, this, &vue::onSaisie);

    menuGraph->addSeparator();

    auto actionAjout = new QAction{"Ajout Noeud"};
    actionAjout->setToolTip("Ajout Noeud");
    menuGraph->addAction(actionAjout);
    connect(actionAjout, &QAction::triggered, this, &vue::onAjout);

    auto actionSupprimer = new QAction{"Supprimer Noeud"};
    actionSupprimer->setToolTip("Supprimer Noeud");
    menuGraph->addAction(actionSupprimer);
    connect(actionSupprimer, &QAction::triggered, this, &vue::onSuppression);

    menuGraph->addSeparator();

    auto actionQuitter = new QAction{"Quitter"};
    actionQuitter->setToolTip("Quitter application");
    menuGraph->addAction(actionQuitter);
    connect(actionQuitter, &QAction::triggered, this, &vue::onQuitter);

    //MENU ALGO
    auto menuAlgo = d_fenetre->menuBar()->addMenu("&Algorithm");

    auto actionDistance = new QAction{"Distance"};
    actionDistance->setToolTip("Distance algorithme");
    menuAlgo->addAction(actionDistance);
    connect(actionDistance, &QAction::triggered, this, &vue::onDistance);

    auto actionRang = new QAction{"Rang"};
    actionRang->setToolTip("Rang algorithme");
    menuAlgo->addAction(actionRang);
    connect(actionRang, &QAction::triggered, this, &vue::onRang);

    auto actionTarjan = new QAction{"Tarjan"};
    actionTarjan->setToolTip("Tarjan algorithme");
    menuAlgo->addAction(actionTarjan);
    connect(actionTarjan, &QAction::triggered, this, &vue::onTarjan);

    auto actionOrdonnancement = new QAction{"Ordonnancement"};
    actionOrdonnancement->setToolTip("Ordonnancement algorithme");
    menuAlgo->addAction(actionOrdonnancement);
    connect(actionOrdonnancement, &QAction::triggered, this, &vue::onOrdonnancement);

    auto actionDijkstra = new QAction{"Dijkstra"};
    actionDijkstra->setToolTip("Dijkstra algorithme");
    menuAlgo->addAction(actionDijkstra);
    connect(actionDijkstra, &QAction::triggered, this, &vue::onDijkstra);

    auto actionDantzig = new QAction{"Dantzig"};
    actionDantzig->setToolTip("Dantzig algorithme");
    menuAlgo->addAction(actionDantzig);
    connect(actionDantzig, &QAction::triggered, this, &vue::onDantzig);

    auto actionKruskal = new QAction{"Kruskal"};
    actionKruskal->setToolTip("Kruskal algorithme");
    menuAlgo->addAction(actionKruskal);
    connect(actionKruskal, &QAction::triggered, this, &vue::onKruskal);

    auto SousMenuPrufer = menuAlgo->addMenu("Prufer");

    auto actionPruferEncode = new QAction{"Prufer_encode"};
    actionPruferEncode->setToolTip("Prufer encode");
    SousMenuPrufer->addAction(actionPruferEncode);
    connect(actionPruferEncode, &QAction::triggered, this, &vue::onPruferEncode);

    auto actionPruferDecode = new QAction{"Prufer_decode"};
    actionPruferDecode->setToolTip("Prufer decode");
    SousMenuPrufer->addAction(actionPruferDecode);
    connect(actionPruferDecode, &QAction::triggered, this, &vue::onPruferDecode);

/*
    const vector<int> fs {6, 2, 3, 0, 3, 0, 0};
    const vector<int> aps {3, 1, 4, 6};
    Graph g(fs,aps);
    auto widGraph = new widgetGraph(g);
    mainLayout->addWidget(widGraph);
*/
    // POUR AJOUTER LE GRAPH DANS LA VUE
    auto gwLayout = new QVBoxLayout();
    mainLayout->addLayout(gwLayout);

    GraphWidget* gw = new GraphWidget();
    gwLayout->addWidget(gw);
    gw->show();
    //gw->close();
}

void vue::metAJourGraphe()
{
    //MAj fs/aps..
    metAJourNoeuds();
}

void vue::metAJourNoeuds()
{
    //Ici, on modifie fs / aps / matrice voire meme le graphe jsp
}

void vue::onQuitter()
{
    emit Quitter();
}
void vue::onCharger()
{
    emit Charger();
}
void vue::onSaisie()
{
    emit Saisie();
}
void vue::onAjout()
{
    emit Ajout();
}
void vue::onSuppression()
{
    emit Suppression();
}
void vue::onDistance()
{
    emit AlgorithmeSelectionneDistance();
}

void vue::onRang()
{
    emit AlgorithmeSelectionneRang();
}

void vue::onTarjan()
{
    emit AlgorithmeSelectionneTarjan();
}

void vue::onOrdonnancement()
{
    emit AlgorithmeSelectionneOrdonnancement();
}
void vue::onDijkstra()
{
    emit AlgorithmeSelectionneDijkstra();
}
void vue::onDantzig()
{
    emit AlgorithmeSelectionneDantzig();
}
void vue::onKruskal()
{
    emit AlgorithmeSelectionneKruskal();
}
void vue::onPruferEncode()
{
    emit AlgorithmeSelectionnePruferEncode();
}
void vue::onPruferDecode()
{
    emit AlgorithmeSelectionnePruferDecode();
}

