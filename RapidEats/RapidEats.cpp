
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
    IndexPQ<Valor> pq;
    int numVertices;
public:

    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig), numVertices(g.V()),
        dist(g.V(), INF), pq(g.V()) {
        dist[origen] = 0;
       
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
           
        }
       
    }
};


bool resuelveCaso() {

    // leer los datos de la entrada
    int n; cin >> n; 

    if (!std::cin)  // fin de la entrada
        return false;

    int c; cin >> c;
    DigrafoValorado<int> g(n);
    for (int i = 0; i < c;i++) {
        int ini, fin, coste;
        cin >> ini >> fin >> coste;
        AristaDirigida<int> a(ini - 1, fin - 1, coste);
        AristaDirigida<int> noA(fin - 1, ini - 1, coste);

        g.ponArista(a);
        g.ponArista(noA);

    }

    int k; cin >> k;
    for (int i = 0; i < k;i++) {
        int origen, destino;
        cin >> origen >> destino;
        Dijkstra<int> sol(g, origen-1);
        if (sol.distancia(destino-1) == sol.getINF()) {
            cout << "NO LLEGA\n";
        }
        else cout << sol.distancia(destino-1) << "\n";
       
    }
    cout << "---\n";
    // resolver el caso posiblemente llamando a otras funciones

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
