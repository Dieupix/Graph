#include "graph.h"

// ---------- Private functions ----------
// ---------- End of private functions ----------



// ---------- Constructors ----------
Graph::Graph() : est_oriente{false}, a_des_poids{false}
{}

Graph::Graph(bool est_oriente, bool a_des_poids) : est_oriente{est_oriente}, a_des_poids{a_des_poids}
{}

Graph::Graph(vector<int> FS, vector<int> APS, bool est_oriente, bool a_des_poids) : FS{FS}, APS{APS}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
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
    return FS;
}

vector<int> Graph::getAPS() const
{
    return APS;
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
void Graph::FS_APS_to_MatAdj(vector<vector<int>> &matAdj) const
{
    unsigned size = APS[0];
    matAdj.resize(size+1);
    matAdj[0].resize(size+1, 0);
    matAdj[0][0] = size;
    matAdj[0][1] = FS[0] - size;

    for(unsigned i = 1; i < APS.size(); ++i)
    {
        matAdj[i].resize(size+1, 0);

        unsigned j = APS[i];
        unsigned k = FS[j];

        while(k != 0)
        {
            matAdj[i][k] = 1;
            ++j;
            k = FS[j];
        }
    }
}

void Graph::matAdj_to_FS_APS(vector<int> &FS, vector<int> &APS) const
{
    //@TODO - to be fixed
    unsigned size = matAdj[0][0];

    APS.resize(size + 1, 0);
    FS.resize(size + matAdj[0][1], 0);

    for(unsigned i = 1; i < matAdj.size(); ++i)
    {
        for(unsigned j = 1; j < matAdj[i].size(); ++j)
        {
            if(matAdj[i][j] != 0)
            {
                FS.push_back(j+1);
            }
        }
        FS.push_back(0);
    }
    FS[0] = (unsigned) FS.size()-1;
}

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
