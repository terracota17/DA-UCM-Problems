
/*@ <answer>
 *
 * Nombre y Apellidos: Néstor Márin Gómez DA42 && Javier Parra González DA45
 *
 *@ </answer> */

#include <iostream>
#include <fstream>
#include <deque>
#include <vector>
using namespace std;

#include "Digrafo.h"  // propios o los de las estructuras de datos de clase

/*@ <answer>

 Escribe aquí un comentario general sobre la solución, explicando cómo
 se resuelve el problema y cuál es el coste de la solución, en función
 del tamaño del problema.

    Hemos creado una clase CicloDirigido, añadiendo un atributo privado vertices, para saber el num de vertices que contiene el grafo dirigido.
    Hemos modificado el contructor de la clase mencionada anteriormente, para saber si haciendo una llamada desde la linea 0 (vertice 0) del progrmama, se llegaba al final del programa.
    Hemos modificado la llamada dfs, para que cuando detectase un ciclo no terminara la llamada del algoritmo dfs.

    Hemos añadido a la clase, una nueva operacion llamada visitadoUlt() que nos devuelve si el ultimo vertices o ultima linea ha sida visitada.

    A la hora de leer los datos de entrada, creamos un grafo dirigido que contiene el numero de (lineas + 1 , vertices + 1).
    Segun el tipo de intruccion leida, creamos las ariatas entre los vertices.

    Finalmente creamos una instacnia de la clase para resolver el problema, y comprobamos si hay ciclo y se ha llegado al final o no.

    Coste : O(lineas) + O(vertices + aristas) = O(vertices + aristas)

 @ </answer> */


 // ================================================================
 // Escribe el código completo de tu solución aquí debajo
 // ================================================================
 //@ <answer>


class CicloDirigido {
    using Camino = deque<int>;

public:

    CicloDirigido(Digrafo const& g, int ver) : visit(g.V(), false), ant(g.V()), apilado(g.V(), false), hayciclo(false), vertices(ver) {
        dfs(g, 0);  //O(v+A) siendo V el num de vertices y a el num de aristas
    }

    bool hayCiclo() const { return hayciclo; }
    Camino const& ciclo() const { return _ciclo; }

    bool visitadoUlt() const { //O(1)
        return visit[this->vertices - 1];
    }

private:
    int vertices;
    std::vector<bool> visit; // visit[v] = ¿se ha alcanzado a v en el dfs? 
    std::vector<int>  ant;
    std::vector<bool> apilado;

    Camino _ciclo;

    bool hayciclo;

    //O(Vertices + aristas)
    void dfs(Digrafo const& g, int v) {
        apilado[v] = true;
        visit[v] = true;
        for (int w : g.ady(v)) {

            if (!visit[w]) {
                ant[w] = v; dfs(g, w);
            }
            else if (apilado[w]) {
                hayciclo = true;
                for (int x = v; x != w; x = ant[x]) _ciclo.push_front(x); _ciclo.push_front(w); _ciclo.push_front(v);
            }
        } apilado[v] = false;
    }


};


bool resuelveCaso() {

    // leer los datos de la entrada
    int lineas; cin >> lineas;

    if (!std::cin)  // fin de la entrada
        return false;


    Digrafo g(lineas + 1); //O(1)
    int i = 0;
    //O(lineas) siendo lineas el numero de lineas
    while (i < lineas) {
        char tipo; int salto;
        cin >> tipo;
        if (tipo == 'A') {
            g.ponArista(i, i + 1); //O(1)
        }
        else if (tipo == 'J') {
            cin >> salto;
            g.ponArista(i, salto - 1); //O(1)
        }
        else if (tipo == 'C') {
            cin >> salto;
            g.ponArista(i, salto - 1); //O(1)
            g.ponArista(i, i + 1); //O(1)
        }

        i++;
    }

    // resolver el caso posiblemente llamando a otras funciones
    CicloDirigido ciclo(g, lineas + 1); //O(v+A)

    // escribir la solución
    if (!ciclo.visitadoUlt()) {
        cout << "NUNCA" << "\n";
    }
    else {
        if (ciclo.hayCiclo() && ciclo.visitadoUlt()) {
            cout << "A VECES" << "\n";
        }else if(!ciclo.hayCiclo() && ciclo.visitadoUlt())
            cout << "SIEMPRE" << "\n";
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
