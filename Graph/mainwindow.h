#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgetgraph.h"
#include "vue.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow* parent = nullptr);
private:
    widgetGraph d_g;
    vue d_vue;

    bool verifieDistance();
    bool verifieRang();
    bool verifieTarjan();
    bool verifieOrdonnancement();
    bool verifieDijkstra();
    bool verifieDantzig();
    bool verifieKruskal();
    bool verifiePruferEncode();
    bool verifiePruferDecode();

private slots :
    void onCheck_OrienteeChange(bool estoriente);
    void onCheck_A_des_PoidsChange(bool a_des_poids);
    void onCheck_FsAps_MatAdjChange(bool fs_aps_utilise);

    void charge();
    void saisie();
    void ajoute();
    void supprime();
    void onClick_Distance();
    void onClick_Rang();
    void onClick_Tarjan();
    void onClick_Ordonnancement();
    void onClick_Dijkstra();
    void onClick_Dantzig();
    void onClick_Kruskal();
    void onClick_Prufer_encode();
    void onClick_Prufer_decode();
};

#endif // MAINWINDOW_H
