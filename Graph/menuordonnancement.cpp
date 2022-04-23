#include "menuordonnancement.h"

menuOrdonnancement::menuOrdonnancement(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceOrdonnancement();

    connect(&d_vue, &vue::Valider_Ordonnancement, this, &menuOrdonnancement::onClick_valider);
    connect(&d_vue, &vue::Quitter_Ordonnancement, this, &menuOrdonnancement::close);
}

vector<int> menuOrdonnancement::getDuree()
{
    return d_duree;
}
void menuOrdonnancement::onClick_valider()
{
    d_duree = d_vue.getDureeTaches();

    emit valide();

    close();
}

