/*
    Analysis of Algorithms - Lab 04
    Punto 3: Breadth First Search (BFS)
    Autor: Camilo

    Estructura de datos elegida: LISTA DE ADYACENCIA.
    Razon: igual que en DFS, con lista el recorrido es Theta(|V|+|E|)
    frente a Theta(V^2) de la matriz, y no se desperdicia memoria en
    las parejas de vertices que no estan conectadas.

    Compilar: g++ Assigment04_pt3.cpp -o bfs
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

class Grafo {
private:
    int V;
    vector<string> valores;
    vector<vector<int>> ady;
    vector<bool> visitado;
    vector<int> nivel;            // distancia en numero de aristas desde la raiz

public:
    Grafo(int n) {
        V = n;
        valores.resize(n);
        ady.resize(n);
    }

    void setValor(int v, const string &etiqueta) { valores[v] = etiqueta; }

    void agregarArista(int u, int v) {
        ady[u].push_back(v);
        ady[v].push_back(u);
    }

    // BFS desde un vertice: usa una COLA en lugar de una pila
    void bfs(int inicio) {
        queue<int> cola;
        visitado[inicio] = true;
        nivel[inicio] = 0;
        cola.push(inicio);

        while (!cola.empty()) {
            int v = cola.front();
            cola.pop();
            cout << valores[v] << " ";

            for (size_t i = 0; i < ady[v].size(); i++) {
                int w = ady[v][i];
                if (!visitado[w]) {
                    visitado[w] = true;
                    nivel[w] = nivel[v] + 1;
                    cola.push(w);
                }
            }
        }
    }

    // Recorrido completo: cubre todas las componentes conexas
    void BFS() {
        visitado.assign(V, false);
        nivel.assign(V, -1);

        cout << "Recorrido BFS: ";
        for (int v = 0; v < V; v++) {
            if (!visitado[v])
                bfs(v);
        }
        cout << "\n";

        cout << "Nivel de cada nodo (aristas desde la raiz de su componente):\n";
        for (int v = 0; v < V; v++)
            cout << "  " << valores[v] << " : " << nivel[v] << "\n";
    }

    void imprimirListaAdyacencia() {
        cout << "Lista de adyacencia:\n";
        for (int v = 0; v < V; v++) {
            cout << "  " << valores[v] << " -> ";
            for (size_t i = 0; i < ady[v].size(); i++)
                cout << valores[ady[v][i]] << " ";
            cout << "\n";
        }
        cout << "\n";
    }
};

int main() {
    // Mismo grafo de la clase (Figura 3.11, Levitin)
    Grafo g(10);
    string etiquetas[10] = {"a","b","c","d","e","f","g","h","i","j"};
    for (int i = 0; i < 10; i++)
        g.setValor(i, etiquetas[i]);

    g.agregarArista(0, 2);  // a-c
    g.agregarArista(0, 3);  // a-d
    g.agregarArista(0, 4);  // a-e
    g.agregarArista(2, 3);  // c-d
    g.agregarArista(2, 5);  // c-f
    g.agregarArista(1, 4);  // b-e
    g.agregarArista(1, 5);  // b-f
    g.agregarArista(4, 5);  // e-f
    g.agregarArista(6, 7);  // g-h
    g.agregarArista(6, 9);  // g-j
    g.agregarArista(7, 8);  // h-i
    g.agregarArista(8, 9);  // i-j

    g.imprimirListaAdyacencia();
    g.BFS();

    return 0;
}
