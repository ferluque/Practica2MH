//
// Created by fl156 on 29/03/2022.
//

#ifndef MDD_SOLUTION_H
#define MDD_SOLUTION_H

#include <vector>
#include <iostream>
#include <fstream>
#include <map>
#include "random.hpp"
#include "

class Solution {
private:
    std::vector<bool> selected;
    float diff;
    float max_delta;
    float min_delta;
    std::map<int,float> deltas;

    void check_max_min(float new_delta);

    /**
     * Actualiza el valor de diff con respecto al último valor introducido u
     * @param d La matriz de distancias
     * @param u El último punto introducido
     */
    void update_diff(const std::vector<std::vector<float>>& d, int u);

    /**
     * Calcula la dispersión de un punto u en el conjunto de seleccionados
     * @param u El punto
     * @param d La matriz de distancias
     * @return El valor de delta
     */
    float delta(int u, const std::vector<std::vector<float>>& d);

    /**
     * Intercambia el vecino i por j y modifica valores correspondientes
     * @param i
     * @param j
     * @param d
     * @return Devuelve la solución con los puntos cambiados
     */
    Solution exchange(int i, int j, std::vector<std::vector<float>> d);
public:
    Solution();
    /**
     * Constructor que inicializa la solución con un punto inicial
     * @param p0 El punto inicial
     * @param d La matriz de distancias
     */
    Solution(int p0, const std::vector<std::vector<float>>& d);
    /**
     * Constructor que inicializa la solución al vector de seleccionados que le pasamos (función utilizada en la bl)
     * @param s El vector de seleccionados
     * @param d La matriz de distancias
     */
    Solution(std::vector<int> s, const std::vector<std::vector<float>> d);
    /**
     * Constructor de copia
     * @param c
     */
    Solution(const Solution& c);
    /**
     * Devuelve el nuevo valor de la función objetivo (factorizada) tras la inclusión de un nuevo punto
     * @param u El punto nuevo
     * @param d La matriz de distancias
     * @return El valor de diff para selected union u
     */
    float get_new_diff(int u, const std::vector<std::vector<float>>& d);
    // Función para GREEDY
    /**
     * Añade un punto a la solución y actualiza el valor de diff
     * @param u
     * @param d
     */
    void add(int u, const std::vector<std::vector<float>>& d);
    // FUNCIÓN PARA BL
    /**
     * Mecanismo de generación de vecinos. Intercambia el elemento i por el j y devuelve la solución con el respectivo
     * valor de diff, max y min delta y deltas
     * @param i El elemento que saca
     * @param j El elemento que mete
     * @return El vecino
     */
    Solution neighbor(int i, int j, std::vector<std::vector<float>> d);


    float get_diff() const;

    int get_size() const;

    const std::vector<bool>& get_selected();

    void print_dist(std::string file_out, const std::vector<std::vector<float>>& d);

    // AGG-Uniforme
    Solution cruce_uniforme(const Solution& s) const;
    std::vector<bool> repare(std::vector<bool> h, const Problem& p) const;
    Solution(const std::vector<bool>& s, const Problem& p);
};

std::ostream& operator<<(std::ostream& out, Solution s);

template <class T>
std::ostream& operator<<(std::ostream& out, std::vector<T> v);

#endif //MDD_SOLUTION_H
