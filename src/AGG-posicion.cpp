//
// Created by Fernando on 06/05/2022.
//

#include "Solution.h"
#include "Problem.h"
#include "random.hpp"
#include <iostream>
#include <filesystem>

using namespace std;
using Random = effolkronium::random_static;

Solution AGG_posicion(int M, Problem problema);

int main () {
    Random::seed(0);
    int M=50;
    string path = "..\\datos";
    ofstream salida;
    salida.open("..\\resultados\\AGG-posicion.csv");
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        string file = entry.path().u8string();
        salida << file << ";";

        Problem p(file);
        auto tinicio = clock();
        Solution S = AGG_posicion(M,p);
        auto tfin = clock();
        salida << S.get_diff() << ";" << double(tfin-tinicio)/CLOCKS_PER_SEC*1000 << ";" << endl;
        cout << "Terminado " << file << endl;
    }
}

Solution AGG_posicion(int M, Problem problema) {
    vector<Solution> Padres = genera_p0(M,problema);

    int evaluaciones = 0;
    while (evaluaciones < 1e5) {
        // SELECCIÓN
        // Hacer torneo entre los 50 padres para obtener 50 padres (algunos estarán repetidos pero elimina los peores)
        // Aprovechamos ya para guardar el mejor padre
        vector<Solution> intermedia(M);
        vector<int> torneos = range(0, 2 * M);
        Random::shuffle(torneos);
        int mejor_padre = 0;
        for (int i = 0, j = 0; i < intermedia.size(); i++, j += 2) {
            // Gana primero
            if (Padres[(torneos[j]) % M].get_diff() <= Padres[(torneos[j + 1]) % M].get_diff())
                intermedia[i] = Padres[(torneos[j]) % M];
            else
                intermedia[i] = Padres[(torneos[j + 1]) % M];
            if (i == 0)
                mejor_padre = 0;
            else if (intermedia[mejor_padre].get_diff() > intermedia[i].get_diff())
                mejor_padre = i;
            evaluaciones += 4;
        }

        // CRUCES
        // Vector aleatorio de cruces: Pc = 0.7
        float pc = 0.7;
        int cruces_esperados = pc * M / 2;
        vector<Solution> hijos(M);
        vector<int> cruces = range(0, M);
        Random::shuffle(cruces);
        int last = 0;
        // Los cruces
        for (int i = 0, j = 0; j < cruces_esperados; i += 2, j++) {
            pair<Solution, Solution> doshijos = intermedia[i].cruce_posicion(intermedia[i + 1], problema);
            hijos[i] = doshijos.first;
            hijos[i + 1] = doshijos.second;
            last = i + 2;
        }
        // Los que no cruzan
        for (int i = last; i < cruces.size(); i++)
            hijos[i] = intermedia[i];

        // MUTACIÓN
        float pm = 0.1;
        int mutaciones_esperadas = pm * M;
        vector<int> mutaciones = range(0, M);
        Random::shuffle(mutaciones);

        for (int i = 0; i < mutaciones_esperadas; i++)
            hijos[mutaciones[i]] = hijos[mutaciones[i]].mutacion(problema);
        for (int i = mutaciones_esperadas; i < mutaciones.size(); i++)
            hijos[mutaciones[i]] = hijos[mutaciones[i]];

        // Buscamos el peor hijo y si es peor que el mejor padre lo sustituímos
        int peor_hijo = 0;
        for (int i = 0; i < hijos.size(); i++) {
            if (hijos[i].get_diff() > hijos[peor_hijo].get_diff())
                peor_hijo = i;
            evaluaciones +=2;
        }
        if (intermedia[mejor_padre].get_diff() < hijos[peor_hijo].get_diff())
            hijos[peor_hijo] = intermedia[mejor_padre];
        evaluaciones += 2;
        // Reemplazamiento:
        Padres = hijos;
    }
    // Nos quedamos con el mejor de los últimos Padres que son los hijos de la última época ejecutada
    int mejor = 0;
    for (int i=1; i<Padres.size(); i++)
        if (Padres[i].get_diff()<Padres[mejor].get_diff())
            mejor = i;
    return Padres[mejor];
}
