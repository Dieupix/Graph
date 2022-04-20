#ifndef VUE_H
#define VUE_H

#include <QObject>
#include <QMainWindow>
#include "widgetgraph.h"
#include "graph.h"

class vue : public QMainWindow
{
    Q_OBJECT
public:
    vue(QMainWindow* fenetre);

    void creeInterface();
    void metAJourGraphe(const widgetGraph& g);
    void metAJourNoeud(const Noeud& n);

private://FENETRE DONT ON GERE L'INTERFACE
    QMainWindow* d_fenetre;
    //ICI, on insère les objets QCheckBox, QLabel, ...

signals: //SIGNAUX EMIS
    void OrienteeChange(bool estoriente);
    void A_des_PoidsChange(bool a_des_poids);
    void FsAps_MatAdjChange(bool fs_aps_utilise);

private slots : //TRANSFORME LA VALEUR D'UN SIGNAL

};

#endif // VUE_H
