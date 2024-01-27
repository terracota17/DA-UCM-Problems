#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
using namespace std;

int tallaje(vector<int> const& tallas_jug, vector<int> const& tallas_actuales) {
    int sol = 0;
    int i = 0;
    int j = 0;

    while (i < tallas_jug.size() && j < tallas_actuales.size()) {
        if (tallas_actuales[j] >= tallas_jug[i]) {
            i++;
        }
        j++;
    }

    sol = (tallas_jug.size() - i) > 0 ? (tallas_jug.size() - i) : 0;

    return sol;
}

bool resuelveCaso() {
    // leer los datos de la entrada
    int n;
    cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;
    int m;
    cin >> m;
    vector<int> tallas_jug(n);
    for (int i = 0; i < n; i++) {
        cin >> tallas_jug[i];
    }

    vector<int> tallas_actuales(m);
    for (int i = 0; i < m; i++) {
        cin >> tallas_actuales[i];
    }
    sort(tallas_jug.begin(), tallas_jug.end());
    sort(tallas_actuales.begin(), tallas_actuales.end());

    // resolver el caso posiblemente llamando a otras funciones
    cout << tallaje(tallas_jug, tallas_actuales) << "\n";
    // escribir la solución

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
