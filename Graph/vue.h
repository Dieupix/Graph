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
#include <QTextEdit>
#include "noeud.h"

class vue : public QMainWindow
{
    Q_OBJECT
public:
    vue(QMainWindow* fenetre);

    void creeInterface();
    void creeInterfaceSaisie();
    void creeInterfacePruferDecode();
    void creeInterfaceDijkstra();
    void creeInterfaceOrdonnancement();

    void metAJourGraphe();
    void metAJourNoeuds();

    int getPoids();
    int getSuc();
    int getPred();
    int getId();
    //Pour Prufer decode
    vector<int> getP();
    //Pour Dijkstra
    int getSommet_depart();
    //Pour Ordonnancement
    vector<int> getDureeTaches();
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
    QLineEdit* d_id;

    QLineEdit* d_p;
    QLineEdit* d_sommet_depart;

    QTextEdit* d_taches;

    void setupMenu();
    void setupMenuFichier();
    void setupMenuAlgo();
    void setupMenuInfo();
    void menuSaisie();
    void fenetrePruferDecode();
    void fenetreDijkstra();
    void fenetreOrdonnancement();
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


    void InfoDistance();
    void InfoRang();
    void InfoTarjan();
    void InfoOrdonnancement();
    void InfoDijkstra();
    void InfoDantzig();
    void InfoKruskal();
    void InfoPrufer_encode();
    void InfoPrufer_decode();

    void Ajouter();
    void Valider_PruferDecode();
    void Quitte_PruferDecode();
    void Valider_Dijkstra();
    void Quitter_Dijkstra();
    void Valider_Ordonnancement();
    void Quitter_Ordonnancement();
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


    void oninfoDistance();
    void oninfoRang();
    void oninfoTarjan();
    void oninfoOrdonnancement();
    void oninfoDijkstra();
    void oninfoDantzig();
    void oninfoKruskal();
    void oninfoPrufer_encode();
    void oninfoPrufer_decode();

    void onAjouter();
    void onValide_PruferDecode();
    void onQuitte_PruferDecode();
    void onValide_Dijkstra();
    void onQuitte_Dijkstra();
    void onValide_Ordonnancement();
    void onQuitte_Ordonnancement();
};

#endif // VUE_H
