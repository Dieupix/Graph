#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include<QWidget>
#include "widgetgraph.h"
#include "vue.h"

class MainWindow : public QWidget
{
    Q_OBJECT
public:
    MainWindow(QWidget* parent = nullptr);
    MainWindow(QWidget* parent = nullptr, const Graph& g = new Graph());
private:
    widgetGraph d_g;
    vue d_vue;

private slots :
    void onCheck_OrienteeChange(bool estoriente);
    void onCheck_A_des_PoidsChange(bool a_des_poids);
    void onCheck_FsAps_MatAdjChange(bool fs_aps_utilise);
};

#endif // MAINWINDOW_H
