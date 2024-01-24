/*@ <answer>
 *
 * Nombre y Apellidos: Javier Parra Gonzalez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
using namespace std;
using lli = long long int;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


int num_formas(int i, int C) {
    int n = i;
    Matriz<lli> nf(n + 1, C + 1, 0);
    nf[0][0] = 1;
    for (int i = 1; i <= n; ++i) {
        nf[i][0] = 1;
        for (int j = 1; j <= C; ++j)
            nf[i][j] = nf[i - 1][j] + nf[i - 1][j - i];
    }
    return nf[n][C];
}


void resuelveCaso() {

    // leer los datos de la entrada
    int n, C;
    cin >> n >> C;
    // resolver el caso posiblemente llamando a otras funciones
    cout << num_formas(n, C) << "\n";
    // escribir la solución
}

//@ </answer>
//  Lo que se escriba dejado de esta línea ya no forma parte de la solución.

int main() {
    // ajustes para que cin extraiga directamente de un fichero
#ifndef DOMJUDGE
    std::ifstream in("casos.txt");
    auto cinbuf = std::cin.rdbuf(in.rdbuf());
#endif

    int numCasos;
    std::cin >> numCasos;
    for (int i = 0; i < numCasos; ++i)
        resuelveCaso();

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
