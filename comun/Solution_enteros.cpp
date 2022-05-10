//
// Created by Fernando on 08/05/2022.
//
#include "Solution_enteros.h"
#include <algorithm>
#include "random.hpp"

using Random = effolkronium::random_static;
using namespace std;

void Solution_enteros::check_max_min(float new_delta) {
    max_delta = min_delta = deltas.begin()->second;
    for (auto it = deltas.begin(); it != deltas.end(); ++it) {
        if ((*it).second > max_delta)
            max_delta = (*it).second;
        if ((*it).second < min_delta)
            min_delta = (*it).second;
    }
    diff = max_delta - min_delta;
}

float Solution_enteros::delta(int u, const std::vector<std::vector<float>> &d) const {
    float de = 0.0;
    for (int i: selected)
        de += d[i][u];
    return de;
}

Solution_enteros Solution_enteros::exchange(int i, int j, vector<vector<float>> d) {
    // Saco la i de selected y de deltas
    selected.erase(find(selected.begin(), selected.end(), i));
    deltas.erase(i);

    // Meto j en selected
    selected.push_back(j);
    deltas[j] = delta(j,d);

    // FUNCIÓN OBJETIVO FACTORIZADA
    // Actualizo los valores de min_delta y max_delta
    // Para ello tengo que restar d[i][selected[k]] y sumar d[j][selected[k]] a los deltas
    deltas[selected[0]] = min_delta = max_delta = deltas[selected[0]] - d[i][selected[0]] + d[j][selected[0]];
    for (int k = 1; k < selected.size()-1; k++) {
        float de = deltas[selected[k]] = deltas[selected[k]] - d[i][selected[k]] + d[j][selected[k]];
        if (de>max_delta)
            max_delta = de;
        if (de<min_delta)
            min_delta = de;
    }
    if (deltas[j]>max_delta)
        max_delta = deltas[j];
    if (deltas[j]<min_delta)
        min_delta = deltas[j];
    diff = max_delta - min_delta;
    return *this;
}

Solution_enteros::Solution_enteros(std::vector<int> s, const Problem& p) {
    selected = s;
    deltas[selected[0]] = max_delta = min_delta = delta(s[0], p.get_d());
    for (int i = 1; i < selected.size(); i++) {
        float de = delta(selected[i],p.get_d());
        deltas[selected[i]] = de;
        if (de>max_delta)
            max_delta = de;
        if (de<min_delta)
            min_delta = de;
    }
    diff = max_delta - min_delta;
}

Solution_enteros::Solution_enteros(const Solution_enteros &c) {
    this->selected = c.selected;
    this->max_delta = c.max_delta;
    this->min_delta = c.min_delta;
    this->diff = c.diff;
    this->deltas = c.deltas;
};

Solution_enteros Solution_enteros::neighbor(int i, int j, std::vector<std::vector<float>> d) {
    Solution_enteros vecino(*this);
    return vecino.exchange(i, j, d);
}

void Solution_enteros::print_dist(std::string file_out, const std::vector<std::vector<float>> &d) {
    ofstream out;
    out.open(file_out);
    out << ";";
    for (int i: selected)
        out << i << ";";
    out << endl;
    for (int i: selected) {
        out << i << ";";
        for (int j: selected) {
            out << d[i][j] << ";";
        }
        out << endl;
    }
}

ostream& operator<<(ostream& out, Solution_enteros s) {
    out << "Escogidos: (";
    vector<int> selected = s.get_selected();
    for (int i : selected) {
        out << i << ", ";
    }
    out << ")" << endl;
    out << "Valor de diff: " << s.get_diff() << endl;
    return out;
}

float Solution_enteros::avg(std::vector<bool> h, const Problem &p) const {
    float avg = 0.0;
    for (int i=0; i<h.size(); i++)
        if (h[i])
            avg += delta(i, p.get_d());
    return avg/(int)std::count(h.begin(), h.end(), true);
}

std::vector<bool> Solution_enteros::repare(std::vector<bool> h, const Problem& p) {
    // Calculamos cuánto nos pasamos
    int sizeS = count(h.begin(),h.end(),true);
    int v = p.get_m()-count(h.begin(), h.end(), true);
    if (v==0)
        return h;
    if (v<0) {
        while (v<0) {
            float average = avg(h,p);
            int j;
            bool primero = true;
            float max;
            for (int i=0; i<h.size(); i++) {
                if (h[i]) {
                    if (primero) {
                        j = i;
                        max = abs(delta(j, p.get_d())-average);
                        primero = false;
                    } else {
                        float deltai = delta(i, p.get_d());
                        if (abs(deltai-average) > max) {
                            j = i;
                            max = abs(deltai-average);
                        }
                    }
                }
            }
            h[j] = 0;
            average = avg(h,p);
            v++;
        }
    }
    if (v>0) {
        while (v>0) {
            float average = avg(h,p);
            int j;
            bool primero = true;
            float min;
            for (int i=0; i<h.size(); i++) {
                if (!h[i]) {
                    if (primero) {
                        j = i;
                        min = abs(delta(j, p.get_d())-average);
                        primero = false;
                    } else {
                        float deltai = delta(i, p.get_d());
                        if (abs(deltai-average) < min) {
                            j = i;
                            min = abs(deltai-average);
                        }
                    }
                }
            }
            h[j] = 1;
            average = avg(h,p);
            v--;
        }
    }
    return h;
}

pair<Solution_enteros,Solution_enteros> Solution_enteros::cruce_uniforme(const Solution_enteros &otra, const Problem &p) {
    vector<bool> s1(p.get_n(),false);
    vector<bool> s2(p.get_n(), false);
    for (int i=0; i<selected.size(); i++) {
        s1[selected[i]] = true;
        s2[otra.selected[i]] = true;
    }
    vector<bool> h1(s1.size());
    vector<bool> h2(s1.size());
    // Nos quedamos con los que coincidan
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == s2[i])
            h1[i] = h2[i] = s1[i];
            // Los que no se elige aleatoriamente de uno u otro
        else {
            bool uno = Random::get<bool>();
            if (uno)
                h1[i] = s1[i];
            else
                h1[i] = s2[i];
            uno = Random::get<bool>();
            if (uno)
                h2[i] = s1[i];
            else
                h2[i] = s2[i];
        }
    }
    h1 = repare(h1, p);
    h2 = repare(h2, p);
    return pair<Solution_enteros,Solution_enteros>(Solution_enteros(h1,p),Solution_enteros(h2,p));
}

Solution_enteros::Solution_enteros(std::vector<bool> h, const Problem &p) {
    selected = vector<int>(p.get_m());
    int pos = 0;
    for (int i=0; i<h.size(); i++) {
        if (h[i]) {
            selected[pos] = i;
            ++pos;
        }
    }
    max_delta = min_delta = deltas[selected[0]] = delta(selected[0],p.get_d());
    for (int i=1; i<selected.size(); i++) {
        float de = deltas[selected[i]] = delta(selected[i], p.get_d());
        if (de > max_delta)
            max_delta = de;
        if (de < min_delta)
            min_delta = de;
    }
    diff = max_delta-min_delta;
}

vector<int> range(int init, int fin) {
    assert(fin > init);
    vector<int> v(fin - init);
    for (int i = init; i < fin; i++)
        v[i - init] = i;
    return v;
}

vector<Solution_enteros> genera_p0(int M, const Problem& p) {
    vector<Solution_enteros> p0(M);
    vector<int> seleccionados = range(0,p.get_n());
    for (int i=0; i<M; i++) {
        Random::shuffle(seleccionados);
        p0[i] = Solution_enteros(vector<int>{seleccionados.begin(),seleccionados.begin()+p.get_m()},p);
    }
    return p0;
}

Solution_enteros::Solution_enteros(){}

Solution_enteros Solution_enteros::mutacion(const Problem &p) const {
    Solution_enteros otra(*this);

    // Sacar es un índice
    int sacar = Random::get<int>(0,otra.selected.size()-1);
    // Meter es un punto
    int meter = Random::get<int>(0,p.get_n()-1);
    while (std::find(otra.selected.begin(), otra.selected.end(), meter)!=otra.selected.end())
        meter = Random::get<int>(0,p.get_n()-1);

    // Sacamos de la solución
    int valorsacado = otra.selected[sacar];
    otra.deltas.erase(valorsacado);
    otra.selected.erase(otra.selected.begin()+sacar);

    // Metemos y actualizamos deltas
    otra.max_delta = otra.min_delta = otra.deltas[otra.selected[0]] = otra.deltas[otra.selected[0]] - p.get_d()[valorsacado][otra.selected[0]] + p.get_d()[meter][otra.selected[0]];

    for (int i=1; i<otra.selected.size(); i++) {
        float de = otra.deltas[otra.selected[i]] = otra.deltas[otra.selected[i]] - p.get_d()[valorsacado][otra.selected[i]] + p.get_d()[meter][otra.selected[i]];
        if (de > otra.max_delta)
            otra.max_delta = de;
        if (de < otra.min_delta)
            otra.min_delta = de;
    }
    float de = otra.deltas[meter] = otra.delta(meter,p.get_d());
    otra.selected.push_back(meter);
    if (de > max_delta)
        otra.max_delta = de;
    if (de < min_delta)
        otra.min_delta = de;
    otra.diff = otra.max_delta-otra.min_delta;
    return otra;
}