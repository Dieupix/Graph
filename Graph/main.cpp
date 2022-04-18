#include "mainwindow.h"
#include <QApplication>

#include "test.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    widgetGraph g = new widgetGraph();
    MainWindow w{g};
    w.show();



    int exe = a.exec();

    //test(); // Pour lancer les tests

    return exe;
}

