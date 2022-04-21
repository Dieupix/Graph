#ifndef APPLICATION_H
#define APPLICATION_H

#include "graph.h"

class application
{
public:
    application();
    void load();
    void FSandAPS();
    void matrice();
    void fichier();
private:
    Graph d_graphe;
};

#endif // APPLICATION_H
