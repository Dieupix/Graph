#include "menupruferdecode.h"

menuPruferDecode::menuPruferDecode(QWidget *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfacePruferDecode();
}
vector<int> menuPruferDecode::getP()
{
    return d_p;
}

