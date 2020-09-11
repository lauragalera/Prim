/*Laura Galera Alfaro
 * u1959173
 * s8
 */

#include "GrafEtiquetatVMap.h"

GrafEtiquetatVMap::GrafEtiquetatVMap(int nVertexs, bool dirigit) {

    _nVertexs = nVertexs;
    _dirigit = dirigit;
    _arestes.resize(nVertexs + 1);
}

GrafEtiquetatVMap::GrafEtiquetatVMap(string nomFitxerTGF, bool dirigit) {

    _dirigit = dirigit;
    _nVertexs = 0;
    ifstream f_ent(nomFitxerTGF.c_str());
    string seqvertex;
    getline(f_ent, seqvertex);
    while (seqvertex != "#") {
        _nVertexs++;
        getline(f_ent, seqvertex);
    }
    _arestes.resize(_nVertexs + 1);
    int v1, v2;
    double etiq;
    f_ent >>v1;
    while (!f_ent.eof()) {
        f_ent >>v2;
        f_ent >>etiq;
        AfegirAresta(v1, v2, etiq);
        f_ent>>v1;
    }
    f_ent.close();
}

int GrafEtiquetatVMap::nVertexs() const {
    return _nVertexs;
}

bool GrafEtiquetatVMap::esDirigit() const {
    return _dirigit;
}

void GrafEtiquetatVMap::AfegirAresta(int v1, int v2, double e) {

    if (not ExisteixAresta(v1, v2)) {
        _arestes[v1][v2] = e;
        if (not _dirigit) _arestes[v2][v1] = e;
    }
}

map<int, double> GrafEtiquetatVMap::successors(int v) const {
    return _arestes[v];
}

bool GrafEtiquetatVMap::ExisteixAresta(int v1, int v2) const {

    return _arestes[v1].end() != _arestes[v1].find(v2);
}

void GrafEtiquetatVMap::EsborrarAresta(int v1, int v2) {
    if (ExisteixAresta(v1, v2))
        _arestes[v1].erase(v2);
    if (not _dirigit)
        _arestes[v2].erase(v1);
}

double GrafEtiquetatVMap::EtiquetaAresta(int v1, int v2) const {
    if (not ExisteixAresta(v1, v2)) throw "Aresta innexistent";
    else {
        return _arestes[v1].at(v2);
    }
}

void GrafEtiquetatVMap::EscriureGraf(string nomFitxerTGF) const {

    ofstream f_sort(nomFitxerTGF.c_str());
    f_sort << "Graf no dirigit amb pesos" << endl;
    f_sort << "Vèrtexs del graf" << endl;
    for (int i = 1; i <= _nVertexs; i++)
        f_sort << i << endl;

    int posicio_vertex = 0;

    f_sort << "Arestes del graf" << endl;
    for (auto i : _arestes) {
        for (pair<int, double> j : i) {
            if (posicio_vertex <= j.first)
                f_sort << posicio_vertex << " " << j.first << " " << j.second << endl;
        }
        posicio_vertex++;
    }
    f_sort.close();
}



