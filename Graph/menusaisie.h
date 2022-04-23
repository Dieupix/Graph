#ifndef MENUSAISIE_H
#define MENUSAISIE_H

#include "vue.h"

class menuSaisie : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuSaisie(QMainWindow *parent = nullptr);

    int getId() const;
    int getPoids() const;
    vector<int> getSuc() const;
    vector<int> getPred() const;

signals:
    void envoieAjout();

private slots:
    void onClick_valider();

private:
    vue d_vue;
    int d_id;
    int d_poids;
    vector<int> d_suc;
    vector<int> d_pred;
};

#endif // MENUSAISIE_H
