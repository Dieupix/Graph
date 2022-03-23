#ifndef NOEUD_H
#define NOEUD_H

#include <iostream>
#include <string>
#include <vector>

using std::string;
using std::vector;

class Noeud
{
public:
    Noeud(int id, const vector<string>& info);
    Noeud(int id, const vector<string>& info, const vector<int>& poids_arcs);
    int getId() const;
    vector<string> getInfo() const;
    vector<int> getPoids() const;
    void setId(int id);
    void setInfo(const vector<string>& info);
    void setPoids(const vector<int>& poids_arcs);
    friend std::ostream& operator<<(std::ostream& os, const Noeud& n);
private:
    int d_id;
    vector<string> d_info;
    vector<int> d_poids_arcs;
};

#endif // NOEUD_H
