#include "mainwindow.h"
#include<iostream>
#include<QMessageBox>

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow{parent}, d_wg{new widgetGraph()}, d_vue{this}, menuPruferD{new menuPruferDecode}, menuDijkstra{new menudijkstra}, menuOrd{new menuOrdonnancement}, menuS{new menuAjout}, menuSuppr{new menuSupprimer}, menuFSAPS{new class saisieFSAPS}
{
    d_vue.creeInterface(d_wg);
    d_vue.metAJourGraphe();

    connect(&d_vue, &vue::OrienteeChange, this, &MainWindow::onCheck_OrienteeChange);
    connect(&d_vue, &vue::A_des_PoidsChange, this, &MainWindow::onCheck_A_des_PoidsChange);
    connect(&d_vue, &vue::FsAps_MatAdjChange, this, &MainWindow::onCheck_FsAps_MatAdjChange);

    connect(&d_vue, &vue::Quitter, this, &MainWindow::close);
    connect(&d_vue, &vue::Charger, this, &MainWindow::charge);
    connect(&d_vue, &vue::SaisieFSAPS, this, &MainWindow::saisieFSAPS);
    connect(&d_vue, &vue::SaisieMatrice, this, &MainWindow::saisieMatrice);
    connect(&d_vue, &vue::Ajout, this, &MainWindow::ajoute);
    connect(&d_vue, &vue::Suppression, this, &MainWindow::supprime);

    connect(&d_vue, &vue::AlgorithmeSelectionneDistance, this, &MainWindow::onClick_Distance);
    connect(&d_vue, &vue::AlgorithmeSelectionneRang, this, &MainWindow::onClick_Rang);
    connect(&d_vue, &vue::AlgorithmeSelectionneTarjan, this, &MainWindow::onClick_Tarjan);
    connect(&d_vue, &vue::AlgorithmeSelectionneOrdonnancement, this, &MainWindow::onClick_Ordonnancement);
    connect(&d_vue, &vue::AlgorithmeSelectionneDijkstra, this, &MainWindow::onClick_Dijkstra);
    connect(&d_vue, &vue::AlgorithmeSelectionneDantzig, this, &MainWindow::onClick_Dantzig);
    connect(&d_vue, &vue::AlgorithmeSelectionneKruskal, this, &MainWindow::onClick_Kruskal);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferEncode, this, &MainWindow::onClick_Prufer_encode);
    connect(&d_vue, &vue::AlgorithmeSelectionnePruferDecode, this, &MainWindow::onClick_Prufer_decode);

    connect(menuPruferD, &menuPruferDecode::valide, this, &MainWindow::onValiderPruferDecode);
    connect(menuDijkstra, &menudijkstra::valide, this, &MainWindow::onValiderDijkstra);
    connect(menuOrd, &menuOrdonnancement::valide, this, &MainWindow::onValiderOrdonnancement);
    connect(menuS, &menuAjout::envoieAjout, this, &MainWindow::onValiderAjout);
    connect(menuFSAPS, &saisieFSAPS::envoieSaisieFSAPS, this, &MainWindow::onValideSaisieFSAPS);

    connect(&d_vue, &vue::InfoDistance, this, &MainWindow::onClickDistance_INFO);
    connect(&d_vue, &vue::InfoRang, this, &MainWindow::onClickRang_INFO);
    connect(&d_vue, &vue::InfoTarjan, this, &MainWindow::onClickTarjan_INFO);
    connect(&d_vue, &vue::InfoOrdonnancement, this, &MainWindow::onClickOrdonnancement_INFO);
    connect(&d_vue, &vue::InfoDijkstra, this, &MainWindow::onClickDijkstra_INFO);
    connect(&d_vue, &vue::InfoDantzig, this, &MainWindow::onClickDantzig_INFO);
    connect(&d_vue, &vue::InfoKruskal, this, &MainWindow::onClickKruskal_INFO);
    connect(&d_vue, &vue::InfoPrufer_encode, this, &MainWindow::onClickPrufer_encode_INFO);
    connect(&d_vue, &vue::InfoPrufer_decode, this, &MainWindow::onClickPrufer_decode_INFO);

}

bool MainWindow::verifieDistance()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit oriente.
    return d_wg.getOriente() && (d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide());
}

bool MainWindow::verifieRang()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit oriente.
    return d_wg.getOriente() && (d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide());
}
bool MainWindow::verifieTarjan()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide();
}
bool MainWindow::verifieOrdonnancement(const vector<int>& duree_taches, const vector<int>& fs, const vector<int>& aps)
{
    //Il faut que fs et aps soit initialisé.
    //Il faut que duree_taches soit correctement initisalisé et saisie
    ///IL FAUT VERIFIER FS ET APS OK
    int n = aps[0];
    return (duree_taches[0] != n); //FALSE : pas assez de duree dans le tableau pour le nombre de sommets saisis !
}

bool MainWindow::verifieDijkstra(int sommet_depart)
{
    //Il faut que le graphe soit oriente.
    //Il faut que fs et aps soit initialisé ou la matrice.
    //Il faut que le cout soit correct, qu'il ne contienne pas de cout < 0
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                bool sommet_correct = true;
                bool couts_correct = true;
                if(sommet_depart <= 0 || sommet_depart > d_wg.getAps()[0])
                    sommet_correct = false; //Le sommet saisi n'est pas valide !
                else
                {
                    if(d_wg.verifieCout_NonVide())
                    {
                        vector<vector<int>> couts = d_wg.getCouts();
                        if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                            couts_correct = false; //Les elements presents dans le cout ne correspondent pas avec le fs et aps
                        else
                        {
                            for(unsigned i = 1 ; i < couts.size() ; ++i)
                                for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                                    if(couts[i][j] < 0)
                                        couts_correct = false; //Cout negatif interdit !
                        }
                    }
                    else return false; //Cout vide
                }
                return sommet_correct && couts_correct;
            }
            return false; //Graphe Vide - Fs & Aps
        }
        else
        {
            if(d_wg.verifieMatrice_NonVide())
            {
                bool sommet_correct = true;
                bool couts_correct = true;
                int n = d_wg.getMatrice()[0][0];
                int m = d_wg.getMatrice()[0][1];
                if(sommet_depart <= 0 || sommet_depart > n)
                    sommet_correct = false; //Le sommet saisi n'est pas valide !
                else
                {
                    vector<vector<int>> couts = d_wg.getCouts();
                    if(couts[0][0] != n || couts[0][1] != m)
                        couts_correct = false; //Les elements presents dans le cout ne correspondent pas avec la matrice
                    else
                    {
                        for(unsigned i = 1 ; i < couts.size() ; ++i)
                            for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                                if(couts[i][j] < 0)
                                    couts_correct = false; //Cout negatif interdit !
                    }
                }
                return sommet_correct && couts_correct;
            }
            return false; //Cout vide
        }
    }
    else return false; //Graphe Non Oriente
}
bool MainWindow::verifieDantzig()
{
    //Il faut que le graphe soit oriente.
    //Il faut que le cout soit bien initialisé ou la matrice.
    if(d_wg.getOriente())
    {
        if(d_wg.getUsingFSandAPS())
        {
            if(d_wg.verifieFS_APS_NonVide())
            {
                bool cout_correct = true;
                vector<vector<int>> couts = d_wg.getCouts();
                if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                    cout_correct = false; //Les elements presents dans le cout ne correspondent pas avec le fs et aps
                return cout_correct;
            }
            return false; //Graphe Vide - Fs & Aps
        }
        else
        {
           if(d_wg.verifieMatrice_NonVide())
           {
               bool cout_correct = true;
               int n = d_wg.getMatrice()[0][0];
               int m = d_wg.getMatrice()[0][1];
               vector<vector<int>> couts = d_wg.getCouts();
               if(couts[0][0] != n || couts[0][1] != m)
                   cout_correct = false; //Les elements presents dans le cout ne correspondent pas avec la matrice
               return cout_correct;
           }
           return false; //Graphe Vide - Matrice
        }
    }
    else return false; //Graphe Non Oriente
}

bool MainWindow::verifieKruskal()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit non oriente.
    return !d_wg.getOriente() && (d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide());
}

bool MainWindow::verifiePruferEncode()
{
    //Il faut que fs et aps soit initialisé ou la matrice ET que le graphe soit non oriente.
    return !d_wg.getOriente() && (d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide());
}

bool MainWindow::verifiePruferDecode(const vector<int>& p)
{
    bool p_correct = true;
    unsigned m = p[0];
    if(m != p.size())
        p_correct = false; //P n'est pas correctement saisi : p[0] contient le nombre total d'elements du tableau
    else
    {
        for(unsigned i = 1 ; i < m ; ++i)
            if(p[i] <= 0 || p[i] > (int)m+2)
                p_correct = false; //P n'est pas correctement saisi : un (ou plusieurs) des elements est soit negatif soit superieur a p[0] + 2
    }
    return p_correct;
}

void MainWindow::charge()
{
    //Chargement d'un widgetGraph
    //Ajouter un istream
    //d_wg.loadFrom();
}

void MainWindow::saisieMatrice()
{
    //Saisie d'un widgetGraph
    //Ajouter un ostream
    //d_wg.save();
}

void MainWindow::saisieFSAPS()
{
    //Saisie d'un widgetGraph
    //Ajouter un ostream
    //d_wg.save();
    menuFSAPS->show();
}

void MainWindow::ajoute()
{
    //Ajoute un noeud
    menuS->show();
}

void MainWindow::supprime()
{
    //Supprime un noeud
    menuSuppr->show();
}

void MainWindow::onCheck_OrienteeChange(bool estoriente)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe();
}

void MainWindow::onCheck_A_des_PoidsChange(bool a_des_poids)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe();
}

void MainWindow::onCheck_FsAps_MatAdjChange(bool fs_aps_utilise)
{
    //COMPLETER + MAJ la vue
    d_vue.metAJourGraphe();
}

void MainWindow::onClick_Distance()
{
    vector<vector<int>> mat_dist;
    if(verifieDistance())
    {
         mat_dist = d_wg.englobe_Distance();
    }
    //Mettre a jour ce qui affiche la matrice -- QMessageBox?
    /*
    for(unsigned i = 1 ; i < mat_dist.size() ; ++i)
        printVector(mat_dist[i]);
    */
}

void MainWindow::onClick_Rang()
{
    vector<int> rang;
    if(verifieRang())
    {
        rang = d_wg.englobe_Rang();
    }
    //Mettre a jour ce qui affiche le tableau de rang -- QMessageBox ?
    //printVector(rang);
}

void MainWindow::onClick_Tarjan()
{
    if(verifieTarjan())
    {
        widgetGraph wg = d_wg.englobe_Tarjan();
        //Mettre a jour la vue a partir du nouveau graphe -- A voir
        d_vue.metAJourGraphe();
    }

}

void MainWindow::onClick_Ordonnancement()
{
    menuOrd->show();
}

void MainWindow::onClick_Dijkstra()
{
    menuDijkstra->show();
}

void MainWindow::onClick_Dantzig()
{
    if(verifieDantzig())
    {
        d_wg.englobe_Dantzig();
        d_vue.metAJourGraphe();
    }
}

void MainWindow::onClick_Kruskal()
{
    if(verifieKruskal())
    {
        d_wg.englobe_Kruskal();
        d_vue.metAJourGraphe();
    }
}

void MainWindow::onClick_Prufer_encode()
{
    if(verifiePruferEncode())
    {
        vector<int> p = d_wg.englobe_Prufer_encode();
    }
}

void MainWindow::onClick_Prufer_decode()
{
    menuPruferD->show();
}

void MainWindow::onClickDistance_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner l'ensemble des distances separant chaque sommet du graphe de l'ensemble des autres.\n"
                    "Il sert notamment des les problèmes de réseaux ou de trajet lorsq'un arc ne possède pas de poids.\n"
                    "Son resultat est donne sous la forme d'une matrice appelee matrice des distances.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme des distances",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickRang_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le rang de chaque sommet du graphe.\n"
                    "Le rang d'un sommet est la longueur d'une plus long chemin arrivant à lui.\n"
                    "On suppose que si le graphe admet un circuit alors les sommets concernes auront un rang egal a -1.\n"
                    "Il sert dans le domaine mathematique afin de determiner par exemple la dimension d'un graphe.\n"
                    "Son resultat est donne sous la forme d'un tableau contenant le rang de chaque sommet.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme du rang",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickTarjan_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le graphe reduit du graphe courant.\n"
                    "Le graphe reduit est sans circuit et ses sommets correspondent aux composantes fortement connexes du graphe.\n"
                    "Il est utilise pour simplifier des graphes complexes par exemple.\n"
                    "Son resultat est donne sous la forme d'un nouveau graphe (le graphe reduit).\n"
                    "De plus, les bases des deux graphes seront aussi indiquees.\n"
                    "Pour rappel, la base d'un graphe est l'ensemble des sommets necessaires pour qu'a partir de ce dernier, on puisse atteindre n'importe quel sommet.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Tarjan",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickOrdonnancement_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner l'ensemble des dates au plus tot et date au plus tard afin d'en deduire un (des) chemin(s) critique(s).\n"
                    "Un chemin critique est un chemin du graphe composes de sommets dont les durees de realisation ne peuvent etre retardees.\n"
                    "Il est notamment utilise dans les gestion de planification de taches afin d'etablir le meilleur planning possible.\n"
                    "Son resultat est donne sous la forme d'un nouveau graphe compose des sommets critiques et du(des) chemin(s) critique(s).\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : L'ordonnancement",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickDijkstra_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le(s) chemin(s) le(s) plus court(s) d'un graphe a partir d'un sommet de depart donne.\n"
                    "Il est utilise, comme la distance, pour determiner le plus court chemin entre deux points (villes, réseau, ...) mais en tenant compte des poids des arcs.\n"
                    "Son resultat est donne sous la forme de deux tableaux representant respectivement le poids minimal du chemin (d) et le chemin (pr).\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Dijkstra",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickDantzig_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner la matrice de cout la plus optimale possible en tenant compte des raccourcis proposes par le graphe compte tenu de ses poids.\n"
                    "Son resultat est donne sous la forme d'une matrice appellee matrice des couts.\n"
                    "Il est utilise, comme la distance, pour determiner le plus court chemin entre deux points (villes, réseau, ...) mais en tenant compte des poids des arcs.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Dantzig",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickKruskal_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner un arbre recouvrant minimal d'un graphe non oriente.\n"
                    "Il est par exemple utilise pour simplifier des cablages.\n"
                    "Son resultat est donne sous la forme d'un nouveau graphe.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Kruskal",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickPrufer_encode_INFO()
{
    QString texte = "Cet algorithme a pour but de coder un graphe donne sous la forme d'un tableau de Prufer.\n"
                    "Il peut etre utile pour representer n'importe quel probleme sous forme d'un tableau d'entier unique.\n"
                    "Son resultat est donne sous la forme d'un tableau d'entier.\n"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Prufer [encodage]",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onClickPrufer_decode_INFO()
{
    QString texte = "Cet algorithme a pour but de decoder un tableau de Prufer en graphe.\n"
                    "Son resultat est donne sous la forme d'un graphe.\n"
                    "La complexite de cet algorithme est en O( .. ).";
    auto info = new QMessageBox{QMessageBox::Information,"Information : Algorithme de Prufer [decodage]",texte,QMessageBox::Close};
    info->exec();
}

void MainWindow::onValiderAjout()
{
    /*cout<<"ID : "<<menuS->getId()<<endl;
    cout<<"Poids : "<<menuS->getPoids()<<endl;
    cout<<"Suc : ";
    printVector(menuS->getSuc());
    cout<<"Pred : ";
    printVector(menuS->getPred());*/

    vector<int> Pred;
    vector<int> Suc;

    vector<int> menuPred = menuS->getPred();
    vector<int> menuSuc = menuS->getSuc();

    int k1 = 1;
    int k2 = 1;


    int nbNoeud = d_wg.getAps()[0] + 2;

    for(int i = 0; i < nbNoeud; i++)
    {
        if(menuPred[k1] == i)
        {
            Pred.push_back(1);
            k1++;
        }
        else
            Pred.push_back(0);
        if(menuSuc[k2] == i)
        {
             Suc.push_back(1);
             k2++;
        }
        else
            Suc.push_back(0);
    }

    Noeud n{d_wg.getAps()[0] + 1};
    d_wg.ajouterNoeud(n, Pred, Suc);
}

void MainWindow::onValiderPruferDecode()
{
    if(verifiePruferDecode(menuPruferD->getP()))
    {
        widgetGraph wg = d_wg.englobe_Prufer_decode(menuPruferD->getP());
        d_vue.metAJourGraphe();
    }
}

void MainWindow::onValiderDijkstra()
{
    vector<int> d, pr;
    if(verifieDijkstra(menuDijkstra->getSommet()))
    {
        d_wg.englobe_Dijkstra(menuDijkstra->getSommet(),d,pr);
    }
    cout<<"Affichage de d : "<<endl;
    printVector(d);
    cout<<endl;
    cout<<"Affichage de pr : "<<endl;
    printVector(pr);
    cout<<endl;
}

void MainWindow::onValiderOrdonnancement()
{
    if(verifieOrdonnancement(menuOrd->getDuree(),menuOrd->getFs(),menuOrd->getAps()))
    {
        widgetGraph wg = d_wg.englobe_Ordonnancement(menuOrd->getDuree(),menuOrd->getFs(),menuOrd->getAps());
        d_vue.metAJourGraphe();
    }
}

void MainWindow::onValideSaisieFSAPS()
{
    //A faire quand on pourra charger des graphes
    vector<int> FS = menuFSAPS->getFS();
    vector<int> APS = menuFSAPS->getAPS();
    Graph g{FS, APS};
    if(menuFSAPS->getCheck())
    {
        vector<vector<int>> cout = menuFSAPS->getCout();
        g.setCout(cout);
    }
    d_wg.loadGraph(g);
}


