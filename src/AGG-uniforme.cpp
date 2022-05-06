//
// Created by fl156 on 05/05/2022.
//

#include "Problem.h"
#include "Solution.h"
#include "random.hpp"
#include <vector>
#include <iostream>

using Random = effolkronium::random_static;
using namespace std;


int main() {
//    Problem problema("datos/GKD-b_6_n25_m7.txt");
    // M = 50 padres
    int M = 50;
//    vector<Solution> Padres(50);

    // Generar los M padres de alguna forma

    // Vector aleatorio de cruces: Pc = 0.7
    float pc = 0.7;
    int cruces_esperados = pc*50;
    Random::seed(0);
    vector<int> cruces(2*M);
    for (int i=0; i<cruces.size(); i++)
        cruces[i] = i;
    Random::shuffle(cruces);

    for (int i=0; i<cruces_esperados; i+=2)
        cout << "(" << cruces[i] << ","<<cruces[i+1]<< ")"<< " ";
}
