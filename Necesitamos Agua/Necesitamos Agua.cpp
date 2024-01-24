
/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra Gonzalez && Nestor Marin Gomez
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include "DigrafoValorado.h"
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
public:
    Dijkstra(DigrafoValorado<Valor> const& g, int orig) : origen(orig),
        dist(g.V(), INF), pq(g.V()) {

        dist[origen] = 0;
        pq.push(origen, 0);

        while (!pq.empty()) {
            int v = pq.top().elem; pq.pop();
            for (auto a : g.ady(v))
                relajar(a);
        }
    }


    bool hayCamino(int v) const { return dist[v] != INF; }

    Valor distancia(int v) const { return dist[v]; }

private:

    const Valor INF = std::numeric_limits<Valor>::max();
    int origen;
    std::vector<Valor> dist;
    IndexPQ<Valor> pq;

    void relajar(AristaDirigida<Valor> a) {
        int v = a.desde(), w = a.hasta();
        if (dist[w] > dist[v] + a.valor()) {
            dist[w] = (dist[v] + a.valor());
            pq.update(w, dist[w]);
        }
    }
};


struct tParejas {
    long long int i, dif, menor, mayor;
    tParejas() {}
    tParejas(long long int i, long long int d, long long int menor, long long int mayor) : i(i), dif(d), menor(menor), mayor(mayor) {}

    bool operator<(tParejas  const& p1) {
        return (dif > p1.dif);
    }
};



bool resuelveCaso() {

    // leer los datos de la entrada
    int nPueblos, mCarreteras;
    cin >> nPueblos >> mCarreteras;
    if (!std::cin)  // fin de la entrada
        return false;

    DigrafoValorado<long long int> g(nPueblos);


    for (int i = 0; i < mCarreteras; i++) {
        int origen, destino, coste;
        cin >> origen >> destino >> coste;
        AristaDirigida<long long int> a(origen - 1, destino - 1, coste);
        AristaDirigida<long long int> noa(destino - 1, origen - 1, coste);
        g.ponArista(a);
        g.ponArista(noa);
    }

    Dijkstra<long long int> sol(g, 0); //norte
    Dijkstra<long long int> sol1(g, nPueblos - 1); //sur


    int a = 0;


    vector<tParejas> parejas(nPueblos - 2);
    for (int i = 0; i < parejas.size(); i++) {
        long long int dif = abs(sol1.distancia(i + 1) - sol.distancia(i + 1));
        long long int menor, mayor;
        menor = min(sol1.distancia(i + 1), sol.distancia(i + 1));
        mayor = max(sol1.distancia(i + 1), sol.distancia(i + 1));
        tParejas p(i + 1, dif, menor, mayor);
        parejas[i] = (p);

    }

    sort(parejas.begin(), parejas.end());
    long long int contN = (nPueblos / 2) - 1, contS = (nPueblos / 2) - 1;
    long long int suma = 0;

    for (int i = 0; i < parejas.size(); i++) {
        int dist = min(parejas[i].mayor, parejas[i].menor);
        bool norte = (dist == sol.distancia(parejas[i].i) && contN > 0);
        bool sur = (dist == sol1.distancia(parejas[i].i)) && contS > 0;

        if (sur) {
            //sur
            contS--;
            suma += dist;
        }
        else if (norte) {
            //norte
            contN--;
            suma += dist;
        }
        else {
            //cuando ambos son false
            if (contS > 0) {
                //va pal sur
                //norte
                contS--;
                suma += (sol1.distancia(parejas[i].i));
            }
            else if(contN > 0 ) {
                //norte
                contN--;
                suma += (sol.distancia(parejas[i].i));;
                
            }
        }

    }

    // resolver el caso posiblemente llamando a otras funciones

    std::cout << suma  * 2<< "\n";
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
