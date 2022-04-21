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

    int exe = a.exec();

    //test(); // Pour lancer les tests

    return exe;
}

