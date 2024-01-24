#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main() {
    int N;

    while (true) {
        cin >> N;

        if (N == 0) {
            break;
        }

        vector<pair<int, int>> edificios;

        // Leer los extremos occidentales y orientales de cada edificio
        for (int i = 0; i < N; ++i) {
            int Wi, Ei;
            cin >> Wi >> Ei;
            edificios.push_back({ Wi, Ei });
        }

        // Ordenar los extremos de los edificios de manera ascendente según sus extremos orientales (Ei)
        sort(edificios.begin(), edificios.end(), [](const pair<int, int>& a, const pair<int, int>& b) {
            return a.second < b.second;
            });

        int tuneles = 0;
        int extremo_anterior = -1;

        // Iterar sobre los edificios
        for (int i = 0; i < N; ++i) {
            // Verificar si se necesita un túnel entre edificios
            if (edificios[i].first >= extremo_anterior) {
                ++tuneles;
                extremo_anterior = edificios[i].second;
            }
        }

        // Imprimir el número de túneles necesario
        cout << tuneles << endl;
    }

    return 0;
}
