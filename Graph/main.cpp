#include "mainwindow.h"
#include <QApplication>

#include "algorithms.h"
#include "graph.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int exe = a.exec();

    // FS-APS et matAdj correspondent
    vector<int> FS {23, 2, 7 , 0, 3, 5, 0, 4, 0, 6, 0, 0, 2, 5, 7, 0, 9, 0, 9, 0, 10, 0, 8, 9, 0};
    vector<int> APS {10, 1, 4, 7, 9, 11, 12, 16, 18, 20, 22};
    vector<vector<int>> matAdj {
        {10, 12},
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
        vector<vector<int>> matriceDistance(APS[0]+1);
        for(int i = 0 ; i <= APS[0] ; ++i)
            matriceDistance[i].resize(APS[0]+1);

        for(unsigned i = 1 ; i < matriceDistance.size() ; ++i)
        {
            for(unsigned j = 1 ; j < matriceDistance[i].size() ; ++j)
                matriceDistance[i][j] = 0;
        }
    //FIN

    Mat_distance(FS,APS,matriceDistance);


// TEST distance -- Affichage OK
    for(unsigned i = 0 ; i < matriceDistance.size() ; ++i)
    {
        cout<<"LIGNE "<<i<<"   ";
        for(unsigned j = 0 ; j < matriceDistance[i].size() ; ++j)
            cout<<matriceDistance[i][j]<<" ";
        cout<<endl;
    }

    return exe;
}
