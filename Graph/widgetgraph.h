#ifndef WIDGETGRAPH_H
#define WIDGETGRAPH_H

#include "algorithms.h"
#include "graph.h"
#include "widgetedge.h"
#include "widgetnode.h"

#include <QGraphicsView>
#include <QKeyEvent>

class widgetGraph : public QGraphicsView
{
    Q_OBJECT

public:
    widgetGraph(QWidget *parent = nullptr);
    widgetGraph(unsigned sceneSize, QWidget *parent = nullptr);
    widgetGraph(unsigned sceneSizeW, unsigned sceneSizeH, QWidget *parent = nullptr);

    widgetGraph(const widgetGraph& wg);

    vector<int>         getFs() const;
    vector<int>         getAps() const;
    vector<vector<int>> getCouts() const;
    vector<vector<int>> getMatrice() const;
    bool                getUsingFSandAPS() const;
    Graph               getGraph() const;

    void                englobe_Dantzig         ();
    void                englobe_Dijkstra        (int sommet_depart,vector<int>& d, vector<int>& pr);
    vector<vector<int>> englobe_Distance        ();
    widgetGraph         englobe_Kruskal         ();
    widgetGraph         englobe_Ordonnancement  (const vector<int>& duree_taches);
    widgetGraph         englobe_Prufer_decode   (const vector<int>& p);
    vector<int>         englobe_Prufer_encode   ();
    vector<int>         englobe_Rang            ();
    widgetGraph         englobe_Tarjan          ();
    bool                verifieFS_APS_NonVide   ();
    bool                verifieMatrice_NonVide  ();

    void ajouterNoeud   (const Noeud& noeud, const vector<int>& pred, const vector<int>& succ);
    void itemMoved      ();
    void loadFrom       (std::istream& ist);
    void saveIn         (std::ostream& ost);

    void    loadGraph               (const Graph& g);

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
    Graph d_g;

    QGraphicsScene* scene;
    unsigned        sceneSizeW, sceneSizeH;
    int             timerId = 0;

    QList<widgetNode*>  nodes;
    widgetNode*         centerNode;

    void    setup                   ();
    void    transformeVersMatrice   ();
    void    transformeVersFS_APS    ();
    Graph   toGraph                 ();
};

#endif // WIDGETGRAPH_H
