#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;


/*Comentario explicando la solucion:

He utilizado la clase Grafo explicada en clase para representar en memoria los grafos correspondientes a los casos de uso del ejercicio (de esta clase no he modificado nada)

Además he creado un struct llamado tCoste para representar el par [id, coste] donde id es el id de cada vertices posible de grafo y, el coste es el coste que significaraia contarle el rumor a la 
persona i esima de tal forma que he guardado en un monticulo de minimos, todos los costes que aparecen en lso casos de uso con su respectivo id de la persona que le corresponde aquel coste.

Como se pide minimizar el coste, he optado por una cola de minimo de la stl, para que se garantice que siempre se escogera contar el rumor a aquella persona que tiene menor coste.

La solucion al problema consiste en i cogiendo en que menos coste nos suponga y contarle el rumor, deseando asi que esta persona se bien conocida por todo Overcity y lleguemos a finalizar 
cuanto antes la resolucion del problema.

Coste : O(V * (V + A)), donde V es en numero de vertices y A el de aristas del grafo.

*/

using Adys = std::vector<int>; // lista de adyacentes a un vértice
class Grafo {
private:
	int _V; // número de vértices
	int _A; // número de aristas
	std::vector<Adys> _ady; // vector de listas de adyacentes
public:
	Grafo(int V) : _V(V), _A(0), _ady(_V) {}
	int V() const { return _V; }
	int A() const { return _A; }
	void ponArista(int v, int w) {
		if (v < 0 || v >= _V || w < 0 || w >= _V)
			throw std::domain_error("Vertice inexistente");
		++_A;
		_ady[v].push_back(w);
		_ady[w].push_back(v);
	}
	Adys const& ady(int v) const {
		if (v < 0 || v >= _V)
			throw std::domain_error("Vertice inexistente");
		return _ady[v];
	}
};

struct tCoste {
    int id;
    int coste;

    tCoste(int id, int coste) : id(id), coste(coste) {}

    // Operador de comparación para ordenar en la cola de prioridad
    bool operator>(const tCoste& other) const {
        return coste > other.coste;
    }
};

class DifundiendoRumor {
private:
	vector<bool> visit;
	priority_queue<tCoste, vector<tCoste>, greater<tCoste>> cola_min;
	int min_coste = 0;


public:
	//O(V + A)
	void dfs(Grafo const& G, int v) {
		visit[v] = true;
		for (int w : G.ady(v)) {
			if (!visit[w]) {
				dfs(G, w);
			}
		}
	}

	DifundiendoRumor(Grafo const& g, priority_queue<tCoste, vector<tCoste>, greater<tCoste>> cola_min) : visit(g.V(), false), cola_min(cola_min), min_coste(0) {
		for (int i = 0; i < g.V(); i++) {
			tCoste top = cola_min.top(); 
			cola_min.pop(); 
			if (!visit[top.id]) {
				dfs(g, top.id); 
				min_coste += top.coste;
			}
		}

	}

	int coste() const {
		return this->min_coste;
	}
};

bool resuelveCaso() {

	// leer los datos de la entrada
	int n; int m;
	cin >> n;
	if (!std::cin)  // fin de la entrada
		return false;
	cin >> m;

	priority_queue<tCoste, vector<tCoste>, greater<tCoste>> cola_min;
	//cola de minimos config
	for (int i = 0; i < n; i++) {

		int coste; cin >> coste;
		tCoste a = tCoste(i, coste);
		cola_min.push(a); 
	}

	Grafo g(n);
	for (int i = 0; i < m; i++) {
		int ini, fin;
		cin >> ini;
		cin >> fin;
		g.ponArista(ini - 1, fin - 1);
	}

	// resolver el caso posiblemente llamando a otras funciones
	DifundiendoRumor sol(g, cola_min);
	// escribir la solución
	cout << sol.coste() << "\n";
	return true;
}


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
