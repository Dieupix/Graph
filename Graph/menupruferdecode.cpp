#include "menupruferdecode.h"

menuPruferDecode::menuPruferDecode(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfacePruferDecode();

    //connect(&d_vue, &vue::Valide, this, &menuPruferDecode::onValide);
}
vector<int> menuPruferDecode::getP()
{
    return d_p;
}

void menuPruferDecode::onValide()
{
    d_p = d_vue.getP();

    emit valide();
}
