
/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra Gonzalez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>

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

int invernalia_rec(int i, int j, vector<int>  const& carros, vector<int> const& caminos, Matriz<int> const& calidades, Matriz<int>& sol) {

    if (sol[i][j] != -1) //sub problema ya resuelto
        return sol[i][j];

    //caso base
    if (i == 0 || j == 0) sol[i][j] = 0;
    else if (carros[i-1] > caminos[j-1]) {
        sol[i][j] = invernalia_rec(i - 1, j,carros, caminos, calidades, sol);
    }
    else {
        sol[i][j] = max(invernalia_rec(i - 1, j, carros, caminos, calidades, sol),
            invernalia_rec(i, j - 1,carros, caminos, calidades, sol) + calidades[i-1][j-1]);
    }


    return sol[i][j];
}

void resuelveCaso() {


    int n; cin >> n;
    int m; cin >> m;

    // leer los datos de la entrada
    vector<int> carros(n), caminos(m);
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < n; i++) {
        cin >> carros[i];
    }

    for (int i = 0; i < m; i++) {
        cin >> caminos[i];
    }

    Matriz<int> calidades(n,m,0);
    Matriz<int> sol(n + 1, m + 1, -1);
    // resolver
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> calidades[i][j];
        }
    }

    // escribir la solución
    cout << invernalia_rec(n,m,carros, caminos,calidades,sol) << "\n";
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
