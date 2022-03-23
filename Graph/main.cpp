#include "mainwindow.h"
#include "algorithms.h"
#include "graph.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int exe = a.exec();

    // FS-APS et matAdj correspondent
    vector<int> FS {22, 2, 7 , 0, 3, 5, 0, 4, 0, 6, 0, 0, 2, 5, 7, 0, 0, 9, 0, 10, 0, 8, 9, 0};
    vector<int> APS {10, 1, 4, 7, 9, 11, 12, 16, 17, 19, 21};
    vector<vector<int>> matAdj {
        {10, 12},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        {0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0},
    };

    rangToString(FS, APS);

    Graph g = Graph(FS, APS, vector<Noeud>(), true, false);

    return exe;
}
