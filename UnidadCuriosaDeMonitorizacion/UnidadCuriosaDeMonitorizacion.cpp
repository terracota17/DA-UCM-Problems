// UnidadCuriosaDeMonitorizacion.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include<queue>

using namespace std;


struct registro {
    int momento; // cuándo le toca
    int id; // identificador (se utiliza en caso de empate)
    int periodo; // tiempo entre consultas
};
//Unidad Curiosa de Monitorización
//¿Y si el ordena de una forma diferente ?
struct comp_registro {
    bool operator()(registro const& a, registro const& b) {
        return b.momento < a.momento ||
            (a.momento == b.momento && b.id < a.id);
    }
};


bool resuelveCaso() {
    int N; // número de usuarios registrados
    cin >> N;
    if (N == 0) return false; // no hay más casos
    priority_queue<registro, vector<registro>, comp_registro> cola;
    // leemos los registros
    for (int i = 0; i < N; ++i) {
        int id_usu, periodo;
        cin >> id_usu >> periodo;
        cola.push({ periodo, id_usu, periodo });
    }
    int envios; // número de envíos a mostrar
    cin >> envios;
    while (envios--) {
        auto e = cola.top(); cola.pop();
        cout << e.id << '\n';
        e.momento += e.periodo;
        cola.push(e);
    }
    cout << "---\n";
    return true;
}


int main()
{
    while (resuelveCaso());
    return 0;
}

