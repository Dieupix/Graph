#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QObject>
#include<QWidget>
#include "graph.h"
#include "vue.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(const Graph& g, QWidget* parent = nullptr);

private:
    Graph d_g;
    vue d_vue;

private slots :
    void onCheck_OrienteeChange(bool estoriente);
    void onCheck_A_des_PoidsChange(bool a_des_poids);
    void onCheck_FsAps_MatAdjChange(bool fs_aps_utilise);
};

#endif // MAINWINDOW_H
