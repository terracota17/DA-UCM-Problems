
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

//#include "..."  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

int nosInvadenVoraz(vector<int> const& atacantes, vector<int> const& defensas, int n) {
    int batallasGanadas = 0;


    int i = 0; // Índice para recorrer la lista de atacantes
    int j = 0; // Índice para recorrer la lista de defensas

    while (i < n && j < n) {
        if (defensas[j] >= atacantes[i]) {
            // Puedes garantizar la victoria en esta ciudad
            batallasGanadas++;
            i++; // Pasamos a la siguiente ciudad invadida
        }
        j++; // Pasamos al siguiente equipo de defensa
    }

    return batallasGanadas;
}


bool resuelveCaso() {

    // leer los datos de la entrada
    int n; cin >> n;

    if (!std::cin)  // fin de la entrada
        return false;
    vector<int> atacantes(n);
    vector<int> defensas(n);
    for (int i = 0; i < n; i++) {
        cin >> atacantes[i];
    }

    for (int i = 0; i < n; i++) {
        cin >> defensas[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    sort(atacantes.begin(), atacantes.end());
    sort(defensas.begin(), defensas.end(), );
    // escribir la solución
    cout << nosInvadenVoraz(atacantes, defensas, n) <<"\n";
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