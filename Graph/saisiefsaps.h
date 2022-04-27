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
    vector<vector<int>> getCout();
    bool getCheck();
signals:
    void envoieSaisieFSAPS();

private slots:
    void onClick_valider();
private:
    vue d_vue;
    vector<int> d_FS;
    vector<int> d_APS;
    vector<vector<int>> d_cout;
    bool d_Check;
};

#endif // SAISIEFSAPS_H
