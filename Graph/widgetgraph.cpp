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

    scene = new QGraphicsScene(this);
    scene->setItemIndexMethod(QGraphicsScene::NoIndex);
    //scene->setSceneRect(-(int)sceneSizeW / 2, -(int)sceneSizeH / 2, sceneSizeW, sceneSizeH);
    scene->setSceneRect(-(int)sceneSizeW, -(int)sceneSizeH / 2, sceneSizeW * 2, sceneSizeH);
    setScene(scene);

    d_g = Graph();
    loadGraph(d_g);

    // Exemple
    //const vector<int> fs {6, 2, 3, 0, 3, 0, 0};
    //const vector<int> aps {3, 1, 4, 6};
    vector<int> APS{6, 1, 5, 7, 10, 13, 16};
    vector<int> FS{18, 2, 3, 5, 0, 1, 0, 2, 5, 0, 3, 5, 0, 2, 6, 0, 1, 2, 0};
    ajouterNoeud(Noeud(2), {0, 1, 0}, {0, 0, 0});
    ajouterNoeud(Noeud(3), {0, 1, 0, 0}, {0, 0, 1, 0});
    ajouterNoeud(Noeud(4), {0, 0, 1, 1, 0}, {0, 0, 1, 0, 0});
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

    // Ombres
    QRectF sceneRect = this->sceneRect();
    QRectF rightShadow(sceneRect.right(), sceneRect.top() + 5, 5, sceneRect.height());
    QRectF bottomShadow(sceneRect.left() + 5, sceneRect.bottom(), sceneRect.width(), 5);
    if (rightShadow.intersects(rect) || rightShadow.contains(rect))
        painter->fillRect(rightShadow, Qt::darkGray);
    if (bottomShadow.intersects(rect) || bottomShadow.contains(rect))
        painter->fillRect(bottomShadow, Qt::darkGray);

    // Remplissage
    QLinearGradient gradient(sceneRect.topLeft(), sceneRect.bottomRight());
    gradient.setColorAt(0, Qt::white);
    gradient.setColorAt(1, Qt::lightGray);
    painter->fillRect(rect.intersected(sceneRect), gradient);
    painter->setBrush(Qt::NoBrush);
    painter->drawRect(sceneRect);

    // Texte
    QRectF textRect(sceneRect.left() + 4, sceneRect.top() + 4,
                    sceneRect.width() - 4, sceneRect.height() - 4);
    QString message(tr("Cliquez et bouger les noeuds, zoomez avec la molette de la souris ou les boutons '+' et '-'"));

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
{
    Noeud noeud(nodes.back()->getNoeud()->getId()+1);
    vector<int> pred(d_g.getAPS()[0]+1, 0), succ(d_g.getAPS()[0]+1, 0);

    pred[1] = succ[1] = 1;

    ajouterNoeud(noeud, pred, succ);
}

vector<int> widgetGraph::getFs() const
{
    return d_g.getFS();
}

vector<int> widgetGraph::getAps() const
{
    return d_g.getAPS();
}

vector<vector<int>> widgetGraph::getCouts() const
{
    return d_g.getCouts();
}

vector<vector<int>> widgetGraph::getMatrice() const
{
    return d_g.getMatAdj();
}

bool widgetGraph::getUsingFSandAPS() const
{
    return d_g.isUsingFsAndAps();
}

Graph widgetGraph::getGraph() const
{
    return d_g;
}

void widgetGraph::englobe_Dantzig()
{
    vector<vector<int>> c;
    if(Dantzig(c))
    {
        d_g.setCout(c);
    }
}

void widgetGraph::englobe_Dijkstra(int sommet_depart, vector<int>& d, vector<int>& pr)
{
    if(!d_g.isUsingFsAndAps())
    {
        transformeVersFS_APS();
    }
    Dijkstra(d_g.getFS(),d_g.getAPS(),d_g.getCouts(),sommet_depart,d,pr);
}

vector<vector<int>> widgetGraph::englobe_Distance()
{
    vector<vector<int>> matriceDistance;
    if(!d_g.isUsingFsAndAps())
    {
        transformeVersFS_APS();
    }
    mat_distance(d_g.getFS(),d_g.getAPS(),matriceDistance);
    return matriceDistance;
}

widgetGraph widgetGraph::englobe_Kruskal()
{
    widgetGraph wg;
    Graph t;
    if(!d_g.isUsingFsAndAps())
    {
        transformeVersFS_APS();
    }
    Kruskal(d_g,t);
    wg.loadGraph(t);
    return wg;
}

widgetGraph widgetGraph::englobe_Ordonnancement(const vector<int>& duree_taches)
{
    vector<int> new_fs, new_aps;
    vector<int> file_pred;
    vector<int> adr_prem_pred;
    vector<int> file_pred_critique;
    vector<int> adr_prem_pred_critique;
    vector<int> longueur_critique;
    if(!d_g.isUsingFsAndAps())
    {
       transformeVersFS_APS();
    }
    transforme_FS_APS_TO_FP_APP(d_g.getFS(), d_g.getAPS(), file_pred, adr_prem_pred);
    Ordonnancement(file_pred, adr_prem_pred, duree_taches, file_pred_critique, adr_prem_pred_critique, longueur_critique);
    transforme_FP_APP_TO_FS_APS(file_pred_critique,adr_prem_pred_critique,new_fs,new_aps);

    //Affichage de la longueur critique
    //Sur console ?
    printVector(longueur_critique);cout<<"OK";
/*
    widgetGraph new_wg(this);
    new_wg.loadGraph(Graph{new_fs,new_aps});*
    return new_wg;*/return widgetGraph{};
}

widgetGraph widgetGraph::englobe_Prufer_decode(const vector<int>& p)
{
    if(d_g.isUsingFsAndAps())
    {
        transformeVersMatrice();
    }

    vector<vector<int>> mat;
    Prufer_decode(p, mat);

    widgetGraph new_wg(this);
    new_wg.loadGraph(Graph{mat});
    return new_wg;
}

vector<int> widgetGraph::englobe_Prufer_encode()
{
    vector<int> p;
    if(d_g.isUsingFsAndAps())
    {
        transformeVersMatrice();
    }/*
    vector<vector<int>> mat = d_g.getMatAdj();
    cout<<mat[0][0]<<" "<<mat[0][1]<<endl;
    for(unsigned i = 1 ; i < mat.size()  ; ++i)
        printVector(mat[i]);
    //Prufer_encode(d_g.getMatAdj(), p);*/
    return p;
}

vector<int> widgetGraph::englobe_Rang()
{
    vector<int> rg;
    if(!d_g.isUsingFsAndAps())
    {
        transformeVersFS_APS();
    }
    rang(rg,d_g.getFS(),d_g.getAPS());
    return rg;
}

widgetGraph widgetGraph::englobe_Tarjan()
{
    vector<int> cfc, pilch, pred, prem;
    if(!d_g.isUsingFsAndAps())
    {
        transformeVersFS_APS();
    }
    fortconnexe(d_g.getFS(),d_g.getAPS(),cfc,pilch,pred,prem);

    //traitement du resultat
    vector<vector<int>> mat;
    printVector(cfc);
    printVector(prem);
    printVector(d_g.getFS());
    printVector(d_g.getAPS());
    versGrapheReduit(cfc,prem,d_g.getFS(),d_g.getAPS(),mat);

    widgetGraph new_wg(this);
    new_wg.loadGraph(Graph{mat});
    return new_wg;
}

bool widgetGraph::verifieFS_APS_NonVide()
{
    if(d_g.getFS().empty() || d_g.getAPS().empty())
    {
        return false;
    }
    return true;
}

bool widgetGraph::verifieMatrice_NonVide()
{
    vector<vector<int>> mat = d_g.getMatAdj();
    if(mat.empty())
        return false;
    else if(mat[0].size() != 2)
    {
        return false;
    }
    else
    {
        unsigned size = mat[1].size();
        for(unsigned i = 2 ; i < mat.size() ; ++i)
        {
            if(mat[i].size() != size)
                return false;
        }
        return true;
    }
}

bool widgetGraph::verifieCout_NonVide()
{

    if(d_g.getCouts().empty())
        return false;
    else
    {
         vector<vector<int>> cout = d_g.getCouts();
        if(cout[0].size() != 2)
        {
            return false;
        }
        else
        {
            unsigned size = cout[1].size();
            for(unsigned i = 2 ; i < cout.size() ; ++i)
            {
                if(cout[i].size() != size)
                    return false;
            }
            return true;
        }
    }
}


void widgetGraph::ajouterNoeud(const Noeud& noeud, const vector<int>& pred, const vector<int>& succ)
{
    auto node = new widgetNode(this, noeud);
    scene->addItem(node);
    if(nodes.size() != 0)
    {
        auto p = nodes.back()->pos();
        node->setPos(p.x() + 50, std::pow(-1, nodes.back()->getNoeud()->getId()) * 50 + p.y());
    }
    else node->setPos(0, 50);

    for(unsigned i = 0; i < nodes.size(); ++i)
    {
        if(pred[i+1])
        {
            auto edge = new widgetEdge(nodes[i], node);
            nodes[i]->addEdge(edge);
            scene->addItem(edge);
        }
        if(succ[i+1])
        {
            auto edge = new widgetEdge(node, nodes[i]);
            nodes[i]->addEdge(edge);
            scene->addItem(edge);
        }
    }
    nodes << node;
    d_g.ajouterNoeud(noeud, pred, succ);
}

void widgetGraph::loadFrom(std::istream& ist)
{
    d_g.loadFrom(ist);
}

void widgetGraph::transformeVersMatrice()
{
    vector<vector<int>> matrice;
    d_g.FS_APS_to_MatAdj(matrice);
    cout<<matrice[0][0]<<" "<<matrice[0][1]<<endl;
    for(unsigned i = 1 ; i < matrice.size()  ; ++i)
        printVector(matrice[i]);

    d_g = Graph(matrice, d_g.getSommets(), d_g.getEst_oriente(), d_g.getA_Des_Poids());
}

void widgetGraph::transformeVersFS_APS()
{
    vector<int> fs, aps;
    d_g.matAdj_to_FS_APS(fs,aps);

    d_g = Graph(fs, aps, d_g.getSommets(), d_g.getEst_oriente(), d_g.getA_Des_Poids());
}

void widgetGraph::loadGraph(const Graph& g)
{
    d_g = g;
    scene->clear();
    nodes.resize(0);
    unsigned modulo = sqrt(g.getSommets().size());
    int xOff = -(int)modulo;
    for(unsigned i = 1; i < g.getSommets().size(); ++i)
    {
        if(xOff % modulo == 0) xOff = -(int)modulo;

        auto node = new widgetNode(this, *g.getSommets()[i]);
        if(nodes.contains(node)) continue;

        nodes << node;
        scene->addItem(node);
        node->setPos(g.getSommets()[i]->getId() * 30, xOff * 30);

        ++xOff;
    }

    for(unsigned i = 1; i < d_g.getAPS().size(); ++i)
    {
        unsigned j = d_g.getFS()[d_g.getAPS()[i]], k = i;
        while(j != 0)
        {
            int iBis = i-1, jBis = j-1;
            auto edge = new widgetEdge(nodes[iBis], nodes[jBis]);
            nodes[iBis]->addEdge(edge);
            scene->addItem(edge);
            ++k;
            j = d_g.getFS()[k];
        }
    }
}

void widgetGraph::saveIn(std::ostream& ost)
{
    d_g.saveIn(ost);
}



















