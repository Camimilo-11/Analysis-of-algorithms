#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include <iomanip>

using namespace std;

// Genera una instancia aleatoria del problema: pesos, valores y capacidad
void generarInstancia(int n, vector<int> &pesos, vector<int> &valores, int &capacidad) {
    pesos.resize(n);
    valores.resize(n);
    int pesoTotal = 0;

    for (int i = 0; i < n; i++) {
        pesos[i]   = 1 + rand() % 100;   // peso  entre 1 y 100
        valores[i] = 1 + rand() % 100;   // valor entre 1 y 100
        pesoTotal += pesos[i];
    }
    capacidad = pesoTotal / 2;           // capacidad = 50% del peso total
}

/*
    Busqueda exhaustiva: se generan los 2^n subconjuntos posibles.
    Cada subconjunto se representa con los bits de un entero:
    si el bit i esta en 1, el objeto i se mete en la mochila.
    Se descartan los subconjuntos que superan la capacidad y se
    guarda el mejor valor encontrado.
*/
int mochilaExhaustiva(int n, const vector<int> &pesos, const vector<int> &valores,
                      int capacidad, unsigned long long &mejorSubconjunto) {
    unsigned long long totalSubconjuntos = 1ULL << n;   // 2^n
    int mejorValor = 0;
    mejorSubconjunto = 0;

    for (unsigned long long s = 0; s < totalSubconjuntos; s++) {
        int pesoActual = 0;
        int valorActual = 0;

        for (int i = 0; i < n; i++) {
            if (s & (1ULL << i)) {
                pesoActual  += pesos[i];
                valorActual += valores[i];
            }
        }

        if (pesoActual <= capacidad && valorActual > mejorValor) {
            mejorValor = valorActual;
            mejorSubconjunto = s;
        }
    }
    return mejorValor;
}

int main() {
    srand(12345);   // semilla fija para poder repetir el experimento

    const double LIMITE = 30.0;   // segundos
    int nInicial = 3;

    cout << "Problema de la mochila 0/1 - busqueda exhaustiva\n";
    cout << "Limite de tiempo por instancia: " << LIMITE << " s\n\n";
    cout << left << setw(6) << "n" << setw(14) << "2^n"
         << setw(12) << "Capacidad" << setw(14) << "Mejor valor"
         << "Tiempo (s)\n";
    cout << "-------------------------------------------------------------\n";

    for (int n = nInicial; ; n++) {
        vector<int> pesos, valores;
        int capacidad;
        generarInstancia(n, pesos, valores, capacidad);

        unsigned long long mejorSubconjunto;

        auto inicio = chrono::high_resolution_clock::now();
        int mejorValor = mochilaExhaustiva(n, pesos, valores, capacidad, mejorSubconjunto);
        auto fin = chrono::high_resolution_clock::now();

        double tiempo = chrono::duration<double>(fin - inicio).count();

        cout << left << setw(6) << n
             << setw(14) << (1ULL << n)
             << setw(12) << capacidad
             << setw(14) << mejorValor
             << fixed << setprecision(6) << tiempo << "\n";
        cout.flush();

        if (tiempo > LIMITE) {
            cout << "\nEl tiempo supero los " << LIMITE << " s en n = " << n << ".\n";
            cout << "El mayor tamano resuelto dentro del limite fue n = " << n - 1 << ".\n";
            break;
        }
    }

    return 0;
}
