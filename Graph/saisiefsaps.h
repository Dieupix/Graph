#ifndef SAISIEFSAPS_H
#define SAISIEFSAPS_H

#include <QMainWindow>
#include "vue.h"

class saisieFSAPS : public QMainWindow
{
    Q_OBJECT
public:
    explicit saisieFSAPS(QWidget *parent = nullptr);
    vector<int> getFS();
    vector<int> getAPS();
    int getN();
    int getM();
signals:
    void envoieSaisieFSAPS();

private slots:
    void onClick_valider();
private:
    vue d_vue;
    int d_n;
    int d_m;
    vector<int> d_FS;
    vector<int> d_APS;
};

#endif // SAISIEFSAPS_H
