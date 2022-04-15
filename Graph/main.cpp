#include "mainwindow.h"
#include <QApplication>

#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Graph g = new Graph();
    MainWindow w{g};
    w.show();

    //int exe = a.exec();
    int exe = 0;

    test(); // Pour lancer les tests

    return exe;
}

