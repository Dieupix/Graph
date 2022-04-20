#include "vue.h"
#include<QBoxLayout>
#include<QLabel>
#include<QPaintEvent>

#include "graphwidget.h"

vue::vue(QWidget* fenetre) : d_fenetre{fenetre}
{}

void vue::creeInterface()
{
    d_fenetre->setWindowTitle("Graphe");

    auto mainLayout = new QVBoxLayout;
    d_fenetre->setLayout(mainLayout);

    mainLayout->addWidget(new QLabel("Votre graphe :"), 0, Qt::AlignLeft);
    //MATHIS
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

void vue::metAJourGraphe(const widgetGraph& g)
{

}

void vue::metAJourNoeud(const Noeud& n)
{

}

//Faire la suite...
