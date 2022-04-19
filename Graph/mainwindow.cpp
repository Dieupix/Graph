#include "mainwindow.h"

MainWindow::MainWindow(QWidget* parent) : QWidget{parent}, d_g{new widgetGraph()}, d_vue{this}
{
    d_vue.creeInterface();
    d_vue.metAJourGraphe(d_g);
    connect(&d_vue, &vue::OrienteeChange, this, &MainWindow::onCheck_OrienteeChange);
    connect(&d_vue, &vue::A_des_PoidsChange, this, &MainWindow::onCheck_A_des_PoidsChange);
    connect(&d_vue, &vue::FsAps_MatAdjChange, this, &MainWindow::onCheck_FsAps_MatAdjChange);
}

MainWindow::MainWindow(QWidget* parent, const Graph& g) :  QWidget{parent}, d_g{new widgetGraph(g)}, d_vue{this}
{
    d_vue.creeInterface();
    d_vue.metAJourGraphe(d_g);
    connect(&d_vue, &vue::OrienteeChange, this, &MainWindow::onCheck_OrienteeChange);
    connect(&d_vue, &vue::A_des_PoidsChange, this, &MainWindow::onCheck_A_des_PoidsChange);
    connect(&d_vue, &vue::FsAps_MatAdjChange, this, &MainWindow::onCheck_FsAps_MatAdjChange);
}

void MainWindow::onCheck_OrienteeChange(bool estoriente)
{
    //COMPLETER + MAJ la vue   
    d_vue.metAJourGraphe(d_g);
}
void MainWindow::onCheck_A_des_PoidsChange(bool a_des_poids)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe(d_g);
}
void MainWindow::onCheck_FsAps_MatAdjChange(bool fs_aps_utilise)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe(d_g);
}
