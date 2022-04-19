#ifndef GRAPH_H
#define GRAPH_H

#include "noeud.h"
#include "exceptions.h"

#include <memory>

using namespace exceptions;

using std::make_unique;
using std::unique_ptr;

/**
 * @brief The Graph class
 */
class Graph
{
private:
    /**
     * @brief fs
     * @details Représente la file des successeurs de chaque sommet
     */
    vector<int> FS;
    /**
     * @brief aps
     * @details
     */
    vector<int> APS;
    /**
     * @brief matAdj
     * @details
     */
    vector<vector<int>> matAdj;
    /**
     * @brief isUsingFsAndAps
     * @details
     */
    bool usingFsAndAps;
    /**
     * @brief sommets
     * @details
     */
    vector<unique_ptr<Noeud>> sommets;
    /**
     * @brief couts
     * @details
     */
    vector<vector<int>> couts;
    /**
     * @brief est_oriente
     * @details
     */
    bool est_oriente;
    /**
     * @brief a_des_poids
     * @details
     */
    bool a_des_poids;

    // Private functions
    void initialiserSommets(unsigned size);
    void verifIntegritee();
    bool verifIntegriteeSommets();
    bool verifIntegriteeSommets_FS_APS();
    bool verifIntegriteeSommets_MatAdj();

public:

    // Constructors

    Graph(bool est_oriente = true); // couts vide
    Graph(const vector<int>& FS, const vector<int>& APS); // est_oriente = false, couts vide
    Graph(const vector<vector<int>>& matAdj, bool est_oriente = true); // couts vide
    Graph(const vector<int>& FS, const vector<int>& APS, const vector<int>& couts); // est_oriente = false
    Graph(const vector<vector<int>>& matAdj, const vector<int>& couts, bool est_oriente = true);

    Graph(const Graph& g);


    /**
     * @brief Graph
     *
     * @param fs :
     * @param aps:
     * @param est_oriente :
     * @param a_des_poids :
     *
     * @throws PasAssezDeSommetsException() :
     * @throws SommetsNonReliesException() :
     *
     * @returns
     */
    Graph(const vector<int>& fs, const vector<int>& aps, const vector<unique_ptr<Noeud>>& sommets, bool est_oriente, bool a_des_poids);
    /**
     * @brief Graph
     *
     * @param matAdj :
     * @param est_oriente :
     * @param a_des_poids :
     *
     * @throws PasAssezDeSommetsException() :
     * @throws SommetsNonReliesException() :
     *
     * @returns
     */
    Graph(const vector<vector<int>>& matAdj, const vector<unique_ptr<Noeud>>& sommets, bool est_oriente, bool a_des_poids);

    // Destructor

    // Overloads

    // Getters
    /**
     * @brief getEst_oriente
     *
     * @return
     */
    bool getEst_oriente() const;
    /**
     * @brief getA_Des_Poids
     *
     * @return
     */
    bool getA_Des_Poids() const;
    /**
     * @brief getFS
     *
     * @return
     */
    vector<int> getFS() const;
    /**
     * @brief getAPS
     *
     * @return
     */
    vector<int> getAPS() const;
    /**
     * @brief getMatAdj
     *
     * @return
     */
    vector<vector<int>> getMatAdj() const;
    /**
     * @brief isUsingFsAndAps
     *
     * @return
     */
    bool isUsingFsAndAps() const;
    /**
     * @brief getSommets
     *
     * @return
     */
    const vector<unique_ptr<Noeud>>& getSommets() const;

    // Setters

    // Functions
    /**
     * @brief ajouterNoeud
     *
     * @param n
     */
    void ajouterNoeud(unique_ptr<Noeud>& n, const vector<int>& pred, const vector<int>& succ);
    /**
     * @brief FS_APS_to_MatAdj
     *
     * @param matAdj
     */
    void FS_APS_to_MatAdj(vector<vector<int>>& matAdj) const;
    /**
     * @brief loadFrom
     *
     * @param ist
     *
     * @return
     */
    bool loadFrom(std::istream& ist); ///@todo - Alex : to be implemented
    /**
     * @brief matAdj_to_FS_APS
     *
     * @param FS
     * @param APS
     */
    void matAdj_to_FS_APS(vector<int>& FS, vector<int>& APS) const;
    /**
     * @brief print
     *
     * @param ost
     */
    void print(std::ostream& ost) const;
    /**
     * @brief saveIn
     *
     * @param ost
     *
     * @return
     */
    void saveIn(std::ostream& ost) const; ///@todo - Alex : to be implemented
    /**
     * @brief toString
     *
     * @return
     */
    string toString() const;
};

// Global functions
/**
 * @brief operator <<
 *
 * @param ost : The output stream to print the graph on
 * @param g : The graph to print
 *
 * @return Returns the output stream itselft
 */
std::ostream& operator<<(std::ostream& ost, const Graph& g);

#endif // GRAPH_H
