
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "EnterosInf.h"
#include "Matriz.h"

using namespace std;

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


bool tiradas_v(const int N, const int S, const vector<EntInf> &tiradas, const vector<int> &s) {

    tiradas[0] = 0;
    
    for (int i = 1; i <= S;i++) {
        //se coge;
        for (int j = s[i]; j <= N; j++) {
            tiradas[j] = min(tiradas[j], tiradas[j - s[i]] + 1);
        }
    }


    return (tiradas[S][N] < Infinito);


}

bool resuelveCaso() {

    // leer los datos de la entrada
    int objetivo; cin >> objetivo;
    if (!std::cin)  // fin de la entrada
        return false;

    int s; cin >> s;
    // resolver el caso posiblemente llamando a otras funciones

    vector<int> sectores;
    for (int i = 0; i < s; i++) {
        cin >> sectores[i];
    }

    vector<EntInf> m = { Infinito };
    // escribir la solución

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
