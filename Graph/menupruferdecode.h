#ifndef MENUPRUFERDECODE_H
#define MENUPRUFERDECODE_H

#include "vue.h"

class menuPruferDecode : public QMainWindow
{
    Q_OBJECT
public:
    explicit menuPruferDecode(QMainWindow *parent = nullptr);

    vector<int> getP();

signals :
    void valide();

private slots :
<<<<<<< HEAD
    void onClick_valider();
=======
    void onValide();

>>>>>>> 16369c14ef7cdf176108feafdbe3f420a8a2dd3b
private:
    vue d_vue;
    vector<int> d_p;
};

#endif // MENUPRUFERDECODE_H
