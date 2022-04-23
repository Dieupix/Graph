#ifndef VUE_H
#define VUE_H

#include "graph.h"
#include "noeud.h"
#include "widgetgraph.h"

#include <QBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QMainWindow>
#include <QMenuBar>
#include <QPushButton>
#include <QTextEdit>

class vue : public QMainWindow
{
    Q_OBJECT
public:
    vue(QMainWindow* fenetre = nullptr);

    void creeInterface(widgetGraph& wg);
    void creeInterfaceSaisie();
    void creeInterfacePruferDecode();
    void creeInterfaceSupprimer();
    void creeInterfaceSaisieFSAPS();

    void metAJourGraphe();
    void metAJourNoeuds();

    int getPoids();
    vector<int> getSuc();
    vector<int> getPred();
    int getId();

    vector<int> getP();

private://FENETRE DONT ON GERE L'INTERFACE
    //ICI, on insère les objets QCheckBox, QLabel, ...
    QMainWindow* d_fenetre;
    widgetGraph* d_wg;
    QLabel* d_fs;
    QLabel* d_aps;
    QLabel* d_matrice;
    QLabel* d_cout;

    QLineEdit* d_suc;
    QLineEdit* d_prec;
    QLineEdit* d_poids;
    QLineEdit* d_id;

    QLineEdit* d_p;

    QLineEdit* d_idSuppr;

    void setupMenu();
    void setupMenuFichier();
    void setupMenuAlgo();
    void setupMenuInfo();
    void menuAjout();
    void fenetrePruferDecode();
    void fenetreSaisieFSAPS();


    void fenetreMenuSupprimer();

signals: //SIGNAUX EMIS
    void Quitter();
    void Charger();
    void SaisieMatrice();
    void SaisieFSAPS();
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
    void saisieFSAPSValider();

private slots : //TRANSFORME LA VALEUR D'UN SIGNAL
    void onQuitter();
    void onCharger();
    void onSaisieFSAPS();
    void onSaisieMatrice();
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
    void onSaisieFSAPSValider();
};

#endif // VUE_H
