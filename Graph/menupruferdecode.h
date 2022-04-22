#ifndef MENUPRUFERDECODE_H
#define MENUPRUFERDECODE_H

#include "vue.h"
#include <QLabel>
#include <QMainWindow>

class menuPruferDecode : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuPruferDecode(QMainWindow *parent = nullptr);

    vector<int> getP();

private:
    vue d_vue;
    vector<int> d_p;
};

#endif // MENUPRUFERDECODE_H
