#include <iostream>
#include <vector>
#include <deque>
#include <fstream>
#include "Matriz.h"  // Asegúrate de tener la implementación correcta de Matriz y EntInf
#include "EnterosInf.h"  // Asegúrate de tener la implementación correcta de EnterosInf

using namespace std;

void Floyd(Matriz<EntInf> const& G, Matriz<EntInf>& C, Matriz<int>& A) {
    int V = G.numfils(); // número de vértices de G
    // inicialización
    C = G;
    A = Matriz<int>(V, V, -1);
    for (int i = 0; i < V; ++i) {
        for (int j = 0; j < V; ++j) {
            if (i != j && G[i][j] != Infinito)
                A[i][j] = i;
        }
    }
    // actualizaciones de las matrices
    for (int k = 0; k < V; ++k) {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                auto temp = C[i][k] + C[k][j];
                if (temp < C[i][j]) { // es mejor pasar por k
                    C[i][j] = temp;
                    A[i][j] = A[k][j];
                }
            }
        }
    }
}

using Camino = std::deque<int>;
Camino ir_de(int i, int j, Matriz<int> const& A) {
    Camino cam;
    while (j != i) {
        cam.push_front(j);
        j = A[i][j];
    }
    cam.push_front(i);
    return cam;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int N;
    cin >> N;

    if (!std::cin)  // fin de la entrada
        return false;

    Matriz<EntInf> G(N, N, Infinito);
    Matriz<EntInf> C;
    Matriz<int> A;

    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            int coste;
            cin >> coste;
            G[i][j] = coste;
        }
    }

    // resolver el caso posiblemente llamando a otras funciones
    Floyd(G, C, A);

    // escribir la solución
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            cout << C[i][j] << " ";
        }
        cout << "\n";
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
