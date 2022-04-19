#ifndef WIDGETEDGE_H
#define WIDGETEDGE_H

#include<QGraphicsItem>
#include "widgetnode.h"

class widgetEdge : public QGraphicsItem
{
public:
    widgetEdge(widgetNode *sourceNode, widgetNode *destNode);

    widgetNode *sourceNode() const;
    widgetNode *destNode() const;

    void adjust();

    enum { Type = UserType + 2 };
    int type() const override { return Type; }

protected:
    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    widgetNode *source, *dest;

    QPointF sourcePoint;
    QPointF destPoint;
    qreal arrowSize = 10;
};

#endif // WIDGETEDGE_H
