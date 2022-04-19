#include "graph.h"

// ---------- Private functions ----------
void Graph::initialiserSommets(unsigned size)
{
    /* L'indice du tableau représente le numéro du sommet */
    sommets.resize(size + 1);
    for(unsigned i = 0; i < sommets.size(); ++i)
    {
        sommets[i] = make_unique<Noeud>(i);
    }
}

void Graph::verifIntegritee()
{
    /* Sommet est initalisé avec au moins 1 élément */
    if(sommets.size() < 2) throw PasAssezDeSommetsException("ERREUR: Graph: Un graphe doit posseder au moins un sommet");
    if(!verifIntegriteeSommets()) throw SommetsNonReliesException("ERREUR: Graph: Au moins l'un des sommets du graphe n'est pas relie");
}

bool Graph::verifIntegriteeSommets()
{
    if(usingFsAndAps) return verifIntegriteeSommets_FS_APS();
    else return verifIntegriteeSommets_MatAdj();
}

bool Graph::verifIntegriteeSommets_FS_APS()
{
    bool verif = true;
    int nbSommets = APS[0];
    vector<bool> integritee(nbSommets + 1, false);

    for(unsigned i = 0; i < FS.size(); ++i)
    {
        integritee[FS[i]] = true;
    }

    for(unsigned i = 1; i < APS.size(); ++i)
    {
        if(!integritee[i])
        {
            integritee[i] = FS[APS[i]] == 0 ? false : true;
        }
    }

    unsigned k = 1;
    while(k < integritee.size() and verif)
    {
        if(!integritee[k]) verif = false;
        ++k;
    }

    return verif;
}

bool Graph::verifIntegriteeSommets_MatAdj()
{
    int nbSommets = matAdj[0][0];
    vector<bool> integritee(nbSommets + 1, false);

    for(unsigned i = 1; i < matAdj.size(); ++i)
    {
        unsigned j = 1;
        bool verif = false;
        while(j < matAdj[i].size() and !verif)
        {
            if(matAdj[i][j] != 0) verif = true;
            ++j;
        }
    }

    for(unsigned i = 1; i < integritee.size(); ++i)
    {
        if(!integritee[i])
        {
            unsigned j = 1;
            bool verif = false;
            while(j < matAdj.size() and !verif)
            {
                if(matAdj[j][i] != 0) verif = true;
                ++j;
            }
            if(!verif) return false;
        }
    }

    return true;
}
// ---------- End of private functions ----------



// ---------- Constructors ----------
Graph::Graph(bool est_oriente) : FS{1, 0}, APS{1, 1}, usingFsAndAps{true}, est_oriente{est_oriente}
{}

Graph::Graph(const vector<int>& FS, const vector<int>& APS) : FS{FS}, APS{APS}, usingFsAndAps{true}, est_oriente{false}
{
    initialiserSommets(APS[0]);
    verifIntegritee();
}

Graph::Graph(const vector<vector<int>>& matAdj, bool est_oriente) : matAdj{matAdj}, usingFsAndAps{false}, est_oriente{est_oriente}
{
    initialiserSommets(matAdj[0][0]);
    verifIntegritee();
}

Graph::Graph(const vector<int>& FS, const vector<int>& APS, const vector<int>& couts) : FS{FS}, APS{APS},
    usingFsAndAps{true}, couts{couts}, est_oriente{false}
{
    initialiserSommets(APS[0]);
    verifIntegritee();
}

Graph::Graph(const vector<vector<int>>& matAdj, const vector<int>& couts, bool est_oriente) : matAdj{matAdj},
    usingFsAndAps{false}, couts{couts}, est_oriente{est_oriente}
{
    initialiserSommets(matAdj[0][0]);
    verifIntegritee();
}

Graph::Graph(const Graph& g) : usingFsAndAps{g.usingFsAndAps}, est_oriente{g.est_oriente}, a_des_poids{g.a_des_poids}
{
    if(usingFsAndAps)
    {
        FS = g.getFS();
        APS = g.getAPS();
    }
    else
    {
        matAdj = g.getMatAdj();
    }

    if(a_des_poids)
    {
        couts = g.couts;
    }

    sommets.resize(g.getSommets().size());
    for(unsigned i = 0; i < sommets.size(); ++i)
    {
        sommets[i] = make_unique<Noeud>(*g.getSommets()[i]);
    }
}

Graph::Graph(const vector<int>& fs, const vector<int>& aps, const vector<unique_ptr<Noeud>>& sommets, bool est_oriente, bool a_des_poids)
    : FS{fs}, APS{aps}, usingFsAndAps{true}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
{
    initialiserSommets(sommets.size());
    for(unsigned i = 0; i < this->sommets.size(); ++i)
    {
        *this->sommets[i] = *sommets[i];
    }
}

Graph::Graph(const vector<vector<int>>& matAdj, const vector<unique_ptr<Noeud>>& sommets, bool est_oriente, bool a_des_poids)
    : matAdj{matAdj}, usingFsAndAps{false}, est_oriente{est_oriente}, a_des_poids{a_des_poids}
{
    initialiserSommets(sommets.size());
    for(unsigned i = 0; i < this->sommets.size(); ++i)
    {
        *this->sommets[i] = *sommets[i];
    }
}
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

bool Graph::isUsingFsAndAps() const
{
    return usingFsAndAps;
}

const vector<unique_ptr<Noeud>>& Graph::getSommets() const
{
    return sommets;
}
// ---------- End of getters ----------



// ---------- Setters ----------
// ---------- End of setters ----------



// ---------- Public functions ----------
void Graph::ajouterNoeud(unique_ptr<Noeud>& noeud, const vector<int>& pred, const vector<int>& succ)
{
    ///@todo - Alex : to be implemented

    int id = noeud->getId();
    if(usingFsAndAps)
    {
        unsigned i = 1;
        for(auto ite = FS.begin()+1; ite < FS.end(); ++ite)
        {
            if(*ite == 0)
            {
                if(pred[i])
                {
                    ite = FS.insert(ite, id) + 1;
                    for(unsigned tmp = i+1; tmp < APS.size(); ++tmp) ++APS[tmp];
                }
                ++i;
            }
        }

        for(i = 1; i < succ.size(); ++i)
        {
            if(succ[i]) FS.push_back(i);
        }
        FS.push_back(0);
        FS[0] = FS.size() - 1;

        i = FS.size()-2;
        while(FS[i] != 0)
        {
            --i;
        }

        APS.push_back(i+1);
        ++APS[0];
    }
    else
    {
        unsigned n = matAdj.size();
        unsigned nbArcs = 0;
        matAdj.resize(n+1);
        for(unsigned i = 1; i < n; ++i)
        {
            matAdj[i].resize(n+1, 0);
            if(pred[i])
            {
                matAdj[i][id] = 1;
                ++nbArcs;
            }
            if(succ[i])
            {
                matAdj[id][i] = 1;
                ++nbArcs;
            }
        }

        ++matAdj[0][0];
        matAdj[0][1] += nbArcs;

    }

    sommets.push_back(move(noeud));
}

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

bool Graph::loadFrom(std::istream& ist)
{
    ///@todo - Alex : to be implemented
    return false;
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

void Graph::saveIn(std::ostream& ost) const
{
    ///@todo - Alex : to be implemented
    string toPrint = "";

    if(usingFsAndAps)
    {
        toPrint += "FS: [";
        unsigned i = 0;
        for(i = 0; i < FS.size() - 1; ++i)
        {
            toPrint += std::to_string(FS[i]) + ", ";
        }
        toPrint += std::to_string(FS[i]) + "]\n";

        toPrint += "APS: [";
        for(i = 0; i < APS.size() - 1; ++i)
        {
            toPrint += std::to_string(APS[i]) + ", ";
        }
        toPrint += std::to_string(APS[i]) + "]\n";

    } else {
        toPrint += "MATADJ: {\n";
        unsigned i = 0, j = 0;
        for(i = 0; i < matAdj.size(); ++i)
        {
            toPrint += "{";
            for(j = 0; j < matAdj[i].size() - 1; ++j)
            {
                toPrint += std::to_string(matAdj[i][j]) + ", ";
            }
            toPrint += std::to_string(matAdj[i][j]) + "}\n";
        }
        toPrint += "}\n";
    }



    ost << toPrint;
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
std::ostream& operator<<(std::ostream& ost, const Graph& g)
{
    g.print(ost);
    return ost;
}
// ---------- End of global functions ----------
