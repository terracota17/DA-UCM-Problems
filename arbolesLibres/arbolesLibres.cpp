#include <iostream>
#include <fstream>
#include <vector>
#include "Grafo.h"

using namespace std;

class ArbolLibre {
private:
    vector<bool> visit;
    bool conexo = true;
    bool aciciclo = true;

public:
    ArbolLibre(const Grafo& g) : visit(g.V(), false), conexo(true), aciciclo(true) {
        dfs(g, 0, -1);
        for (int h = 0; h < g.V() && conexo; h++) {
            if (!visit[h]) {
                conexo = false;
            }
        }
    }

    bool esLibre() const {
        return conexo && aciciclo;
    }

    void dfs(const Grafo& g, int v, int anterior) {
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (w != anterior) {
                if (!visit[w]) {
                    dfs(g, w, v);
                }
                else {
                    aciciclo = false;
                }
            }
        }
    }
};

bool resuelveCaso() {
    int vertices, aristas;
    cin >> vertices >> aristas;

    if (!cin) // Comprueba si llegamos al final de la entrada
        return false;

    Grafo g(vertices);
    for (int i = 0; i < aristas; i++) {
        int ini, fin;
        cin >> ini >> fin;
        g.ponArista(ini, fin);
    }

    ArbolLibre sol(g);

    if (sol.esLibre()) {
        cout << "SI\n";
    }
    else {
        cout << "NO\n";
    }

    return true;
}

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
