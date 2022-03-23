#include "mainwindow.h"
#include "algorithms.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    int exe = a.exec();

    vector<int> FS {2,7,0,3,5,0,4,0,6,0,0,2,5,7,0,0,9,0,10,0,8,9};
    vector<int> APS {1, 4, 7, 9, 11, 12, 16, 17, 19, 21};
    rangToString(FS, APS);

    return exe;
}
