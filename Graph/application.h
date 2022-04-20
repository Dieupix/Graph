#ifndef APPLICATION_H
#define APPLICATION_H
#include <iostream>
#include <vector>
#include "graph.h"

class application
{
public:
    application();
    void load();
    void FSandAPS();
    void matrice();
private:
    Graph d_graphe;
};

#endif // APPLICATION_H
