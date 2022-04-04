#ifndef TEST_H
#define TEST_H

#include "algorithms.h"

/** FS_1 - APS_1
 *  Un noeud sans prédécesseurs (1)
 */
const vector<int> FS_1 = {16, 2, 3, 0, 4, 7, 0, 4, 0, 5, 0, 6, 7, 0, 0, 6, 0};
const vector<int> APS_1 = {7, 1, 4, 7, 9, 11, 14, 15};

/** FS_2 - APS_2
 *  Un noeud sans prédécesseurs (1)
 *  Une composante fortement connexe (6 - 7)
 */
const vector<int> FS_2 = {17, 2, 3, 0, 4, 7, 0, 4, 0, 5, 0, 6, 7, 0, 7, 0, 6, 0};
const vector<int> APS_2 = {7, 1, 4, 7, 9, 11, 14, 16};

void testDistance();
void testRang();
void testTarjan();

void test();

#endif // TEST_H
