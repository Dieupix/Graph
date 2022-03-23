#ifndef ALGORITHMS_H
#define ALGORITHMS_H

#include<iostream>
#include<vector>

using std::vector;

void distance(const vector<int> fs, const vector<int> aps, int s, vector<int>& dist);
void empiler(int x, vector<int> &pilch);
void demi_degre_interieur(vector<int> FS, vector<int> APS, vector<int> &DDI);
void rang(vector<int> &rang, vector<int> FS, vector<int> APS);
void rangToString(vector<int> FS, vector<int> APS);

#endif // ALGORITHMS_H
