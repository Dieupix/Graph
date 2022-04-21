#ifndef VUE_H
#define VUE_H

#include <QObject>
#include <QMainWindow>
#include <QLabel>
#include<QGraphicsView>
#include "widgetgraph.h"
#include "graph.h"

class vue : public QMainWindow
{
    Q_OBJECT
public:
    vue(QMainWindow* fenetre);

    void creeInterface();
    void metAJourGraphe();
    void metAJourNoeuds();
    void setMenu();

private://FENETRE DONT ON GERE L'INTERFACE
    QMainWindow* d_fenetre;
    QGraphicsView* d_graphe;
    QLabel* d_fs;
    QLabel* d_aps;
    QLabel* d_matrice;
    QLabel* d_cout;
signals: //SIGNAUX EMIS
    void Quitter();
    void Charger();
    void Saisie();
    void Ajout();
    void Suppression();
    void OrienteeChange(bool estoriente);
    void A_des_PoidsChange(bool a_des_poids);
    void FsAps_MatAdjChange(bool fs_aps_utilise);
    void AlgorithmeSelectionneDistance();
    void AlgorithmeSelectionneRang();
    void AlgorithmeSelectionneTarjan();
    void AlgorithmeSelectionneOrdonnancement();
    void AlgorithmeSelectionneDijkstra();
    void AlgorithmeSelectionneDantzig();
    void AlgorithmeSelectionneKruskal();
    void AlgorithmeSelectionnePruferEncode();
    void AlgorithmeSelectionnePruferDecode();
private slots : //TRANSFORME LA VALEUR D'UN SIGNAL
    void onQuitter();
    void onCharger();
    void onSaisie();
    void onAjout();
    void onSuppression();
    void onDistance();
    void onRang();
    void onTarjan();
    void onOrdonnancement();
    void onDijkstra();
    void onDantzig();
    void onKruskal();
    void onPruferEncode();
    void onPruferDecode();
};

#endif // VUE_H
