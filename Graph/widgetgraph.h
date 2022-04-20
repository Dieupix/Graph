#ifndef WIDGETGRAPH_H
#define WIDGETGRAPH_H

#include<QWidget>
#include "graph.h"
using std::vector;

class widgetGraph : public QWidget
{
    Q_OBJECT
public:
    widgetGraph(QWidget* parent = 0);
    widgetGraph(const widgetGraph& g, QWidget* parent = 0);
    widgetGraph(const Graph& g, QWidget* parent = 0);

    void paintEvent(QPaintEvent*);
private:
    vector<int> d_fs;
    vector<int> d_aps;
    vector<QPoint> d_sommets;

    void MouseReleaseEvent(QMouseEvent* e);
    void ajouteSommet(const QPoint& s);
    void enleveSommet(const QPoint& s);
    void dessineGraphe(QPainter& paint);
    void dessineSommet(QPainter& paint, const QPoint& s);
    Graph toGraph();
    void fromGraph(const Graph& g);
};

#endif // WIDGETGRAPH_H
