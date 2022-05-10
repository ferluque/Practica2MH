//
// Created by Fernando on 08/05/2022.
//

#include "Solution_enteros.h"
#include "random.hpp"
#include "bl.h"
#include <filesystem>

using namespace std;
using Random = effolkronium::random_static;

Solution_enteros AM_10_0_1(int M, Problem p, float pls);

// ESCOJO EL ALGORITMO ESTACIONARIO CON CRUCE UNIFORME
int main () {
    Random::seed(0);
    int M=10;

    string path = "..\\datos";
    ofstream salida;
    salida.open("..\\resultados\\AM-10-1.csv");
    for (const auto &entry: std::filesystem::directory_iterator(path)) {
        string file = entry.path().u8string();
        salida << file << ";";

        Problem p(file);
        auto tinicio = clock();
        Solution_enteros S = AM_10_0_1(M,p,0.1);
        auto tfin = clock();
        salida << S.get_diff() << ";" << double(tfin-tinicio)/CLOCKS_PER_SEC*1000 << ";" << endl;
        cout << "Terminado " << file << endl;
    }
}

Solution_enteros AM_10_0_1(int M, Problem p,float pls) {
    int generaciones = 0;
    int evaluaciones = 0;

    // Generamos la población inicial
    vector<Solution_enteros> Padres = genera_p0(M,p);
    // CORRECTO

    // 10 generaciones - búsqueda local (mientras evaluaciones < 1e5)
    while (evaluaciones < 1e5) {
        // Toca búsqueda local
        if ((generaciones%10==0)&&(generaciones/10>=1)){
            // Se aplica al 10% mejor
            int num_bl = M*pls;
            int contador = 0;
            vector<bool> investigado(M,false);
            // Buscamos num_bl veces el mejor
            while (contador < num_bl){
                int mejor = 0;
                // Se busca el mejor no investigado
                for (int i=1; i<Padres.size(); i++)
                    if ((Padres[i].get_diff()<Padres[mejor].get_diff())&&(!investigado[i]))
                        mejor = i;
                // Se hace bl en el
                pair<Solution_enteros,int> par = bl(p,Padres[mejor]);
                Padres[mejor]=par.first;
                evaluaciones+=par.second;
                ++contador;
            }
            generaciones /= 10;
        }
        else {
            ++generaciones;
            // Buscamos el peor de los padres
            int peor_padre=0;
            for (int i=1; i<Padres.size(); i++) {
                if (Padres[i].get_diff() > Padres[peor_padre].get_diff())
                    peor_padre = i;
                evaluaciones += 2;
            }
            // Selección (2 torneos)
            vector<Solution_enteros> intermedia(2);
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
            pair<Solution_enteros, Solution_enteros> hijos;
            hijos = intermedia[0].cruce_uniforme(intermedia[1], p);
            // MUTACIÓN
            float pm = 0.1;
            if (Random::get<float>(0, 1) <= pm)
                hijos.first = hijos.first.mutacion(p);

            if (Random::get<float>(0, 1) <= pm)
                hijos.second = hijos.second.mutacion(p);

            // REEMPLAZAMIENTO
            // El mejor de los dos hijos se mete por el peor de los padres si es mejor que este
            if ((hijos.first.get_diff() < hijos.second.get_diff()) && (hijos.first.get_diff() < Padres[peor_padre].get_diff()))
                Padres[peor_padre] = hijos.first;
            else if (hijos.second.get_diff() < Padres[peor_padre].get_diff())
                Padres[peor_padre] = hijos.second;
            evaluaciones += 6;
        }
    }

    int mejor_padre = 0;
    for (int i=1; i<Padres.size(); i++)
        if (Padres[i].get_diff()<Padres[mejor_padre].get_diff())
            mejor_padre = i;

    return Padres[mejor_padre];
}