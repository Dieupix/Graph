#ifndef MENUPRUFERDECODE_H
#define MENUPRUFERDECODE_H

#include "vue.h"
#include <QLabel>
#include <QMainWindow>

class menuPruferDecode : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuPruferDecode(QWidget *parent = nullptr);

signals:

private:
    QLabel *lbl1;
    vue d_vue;
    vector<int> d_p;
};

#endif // MENUPRUFERDECODE_H
