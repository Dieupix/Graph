#ifndef GRAPH_H
#define GRAPH_H

#include "noeud.h"

class Graph
{
private:
    /**
     * @brief fs
     * @details Représente la file des successeurs de chaque sommet
     */
    vector<int> fs;
    /**
     * @brief aps
     * @details
     */
    vector<int> aps;
    /**
     * @brief matAdj
     * @details
     */
    vector<vector<int>> matAdj;

    /**
     * @brief sommets
     * @details
     */
    vector<Noeud> sommets;

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

public:

    // Constructors
    /**
     * @brief Default constructor
     *
     * @returns Creates a graph
     */
    Graph();
    /**
     * @brief Graph
     *
     * @param est_oriente
     *
     * @returns
     */
    Graph(bool est_oriente, bool a_des_poids);
    /**
     * @brief Graph
     *
     * @param fs
     * @param aps
     * @param est_oriente
     * @param a_des_poids
     *
     * @returns
     */
    Graph(vector<int> fs, vector<int> aps, bool est_oriente, bool a_des_poids);
    /**
     * @brief Graph
     *
     * @param matAdj
     * @param est_oriente
     * @param a_des_poids
     *
     * @returns
     */
    Graph(vector<vector<int>> matAdj, bool est_oriente, bool a_des_poids);

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
     * @brief getSommets
     *
     * @return
     */
    vector<Noeud> getSommets() const;

    // Setters

    // Functions
    /**
     * @brief print
     *
     * @param ost
     */
    void print(std::ostream& ost) const;
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
std::ostream& operator<<(std::ostream& ost, const Graph g);

#endif // GRAPH_H
