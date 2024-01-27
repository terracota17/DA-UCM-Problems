
/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra González
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

int agujerosVoraz(vector<int> const& agujeros, int l) {
    int numParches = 1;
    int n = agujeros.size();
    int ini = agujeros[0]; // Inicializa 'ini' con la primera posición de agujero

    for (int i = 1; i < n; i++) {
        if (agujeros[i] > ini + l) {
            // Necesitas un nuevo parche para cubrir los agujeros desde 'ini' hasta 'fin'
            numParches++;
            ini = agujeros[i]; // Actualiza 'ini' al último agujero cubierto
        }
    }

    return numParches;
}

bool resuelveCaso() {

    // leer los datos de la entrada
    int n; cin >> n;

    if (!std::cin)  // fin de la entrada
        return false;

    int l; cin >> l;

    vector<int> agujeros(n);
    for (int i = 0; i < n; i++) {
        cin >> agujeros[i];
    }

    // resolver el caso posiblemente llamando a otras funciones
    sort(agujeros.begin(), agujeros.end()); //ordenamos de menor a mayor

    // escribir la solución
    cout << agujerosVoraz(agujeros, l) << "\n";
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
