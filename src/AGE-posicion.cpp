//
// Created by Fernando on 07/05/2022.
//

#include "Solution.h"
#include <iostream>
#include "random.hpp"
#include "utils.h"
#include <filesystem>

using namespace std;
using Random = effolkronium::random_static;

Solution AGE_posicion(int M, Problem problema);

int main() {
    Random::seed(0);
    int M=50;
    string path = "..\\datos";
    ofstream salida;
    salida.open("..\\resultados\\AGE-posicion.csv");
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        string file = entry.path().u8string();
        salida << file << ";";

        Problem p(file);
        auto tinicio = clock();
        Solution S = AGE_posicion(M,p);
        auto tfin = clock();
        salida << S.get_diff() << ";" << double(tfin-tinicio)/CLOCKS_PER_SEC*1000 << ";" << endl;
        cout << "Terminado " << file << endl;
    }
}

Solution AGE_posicion(int M, Problem problema) {
    vector<Solution> Padres = genera_p0(M, problema);
    int evaluaciones = 0;
    while (evaluaciones < 1e5) {
        // Buscamos el peor de los padres
        int peor_padre = 0;
        for (int i = 1; i < Padres.size(); i++)
            if (Padres[i].get_diff() > Padres[peor_padre].get_diff())
                peor_padre = i;

        // Selección (2 torneos)
        vector<Solution> intermedia(2);
        vector<int> torneos = range(0, M);
        Random::shuffle(torneos);
        for (int i = 0; i < 4; i += 2) {
            if (Padres[torneos[i]].get_diff() <= Padres[torneos[i + 1]].get_diff())
                intermedia[i / 2] = Padres[torneos[i]];
            else
                intermedia[i / 2] = Padres[torneos[i + 1]];
            evaluaciones += 2;
        }

        // CRUCE
        pair<Solution, Solution> hijos;
        hijos = intermedia[0].cruce_posicion(intermedia[1], problema);

        // Mutación
        float pm = 0.1;
        if (Random::get<float>(0, 1) <= pm)
            hijos.first = hijos.first.mutacion(problema);

        if (Random::get<float>(0, 1) <= pm)
            hijos.second = hijos.second.mutacion(problema);

        // REEMPLAZAMIENTO
        // El mejor de los dos hijos se mete por el peor de los padres si es mejor que este
        if ((hijos.first.get_diff() < hijos.second.get_diff()) && (hijos.first.get_diff() < Padres[peor_padre].get_diff()))
            Padres[peor_padre] = hijos.first;
        else if (hijos.second.get_diff() < Padres[peor_padre].get_diff())
            Padres[peor_padre] = hijos.second;
        evaluaciones += 6;
    }
    int mejor = 0;
    for (int i=1; i<Padres.size(); i++)
        if (Padres[i].get_diff()<Padres[mejor].get_diff())
            mejor = i;
    return Padres[mejor];
}

