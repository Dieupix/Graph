#include "mainwindow.h"
#include<iostream>
#include<QMessageBox>

MainWindow::MainWindow(QMainWindow* parent) : QMainWindow{parent}, d_wg{new widgetGraph()}, d_vue{this}, menuPruferD{new menuPruferDecode}, menuDijkstra{new menudijkstra}, menuOrd{new menuOrdonnancement}, menuS{new menuAjout}, menuSuppr{new menuSupprimer}
{
    d_vue.creeInterface(d_wg);
    d_vue.metAJourGraphe();

    connect(&d_vue, &vue::OrienteeChange, this, &MainWindow::onCheck_OrienteeChange);
    connect(&d_vue, &vue::A_des_PoidsChange, this, &MainWindow::onCheck_A_des_PoidsChange);
    connect(&d_vue, &vue::FsAps_MatAdjChange, this, &MainWindow::onCheck_FsAps_MatAdjChange);

    connect(&d_vue, &vue::Quitter, this, &MainWindow::close);
    connect(&d_vue, &vue::Charger, this, &MainWindow::charge);
    connect(&d_vue, &vue::Saisie, this, &MainWindow::saisie);
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
    //Il faut que fs et aps soit initialisé ou la matrice.
    return d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide();
}

bool MainWindow::verifieRang()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide();
}
bool MainWindow::verifieTarjan()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide();
}
bool MainWindow::verifieOrdonnancement(const vector<int>& duree_taches)
{
    //Il faut que fs et aps soit initialisé.
    //Il faut que duree_taches soit correctement initisalisé et saisie
    if(d_wg.getUsingFSandAPS())
    {
        if(d_wg.verifieFS_APS_NonVide())
        {
            int n = d_wg.getAps()[0];
            return (duree_taches[0] != n);
        }
        return false;
    }
    else
    {
        if(d_wg.verifieMatrice_NonVide())
        {
            int n = d_wg.getMatrice()[0][0];
            return(duree_taches[0] != n);
        }
        return false;
    }
}
bool MainWindow::verifieDijkstra(int sommet_depart)
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    //Il faut que le cout soit correct, qu'il ne contienne pas de cout < 0
    if(d_wg.getUsingFSandAPS())
    {
        if(d_wg.verifieFS_APS_NonVide())
        {
            bool sommet_correct = true;
            bool couts_correct = true;
            if(sommet_depart <= 0 || sommet_depart > d_wg.getAps()[0])
                sommet_correct = false;
            else
            {
                vector<vector<int>> couts = d_wg.getCouts();
                if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                    couts_correct = false;
                else
                {
                    for(unsigned i = 1 ; i < couts.size() ; ++i)
                        for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                            if(couts[i][j] < 0)
                                couts_correct = false;
                }
            }
            return sommet_correct && couts_correct;
        }
        return false;
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
                sommet_correct = false;
            else
            {
                vector<vector<int>> couts = d_wg.getCouts();
                if(couts[0][0] != n || couts[0][1] != m)
                    couts_correct = false;
                else
                {
                    for(unsigned i = 1 ; i < couts.size() ; ++i)
                        for(unsigned j = 1 ; j < couts[i].size() ; ++j)
                            if(couts[i][j] < 0)
                                couts_correct = false;
                }
            }
            return sommet_correct && couts_correct;
        }
        return false;
    }


}
bool MainWindow::verifieDantzig()
{
    //Il faut que le cout soit bien initialisé ou la matrice.
    if(d_wg.getUsingFSandAPS())
    {
        if(d_wg.verifieFS_APS_NonVide())
        {
            bool cout_correct = true;
            vector<vector<int>> couts = d_wg.getCouts();
            if(couts[0][0] != d_wg.getAps()[0] || couts[0][1] != (d_wg.getFs()[0] - d_wg.getAps()[0]))
                cout_correct = false;
            return cout_correct;
        }
        return false;
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
               cout_correct = false;
           return cout_correct;
       }
       return false;
    }
}
bool MainWindow::verifieKruskal()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide();
}
bool MainWindow::verifiePruferEncode()
{
    //Il faut que fs et aps soit initialisé ou la matrice.
    return d_wg.verifieFS_APS_NonVide() || d_wg.verifieMatrice_NonVide();
}
bool MainWindow::verifiePruferDecode(const vector<int>& p)
{
    bool p_correct = true;
    unsigned m = p[0];
    if(m != p.size())
        p_correct = false;
    else
    {
        for(unsigned i = 1 ; i < m ; ++i)
            if(p[i] <= 0 || p[i] > (int)m+2)
                p_correct = false;
    }
    return p_correct;
}

void MainWindow::charge()
{
    //Chargement d'un widgetGraph
    //Ajouter un istream
    //d_wg.loadFrom();
}

void MainWindow::saisie()
{
    //Saisie d'un widgetGraph
    //Ajouter un ostream
    //d_wg.save();



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
    if(verifieDistance())
    {
        vector<vector<int>> mat_dist = d_wg.englobe_Distance();
    }//retourner la matrice
}

void MainWindow::onClick_Rang()
{
    if(verifieRang())
    {
        vector<int> rang = d_wg.englobe_Rang();
    }//retourner le rang
}

void MainWindow::onClick_Tarjan()
{
    if(verifieTarjan())
    {
        widgetGraph wg = d_wg.englobe_Tarjan();
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
    QString texte = "Cet algorithme a pour but de determiner l'ensemble des distances separant chaque sommet du graphe de l'ensemble des autres."
                    "Son resultat est donne sous la forme d'une matrice appellee matrice des distances."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme des distances");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickRang_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le rang de chaque sommet du graphe."
                    "Le rang d'un sommet est la longueur d'une plus long chemin arrivant à lui."
                    "On suppose que si le graphe admet un circuit alors les sommets concernes auront un rang egal a -1."
                    "Son resultat est donne sous la forme d'un tableau contenant le rang de chaque sommet."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme du rang");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickTarjan_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le graphe reduit du graphe courant."
                    "Le graphe reduit est sans circuit et ses sommets correspondent aux composantes fortement connexes du graphe."
                    "Son resultat est donne sous la forme d'un nouveau graphe (le graphe reduit)."
                    "De plus, les bases des deux graphes seront aussi indiquees."
                    "Pour rappel, la base d'un graphe est l'ensemble des sommets necessaires pour qu'a partir de ce dernier, on puisse atteindre n'importe quel sommet"
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme de Tarjan");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickOrdonnancement_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner l'ensemble des dates au plus tot et date au plus tard afin d'en deduire un (des) chemin(s) critique(s)."
                    "Un chemin critique est un chemin du graphe composes de sommets dont les durees de realisation ne peuvent etre retardees."
                    "Son resultat est donne sous la forme d'un nouveau graphe compose des sommets critiques et du(des) chemin(s) critique(s)."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : L'ordonnancement");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickDijkstra_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner le(s) chemin(s) le(s) plus court(s) d'un graphe a partir d'un sommet de depart donne."
                    "Son resultat est donne sous la forme de deux tableaux representant respectivement le poids minimal du chemin (d) et le chemin (pr)."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme de Dijkstra");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickDantzig_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner la matrice de cout la plus optimale possible en tenant compte des raccourcis proposes par le graphe compte tenu de ses poids."
                    "Son resultat est donne sous la forme d'une matrice appellee matrice des couts."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme de Dantzig");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickKruskal_INFO()
{
    QString texte = "Cet algorithme a pour but de determiner un arbre recouvrant minimal d'un graphe non oriente."
                    "Son resultat est donne sous la forme d'un nouveau graphe."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme de Kruskal");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickPrufer_encode_INFO()
{
    QString texte = "Cet algorithme a pour but de coder un graphe donne sous la forme d'un tableau de Prufer."
                    "Son resultat est donne sous la forme d'un tableau."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme de Prufer [encodage]");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
    info->exec();
}
void MainWindow::onClickPrufer_decode_INFO()
{
    QString texte = "Cet algorithme a pour but de decoder un tableau de Prufer en graphe."
                    "Son resultat est donne sous la forme d'un graphe."
                    "La complexite de cet algorithme est en O( .. )";
    auto info = new QMessageBox{};
    info->setWindowTitle("Information : Algorithme de Prufer [decodage]");
    info->setText(texte);
    info->setIcon(QMessageBox::Information);
    info->setStandardButtons(QMessageBox::Close);
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


    int nbNoeud = 6;//d_wg.getAps()[0] + 2;

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

    printVector(menuPred);
    printVector(Suc);
    printVector(Pred);

    Noeud n{menuS->getId()};
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
    if(verifieOrdonnancement(menuOrd->getDuree()))
    {
        widgetGraph wg = d_wg.englobe_Ordonnancement(menuOrd->getDuree());
        d_vue.metAJourGraphe();
    }
}




