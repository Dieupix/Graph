#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "widgetgraph.h"
#include "vue.h"
#include "menuajout.h"
#include "menupruferdecode.h"

#include "menudijkstra.h"
#include "menuordonnancement.h"

#include "menusupprimer.h"
#include "saisiefsaps.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QMainWindow* parent = nullptr);
private:
    widgetGraph* d_wg;
    vue d_vue;

    bool verifieDistance();
    bool verifieRang();
    bool verifieTarjan();
    bool verifieOrdonnancement(const vector<int>& duree_taches, const vector<int>& fs, const vector<int>& aps);
    bool verifieDijkstra(int sommet_depart);
    bool verifieDantzig();
    bool verifieKruskal();
    bool verifiePruferEncode();
    bool verifiePruferDecode(const vector<int>& p);

    menuPruferDecode *menuPruferD;
    menudijkstra *menuDijkstra;
    menuOrdonnancement *menuOrd;
    menuAjout *menuS;
    menuSupprimer *menuSuppr;
    saisieFSAPS *menuFSAPS;
    //menuPruferDecode& menuPruferD;
private slots :
    void onCheck_OrienteeChange(bool estoriente);
    void onCheck_A_des_PoidsChange(bool a_des_poids);
    void onCheck_FsAps_MatAdjChange(bool fs_aps_utilise);

    void charge();
    void saisieMatrice();
    void saisieFSAPS();
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
    void onValiderPruferDecode();
    void onValiderDijkstra();
    void onValiderOrdonnancement();
    void onValideSaisieFSAPS();
};

#endif // MAINWINDOW_H
