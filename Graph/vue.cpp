#include "vue.h"
#include<QBoxLayout>
#include<QLabel>



vue::vue(QWidget* fenetre) : d_fenetre{fenetre}
{}

void vue::creeInterface(const Graph& g)
{
    d_fenetre->setWindowTitle("Graphe");
    auto mainLayout = new QVBoxLayout;
    mainLayout->addWidget(new QLabel("Votre graphe :"),0,Qt::AlignLeft);
    //MATHIS


    d_fenetre->setLayout(mainLayout);
}

//Faire la suite...
