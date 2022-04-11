#include "test.h"
#include "graph.h"

void test()
{
    /*
    testTarjan();

    cout << endl;

    testPrufer();
    */
    //testOrdonnancement();
    testDantzig();
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

void testOrdonnancement()
{
    vector<int> new_fs, new_aps;
    englobe_ordonnancement(FS_5, APS_5, duree_taches,new_fs,new_aps);
    Graph ng = new Graph(new_aps,new_fs); ///QU'ON PEUT ENSUITE MANIPULER
}

void testDantzig()
{
    //Graph g = new Graph(FS_6,APS_6, COUTS_6);
    vector<vector<int>> couts = COUTS_6;
    cout<<"Matrice des Couts Initiale: "<<endl;
    for(unsigned i = 0 ; i < couts.size() ;++i)
    {
        printVector(couts[i]);
    }
    cout<<endl;
    cout<<endl;
    cout<<"Dantzig : "<<endl;
    Dantzig(couts);

    cout<<"Nouvelle Matrice des Couts : "<<endl;
    for(unsigned i = 0 ; i < couts.size() ;++i)
    {
        printVector(couts[i]);
    }
}
