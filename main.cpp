/*Laura Galera Alfaro
 * u1959173
 * s8
 */


#include <iostream>
#include <cstdlib>
#include <memory>
#include <limits>
#include "GrafEtiquetatVMap.h"

using namespace std;

const double INF = numeric_limits<double>::infinity();

struct Node {
    bool solucio;
    int origen;
    double distancia;

    Node() {
        solucio = false;
        origen = 0;
        distancia = INF;
    }

    Node(bool sol, int ori, double dist) {
        solucio = sol;
        origen = ori;
        distancia = dist;
    }
}; //tupla amb solucio, origen i distancia, juntament amb dos constructors

//Pre: v i g han de tenir la mateixa mida
//Post: s'actualitzen les distàncies als vèrtexs adjacents a destí si no han sigut afegits i a més
//si el pes per accedir-hi disminueix des de destí.

void actualitzarNodes(vector<Node> &v, const GrafEtiquetatVMap &g, int desti) {

    for (pair<int, double> i : g.successors(desti)) {
        if (!v[i.first].solucio and (v[i.first].distancia == INF or v[i.first].distancia > i.second)) {
            v[i.first].origen = desti;
            v[i.first].distancia = i.second;
        }
    }
}

//Pre:--
//Post: retorna el vèrtex que encara no ha sigut inclós a l'arbre i té la distància més petita per accedir a ell des d'algun dels ja afegits

int nodeProper(vector <Node> v) {

    int vertex;
    double distMin = INF;

    int i = 0;
    for (Node n : v) {
        if (!n.solucio and n.distancia < distMin) {
            vertex = i;
            distMin = n.distancia;
        }
        i++;
    }
    return vertex;
}

// Pre:  g  és un graf no dirigit
// Post: retorna un graf no dirigit que correspon a l'arbre d'expansió de cost mínim generat mitjançant l'algorisme de Prim

shared_ptr<GrafEtiquetatVMap> Prim(const GrafEtiquetatVMap & g) {

    shared_ptr<GrafEtiquetatVMap> g_prim(new GrafEtiquetatVMap(g.nVertexs()));

    if (g.nVertexs() > 0) {
        int i = 2;
        vector<Node> v(g.nVertexs() + 1); // no es fa servir la posició 0
        v[1] = Node(true, 1, 0.0); // 1: node de referència
        actualitzarNodes(v, g, 1); // distàncies a 1
        while (i <= g.nVertexs()) {
            int desti = nodeProper(v); // node nou amb distància mínima
            g_prim->AfegirAresta(desti, v[desti].origen, v[desti].distancia);
            v[desti].solucio = true;
            actualitzarNodes(v, g, desti); // distàncies al nou node
            i++;
        }
    }
    return g_prim;
}

// Pre:  str és un nom de fitxer amb extensió
// Post: retorna el nom (sense l'extensió) i l'extensió del fitxer,
//       entenent per extensió la seqüència de caràcters després
//       del darrer punt

pair<string, string> splitFilename(const std::string& str) {
    std::size_t found = str.find_last_of(".");
    return make_pair(str.substr(0, found), str.substr(found + 1));
}

// Pre:  F.ext conté la descripció d'un graf etiquetat, no dirigit i connex
//       en format TGF
// Post: llegeix el nom d'un fitxer F.ext pel canal d'entrada i, mostra
//       el graf resultant de trobar un arbre generador mínimal.

int main() {
    string nomF;
    cout << "Fitxer TGF: ";
    getline(cin, nomF);
    pair<string, string> nom_ext = splitFilename(nomF);
    GrafEtiquetatVMap g(nomF);
    shared_ptr<GrafEtiquetatVMap> arbre = Prim(g);
    string nom = nom_ext.first + "_prim." + nom_ext.second;
    cout << nom << endl;
    arbre->EscriureGraf(nom);
}

