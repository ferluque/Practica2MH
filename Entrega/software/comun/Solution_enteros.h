//
// Created by fl156 on 29/03/2022.
//

#ifndef MDD_SOLUTION_H
#define MDD_SOLUTION_H

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "Problem.h"

class Solution_enteros {
private:
    std::vector<int> selected;
    float diff;
    float max_delta;
    float min_delta;
    std::map<int,float> deltas;

    void check_max_min(float new_delta);

//    /**
//     * Actualiza el valor de diff con respecto al último valor de selected
//     * @param d La matriz de distancias
//     */
//    void update_diff(const vector<vector<float>>& d){
//        // Actualizamos los valores de delta anteriores para todos con el nuevo punto
//        int nuevo = selected[selected.size()-1];
//
//        deltas[0] += d[selected[0]][nuevo];
//        max_delta = min_delta = deltas[0];
//        for (int i=1; i<deltas.size(); i++) {
//            deltas[i] += d[selected[i]][nuevo];
//            check_max_min(deltas[i]);
//        }
//
//        // Añado el delta del punto nuevo
//        deltas.push_back(delta(nuevo, d));
//        check_max_min(deltas[deltas.size()-1]);
//
//        diff = max_delta-min_delta;
//    };

    /**
     * Calcula la dispersión de un punto u en el conjunto de seleccionados
     * @param u El punto
     * @param d La matriz de distancias
     * @return El valor de delta
     */
    float delta(int u, const std::vector<std::vector<float>>& d) const;

    /**
     * Intercambia el vecino i por j y modifica valores correspondientes
     * @param i
     * @param j
     * @param d
     * @return Devuelve la solución con los puntos cambiados
     */
    Solution_enteros exchange(int i, int j, std::vector<std::vector<float>> d);
public:
//    /**
//     * Constructor que inicializa la solución con un punto inicial
//     * @param p0 El punto inicial
//     * @param d La matriz de distancias
//     */
//    Solution(int p0, const vector<vector<float>>& d) {
//        selected.push_back(p0);
//        min_delta = max_delta = 0.0;
//        diff = 0.0;
//        deltas.push_back(0.0);
//    };
    /**
     * Constructor que inicializa la solución al vector de seleccionados que le pasamos (función utilizada en la bl)
     * @param s El vector de seleccionados
     * @param d La matriz de distancias
     */
    Solution_enteros(std::vector<int> s, const Problem& p);

    /**
     * Constructor de copia
     * @param c
     */
    Solution_enteros(const Solution_enteros& c);
//    /**
//     * Devuelve el nuevo valor de la función objetivo (factorizada) tras la inclusión de un nuevo punto
//     * @param u El punto nuevo
//     * @param d La matriz de distancias
//     * @return El valor de diff para selected union u
//     */
//    float get_new_diff(int u, const vector<vector<float>>& d) {
//        Solution posible(*this);
//        posible.add(u,d);
//        return posible.get_diff();
//
//    };
//    /**
//     * Añade un punto a la solución y actualiza el valor de diff
//     * @param u
//     * @param d
//     */
//    void add(int u, const vector<vector<float>>& d) {
//        selected.push_back(u);
//        update_diff(d);
//    };
    /**
     * Mecanismo de generación de vecinos. Intercambia el elemento i por el j y devuelve la solución con el respectivo
     * valor de diff, max y min delta y deltas
     * @param i El elemento que saca
     * @param j El elemento que mete
     * @return El vecino
     */
    Solution_enteros neighbor(int i, int j, std::vector<std::vector<float>> d);


    float get_diff() const {return diff;};

    int get_size() const {return (int)selected.size();};

    const std::vector<int>& get_selected() {return selected;};

    void print_dist(std::string file_out, const std::vector<std::vector<float>>& d);

    // AGE-uniforme
    std::pair<Solution_enteros,Solution_enteros> cruce_uniforme(const Solution_enteros& otra, const Problem& p);
    std::vector<bool> repare(std::vector<bool> h, const Problem& p);
    float avg(std::vector<bool> h, const Problem& p)const;
    Solution_enteros(std::vector<bool> h, const Problem& p);
    Solution_enteros();
    Solution_enteros mutacion(const Problem& p)const;
};

std::ostream& operator<<(std::ostream& out, Solution_enteros s);

template <class T>
std::ostream& operator<<(std::ostream& out, std::vector<T> v) {
    out << "(";
    for (auto it=v.begin(); it!=v.end();++it)
        out << *it << ",";
    out <<")" << std::endl;
    return out;
}

std::vector<int> range(int init, int fin);

std::vector<Solution_enteros> genera_p0(int M, const Problem& p);

#endif //MDD_SOLUTION_H
