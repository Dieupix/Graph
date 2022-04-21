#ifndef widgetGraphBisBIS_H
#define widgetGraphBisBIS_H

#include<QWidget>
#include "graph.h"
using std::vector;

class widgetGraphBis : public QWidget
{
    Q_OBJECT
public:
    widgetGraphBis(QWidget* parent = 0);
    widgetGraphBis(const widgetGraphBis& g, QWidget* parent = 0);
    widgetGraphBis(const Graph& g, QWidget* parent = 0);

    void paintEvent(QPaintEvent*);
    vector<QPoint> getSommets();
    vector<int> getFs();
    vector<int> getAps();

    vector<vector<int>> englobe_Distance();
    vector<int> englobe_Rang();
    widgetGraphBis englobe_Tarjan();
    widgetGraphBis englobe_Ordonnancement();
    void englobe_Dijkstra(int sommet_depart);
    void englobe_Dantzig();
    void englobe_Kruskal();
    vector<int> englobe_Prufer_encode();
    widgetGraphBis englobe_Prufer_decode(const vector<int>& p);

    void loadFrom(std::istream& ist);
    void saveIn(std::ostream& ost);
    void ajouterNoeud();

private:
    vector<int> d_fs;
    vector<int> d_aps;
    vector<QPoint> d_sommets;
    vector<vector<int>> d_couts;
    vector<vector<int>> d_matrice;

    void MouseReleaseEvent(QMouseEvent* e);
    void ajouteSommet(const QPoint& s);
    void enleveSommet(const QPoint& s);
    void dessineGraphe(QPainter& paint);
    void dessineSommet(QPainter& paint, const QPoint& s);
    Graph toGraph();
    void fromGraph(const Graph& g);
};

#endif // WIDGETGRAPHBIS_H
