#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgetgraph.h"
#include "vue.h"
#include "menuajout.h"
#include "menupruferdecode.h"

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
    bool verifieOrdonnancement(const vector<int>& duree_taches);
    bool verifieDijkstra(int sommet_depart);
    bool verifieDantzig();
    bool verifieKruskal();
    bool verifiePruferEncode();
    bool verifiePruferDecode(const vector<int>& p);

    menuAjout *menuS;
    //menuPruferDecode& menuPruferD;
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

    void onClickDistance_INFO();
    void onClickRang_INFO();
    void onClickTarjan_INFO();
    void onClickOrdonnancement_INFO();
    void onClickDijkstra_INFO();
    void onClickDantzig_INFO();
    void onClickKruskal_INFO();
    void onClickPrufer_encode_INFO();
    void onClickPrufer_decode_INFO();

    void onValiderAjout();
};

#endif // MAINWINDOW_H
