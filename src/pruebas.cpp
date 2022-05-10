//
// Created by Fernando on 07/05/2022.
//

#include "Solution_enteros.h"
#include "Problem.h"
#include <iostream>
#include <vector>
#include "random.hpp"

using namespace std;
using Random = effolkronium::random_static;


int main() {
//    Random::seed(0);
//    Problem p("..\\datos\\GKD-b_6_n25_m7.txt");
//    Solution_enteros una({3,4,5,6,7,8,9},p.get_d());
//
//    cout << una<<endl;
//    una.print_dist("..\\resultados\\una0-6.csv", p.get_d());
//
//    Solution_enteros otra({3,5,10,0,12,1,2},p.get_d());
//    cout << otra<<endl;
//    otra.print_dist("..\\resultados\\otra1-8.csv",p.get_d());
//
//    pair<Solution_enteros,Solution_enteros> cruce = una.cruce_uniforme(otra,p);
//
//    cout << cruce.first<< endl;
//    cruce.first.print_dist("..\\resultados\\cruce1.csv",p.get_d());
//    cout << cruce.second << endl;
//    cruce.second.print_dist("..\\resultados\\cruce2.csv",p.get_d());
    Random::seed(0);
    Problem p("..\\datos\\GKD-b_6_n25_m7.txt");
    vector<int> v = {1,2,3,4,5,6,7};
    Solution_enteros s(v,p);
    cout << s << endl;
    s.print_dist("..\\resultados\\sinmutar.csv",p.get_d());

    s = s.mutacion(p);
    cout << s << endl;
    s.print_dist("..\\resultados\\mutado.csv",p.get_d());
}