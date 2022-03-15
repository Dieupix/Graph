#include "graph.h"

// ---------- Constructors ----------
Graph::Graph() : est_oriente{false}, a_des_poids{false}
{}

Graph::Graph(bool est_oriente, bool a_des_poids) : est_oriente{est_oriente}, a_des_poids{a_des_poids}
{}

Graph::Graph(vector<int> fs, vector<int> aps, bool est_oriente, bool a_des_poids) : fs{fs}, aps{aps}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
{}

Graph::Graph(vector<vector<int>> matAdj, bool est_oriente, bool a_des_poids) : matAdj{matAdj}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
{}
// ---------- End of constructeurs ----------



// ---------- Destructor ----------
// ---------- End of destructor ----------



// ---------- Overloads ----------
// ---------- End of overloads ----------



// ---------- Getters ----------
bool Graph::getEst_oriente() const
{
    return est_oriente;
}

bool Graph::getA_Des_Poids() const
{
    return a_des_poids;
}

vector<int> Graph::getFS() const
{
    return fs;
}

vector<int> Graph::getAPS() const
{
    return aps;
}

vector<vector<int>> Graph::getMatAdj() const
{
    return matAdj;
}

vector<Noeud> Graph::getSommets() const
{
    return sommets;
}
// ---------- End of getters ----------



// ---------- Setters ----------
// ---------- End of setters ----------



// ---------- Functions ----------
void Graph::print(std::ostream& ost) const
{
    ost << toString();
}

string Graph::toString() const
{
    //@TODO To be implemented
    return "";
}
// ---------- End of funtions ----------



// ---------- Global functions ----------
std::ostream& operator<<(std::ostream& ost, const Graph g)
{
    g.print(ost);
    return ost;
}
// ---------- End of global functions ----------
