#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include<iostream>
#include<vector>
#include "graph.h"
using std::cout;
using std::endl;
using std::vector;

void demi_degre_interieur   (const vector<int>& FS, const vector<int>& APS, vector<int>& DDI);
void descente_largeur       (int r, const vector<int>& fs, const vector<int>& aps, vector<int>& dist);
void empiler                (int x, vector<int>& pilch);
void fortconnexe            (const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem);
void mat_distance           (const vector<int>& FS, const vector<int>& APS, vector<vector<int>>& matriceDistance);
void printVector            (const vector<int>& vector);
void Prufer_encode          (vector<vector<int>> mat, vector<int>& p);
void Prufer_decode          (const vector<int>& p, vector<vector<int>>& mat);
void rang                   (vector<int>& rang, const vector<int>& FS, const vector<int>& APS);
void rangToString           (const vector<int>& FS, const vector<int>& APS);
void Tarjan                 (const vector<int>& FS, const vector<int>& APS);
void traversee              (int s, int& p, int& k, const vector<int>& FS, const vector<int>& APS, vector<int>& cfc, vector<int>& pilch, vector<int>& pred, vector<int>& prem, vector<int>& tarj, vector<bool>& entarj, vector<int>& num, vector<int>& ro);
void Ordonnancement         (const vector<int> file_pred, const vector<int> adr_prem_pred, const vector<int> duree_taches, vector<int>& file_pred_critique, vector<int>& adr_prem_pred_critique, vector<int>& longueur_critique);
void englobe_ordonnancement (const vector<int>& fs, const vector<int>& aps, const vector<int>& duree_taches, vector<int>& new_fs, vector<int>& new_aps);
void transforme_FS_APS_TO_FP_APP(const vector<int>& fs, const vector<int>& aps, vector<int>& fp, vector<int>& app);
void transforme_FP_APP_TO_FS_APS(const vector<int>& fp, const vector<int>& app, vector<int>& fs, vector<int>& aps);
bool Dantzig                (vector<vector<int>>& c);
void Kruskal                (Graph g);
void Dijkstra               (const vector<int>& fs, const vector<int>& aps, const vector<vector<int>>& p, int s, vector<int> &d, vector<int> &pr);

#endif // ALGORITHMS_H
