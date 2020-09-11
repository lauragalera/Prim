/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   GrafEtiquetatVMap.h
 * Author: laura
 *
 * Created on November 20, 2019, 5:31 PM
 */
#include <vector>
#include <map>
#include <fstream>

#ifndef GRAFETIQUETATVMAP_H
#define GRAFETIQUETATVMAP_H

using namespace std;

class GrafEtiquetatVMap {
public:

    // Pre:  nVertexs >= 0
    // Post: el graf té  nVertexs i cap aresta; és interpretat com a dirigit o no depenent del valor del 2n paràmetre
    GrafEtiquetatVMap(int nVertexs, bool dirigit = false);

    // Pre:  nomFitxerTGF és el nom d'un fitxer de text que conté la descripció d'un graf en format TGF.
    // Post: el graf conté els vèrtexs, pesos i arestes definits al fitxer, interpretant les arestes com a dirigides o no depenent del valor del 2n paràmetre.
    GrafEtiquetatVMap(string nomFitxerTGF, bool dirigit = false);

    // Pre:  ---
    // Post: diu quants vèrtexs té el graf
    int nVertexs() const;

    // Pre:  ---
    // Post: diu si el graf és dirigit
    bool esDirigit() const;

    // Pre:  1 <= v1 <= nVertexs() /\ 1 <= v2 <= nVertexs()
    // Post: el graf conté l'aresta (v1,v2) i el seu pes
    void AfegirAresta(int v1, int v2, double e);

    //Pre: 1 <= v <= nVertexs()
    // Post: retorna els successors (adjacents si no dirigit) del vèrtex v
    map<int, double> successors(int v) const;

    // Pre:  1 <= v1 <= nVertexs() /\ 1 <= v2 <= nVertexs().
    // Post: diu si el graf conté l'aresta (v1,v2)
    bool ExisteixAresta(int v1, int v2) const;

    // Pre:  el graf conté l'aresta (v1,v2)
    // Post: el graf no conté l'aresta (v1,v2)
    void EsborrarAresta(int v1, int v2);

    //Pre: 1 <= v1 <= nVertexs() /\ 1 <= v2 <= nVertexs().
    //Post: retorna el pes de l'aresta (v1, v2)
    double EtiquetaAresta(int v1, int v2) const;

    // Pre:  ---
    // Post: crea el fitxer  nomFitxerTGF  amb la descripció del graf en format TGF
    void EscriureGraf(string nomFitxerTGF) const;

private:

    int _nVertexs; // = _arestes.size()-1 (vèrtexs comencen a 1)
    bool _dirigit;
    vector<map<int, double>> _arestes;
};

#endif /* GRAFETIQUETATVMAP_H */

