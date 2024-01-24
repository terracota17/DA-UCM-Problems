
/*@ <answer>
 *
 * Nombre y Apellidos: Javier Parra González
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include "Grafo.h"
#include <vector>
#include <queue>

using namespace std;

/*@ <answer

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>

struct Consulta {
    int origen, ttl;
    Consulta(){}
    Consulta(int origen, int ttl) : origen(origen), ttl(ttl) {}
};



class NodoLejano {
private:
    int kConsultas;
    int nNodos;
    int visitados = 0;;
    vector<bool> visit;
    vector<int> ant;
    vector<int> dist;
    vector<Consulta> con;
    
public:
    
    NodoLejano(const Grafo& g, const int kCon, vector<Consulta> consultas, int n) : visit(g.V(), false), ant(g.V()),  dist(g.V()), kConsultas(kCon), con(consultas), nNodos(n) {}

   
    // O(V + A)
    void bfs(Grafo const& g, Consulta& con) {
        std::queue<int> q;
        dist[con.origen] = 0; visit[con.origen] = true;
        q.push(con.origen);
        while (!q.empty()) {
            int v = q.front(); q.pop();
            for (int w : g.ady(v)) {
                if (!visit[w]) {
                    ant[w] = v; dist[w] = dist[v] + 1; visit[w] = true;
                    q.push(w);
                }
            }
        }
    }


    void reset() {
        std::fill(dist.begin(), dist.end(), 0);
        std::fill(ant.begin(), ant.end(), 0);
        std::fill(visit.begin(), visit.end(), 0);
    }

    void printSol(const Grafo& g) {
        for (int i = 0; i < kConsultas; i++) {
            bfs(g, con[i]);
            int unreachableNodes = 0;
            for (int j = 0; j < nNodos; j++) {
                if (!visit[j] || dist[j] > con[i].ttl) {
                    unreachableNodes++;
                }
            }
            cout << unreachableNodes << "\n";
            reset();
        }
        cout << "---\n";
    }

};


bool resuelveCaso() {

    // leer los datos de la entrada
    int n, c; cin >> n >> c;
    
    if (!cin) return false;
    
    Grafo g(n);

    for (int i = 0; i < c; i++) {
        int ini, fin; cin >> ini >> fin;
        g.ponArista(ini - 1, fin - 1);
    }

    int kConsultas; cin >> kConsultas;
    vector<Consulta> consultas(kConsultas);
    for (int i = 0; i < kConsultas; i++) {
        int origen, ttl; cin >> origen >> ttl;
        consultas[i] = Consulta(origen-1, ttl);
    }


    // resolver el caso posiblemente llamando a otras funciones
    NodoLejano sol(g, kConsultas, consultas, n);
    // escribir la solución
    sol.printSol(g);
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

    while (resuelveCaso()){}

    // para dejar todo como estaba al principio
#ifndef DOMJUDGE
    std::cin.rdbuf(cinbuf);
    system("PAUSE");
#endif
    return 0;
}
