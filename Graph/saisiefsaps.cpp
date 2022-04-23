#include "saisiefsaps.h"

saisieFSAPS::saisieFSAPS(QWidget *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceSaisieFSAPS();
}
