#include <iostream>
#include <fstream>
#include "IndexPQ.h"
#include <vector>

using namespace std;

bool resuelveCaso() {
    int N, P;

    cin >> N >> P;

    if (N == 0 && P == 0) {
        return false;
    }

    IndexPQ<int, std::greater<int>> mayores(100000); // Cola de prioridad para los pájaros mayores
    IndexPQ<int, less<int>> jovenes(100000); // Cola de prioridad para los pájaros jóvenes

    vector<int> edades(N); // Crear un vector del tamaño adecuado

    for (int i = 0; i < N; ++i) {
        cin >> edades[i];

        if (i < N / 2) {
            jovenes.push(i, edades[i]);
        }
        else {
            mayores.push(i, edades[i]);
        }
    }

    vector<int> resultados;
    resultados.reserve(P);

    for (int i = 0; i < P; ++i) {
        int nueva_edad;
        cin >> nueva_edad;

        if (nueva_edad > mayores.top().prioridad) {
            // Reemplazar el pájaro mayor por el nuevo pájaro
            int viejo = mayores.top().elem;
            mayores.pop();
            mayores.push(viejo, nueva_edad);
        }
        else if (nueva_edad < jovenes.top().prioridad) {
            // Reemplazar el pájaro joven por el nuevo pájaro
            int joven = jovenes.top().elem;
            jovenes.pop();
            jovenes.push(joven, nueva_edad);
        }

        // El pájaro que ocupa la punta es el de mayor edad
        resultados.push_back(mayores.top().prioridad);
    }

    // Imprimir los resultados
    for (int i = 0; i < P; ++i) {
        cout << resultados[i];
        if (i < P - 1) {
            cout << ' ';
        }
    }
    cout << endl;

    return true;
}

int main() {
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    while (resuelveCaso());

#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
