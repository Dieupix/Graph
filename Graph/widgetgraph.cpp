#include "widgetgraph.h"

widgetGraph::widgetGraph(QWidget *parent)
    : QGraphicsView(parent), sceneSizeW{400}, sceneSizeH{400}
{
    setup();
}

widgetGraph::widgetGraph(unsigned sceneSize, QWidget *parent)
    : QGraphicsView(parent), sceneSizeW{sceneSize}, sceneSizeH{sceneSize}
{
    setup();
}

widgetGraph::widgetGraph(unsigned sceneSizeW, unsigned sceneSizeH, QWidget *parent)
    : QGraphicsView(parent), sceneSizeW{sceneSizeW}, sceneSizeH{sceneSizeH}
{
    setup();
}

widgetGraph::widgetGraph(const widgetGraph& wg) : QGraphicsView(wg.parentWidget()),
    sceneSizeW{wg.sceneSizeW}, sceneSizeH{wg.sceneSizeH}
{
    setup();
}

void widgetGraph::setup()
{
    setMinimumSize(sceneSizeW, sceneSizeH);
    setCacheMode(CacheBackground);
    setViewportUpdateMode(BoundingRectViewportUpdate);
    setRenderHint(QPainter::Antialiasing);
    setTransformationAnchor(AnchorUnderMouse);
    scale(qreal(0.8), qreal(0.8));
    setWindowTitle(tr("Elastic Nodes"));

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    scene->setSceneRect(-(int)sceneSizeW / 2, -(int)sceneSizeH / 2, sceneSizeW, sceneSizeH);
    setScene(scene);

    // Exemple
    //const vector<int> fs {6, 2, 3, 0, 3, 0, 0};
    //const vector<int> aps {3, 1, 4, 6};
    vector<int> APS{6, 1, 5, 7, 10, 13, 16};
    vector<int> FS{18, 2, 3, 5, 0, 1, 0, 2, 5, 0, 3, 5, 0, 2, 6, 0, 1, 2, 0};
    Graph g;
    g.ajouterNoeud(Noeud(2), {0, 1, 0}, {0, 0, 0});
    g.ajouterNoeud(Noeud(3), {0, 1, 0, 0}, {0, 0, 1, 0});
    loadGraph(g);
}

void widgetGraph::itemMoved()
{
    if (!timerId)
        timerId = startTimer(1000 / 25);
}

void widgetGraph::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Up:
        centerNode->moveBy(0, -20);
        break;
    case Qt::Key_Down:
        centerNode->moveBy(0, 20);
        break;
    case Qt::Key_Left:
        centerNode->moveBy(-20, 0);
        break;
    case Qt::Key_Right:
        centerNode->moveBy(20, 0);
        break;
    case Qt::Key_Plus:
        zoomIn();
        break;
    case Qt::Key_Minus:
        zoomOut();
        break;
    case Qt::Key_Space:
    case Qt::Key_Enter:
        shuffle();
        break;
    default:
        QGraphicsView::keyPressEvent(event);
    }
}

void widgetGraph::timerEvent(QTimerEvent *event)
{
    Q_UNUSED(event);

    /*QList<widgetNode *> nodes;
    const QList<QGraphicsItem *> items = scene()->items();
    for (QGraphicsItem *item : items) {
        if (widgetNode *node = qgraphicsitem_cast<widgetNode *>(item))
            nodes << node;
    }*/

    for (widgetNode *node : qAsConst(nodes))
        node->calculateForces();

    bool itemsMoved = false;
    for (widgetNode *node : qAsConst(nodes)) {
        if (node->advancePosition())
            itemsMoved = true;
    }

    if (!itemsMoved) {
        killTimer(timerId);
        timerId = 0;
    }
}

void widgetGraph::wheelEvent(QWheelEvent *event)
{
    scaleView(pow(2., event->angleDelta().y() / 240.0));
}

void widgetGraph::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);

    // Shadow
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Fill
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Text
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Click and drag the nodes around, and zoom with the mouse "
                       "wheel or the '+' and '-' keys"));

    QFont font = painter->font();
    font.setBold(true);
    font.setPointSize(14);
    painter->setFont(font);
    painter->setPen(Qt::lightGray);
    painter->drawText(textRect.translated(2, 2), message);
    painter->setPen(Qt::black);
    painter->drawText(textRect, message);
}

void widgetGraph::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}

void widgetGraph::zoomIn()
{
    scaleView(1.2);
}

void widgetGraph::zoomOut()
{
    scaleView(1 / 1.2);
}

void widgetGraph::shuffle()
{}

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
    widgetGraph new_wg(this);
    new_wg.loadGraph(g);
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

    widgetGraph new_wg(this);
    new_wg.loadGraph(Graph{new_fs,new_aps});
    return new_wg;
}

void widgetGraph::englobe_Dijkstra(int sommet_depart)
{
    vector<int> d;
    vector<int> pr;
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
    widgetGraph new_wg(this);
    new_wg.loadGraph(Graph{d_matrice});
    return new_wg;
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

void widgetGraph::loadGraph(const Graph& g)
{
    d_aps = g.getAPS();
    d_fs = g.getFS();

    nodes.resize(0);
    unsigned modulo = sqrt(g.getSommets().size());
    int xOff = -(int)modulo;
    for(unsigned i = 1; i < g.getSommets().size(); ++i)
    {
        if(xOff % modulo == 0) xOff = -(int)modulo;

        auto node = new widgetNode(this, *g.getSommets()[i]);
        nodes << node;
        scene->addItem(node);
        node->setPos(g.getSommets()[i]->getId() * 30, xOff * 30);

        ++xOff;
    }

    for(unsigned i = 1; i < d_aps.size(); ++i)
    {
        unsigned j = d_fs[d_aps[i]], k = i;
        while(j != 0)
        {
            int iBis = i-1, jBis = j-1;
            auto edge = new widgetEdge(nodes[iBis], nodes[jBis]);
            nodes[iBis]->addEdge(edge);
            scene->addItem(edge);
            ++k;
            j = d_fs[k];
        }
    }
}

void widgetGraph::saveIn(std::ostream& ost)
{
    Graph g = toGraph();
    g.saveIn(ost);
}

Graph widgetGraph::toGraph()
{
    /*vector<unique_ptr<Noeud>> sommets;
    sommets.reserve(d_sommets.size());
    for(unsigned i = 1 ; i < d_sommets.size() ; ++i)
    {
        sommets.push_back(std::make_unique<Noeud>(i));
    }
    //Est oriente par défaut et n'a pas de poids predefini
    return Graph(d_fs,d_aps,sommets,true,false);*/
    return Graph();
}

















