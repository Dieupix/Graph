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
    QList<widgetNode *> nodes;
    widgetNode          *centerNode;
    unsigned            sceneSizeW, sceneSizeH;
    int                 timerId = 0;

    void setup();
};

#endif // GRAPHWIDGET_H
