#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include<iostream>
#include<vector>

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

#endif // ALGORITHMS_H
