
/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra González
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <vector>
#include "GrafoValorado.h"  // propios o los de las estructuras de datos de clase

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

class Reparto {
private:
    bool cabe;
    vector<bool> visit;
public:


    Reparto(const GrafoValorado <int> & g, int origen,  int destino, int anchuraMax): cabe(false) ,visit(g.V(), false) {
        dfs(g,origen, anchuraMax);
        this->cabe = (visit[destino]) ? true : false;
    }

    // visita los nodos alcanzables desde v respetando el umbral
    void dfs(GrafoValorado<int> const& G, int v, int umbral) {
        visit[v] = true;
        for (auto a : G.ady(v)) {
            if (a.valor() >= umbral) {
                int w = a.otro(v);
                if (!visit[w])
                    dfs(G, w, umbral);
            }
        }
    }

    bool cabeElCamion() const {
        return this->cabe;
    }
};

bool resuelveCaso() {

    // leer los datos de la entrada
    int v; cin >> v; int eAristas; cin >> eAristas;

    if (!std::cin)  // fin de la entrada
        return false;

    GrafoValorado<int> g(v);

    for (int i = 0; i < eAristas;i++) {
        int desde, hasta, valor; cin >> desde >> hasta >>valor;
        Arista<int> a(desde-1, hasta-1, valor);
        Arista<int> noA(hasta - 1, desde - 1, valor);
        g.ponArista(a);
        g.ponArista(noA);
    }

    int kCON; cin >> kCON;

    for (int i = 0; i < kCON;i++) {
        int origen=0, destino=0, anchuraCamioneta = 0;
        cin >> origen >> destino >> anchuraCamioneta;

        // resolver el caso posiblemente llamando a otras funciones
        Reparto r(g, origen-1, destino-1, anchuraCamioneta);

        // escribir la solución
        if (r.cabeElCamion()) cout << "SI\n";
        else cout << "NO\n";
    }
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
