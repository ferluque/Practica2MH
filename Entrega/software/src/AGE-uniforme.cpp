//
// Created by Fernando on 07/05/2022.
//

#include "Solution.h"
#include <iostream>
#include "random.hpp"
#include <filesystem>

using namespace std;
using Random = effolkronium::random_static;

Solution AGE_uniforme(int M, Problem problema);

int main() {
    Random::seed(0);
    int M=50;
    string path = "..\\datos";
    ofstream salida;
    salida.open("..\\resultados\\AGE-uniforme.csv");
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        string file = entry.path().u8string();
        salida << file << ";";

        Problem p(file);
        auto tinicio = clock();
        Solution S = AGE_uniforme(M,p);
        auto tfin = clock();
        salida << S.get_diff() << ";" << double(tfin-tinicio)/CLOCKS_PER_SEC*1000 << ";" << endl;
        cout << "Terminado " << file << endl;
    }
}

Solution AGE_uniforme(int M, Problem problema) {
    vector<Solution> Padres = genera_p0(M, problema);
    int evaluaciones = 0;
    while (evaluaciones < 1e5) {
        // Buscamos los dos peores padres
        pair<int,int> peores_padres(0,0);
        float peor_diff = Padres[peores_padres.first].get_diff();
        evaluaciones++;

        for (int i = 1; i < Padres.size(); i++) {
            float diff_padre = Padres[i].get_diff();
            if (diff_padre > peor_diff) {
                peores_padres.first = i;
                peor_diff = diff_padre;
            }
            evaluaciones++;
        }

        peor_diff = Padres[peores_padres.second].get_diff();
        for (int i=1; i<Padres.size(); i++) {
            float diff_padre = Padres[i].get_diff();
            if ((diff_padre>peor_diff)&&(i!=peores_padres.first)) {
                peores_padres.second = i;
                peor_diff = diff_padre;
            }
            evaluaciones++;
        }

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
        hijos = intermedia[0].cruce_uniforme(intermedia[1], problema);

        // Mutación
        float pm = 0.1;
        if (Random::get<float>(0, 1) <= pm)
            hijos.first = hijos.first.mutacion(problema);

        if (Random::get<float>(0, 1) <= pm)
            hijos.second = hijos.second.mutacion(problema);

        // REEMPLAZAMIENTO
        // Los dos hijos compiten por entrar
        // El Padres[peores_padres.first] es peor que el second
        // El primero es mejor que el segundo
        float hijo1 = hijos.first.get_diff();
        float hijo2 = hijos.second.get_diff();
        float padremalo = Padres[peores_padres.second].get_diff();
        float padrepeor = Padres[peores_padres.first].get_diff();
        if (hijo1<hijo2) {
            // Si el primero se puede meter por el padre más malo se mete
            if (hijo1<padrepeor) {
                Padres[peores_padres.first] = hijos.first;
                // Y vemos si el segundo se puede meter por el menos malo
                if (hijo2<padremalo)
                    Padres[peores_padres.second] = hijos.second;
            }
            // Si no se puede meter por el peor a ver si se puedem eter por el menos malo
            // Además, si el 1 no se puede meter por el peor, menos va a poder el 2
            if (hijo1<padremalo) {
                Padres[peores_padres.second] = hijos.first;
                // Ya aquí el 2 no se puede meter
            }
        }
            // El segundo hijo es mejor o igual que el primero
        else {
            // Si el segundo se puede meter por el padre más malo se mete
            if (hijo2<padrepeor) {
                Padres[peores_padres.first] = hijos.second;
                // Y vemos si el primero se puede meter por el menos malo
                if (hijo1<padremalo)
                    Padres[peores_padres.second] = hijos.first;
            }
            // Si no se puede meter por el peor a ver si se puedem eter por el menos malo
            // Además, si el 2 no se puede meter por el peor, menos va a poder el 1
            if (hijo2<padremalo) {
                Padres[peores_padres.second] = hijos.second;
                // Ya aquí el1 1 no se puede meter
            }
        }
        evaluaciones += 4;
    }
    int mejor = 0;
    for (int i=1; i<Padres.size(); i++)
        if (Padres[i].get_diff()<Padres[mejor].get_diff())
            mejor = i;
    return Padres[mejor];
}
