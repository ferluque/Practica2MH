//
// Created by fl156 on 05/05/2022.
//

#include "Solution.h"
#include <iostream>
#include <vector>

using namespace std;
using Random = effolkronium::basic_random_static;

void Solution::check_max_min(float new_delta) {
    if (new_delta > max_delta)
        max_delta = new_delta;
    if ((new_delta < min_delta)||(selected.size()==2))
        min_delta = new_delta;
}

void Solution::update_diff(const vector<vector<float>> &d, int u){
    // Actualizamos los valores de delta anteriores para todos con el nuevo punto
//    int nuevo = selected[selected.size()-1];
//
//    deltas[0] += d[selected[0]][nuevo];
//    max_delta = min_delta = deltas[0];
//    for (int i=1; i<deltas.size(); i++) {
//        deltas[i] += d[selected[i]][nuevo];
//        check_max_min(deltas[i]);
//    }
//
//    // Añado el delta del punto nuevo
//    deltas.push_back(delta(nuevo, d));
//    check_max_min(deltas[deltas.size()-1]);
//
//    diff = max_delta-min_delta;
    max_delta = min_delta = deltas.begin()->second;
    for (map<int,float>::iterator it = deltas.begin(); it != deltas.end(); ++it) {
        (*it).second += d[(*it).first][u];
        check_max_min((*it).second);
    }
    deltas[u] = delta(u,d);

    diff = max_delta-min_delta;
    // ACTUALIZAR CON NUEVA CODIFICACIÓN
}

// ACTUALIZADO
float Solution::delta(int u, const vector<vector<float>> &d){
    float de = 0.0;
    for (int i=0; i<selected.size(); i++)
        if (selected[i])
            de+=d[i][u];
    return de;
}

Solution Solution::exchange(int i, int j, vector<vector<float>> d) {
    // ACTUALIZARLO CUANDO SEA NECESARIO
//    // EN primer lugar busco la posición de i en selected ( y en delta )
//    int posi = -1;
//    for (int k=0; (k<selected.size()) && (posi ==-1); k++)
//        if (selected[k] == i)
//            posi = k;
//
//    // Saco i de selected y de delta
//    selected.erase(selected.begin()+posi);
//    deltas.erase(deltas.begin()+posi);
//
//    // Meto j en selected y en delta
//    selected.push_back(j);
//    deltas.push_back(0.0);
//
//    // Actualizo los valores de min_delta y max_delta
//    // Para ello tengo que restar d[i][selected[k]] y sumar d[j][selected[k]] a los deltas
//    deltas[0] = min_delta = max_delta = deltas[0] - d[i][selected[0]] + d[j][selected[0]];
//    for (int k=1; k<deltas.size()-1; k++) {
//        deltas[k] = deltas[k] - d[i][selected[k]] + d[j][selected[k]];
//        check_max_min(deltas[k]);
//    }
//    deltas[deltas.size()-1] = delta(j, d);
//    check_max_min(deltas[deltas.size()-1]);
//    diff = max_delta - min_delta;
//    return *this;
}

// ACTUALIZADO
Solution::Solution(int p0, const vector<vector<float>> &d)  {
    selected.resize(d.size());
    selected[p0] = true;
    min_delta = max_delta = 0.0;
    diff = 0.0;
    deltas[p0] = 0.0;
};

Solution::Solution(vector<int> s, const vector<vector<float>> d) {
// ACTUALIZAR CUANDO HAGA FALTA
//    selected = s;
//    deltas.resize(s.size());
//    deltas[0] = max_delta = min_delta = delta(s[0], d);
//    for (int i=1; i<selected.size(); i++) {
//        deltas[i] = delta(selected[i], d);
//        check_max_min(deltas[i]);
//    }
//    diff = max_delta - min_delta;
}

// NO HAY NADA QUE ACTUALIZAR
Solution::Solution(const Solution &c) {
    this->selected = c.selected;
    this->max_delta = c.max_delta;
    this->min_delta = c.min_delta;
    this->diff = c.diff;
    this->deltas = c.deltas;
}

// CREO QUE NO HAY NADA QUE ACTUALIZAR
float Solution::get_new_diff(int u, const vector<vector<float>> &d) {
    Solution posible(*this);
    posible.add(u,d);
    return posible.get_diff();
}

//
void Solution::add(int u, const vector<vector<float>> &d)  {
    selected[u] = true;
    // ACTUALIZAR UPDATE_DIFF, HARÁ FALTA DARLE LA u
    update_diff(d, u);
}

// CREO QUE NO HAY QUE ACTUALIZAR NADA, SÍ EN exchange
Solution Solution::neighbor(int i, int j, vector<vector<float>> d)  {
    Solution vecino(*this);
    return vecino.exchange(i,j,d);
}

float Solution::get_diff() const {return diff;}

int Solution::get_size() const {return (int)selected.size();}

const vector<bool>& Solution::get_selected() {return selected;};

void Solution::print_dist(string file_out, const vector<vector<float>> &d) {
    ofstream out;
    out.open(file_out);
    out << ";";
    for (int i=0; i<selected.size(); i++)
        if (selected[i])
            out << i << ";";
    out << endl;
    for (int i=0; i<selected.size(); i++) {
        if (selected[i]) {
            out << i << ";";
            for (int j=0; j<selected.size(); j++) {
                if (selected[j])
                    out << d[i][j] << ";";
            }
            out << endl;
        }
    }
}

ostream& operator<<(ostream& out, Solution s) {
    out << "Escogidos: (";
    vector<bool> selected = s.get_selected();
    for (int i=0; i<selected.size(); i++)
        if (selected[i])
            out << i << ", ";
    out << ")" << endl;
    out << "Valor de diff: " << s.get_diff() << endl;
    return out;
}

template <class T>
ostream& operator<<(ostream& out, vector<T> v)  {
    out << "(";
    for (auto it=v.begin(); it!=v.end();++it)
        out << *it << ",";
    out <<")" << endl;
    return out;
}

Solution::Solution() {
    max_delta= min_delta = 0;
}

// AGG-Uniforme
Solution Solution::cruce_uniforme(const Solution &s, const Problem p) const {
    vector<bool> s1 = this->selected;
    vector<bool> s2 = s.selected;

    vector<bool> h(s1.size());
    // Nos quedamos con los que coincidan
    for (int i = 0; i < s1.size(); i++) {
        if (s1[i] == s2[i])
            h[i] = s1[i];
        else {
            bool uno = Random::get<bool>();
            if (uno)
                h[i] = s1[i];
            else
                h[i] = s2[i];
        }
        h = repare(h, p);
        return Solution(h);
    }
}

Solution::Solution(const std::vector<bool> &s, const Problem &p) {
    selected = s;
    deltas.resize(p)
    for (int i=0; i<selected.size(); i++)
        if
}


