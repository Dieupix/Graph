#ifndef WIDGETGRAPH_H
#define WIDGETGRAPH_H

#include "algorithms.h"
#include "graph.h"
#include "widgetnode.h"
#include "widgetedge.h"

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

    vector<int> getFs();
    vector<int> getAps();
    vector<vector<int>> getCouts();
    vector<vector<int>> getMatrice();
    bool getUsingFSandAPS();

    bool verifieFS_APS_NonVide();
    bool verifieMatrice_NonVide();
    vector<vector<int>> englobe_Distance();
    vector<int> englobe_Rang();
    widgetGraph englobe_Tarjan();
    widgetGraph englobe_Ordonnancement(const vector<int>& duree_taches);
    void englobe_Dijkstra(int sommet_depart,vector<int>& d, vector<int>& pr);
    void englobe_Dantzig();
    widgetGraph englobe_Kruskal();
    vector<int> englobe_Prufer_encode();
    widgetGraph englobe_Prufer_decode(const vector<int>& p);

    void ajouterNoeud();
    void itemMoved();
    void loadFrom(std::istream& ist);
    void saveIn(std::ostream& ost);

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
    vector<vector<int>> d_matrice;
    vector<vector<int>> d_couts;
    bool d_isUsingFsAndAps;

    QGraphicsScene      *scene;
    unsigned            sceneSizeW, sceneSizeH;
    int                 timerId = 0;

    QList<widgetNode *> nodes;
    widgetNode          *centerNode;

    void setup();
    void transformeVersMatrice();
    void transformeVersFS_APS();
    void loadGraph(const Graph& g);
    Graph toGraph();
};

#endif // WIDGETGRAPH_H
