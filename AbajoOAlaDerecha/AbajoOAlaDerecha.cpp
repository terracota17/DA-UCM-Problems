
/*@ <answer>
 *
 * Nombre y Apellidos: Nestor Marin Gomez DA42 && Javier Parra Gonzalez DA45
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
using namespace std;
using lli = long long int;

#include "Matriz.h"  // propios o los de las estructuras de datos de clase
#include "EnterosInf.h"

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

num_formas(entrada, i, j) devuevle el numero de formas de llear desde i j, hasta la posicion (n, m) siendo n en num de filas y m =el num de columnas

 Ecuacion de recurencia: num_formas(const  Matriz <lli>& entrada, int i, int j)

    //Caso base:
        1 si i = n && j == m

    //Caso recurisivo

        num_formas(entrada, i, j) = num_formas(entrada,i+entrada[i][j], j) + num_formas(entrada, i, j + entrada[i][j]);



        //Coste cuadratico = O(n * m ) siendo n el num de filas y m el numero de columnas, porque se rellena la tabla solucion de n,m

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


lli num_formas(const  Matriz <lli>& entrada, int i, int j) {

    lli nn = entrada.numfils(); lli mm = entrada.numcols();
    Matriz<lli> sol(nn, mm, 0);

    for (lli i = nn - 1; i >= 0; i--) {
        for (lli j = mm - 1; j >= 0; j--) {
            lli abajo, derecha;
            if (nn - 1 == i && mm - 1 == j) { //Caso base
                sol[nn - 1][mm - 1] = 1;
            }
            else { //caso recursivo
                abajo = i + entrada[i][j];
                derecha = j + entrada[i][j];
                if (derecha < mm) {
                    sol[i][j] = sol[i][derecha];
                }

                if (abajo < nn) {
                    sol[i][j] += sol[abajo][j];
                }
            }

        }
    }

    return sol[0][0];

}


bool resuelveCaso() {

    // leer los datos de la entrada
    int n, m;
    cin >> n;
    if (!std::cin)  // fin de la entrada
        return false;
    cin >> m;

    Matriz<lli> matrizEntrada(n, m);
    // resolver el caso posiblemente llamando a otras funciones
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int num; cin >> num;
            matrizEntrada[i][j] = num;
        }
    }

    cout << num_formas(matrizEntrada, 0, 0) << "\n";
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
