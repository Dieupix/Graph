#include "widgetgraph.h"
#include<QPainter>
#include<QMouseEvent>

widgetGraph::widgetGraph(QWidget *parent) : QWidget{parent}
{}

widgetGraph::widgetGraph(const widgetGraph& g) :  d_fs{g.d_fs}, d_aps{g.d_aps}, d_sommets{g.d_sommets}
{}

void widgetGraph::paintEvent(QPaintEvent*)
{
    QPainter paint{this};

    for(unsigned i = 1 ; i < d_sommets.size() ; ++i)
        dessineSommet(paint, d_sommets[i]);

    dessineGraphe(paint);
}

void widgetGraph::dessineGraphe(QPainter& paint)
{
    for(int i = 1 ; i < d_aps[0] ; ++i)
    {
        int k = d_aps[i];
        while(d_fs[k] != 0)
        {
            paint.drawLine(d_sommets[d_aps[i]], d_sommets[d_fs[k]]);
            ++k;
        }
    }
}
void widgetGraph::dessineSommet(QPainter& paint, const QPoint& s)
{
    //A tester
    paint.drawEllipse(s.x() - 3 , s.y() - 3 , 6 , 6);
}

void widgetGraph::MouseReleaseEvent(QMouseEvent* e)
{
    if(e->button() == Qt::LeftButton)
    {
        ajouteSommet(e->pos());
    }
    else if(e->button() == Qt::RightButton)
    {
        enleveSommet(e->pos());
    }
    update();
}

void widgetGraph::ajouteSommet(const QPoint& p)
{
    d_sommets.push_back(p);
    d_aps.push_back(d_fs[0]);
    d_fs[0]++;
    d_fs.push_back(0);
}

void widgetGraph::enleveSommet(const QPoint& s)
{
    //...
}







