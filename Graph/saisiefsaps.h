#ifndef SAISIEFSAPS_H
#define SAISIEFSAPS_H

#include <QMainWindow>
#include "vue.h"

class saisieFSAPS : public QMainWindow
{
    Q_OBJECT
public:
    explicit saisieFSAPS(QWidget *parent = nullptr);

signals:
private:
    vue d_vue;
};

#endif // SAISIEFSAPS_H
