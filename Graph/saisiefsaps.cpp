#include "saisiefsaps.h"

saisieFSAPS::saisieFSAPS(QWidget *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceSaisieFSAPS();

    connect(&d_vue, &vue::saisieFSAPSValider, this, &saisieFSAPS::onClick_valider);
    connect(&d_vue, &vue::Quitter, this, &saisieFSAPS::close);
}

void saisieFSAPS::onClick_valider()
{
    d_n = d_vue.getNSaisie();
    d_m = d_vue.getMSaisie();
    d_FS = d_vue.getFSSaisie();
    d_APS = d_vue.getAPSSaisie();

    emit envoieSaisieFSAPS();

    close();
}

vector<int> saisieFSAPS::getFS()
{
    return d_FS;
}

vector<int> saisieFSAPS::getAPS()
{
    return d_APS;
}

int saisieFSAPS::getN()
{
    return d_n;
}

int saisieFSAPS::getM()
{
    return d_m;
}
