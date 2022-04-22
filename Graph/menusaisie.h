#ifndef MENUSAISIE_H
#define MENUSAISIE_H

#include "vue.h"
#include <QLabel>
#include <QMainWindow>

class menuSaisie : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuSaisie(QWidget *parent = nullptr);

signals:

private:
    QLabel *lbl1;
    vue d_vue;

};

#endif // MENUSAISIE_H
