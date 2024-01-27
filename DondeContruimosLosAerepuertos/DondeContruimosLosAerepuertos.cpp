
/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra González
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"

using namespace std;
template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    int numAereo;

public:
    Valor costeARM() const {
        return coste;
    }

    int numAerepuertos() const { return this->numAereo; }
    

    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }

    ARM_Kruskal(GrafoValorado<Valor> const& g, Valor costoAeropuerto) : coste(0), numAereo(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());

        while (!pq.empty()) {
            auto a = pq.top();
            pq.pop();
            int v = a.uno();
            int w = a.otro(v);

            if (!cjtos.unidos(v, w)) {
                // Verificar si construir un aeropuerto sería más barato que agregar la arista
                if (a.valor() >= costoAeropuerto) {
                    numAereo++;
                }
                else {
                    _ARM.push_back(a);
                    coste += a.valor();
                }

                cjtos.unir(v, w);

                if (_ARM.size() == g.V() - 1) {
                    break;
                }
            }
        }

        this->numAereo += cjtos.num_cjtos();
    }
};

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

bool resuelveCaso() {

    // leer los datos de la entrada
    int localidades; cin >> localidades;
    int m; cin >> m; int coste; cin  >> coste;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(localidades);
    for (int i = 0; i < m; i++) {
        int ini, fin, coste;
        cin >> ini >> fin >> coste;
        Arista<int> a(ini - 1, fin - 1, coste);
      
        g.ponArista(a);
       
    }

    // resolver el caso posiblemente llamando a otras funciones
    ARM_Kruskal<int> sol(g, coste);
    cout << sol.costeARM() + (coste * sol.numAerepuertos()) << " " << sol.numAerepuertos() << "\n";
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
