#include "mainwindow.h"
#include <QApplication>

#include "test.h"

int main(int argc, char *argv[])
{
    /*QApplication a(argc, argv);
    MainWindow w;
    w.show();*/

    //int exe = a.exec();
    int exe = 0;

    test(); // Pour lancer les tests

    return exe;
}
