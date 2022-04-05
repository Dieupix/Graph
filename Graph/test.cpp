#include "test.h"

void test()
{
    testTarjan();

    cout << endl;

    testPrufer();
}

/* -------------------------------------------------- */

void testDistance()
{
    vector<vector<int>> matriceDistance(APS_1[0]+1, vector<int>(APS_1[0]+1, 0));
    mat_distance(FS_1, APS_1, matriceDistance);

    // TEST distance -- Affichage OK
    for(unsigned i = 0 ; i < matriceDistance.size() ; ++i)
    {
        cout<<"LIGNE "<<i<<"\t";
        for(auto j : matriceDistance[i]) cout << j << " ";
        cout<<endl;
    }
}

void testPrufer()
{
    vector<int> p;
    vector<vector<int>> mat;

    Prufer_encode(matAdj_3, p);

    cout << "p:     "; printVector(p);

    Prufer_decode(p, mat);

    cout << "mat:   "; printVector(mat[0]);
    for(unsigned i = 1; i < mat.size(); ++i){
        cout << "       "; printVector(mat[i]);
    }
}

void testRang()
{

}

void testTarjan()
{
    cout << "Tarjan: " << endl;
    Tarjan(FS_4, APS_4);
}
