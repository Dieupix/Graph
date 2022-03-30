#include "mainwindow.h"
#include <QApplication>

#include "algorithms.h"
#include "graph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    //int exe = a.exec();
    int exe = 0;

    // FS-APS et matAdj correspondent
    vector<int> FS {24, 2, 7, 0, 3, 5, 0, 4, 0, 6, 0, 0, 2, 5, 7, 0, 9, 0, 9, 0, 10, 0, 8, 9, 0};
    vector<int> APS {10, 1, 4, 7, 9, 11, 12, 16, 18, 20, 22};
    vector<vector<int>> matAdj {
        {12, 19},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    };

    rangToString(FS, APS);

    //INITIALISATION DE LA MATRICE DES DISTANCES
        vector<vector<int>> matriceDistance(APS[0]+1, vector<int>(APS[0]+1, 0));
    //FIN

    mat_distance(FS,APS,matriceDistance);


// TEST distance -- Affichage OK
    for(unsigned i = 0 ; i < matriceDistance.size() ; ++i)
    {
        cout<<"LIGNE "<<i<<"\t";
        for(auto j : matriceDistance[i]) cout << j << " ";
        cout<<endl;
    }

    // TEST TARJAN
    // Tarjan(FS, APS);
    // FIN TARJAN

    return exe;
}
