#include "menusaisie.h"

menuSaisie::menuSaisie(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
     d_vue.creeInterfaceSaisie();

      connect(&d_vue, &vue::Ajouter, this, &menuSaisie::onClick_valider);
      connect(&d_vue, &vue::Quitter, this, &menuSaisie::close);

}

void menuSaisie::onClick_valider()
{
    d_id = d_vue.getPoids();
    d_pred.push_back(d_vue.getPred());
    d_suc.push_back(d_vue.getSuc());
    close();
}

void menuSaisie::onClick_quitter()
{

}

int  menuSaisie::getId() const
{
    return d_id;
}

vector<int> menuSaisie::getPred() const
{
    return d_pred;
}

vector<int> menuSaisie::getSuc() const
{
    return d_suc;
}
