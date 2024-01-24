
/*@ <answer>
 *
 * Nombre y Apellidos:Javier Parra González
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>

using namespace std;

#include "DiGrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class CicloDirigido {
    using Camino = std::deque<int>;
private:
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs?
    std::vector<int> ant; // ant[v] = vértice anterior en el camino a v
    std::vector<bool> apilado; // apilado[v] = ¿está el vértice v en la pila?
    Camino _ciclo; // ciclo dirigido (vacío si no existe)
    bool hayciclo;

    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {
            if (hayciclo) // si hemos encontrado un ciclo terminamos
                return;
            if (!visit[w]) { // encontrado un nuevo vértice, seguimos
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) { // hemos detectado un ciclo
                // se recupera retrocediendo
                hayciclo = true;
                for (int x = v; x != w; x = ant[x])
                    _ciclo.push_front(x);
                _ciclo.push_front(w); _ciclo.push_front(v);
            }
        }
        apilado[v] = false;
    }

public:
    CicloDirigido(Digrafo const& g) : visit(g.V(), false), ant(g.V()),
        apilado(g.V(), false), hayciclo(false) {
        for (int v = 0; v < g.V(); ++v)
            if (!visit[v])
                dfs(g, v);
    }

    bool hayCiclo() const { return hayciclo; }
    Camino const& ciclo() const { return _ciclo; }

};


class Ordenando {
private:
    class OrdenTopologico {
    public:
        // g es DAG
        OrdenTopologico(Digrafo const& g) : visit(g.V(), false) {
            for (int v = 0; v < g.V(); ++v)
                if (!visit[v])
                    dfs(g, v);
        }

        // devuelve la ordenación topológica
        std::deque<int> const& orden() const {
            return _orden;
        }

    private:
        std::vector<bool> visit;
        std::deque<int> _orden; // ordenación topológica
        void dfs(Digrafo const& g, int v) {
            visit[v] = true;
            for (int w : g.ady(v))
                if (!visit[w])
                    dfs(g, w);
            _orden.push_front(v);
        }
    };

    vector<bool> visit;
    OrdenTopologico ordenT;

public:

    Ordenando(Digrafo const & g) : visit(g.V(), false), ordenT(g) {}

    deque<int> const& ordenTopologico() const {
        return this->ordenT.orden();
    }

};

bool resuelveCaso() {

    // leer los datos de la entrada
    
    int numTareas; cin >> numTareas; //1...N
    int m; cin >> m;
    
    if (!std::cin)  // fin de la entrada
        return false;

    Digrafo g(numTareas);

    for (int i = 0; i < m;i++) {
        int ini, fin; cin >> ini >> fin;
        g.ponArista(ini-1,fin-1);
    }

    // resolver el caso posiblemente llamando a otras funciones
    //antes hay que comprobar que el grafo no es ACICICILO y es DAG
    CicloDirigido ciclo(g);
    if (ciclo.hayCiclo()) cout << "Imposible" << "\n";
    else {
        Ordenando sol(g);
        // escribir la solución
        for (int w : sol.ordenTopologico()) {
            cout << w  + 1 <<  " ";
        }
        cout << "\n";
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
