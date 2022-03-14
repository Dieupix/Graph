#ifndef NOEUD_H
#define NOEUD_H
#include <vector>
#include <string>
#include <iostream>

class Noeud
{
public:
    Noeud(int id, std::vector<std::string> info);
    Noeud(int id, std::vector<std::string> info, std::vector<int> poids_arcs);
    int getId() const;
    std::vector<std::string> getInfo() const;
    std::vector<int> getPoids() const;
    void setId(int id);
    void setInfo(std::vector<std::string> info);
    void setPoids(std::vector<int> poids_arcs);
    friend std::ostream& operator<<(std::ostream& os, const Noeud& n);
private:
    int d_id;
    std::vector<std::string> d_info;
    std::vector<int> d_poids_arcs;
};

#endif // NOEUD_H
