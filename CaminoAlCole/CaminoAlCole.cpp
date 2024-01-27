
/*@ <answer>
 *
 * Nombre y Apellidos:
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "DigrafoValorado.h"  // propios o los de las estructuras de datos de clase
#include "IndexPQ.h"

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

template <typename Valor>
class Dijkstra {
private:
    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    std::vector<int> num_caminos;
    IndexPQ<Valor> pq;
    int numVertices;
public:

    int numCaminos(int v) const { return num_caminos[v]; }

    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig), numVertices(g.V()),
        dist(g.V(), INF), pq(g.V()), num_caminos(g.V(), 0) {
        dist[origen] = 0;
        num_caminos[origen] = 1;
        pq.push(origen, 0);
        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }
    
    Valor distancia(int v) const { return dist[v]; }

    int getINF() const { return INF; }

  

private:
    
    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = dist[v] + a.valor();
            pq.update(w, dist[w]);
            num_caminos[w] = num_caminos[v];
        }
        else if (dist[w] == dist[v] + a.valor()) {
            num_caminos[w] += num_caminos[v];
        }
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada
    int n; cin >> n;

    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<int> g(n);
    int c; cin >> c;
    for (int i = 0; i < c; i++) {
        int ini, fin, coste;
        cin >> ini >> fin >> coste;
        AristaDirigida<int> a(ini - 1, fin - 1, coste);

        AristaDirigida<int> noA(fin - 1, ini - 1, coste);
        g.ponArista(a);
        g.ponArista(noA);
    }

    Dijkstra<int> sol(g, 0);
   
    cout << sol.numCaminos(g.V()-1) << "\n";
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
