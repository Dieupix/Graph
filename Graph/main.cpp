#include "mainwindow.h"
#include <QApplication>

#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    const vector<int> fs {6, 2, 3, 0, 3, 0, 0};
    const vector<int> aps {3, 1, 4, 6};
    Graph g(fs,aps);
    MainWindow w{nullptr,g};
    w.show();

    int exe = a.exec();

    //test(); // Pour lancer les tests

    return exe;
}

