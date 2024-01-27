
/*@ <answer>
 *
 * Nombre y Apellidos: Javier Parra Gonzalez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <climits>
using namespace std;

#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "ConjuntosDisjuntos.h"
#include "PriorityQueue.h"
/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

template <typename Valor>
class ARM_Kruskal {
private:
    std::vector<Arista<Valor>> _ARM;
    Valor coste;
    int num_cjtos;
    int minimo;
public:
    
    int disjunto() {
        return this->num_cjtos;
    }
    int mini() {
        return this->minimo;
    }

    Valor costeARM() const {
        return coste;
    }
    std::vector<Arista<Valor>> const& ARM() const {
        return _ARM;
    }
    ARM_Kruskal(GrafoValorado<Valor> const& g) : coste(0), num_cjtos(0), minimo(0) {
        PriorityQueue<Arista<Valor>> pq(g.aristas());
        ConjuntosDisjuntos cjtos(g.V());
        while (!pq.empty()) {
            auto a = pq.top(); pq.pop();
            int v = a.uno(), w = a.otro(v);
            if (!cjtos.unidos(v, w)) {
                cjtos.unir(v, w);
             
                _ARM.push_back(a);
                coste = a.valor();
                minimo = max(minimo, coste);
                if (_ARM.size() == g.V() - 1) break;
            }
        }

        this->num_cjtos = cjtos.num_cjtos();
    }
};

void resuelveCaso() {

    // leer los datos de la entrada
    int n; cin >> n;
    int m; cin >> m;

    GrafoValorado<int> g(n);
    for (int i = 0; i < m;i++) {
        int ini, fin, coste;
        cin >> ini >> fin >> coste;
        Arista<int> a(ini-1, fin-1, coste);
        Arista<int> noa(fin-1, ini-1, coste);
        g.ponArista(a);
        g.ponArista(noa);
    }
    // resolver el caso posiblemente llamando a otras funciones
    ARM_Kruskal<int> sol(g);
    // escribir la solución
    if (sol.disjunto() > 1) {
        cout << "Imposible\n";
    }
    else
        cout << sol.mini() << "\n";
   
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
