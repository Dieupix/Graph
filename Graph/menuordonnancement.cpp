#include "menuordonnancement.h"

menuOrdonnancement::menuOrdonnancement(QMainWindow *parent) : QMainWindow{parent}, d_vue{this}
{
    d_vue.creeInterfaceOrdonnancement();

    connect(&d_vue, &vue::Valider_Ordonnancement, this, &menuOrdonnancement::onClick_valider);
    connect(&d_vue, &vue::Quitter_Ordonnancement, this, &menuOrdonnancement::close);
}

vector<int> menuOrdonnancement::getDuree() const
{
    return d_duree;
}

vector<int> menuOrdonnancement::getFs() const
{
    return d_fs;
}

vector<int> menuOrdonnancement::getAps() const
{
    return d_aps;
}


void menuOrdonnancement::onClick_valider()
{
    d_duree = d_vue.getDureeTaches();
    d_fs = d_vue.getFsOrd();

    vector<int> new_aps(d_duree.size()+1);

    //Construire APS a partir de FS
    new_aps[0] = 0;
    new_aps[1] = 1;
    int k = 2;
    int ind_crt = 1;
    for(int i = 1 ; i < d_fs[0] ; ++i)
    {
        if(d_fs[i] == 0 && k < d_fs[0])
        {
            new_aps[ind_crt] = k;
            ind_crt++;
        }
        k++;
    }

    d_aps = new_aps;

    emit valide();

    close();
}

