#include "mainwindow.h"
#include <QApplication>

#include "test.h"
#include "algorithms.h"
#include "graphwidget.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w{};
    w.show();
    //GraphWidget gw;
    //gw.show();
    vector<int> APS{6, 1, 5, 7, 10, 13, 16};
    vector<int> FS{18, 2, 3, 5, 0, 1, 0, 2, 5, 0, 3, 5, 0, 2, 6, 0, 1, 2, 0};
    vector<vector<int>> cout
    {
        {6,12},
        {0,-1,10,3,-1,6,-1},
        {0,0,-1,-1,-1,-1,-1},
        {0,-1,4,-1,2,-1,-1},
        {0,-1,-1,1,-1,3,-1},
        {0,-1,-1,-1,-1,-1,1},
        {0,2,1,-1,2,-1,-1},
    };
    vector<int> d;
    vector<int> pr;
    Dikjstra(FS, APS, cout, 1, d, pr);
    int exe = a.exec();

    //test(); // Pour lancer les tests

    return exe;
}

