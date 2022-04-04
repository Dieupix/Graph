#include "test.h"

void test()
{
    testTarjan();
}

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

void testRang()
{

}

void testTarjan()
{
    Tarjan(FS_2, APS_2);
}
