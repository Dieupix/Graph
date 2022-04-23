#include "menupruferdecode.h"

menuPruferDecode::menuPruferDecode(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfacePruferDecode();

    connect(&d_vue, &vue::Valider_PruferDecode, this, &menuPruferDecode::onClick_valider);
}
vector<int> menuPruferDecode::getP()
{
    return d_p;
}
void menuPruferDecode::onClick_valider()
{
    d_p = d_vue.getP();

    emit valide();

    close();
}

