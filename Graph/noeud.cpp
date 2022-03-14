#include "noeud.h"

Noeud::Noeud(int id, std::vector<std::string> info) : d_id{id}, d_info{info}
{}

Noeud::Noeud(int id, std::vector<std::string> info, std::vector<int> poids_arcs) : d_id{id}, d_info{info}, d_poids_arcs{poids_arcs}
{}

int Noeud::getId() const
{
    return d_id;
}

std::vector<std::string> Noeud::getInfo() const
{
    return d_info;
}

std::vector<int> Noeud::getPoids() const
{
    return d_poids_arcs;
}
void Noeud::setId(int id)
{
    d_id = id;
}

void Noeud::setInfo(std::vector<std::string> info)
{
    d_info = info;
}

void Noeud::setPoids(std::vector<int> poids_arcs)
{
    d_poids_arcs = poids_arcs;
}

std::ostream& operator<<(std::ostream& os, const Noeud& n)
{
    os << "Id : " << n.getId() << std::endl;

    os << "Infos : " << std::endl;
    std::vector<std::string> info = n.getInfo();
    for(unsigned int i = 0; i < info.size(); ++i)
        os << " - " << i+1 << info[i] << std::endl;

    os << "Poids des arcs : ";

    std::vector<int> poids_arcs = n.getPoids();
    for(unsigned int i = 0; i < poids_arcs.size(); ++i)
       os << " - " << poids_arcs[i] << std::endl;
    return os;
}
