#include <iostream>
#include <vector>
#include <string>

using namespace std;

class Grafo {
private:
    int V;                            // numero de vertices
    vector<string> valores;           // valor (etiqueta) de cada nodo
    vector<vector<int>> ady;          // lista de adyacencia
    vector<bool> visitado;
    vector<int> orden;                // orden en que se visitan (push)
    vector<int> salida;               // orden en que quedan sin salida (pop)

public:
    Grafo(int n) {
        V = n;
        valores.resize(n);
        ady.resize(n);
    }

    void setValor(int v, const string &etiqueta) { valores[v] = etiqueta; }

    // Grafo no dirigido: la arista se agrega en los dos sentidos
    void agregarArista(int u, int v) {
        ady[u].push_back(v);
        ady[v].push_back(u);
    }

    // Visita recursiva de todos los vertices alcanzables desde v
    void dfs(int v) {
        visitado[v] = true;
        orden.push_back(v);
        cout << valores[v] << " ";

        for (size_t i = 0; i < ady[v].size(); i++) {
            int w = ady[v][i];
            if (!visitado[w])
                dfs(w);
        }
        salida.push_back(v);   // el vertice se vuelve un "dead-end" (se saca de la pila)
    }

    // Recorrido completo: cubre tambien los grafos con varias componentes
    void DFS() {
        visitado.assign(V, false);
        orden.clear();
        salida.clear();

        cout << "Recorrido DFS: ";
        for (int v = 0; v < V; v++) {
            if (!visitado[v])
                dfs(v);
        }
        cout << "\n";

        cout << "Orden de salida de la pila (dead-ends): ";
        for (size_t i = 0; i < salida.size(); i++)
            cout << valores[salida[i]] << " ";
        cout << "\n";
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
    // Grafo de ejemplo de la clase (Figura 3.10, Levitin): 10 vertices, 2 componentes
    // a=0 b=1 c=2 d=3 e=4 f=5 g=6 h=7 i=8 j=9
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
    g.DFS();

    return 0;
}
