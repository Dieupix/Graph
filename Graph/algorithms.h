#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include<iostream>
#include<vector>

using std::cout;
using std::endl;
using std::vector;

void demi_degre_interieur   (const vector<int>& FS, const vector<int>& APS, vector<int>& DDI);
void descente_largeur       (int r,const vector<int>& fs, const vector<int>& aps, vector<int>& dist);
void Mat_distance           (const vector<int>& FS, const vector<int>& APS, vector<vector<int>>& matriceDistance);
void empiler                (int x, vector<int>& pilch);
void rang                   (vector<int>& rang, const vector<int>& FS, const vector<int>& APS);
void rangToString           (const vector<int>& FS, const vector<int>& APS);

#endif // ALGORITHMS_H
