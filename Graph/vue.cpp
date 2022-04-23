#include "vue.h"

vue::vue(QMainWindow* fenetre) : d_fenetre{fenetre}
{}

void vue::creeInterface()
{
    //setWindowState(Qt::WindowMaximized);
    d_fenetre->setWindowTitle("Graphe");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    setupMenu();

    mainLayout->addWidget(new QLabel("Votre graphe :"), 0, Qt::AlignLeft);

/*
    const vector<int> fs {6, 2, 3, 0, 3, 0, 0};
    const vector<int> aps {3, 1, 4, 6};
    Graph g(fs,aps);
    auto widGraph = new widgetGraph(g);
    mainLayout->addWidget(widGraph);
*/

    // POUR AJOUTER LE GRAPH DANS LA VUE
    auto gwLayout = new QVBoxLayout();
    mainLayout->addLayout(gwLayout);

    auto gw = new widgetGraph(600);
    gwLayout->addWidget(gw);
    gw->show();
    //gw->close(); //pour fermer le graph
}

void vue::creeInterfaceSaisie()
{
    d_fenetre->setWindowTitle("Ajouter Noeud");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    menuSaisie();
}
void vue::creeInterfacePruferDecode()
{
    d_fenetre->setWindowTitle("Saisie pour Prufer (encode)");

    auto central = new QWidget;
    auto mainLayout = new QVBoxLayout;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);

    fenetrePruferDecode();
}
void vue::setupMenu()
{
    setupMenuFichier();
    setupMenuAlgo();
    setupMenuInfo();
}

void vue::setupMenuFichier()
{
    auto menuGraph = d_fenetre->menuBar()->addMenu("&Fichier");

    auto actionCharger = new QAction{"Charger"};
    actionCharger->setToolTip("Charger graph");
    menuGraph->addAction(actionCharger);
    connect(actionCharger, &QAction::triggered, this, &vue::onCharger);

    auto actionSaisie = new QAction{"Saisie"};
    actionSaisie->setToolTip("Saisir graph");
    menuGraph->addAction(actionSaisie);
    connect(actionSaisie, &QAction::triggered, this, &vue::onSaisie);

    menuGraph->addSeparator();

    auto actionAjout = new QAction{"Ajout Noeud"};
    actionAjout->setToolTip("Ajout Noeud");
    menuGraph->addAction(actionAjout);
    connect(actionAjout, &QAction::triggered, this, &vue::onAjout);

    auto actionSupprimer = new QAction{"Supprimer Noeud"};
    actionSupprimer->setToolTip("Supprimer Noeud");
    menuGraph->addAction(actionSupprimer);
    connect(actionSupprimer, &QAction::triggered, this, &vue::onSuppression);

    menuGraph->addSeparator();

    auto actionQuitter = new QAction{"Quitter"};
    actionQuitter->setToolTip("Quitter application");
    menuGraph->addAction(actionQuitter);
    connect(actionQuitter, &QAction::triggered, this, &vue::onQuitter);
}

void vue::setupMenuAlgo()
{
    auto menuAlgo = d_fenetre->menuBar()->addMenu("&Algorithm");

    auto actionDistance = new QAction{"Distance"};
    actionDistance->setToolTip("Distance algorithme");
    menuAlgo->addAction(actionDistance);
    connect(actionDistance, &QAction::triggered, this, &vue::onDistance);

    auto actionRang = new QAction{"Rang"};
    actionRang->setToolTip("Rang algorithme");
    menuAlgo->addAction(actionRang);
    connect(actionRang, &QAction::triggered, this, &vue::onRang);

    auto actionTarjan = new QAction{"Tarjan"};
    actionTarjan->setToolTip("Tarjan algorithme");
    menuAlgo->addAction(actionTarjan);
    connect(actionTarjan, &QAction::triggered, this, &vue::onTarjan);

    auto actionOrdonnancement = new QAction{"Ordonnancement"};
    actionOrdonnancement->setToolTip("Ordonnancement algorithme");
    menuAlgo->addAction(actionOrdonnancement);
    connect(actionOrdonnancement, &QAction::triggered, this, &vue::onOrdonnancement);

    auto actionDijkstra = new QAction{"Dijkstra"};
    actionDijkstra->setToolTip("Dijkstra algorithme");
    menuAlgo->addAction(actionDijkstra);
    connect(actionDijkstra, &QAction::triggered, this, &vue::onDijkstra);

    auto actionDantzig = new QAction{"Dantzig"};
    actionDantzig->setToolTip("Dantzig algorithme");
    menuAlgo->addAction(actionDantzig);
    connect(actionDantzig, &QAction::triggered, this, &vue::onDantzig);

    auto actionKruskal = new QAction{"Kruskal"};
    actionKruskal->setToolTip("Kruskal algorithme");
    menuAlgo->addAction(actionKruskal);
    connect(actionKruskal, &QAction::triggered, this, &vue::onKruskal);

    auto SousMenuPrufer = menuAlgo->addMenu("Prufer");

    auto actionPruferEncode = new QAction{"Prufer_encode"};
    actionPruferEncode->setToolTip("Prufer encode");
    SousMenuPrufer->addAction(actionPruferEncode);
    connect(actionPruferEncode, &QAction::triggered, this, &vue::onPruferEncode);

    auto actionPruferDecode = new QAction{"Prufer_decode"};
    actionPruferDecode->setToolTip("Prufer decode");
    SousMenuPrufer->addAction(actionPruferDecode);
    connect(actionPruferDecode, &QAction::triggered, this, &vue::onPruferDecode);
}
void vue::setupMenuInfo()
{
    auto menuInfo = d_fenetre->menuBar()->addMenu("&Info");

    auto infoDistance = new QAction{"Distance"};
    infoDistance->setToolTip("Distance algorithme");
    menuInfo->addAction(infoDistance);
    connect(infoDistance, &QAction::triggered, this, &vue::oninfoDistance);

    auto infoRang = new QAction{"Rang"};
    infoRang->setToolTip("Distance algorithme");
    menuInfo->addAction(infoRang);
    connect(infoRang, &QAction::triggered, this, &vue::oninfoRang);

    auto infoTarjan = new QAction{"Tarjan"};
    infoTarjan->setToolTip("Distance algorithme");
    menuInfo->addAction(infoTarjan);
    connect(infoTarjan, &QAction::triggered, this, &vue::oninfoTarjan);

    auto infoOrdonnancement = new QAction{"Ordonnancement"};
    infoOrdonnancement->setToolTip("Distance algorithme");
    menuInfo->addAction(infoOrdonnancement);
    connect(infoOrdonnancement, &QAction::triggered, this, &vue::oninfoOrdonnancement);

    auto infoDijkstra = new QAction{"Dijkstra"};
    infoDijkstra->setToolTip("Distance algorithme");
    menuInfo->addAction(infoDijkstra);
    connect(infoDijkstra, &QAction::triggered, this, &vue::oninfoDijkstra);

    auto infoDantzig = new QAction{"Dantzig"};
    infoDantzig->setToolTip("Distance algorithme");
    menuInfo->addAction(infoDantzig);
    connect(infoDantzig, &QAction::triggered, this, &vue::oninfoDantzig);

    auto infoKruskal = new QAction{"Kruskal"};
    infoKruskal->setToolTip("Distance algorithme");
    menuInfo->addAction(infoKruskal);
    connect(infoKruskal, &QAction::triggered, this, &vue::oninfoKruskal);

    auto SousMenuPrufer = menuInfo->addMenu("Prufer");

    auto infoPruferEncode = new QAction{"Prufer Encode"};
    infoPruferEncode->setToolTip("Distance algorithme");
    SousMenuPrufer->addAction(infoPruferEncode);
    connect(infoPruferEncode, &QAction::triggered, this, &vue::oninfoPrufer_encode);

    auto infoPruferDecode = new QAction{"Prufer Decode"};
    infoDistance->setToolTip("Distance algorithme");
    SousMenuPrufer->addAction(infoPruferDecode);
    connect(infoPruferDecode, &QAction::triggered, this, &vue::oninfoPrufer_decode);
}
void vue::menuSaisie()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton{"Valider", nullptr};
    layoutBas->addWidget(boutonValider);
    connect(boutonValider, &QPushButton::clicked, this, &vue::Ajouter);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    connect(boutonQuitter, &QPushButton::clicked, this, &vue::Quitter);
    layoutBas->addWidget(boutonQuitter);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutSucc = new QHBoxLayout{};
    auto pannelSucc = new QLabel{"Successeur du noeud", nullptr};
    layoutSucc->addWidget(pannelSucc,1);
    //auto textSucc = new QLineEdit{};

    d_suc = new QLineEdit{};
    layoutSucc->addWidget(d_suc);

    auto layoutPrec = new QHBoxLayout{};
    auto pannelPrec = new QLabel{"Predecesseur du noeud", nullptr};
    layoutPrec->addWidget(pannelPrec,1);
    //auto textPrec = new QLineEdit{};

    d_prec = new QLineEdit{};
    layoutPrec->addWidget(d_prec);

    auto layoutPoids = new QHBoxLayout{};
    auto labelPoids = new QLabel{"Poids du noeud", nullptr};
    layoutPoids->addWidget(labelPoids,1);
    //auto textPoids = new QLineEdit{};

    d_poids = new QLineEdit{};
    layoutPoids->addWidget(d_poids);

    layoutInfo->addLayout(layoutSucc);
    layoutInfo->addLayout(layoutPrec);
    layoutInfo->addLayout(layoutPoids);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);
}
void vue::fenetrePruferDecode()
{
    auto layoutBas = new QHBoxLayout{};

    auto boutonValider = new QPushButton{"Valider", nullptr};
    layoutBas->addWidget(boutonValider);
    //connect(boutonValider, &QPushButton::clicked, this, &vue::onValide);

    auto boutonQuitter = new QPushButton{"Quitter", nullptr};
    layoutBas->addWidget(boutonQuitter);

    auto layoutInfo = new QVBoxLayout{};

    auto layoutP = new QHBoxLayout{};
    auto pannelP = new QLabel{"Saisie d'un tableau de Prufer", nullptr};
    layoutP->addWidget(pannelP);
    d_p = new QLineEdit{};
    layoutP->addWidget(d_p);

    layoutInfo->addLayout(layoutP);

    auto mainLayout = new QVBoxLayout;
    mainLayout->addLayout(layoutInfo);
    mainLayout->addLayout(layoutBas);

    auto central = new QWidget;
    central->setLayout(mainLayout);
    d_fenetre->setCentralWidget(central);


}
void vue::metAJourGraphe()
{
    //MAj fs/aps..
    metAJourNoeuds();
}

void vue::metAJourNoeuds()
{
    //Ici, on modifie fs / aps / matrice voire meme le graphe jsp
}

void vue::onQuitter()
{
    emit Quitter();
}
void vue::onCharger()
{
    emit Charger();
}
void vue::onSaisie()
{
    emit Saisie();
}
void vue::onAjout()
{
    emit Ajout();
}
void vue::onSuppression()
{
    emit Suppression();
}
void vue::onDistance()
{
    emit AlgorithmeSelectionneDistance();
}

void vue::onRang()
{
    emit AlgorithmeSelectionneRang();
}

void vue::onTarjan()
{
    emit AlgorithmeSelectionneTarjan();
}

void vue::onOrdonnancement()
{
    emit AlgorithmeSelectionneOrdonnancement();
}
void vue::onDijkstra()
{
    emit AlgorithmeSelectionneDijkstra();
}
void vue::onDantzig()
{
    emit AlgorithmeSelectionneDantzig();
}
void vue::onKruskal()
{
    emit AlgorithmeSelectionneKruskal();
}
void vue::onPruferEncode()
{
    emit AlgorithmeSelectionnePruferEncode();
}
void vue::onPruferDecode()
{
    emit AlgorithmeSelectionnePruferDecode();
}
void vue::oninfoDistance()
{
    emit InfoDistance();
}
void vue::oninfoRang()
{
    emit InfoRang();
}
void vue::oninfoTarjan()
{
    emit InfoTarjan();
}
void vue::oninfoOrdonnancement()
{
    emit InfoOrdonnancement();
}
void vue::oninfoDijkstra()
{
    emit InfoDijkstra();
}
void vue::oninfoDantzig()
{
    emit InfoDantzig();
}
void vue::oninfoKruskal()
{
    emit InfoKruskal();
}
void vue::oninfoPrufer_encode()
{
    emit InfoPrufer_encode();
}
void vue::oninfoPrufer_decode()
{
    emit InfoPrufer_decode();
}

void vue::onAjouter()
{
    emit Ajouter();
}

int vue::getPoids()
{
    return this->d_poids->text().toInt();
}

int vue::getSuc()
{
    return this->d_suc->text().toInt();
}

int vue::getPred()
{
    return this->d_prec->text().toInt();
}
vector<int> vue::getP()
{
    QString s = this->d_p->text();
    vector<int> p;
    QStringList list = s.split(',');
    for(unsigned i = 0 ; i < list.size() ; ++i)
        p.push_back(list[i].toInt());
    return p;
}
