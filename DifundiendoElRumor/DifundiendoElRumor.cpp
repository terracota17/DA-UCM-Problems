#include <iostream>
#include <fstream>
#include <climits>
#include <vector>
#include <algorithm> // Necesario para std::sor
using namespace std;

#include "Grafo.h"

class MinimoCosteRumor {
private:
    vector<bool> visit; // visit[v] = se ha visitado el vértice v?
    vector<int> costes;
    int minimo;

public:
    MinimoCosteRumor(Grafo const& g, vector<int> costee) : visit(g.V(), false), costes(costee), minimo(0) {
        for (int i = 0; i < g.V();i++) {
            if (!visit[i]) {
                minimo += dfs(g, i);
             }
        }
        
    }

    int minimo_coste() const {
        return minimo;
    }

private:
    int dfs(Grafo const& g, int v) {
        visit[v] = true;
        int coste = costes[v];
        for (int w : g.ady(v)) {
            if (!visit[w]) {
                coste += dfs(g, w);
            }
        }
        return coste;
    }
};

bool resuelveCaso() {
    int n;
    cin >> n;

    if (!std::cin)  // fin de la entrada
        return false;

    int m;
    cin >> m;
    vector<int> costes(n);

    for (int i = 0; i < n; i++) {
        cin >> costes[i];
    }

    Grafo g(n);
    for (int i = 0; i < m; i++) {
        int ini, fin;
        cin >> ini >> fin;
        ini--;
        fin--;
        g.ponArista(ini, fin);
       
    } 

    sort(costes.begin(), costes.end());
    MinimoCosteRumor minimoCosteRumor(g, costes);
    cout << minimoCosteRumor.minimo_coste() << "\n";
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
