//
// Created by Fernando on 06/05/2022.
//

#include "Solution.h"
#include "Problem.h"
#include "random.hpp"
#include <iostream>

using namespace std;
using Random = effolkronium::random_static;

/**
 * Genera un vector de M*2 elementos donde se cruzarán 0 con 1, 2 con 3..., hasta llegar a Pc*M
 * @param Pc Probabilidad de cruce
 * @param M Tamaño de la población
 * @return El vector de 2*M enteros
 */
vector<int> genera_cruces(int M);

int main () {
    Problem p("..\\datos\\GKD-b_6_n25_m7.txt");

    int M = 50;

    // GENERAR 50 PADRES NO SÉ COMO



    // Genero vector de Cruces parejas de 0 a 99 y me quedo con los
    float Pc = 0.7;
    vector<int> cruces = genera_cruces(M);
    cout << cruces;

    // me quedo con los Pc*M/2 primeros cruces
    // 0.7*25 = 17
    // Entonces, cómo escojo los 33 elementos restantes de M?

}

vector<int> genera_cruces(int M) {
    vector<int> cruces(M);
    for (int i=0; i<M; i++)
        cruces[i] = (i)%M;
    Random::shuffle(cruces);
    return cruces;
}