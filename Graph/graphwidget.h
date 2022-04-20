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
    void keyPressEvent(QKeyEvent *event) override;
    void timerEvent(QTimerEvent *event) override;
#if QT_CONFIG(wheelevent)
    void wheelEvent(QWheelEvent *event) override;
#endif
    void drawBackground(QPainter *painter, const QRectF &rect) override;

    void scaleView(qreal scaleFactor);

private:
    int timerId = 0;
    widgetNode *centerNode;
    unsigned sceneSizeW, sceneSizeH;

    QList<widgetNode *> nodes;

    void setup();
};

#endif // GRAPHWIDGET_H
