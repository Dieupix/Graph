#ifndef ALGORITHMS_H
#define ALGORITHMS_H
#include<iostream>
#include<vector>
using std::vector;

class algorithms
{
public:
    algorithms();
    void distance(const vector<int> fs, const vector<int> aps, int s, vector<int>& dist);
};

#endif // ALGORITHMS_H
