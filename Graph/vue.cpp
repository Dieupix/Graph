#include "vue.h"
#include<QBoxLayout>
#include<QLabel>

vue::vue(QWidget* fenetre) : d_fenetre{fenetre}
{}

void vue::creeInterface()
{
    d_fenetre->setWindowTitle("Graphe");
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Votre graphe :"),0,Qt::AlignLeft);
    //MATHIS
    auto widGraph = new widgetGraph();
    mainLayout->addWidget(widGraph);

    d_fenetre->setLayout(mainLayout);
}

void vue::metAJourGraphe(const widgetGraph& g)
{

}

void vue::metAJourNoeud(const Noeud& n)
{

}

//Faire la suite...
