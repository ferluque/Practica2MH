//
// Created by Fernando on 08/05/2022.
//

#include "Solution_enteros.h"
#include "random.hpp"

using namespace std;
using Random = effolkronium::random_static;

int main () {
    Random::seed(0);
    Problem p("..\\datos\\GKD-b_6_n25_m7.txt");
    int generaciones = 0;
    int evaluaciones = 0;
    int M = 10;

    vector<int> s = range(0,p.get_n());
    Random::shuffle(s);
    Solution_enteros solution (vector<int>(s.begin(),s.begin()+p.get_m()),p.get_d());

    cout << solution;

}