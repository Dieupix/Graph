#include "graph.h"

// ---------- Private functions ----------
// ---------- End of private functions ----------



// ---------- Constructors ----------
Graph::Graph() : est_oriente{false}, a_des_poids{false}
{}

Graph::Graph(bool est_oriente, bool a_des_poids) : est_oriente{est_oriente}, a_des_poids{a_des_poids}
{}

Graph::Graph(const vector<int>& FS, const vector<int>& APS, const vector<Noeud>& sommets, bool est_oriente, bool a_des_poids) :
    FS{FS}, APS{APS}, sommets{sommets}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
{} ///@todo vérifier l'intégrité des sommets

Graph::Graph(const vector<vector<int>>& matAdj, const vector<Noeud>& sommets, bool est_oriente, bool a_des_poids) :
    matAdj{matAdj}, sommets{sommets}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
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



// ---------- Public functions ----------
void Graph::FS_APS_to_MatAdj(vector<vector<int>> &matAdj) const
{
    unsigned size = APS[0];
    matAdj.clear();
    matAdj.resize(size + 1);
    matAdj[0].resize(2);
    matAdj[0][0] = size;
    matAdj[0][1] = FS[0] - size;

    for(unsigned i = 1; i < APS.size(); ++i)
    {
        matAdj[i].resize(size + 1, 0);

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
    unsigned size = matAdj[0][0];

    APS.resize(size + 1, 0);
    FS.resize(size + matAdj[0][1] + 1, 0);

    APS[0] = size;
    FS[0] = FS.size();

    unsigned k = 1;

    for(unsigned i = 1; i <= size; ++i)
    {
        APS[i] = k;
        for(unsigned j = 1; j <= size; ++j)
        {
            if(matAdj[i][j] != 0)
            {
                FS[k] = j + 1;
                ++k;
            }
        }
        ++k;
    }
}

void Graph::print(std::ostream& ost) const
{
    ost << toString();
}

string Graph::toString() const
{
    string str = "";
    if(matAdj.size() != 0)
    {
        unsigned i = 0, j = 0;
        str.append("MatAdj:[{");
        for(i = 1; i < matAdj.size() - 1; ++i)
        {
            for(j = 1; j < matAdj[i].size() - 1; ++j)
            {
                str += matAdj[i][j];
                str.append(", ");
            }
            str += matAdj[i][j];
            str.append("}, {");
        }
        for(j = 1; j < matAdj[i].size() - 1; ++j)
        {
            str += matAdj[i][j];
            str.append(", ");
        }
        str += matAdj[i][j];
        str.append("}]");

    }else
    {
        str.append("FS:{");
        unsigned i = 0;
        for(i = 0; i < FS.size() - 1; ++i)
        {
            str += FS[i];
            str.append(", ");
        }
        str += FS[i];
        str.append("}, APS;{");

        for(i = 0; i < APS.size() - 1; ++i)
        {
            str += APS[i];
            str.append(", ");
        }
        str += APS[i];
        str.append("}");
    }

    return str;
}
// ---------- End of public funtions ----------



// ---------- Global functions ----------
std::ostream& operator<<(std::ostream& ost, const Graph g)
{
    g.print(ost);
    return ost;
}
// ---------- End of global functions ----------
