#ifndef VUE_H
#define VUE_H

#include "widgetgraph.h"
#include "graph.h"

#include <QPushButton>
#include <QBoxLayout>
#include <QLabel>
#include <QMainWindow>
#include <QMenuBar>
#include <QLineEdit>
#include "noeud.h"

class vue : public QMainWindow
{
    Q_OBJECT
public:
    vue(QMainWindow* fenetre);

    void creeInterface();
    void creeInterfaceSaisie();
    void metAJourGraphe();
    void metAJourNoeuds();

    int getPoids();
    int getSuc();
    int getPred();
private://FENETRE DONT ON GERE L'INTERFACE
    //ICI, on insère les objets QCheckBox, QLabel, ...
    QMainWindow* d_fenetre;
    QGraphicsView* d_graphe;
    QLabel* d_fs;
    QLabel* d_aps;
    QLabel* d_matrice;
    QLabel* d_cout;

    QLineEdit* d_suc;
    QLineEdit* d_prec;
    QLineEdit* d_poids;

    void setupMenu();
    void setupMenuFichier();
    void setupMenuAlgo();

    void menuSaisie();
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

    void Ajouter();

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

    void onAjouter();
};

#endif // VUE_H
