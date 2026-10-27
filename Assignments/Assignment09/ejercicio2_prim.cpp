#include <iostream>
#include <vector>
#include <queue>
#include <tuple>
#include <climits>
#include <string>

using namespace std;

struct Edge {
    int to;
    int weight;
};

void primMST(int V, const vector<vector<Edge>>& adj, char startNode = 'a') {
    int start = startNode - 'a';
    vector<int> key(V, INT_MAX);
    vector<int> parent(V, -1);
    vector<bool> inMST(V, false);

    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    key[start] = 0;
    pq.push({0, start});

    cout << "=== Prim's Algorithm Trace ===" << endl;
    int totalWeight = 0;

    while (!pq.empty()) {
        int u = pq.top().second;
        int w = pq.top().first;
        pq.pop();

        if (inMST[u]) continue;
        inMST[u] = true;
        totalWeight += w;

        char uChar = (char)('a' + u);
        if (parent[u] != -1) {
            char pChar = (char)('a' + parent[u]);
            cout << "Added Edge: (" << pChar << ", " << uChar << ") with weight " << w << endl;
        } else {
            cout << "Starting Node: " << uChar << endl;
        }

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
                pq.push({key[v], v});
            }
        }
    }
    cout << "Total Minimum Spanning Tree Weight: " << totalWeight << endl;
}

int main() {
    int V = 12; // nodes a to l
    vector<vector<Edge>> adj(V);

    auto addEdge = [&](char u, char v, int w) {
        adj[u - 'a'].push_back({v - 'a', w});
        adj[v - 'a'].push_back({u - 'a', w});
    };

    addEdge('a', 'b', 3);
    addEdge('a', 'c', 5);
    addEdge('a', 'd', 4);
    addEdge('b', 'e', 3);
    addEdge('b', 'f', 6);
    addEdge('c', 'd', 2);
    addEdge('c', 'g', 4);
    addEdge('d', 'e', 1);
    addEdge('d', 'h', 5);
    addEdge('e', 'f', 2);
    addEdge('e', 'i', 4);
    addEdge('f', 'j', 5);
    addEdge('g', 'h', 3);
    addEdge('g', 'k', 6);
    addEdge('h', 'i', 6);
    addEdge('h', 'k', 7);
    addEdge('i', 'j', 3);
    addEdge('i', 'l', 5);
    addEdge('j', 'l', 9);
    addEdge('k', 'l', 8);

    primMST(V, adj, 'a');

    return 0;
}
