#include <iostream>
#include <queue>
#include <string>
#include "PriorityQueue.h"

using namespace std;

struct Paciente {
    string nombre;
    int gravedad;
    int tiempo;

    Paciente(string n, int g, int t) : nombre(n), gravedad(g), tiempo(t) {}
};

bool operator<(const Paciente& p1, const Paciente& p2) {
    return !(p1.gravedad > p2.gravedad || p1.gravedad == p2.gravedad && p1.tiempo < p2.tiempo);
}

bool resuelveCaso() {
   
    int n;
    cin >> n;

    if (n == 0)
        return false;

    priority_queue<Paciente> colap;
    for (int i = 0; i < n; i++) {
        
       
        char tipo;
        cin >> tipo;

        if (tipo == 'I') {
            string nombre;
            int gravedad;
            // Ingreso de un nuevo paciente moribundo
            cin >> nombre >> gravedad;

            Paciente nuevo(nombre, gravedad, i);
            colap.push(nuevo);
        }
        else if(tipo == 'A') {
            // Atiende al paciente
            Paciente mas_prioritario = colap.top();
            colap.pop();
            //atinde al paciente
            cout << mas_prioritario.nombre << "\n";
        }
    }

    cout << "---\n";
    return true;
}

int main() {
    while(resuelveCaso());
    return 0;
}
