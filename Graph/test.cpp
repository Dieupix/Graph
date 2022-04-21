#include "test.h"
#include "graph.h"

void test()
{
<<<<<<< HEAD
    //testAjoutNoeud();
    //testTarjan();
/*
    vector<int> cfc {10, 3, 2, 2, 2, 2, 2, 1, 4, 4, 4};
    vector<int> prem {4, 7, 2, 1, 8};
    vector<int> pilch {0, 0, 3, 4, 6, 0, 5, 0, 9, 10 ,0};
    vector<int>fs {26, 2, 7, 0, 3, 5, 0, 4, 0, 6, 0, 4, 0, 2, 5, 7, 0, 0, 1, 9, 0, 10, 0, 3, 8, 9, 0},
               aps {10, 1, 4, 7, 9, 11, 13, 17, 18, 21, 23};
    vector<vector<int>> mat;

    mat.resize(prem[0]+1);
    mat[0].resize(2);
    for(int i = 1 ; i <= prem[0] ;++i)
        mat[i].resize(prem[0]+1,0);

    mat[0][0] = aps[0];
    mat[0][1] = fs[0] - aps[0];

    for(int i = 1 ; i < aps[0] ; ++i)
    {
        int k = aps[i];
        int j = aps[i];
        while(fs[j] != 0)
        {
            if(cfc[fs[j]] != cfc[k] && mat[cfc[k]][cfc[fs[j]]] != 1)
            {
                mat[cfc[k]][cfc[fs[j]]] = 1;
            }
            ++j;
        }
    }

    printVector(cfc);
    printVector(aps);
    printVector(fs);
    for(unsigned i = 1 ; i < mat.size() ;++i)
        printVector(mat[i]);
        */
=======
    testDijkstra();
>>>>>>> f811137d84cb66ccf843ccf52fae5286ab6686e5
}

/* -------------------------------------------------- */

void testAjoutNoeud()
{
    Graph g = Graph(FS_7, APS_7);

    auto n = make_unique<Noeud>(g.getAPS()[0]+1);

    auto pred = {3, 1, 0, 1};
    auto succ = {3, 1, 0, 1};

    g.ajouterNoeud(n, pred, succ);

    cout << "FS:    "; printVector(g.getFS());
    cout << "APS:   "; printVector(g.getAPS());
}

void testDantzig()
{
    //Graph g = Graph(FS_6,APS_6, COUTS_6);
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

void testDijkstra()
{
    vector<int> APS_D{6, 1, 5, 7, 10, 13, 16};
    vector<int> FS_D{18, 2, 3, 5, 0, 1, 0, 2, 5, 0, 3, 5, 0, 2, 6, 0, 1, 2, 0};
    vector<vector<int>> cout_D
    {
        {6,12},
        {0,-1,10,3,-1,6,-1},
        {0,0,-1,-1,-1,-1,-1},
        {0,-1,4,-1,-1,2,-1},
        {0,-1,-1,1,-1,3,-1},
        {0,-1,0,-1,-1,-1,1},
        {0,2,1,-1,-1,-1,-1},
    };

    vector<int> d;
    vector<int> pr;
    Dijkstra(FS_D, APS_D, cout_D, 1, d, pr);

    cout << "d: "; printVector(d);
    cout << "pr:"; printVector(pr);
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

void testOrdonnancement()
{
    vector<int> new_fs, new_aps;
    englobe_ordonnancement(FS_5, APS_5, duree_taches,new_fs,new_aps);
    Graph ng = Graph(new_aps,new_fs); ///QU'ON PEUT ENSUITE MANIPULER
}

void testPrufer()
{
    vector<int> p;
    vector<vector<int>> mat;

    cout << "mat:   "; printVector(matAdj_3[0]);
    for(unsigned i = 1; i < matAdj_3.size(); ++i){
        cout << "       "; printVector(matAdj_3[i]);
    }

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
