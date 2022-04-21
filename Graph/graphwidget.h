#ifndef GRAPHWIDGET_H
#define GRAPHWIDGET_H

#include<QGraphicsView>
#include "widgetnode.h"
#include "widgetedge.h"
#include "graph.h"

class GraphWidget : public QGraphicsView
{
    Q_OBJECT

public:
    GraphWidget(QWidget *parent = nullptr);
    GraphWidget(unsigned sceneSize, QWidget *parent = nullptr);
    GraphWidget(unsigned sceneSizeW, unsigned sceneSizeH, QWidget *parent = nullptr);

    void itemMoved();

public slots:
    void shuffle();
    void zoomIn();
    void zoomOut();

protected:
    void drawBackground (QPainter *painter, const QRectF &rect) override;
    void keyPressEvent  (QKeyEvent *event) override;
    void scaleView      (qreal scaleFactor);
    void timerEvent     (QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent     (QWheelEvent *event) override;
#endif

private:
    vector<int> d_fs;
    vector<int> d_aps;

    QGraphicsScene      *scene;
    QList<widgetNode *> nodes;
    widgetNode          *centerNode;
    unsigned            sceneSizeW, sceneSizeH;
    int                 timerId = 0;

    void setup();

    void loadGraph(const Graph& g);
    Graph toGraph();
};

#endif // GRAPHWIDGET_H
