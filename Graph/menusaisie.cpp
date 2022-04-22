#include "menusaisie.h"

menuSaisie::menuSaisie(QWidget *parent) : QMainWindow{parent}, d_vue{this}
{
     d_vue.creeInterfaceSaisie();
}
