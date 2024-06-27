/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra Gonzalez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <stack>
#include "Matriz.h"

using namespace std;

/*@ <answer>
 *
 * La solución utiliza programación dinámica para calcular la máxima cantidad
 * de oro que se puede recuperar dentro del tiempo permitido. Se emplea una
 * matriz de memoización para almacenar los resultados parciales y evitar
 * cálculos redundantes. El coste de la solución es O(N*T), donde N es el
 * número de cofres y T es el tiempo disponible.
 *
 *@ </answer> */

 // Estructura para almacenar la información de cada tesoro
struct tTesoro {
    int profundidad;
    int oros;

    tTesoro() { }

    tTesoro(int p, int o) : profundidad(p), oros(o) { }
};

// Función recursiva con memoización para calcular el máximo oro recuperable
int maxi_oro(int i, int tiempoRestante, vector<tTesoro> const& tesoros, Matriz<int>& m) {
    if (i == 0 || tiempoRestante == 0) {
        return 0;
    }
    if (m[i][tiempoRestante] != -1) {
        return m[i][tiempoRestante];
    }

    int p = tesoros[i - 1].profundidad;
    int o = tesoros[i - 1].oros;
    int tiempo = 3 * p;

    if (tiempo > tiempoRestante) {
        m[i][tiempoRestante] = maxi_oro(i - 1, tiempoRestante, tesoros, m);
    }
    else {
        m[i][tiempoRestante] = max(
            maxi_oro(i - 1, tiempoRestante, tesoros, m),
            maxi_oro(i - 1, tiempoRestante - tiempo, tesoros, m) + o
        );
    }

    return m[i][tiempoRestante];
}

// Función que resuelve un caso del problema
bool resuelveCaso() {

    // leer los datos de la entrada
    int T;
    cin >> T;

    if (!cin)  // fin de la entrada
        return false;

    int N;
    cin >> N;

    vector<tTesoro> tesoros(N);
    for (int i = 0; i < N; i++) {
        int p, o;
        cin >> p >> o;
        tesoros[i] = tTesoro(p, o);
    }

    // Inicializar la matriz para la programación dinámica con -1
    Matriz<int> m(N + 1, T + 1, -1);

    // Calcular el máximo oro recuperable
    int maxOro = maxi_oro(N, T, tesoros, m);

    // Reconstruir la solución
    stack<int> recover;
    int tiempoRestante = T;
    for (int i = N; i > 0; --i) {
        if (m[i][tiempoRestante] != m[i - 1][tiempoRestante]) {
            recover.push(i - 1);
            tiempoRestante -= 3 * tesoros[i - 1].profundidad;
        }
    }

    // Imprimir la solución
    cout << maxOro << endl;
    cout << recover.size() << endl;
    while (!recover.empty()) {
        cout << tesoros[recover.top()].profundidad << " " << tesoros[recover.top()].oros << endl;
        recover.pop();
    }
    cout << "---" << endl;

    return true;
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

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
