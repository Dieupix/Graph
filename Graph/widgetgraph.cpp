#include "widgetgraph.h"
#include "graph.h"
#include "algorithms.h"
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

vector<QPoint> widgetGraph::getSommets()
{
    return d_sommets;
}
vector<int> widgetGraph::getFs()
{
    return d_fs;
}
vector<int> widgetGraph::getAps()
{
    return d_aps;
}

vector<vector<int>> widgetGraph::englobe_Distance()
{
    vector<vector<int>> matriceDistance;
    mat_distance(d_fs,d_aps,matriceDistance);
    return matriceDistance;
}
vector<int> widgetGraph::englobe_Rang()
{
    vector<int> rg;
    rang(rg,d_fs,d_aps);
    return rg;
}
widgetGraph widgetGraph::englobe_Tarjan()
{
    vector<int> cfc, pilch, pred, prem;
    fortconnexe(d_fs,d_aps,cfc,pilch,pred,prem);
    //Transformer en un nouveau widgetGraph
    vector<vector<int>> mat;
    Graph g{mat};
    widgetGraph new_wg{g};
    return new_wg;
}
widgetGraph widgetGraph::englobe_Ordonnancement()
{
    vector<int> duree_taches, new_fs, new_aps;
    vector<int> file_pred;
    vector<int> adr_prem_pred;
    vector<int> file_pred_critique;
    vector<int> adr_prem_pred_critique;
    vector<int> longueur_critique;
    transforme_FS_APS_TO_FP_APP(d_fs, d_aps, file_pred, adr_prem_pred);
    Ordonnancement(file_pred, adr_prem_pred, duree_taches, file_pred_critique, adr_prem_pred_critique, longueur_critique);
    transforme_FP_APP_TO_FS_APS(file_pred_critique,adr_prem_pred_critique,new_fs,new_aps);

    //Affichage de la longueur critique
    //...
    //printVector(longueur_critique);

    return {new Graph{new_fs,new_aps}};
}
void widgetGraph::englobe_Dijkstra(int sommet_depart)
{
    vector<int> d, pr;
    Dijkstra(d_fs,d_aps,d_couts,sommet_depart,d,pr);
    //Resultat d et pr ??
}
void widgetGraph::englobe_Dantzig()
{
    vector<vector<int>> c;
    if(Dantzig(c))
    {
        d_couts.resize(c.size());
        d_couts[0].resize(2);
        for(unsigned i = 1 ; i < c.size() ;++i)
            d_couts[i].resize(c[i].size());

        for(unsigned i = 0 ; i < c.size() ; ++i)
            for(unsigned j = 0 ; j < d_couts.size(); ++j)
                d_couts[i][j] = c[i][j];
    }
}
void widgetGraph::englobe_Kruskal()
{
    //Push la version finale
}
vector<int> widgetGraph::englobe_Prufer_encode()
{
    vector<int> p;
    Prufer_encode(d_matrice,p);
    return p;
}
widgetGraph widgetGraph::englobe_Prufer_decode(const vector<int>& p)
{
    Prufer_decode(p,d_matrice);
    return {new Graph{d_matrice}};
}

void widgetGraph::loadFrom(std::istream& ist)
{
    Graph g;
    g.loadFrom(ist);
    d_fs = g.getFS();
    d_aps = g.getAPS();
    d_matrice = g.getMatAdj();
    d_couts = g.getCouts();
}

void widgetGraph::save(std::ostream& ost)
{
    Graph g = toGraph();
    g.saveIn(ost);
}

void widgetGraph::ajouterNoeud()
{
    Graph g = toGraph();
    vector<int> pred, succ;
    //g.ajouterNoeud(  ,pred,succ);
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




