#include "widgetgraph.h"
#include "graph.h"
#include<QPainter>
#include<QMouseEvent>

widgetGraph::widgetGraph(QWidget *parent) : QWidget{parent}
{}

widgetGraph::widgetGraph(const widgetGraph& g, QWidget *parent) : QWidget{parent}, d_fs{g.d_fs}, d_aps{g.d_aps}, d_sommets{g.d_sommets}
{}

widgetGraph::widgetGraph(const Graph& g, QWidget* parent) : QWidget{parent}
{
    fromGraph(g);
}

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
    bool est_trouve = false;
    int i = 1;
    //On enleve le Point s de l'ensemble des sommets du graphe
    while(est_trouve == false)
    {
        if(d_sommets[i] == s)
            est_trouve = true;
    }
    for(unsigned j = i ; j < d_sommets.size()-1 ; ++j)
    {
        d_sommets[j] = d_sommets[j+1];
    }
    d_sommets.pop_back();

    //On l'enleve de APS et FS
    //Pour cela, on passe par la matrice d'adjacence
    //On supprime la ligne i et la colonne i qui correspond au numero du sommet s
    //On retransforme la matrice en FS/APS qu'on remplace par les anciens

}


Graph widgetGraph::toGraph()
{
    vector<unique_ptr<Noeud>> sommets;
    sommets.reserve(d_sommets.size());
    for(unsigned i = 1 ; i < d_sommets.size() ; ++i)
    {
        sommets.push_back(std::make_unique<Noeud>(i));
    }
    //Est oriente par défaut et n'a pas de poids predefini
    return Graph(d_fs,d_aps,sommets,true,false);
}

void widgetGraph::fromGraph(const Graph& g)
{
   d_aps = g.getAPS();
   d_fs = g.getFS();
   //vector<unique_ptr<Noeud>> s = g.getSommets();
   int k = 1;
   for(unsigned i = 1 ; i < g.getSommets().size() ; ++i)
   {
      if(i%5 == 0) k+= 3;

      //Range les sommets dans la zone
      d_sommets[i].setX(i*2);
      d_sommets[i].setY(i*k);
   }
}




