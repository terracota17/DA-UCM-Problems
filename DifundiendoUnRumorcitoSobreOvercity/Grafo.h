using Adys = std::vector<int>; // lista de adyacentes a un vértice
class Grafo {
private:
	int _V; // número de vértices
	int _A; // número de aristas
	std::vector<Adys> _ady; // vector de listas de adyacentes
public:
	Grafo(int V) : _V(V), _A(0), _ady(_V) {}
	int V() const { return _V; }
	int A() const { return _A; }	void ponArista(int v, int w) {
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