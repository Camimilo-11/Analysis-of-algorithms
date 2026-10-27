#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <string>

using namespace std;

struct Edge {
    int to;
    int weight;
};

void dijkstra(int V, const vector<vector<Edge>>& adj, char startNode, bool isDirected) {
    int start = startNode - 'a';
    vector<int> dist(V, INT_MAX);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        int u = pq.top().second;
        int d = pq.top().first;
        pq.pop();

        if (d > dist[u]) continue;

        for (const auto& edge : adj[u]) {
            int v = edge.to;
            int weight = edge.weight;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }

    cout << "Shortest paths from source '" << startNode << "' (" << (isDirected ? "Directed" : "Undirected") << "):" << endl;
    for (int i = 0; i < V; ++i) {
        char nodeChar = (char)('a' + i);
        if (dist[i] == INT_MAX) {
            cout << "  Node " << nodeChar << ": Unreachable" << endl;
        } else {
            cout << "  Node " << nodeChar << ": Distance = " << dist[i] << ", Path: ";
            vector<char> path;
            for (int curr = i; curr != -1; curr = parent[curr]) {
                path.push_back((char)('a' + curr));
            }
            for (int j = (int)path.size() - 1; j >= 0; --j) {
                cout << path[j] << (j > 0 ? " -> " : "");
            }
            cout << endl;
        }
    }
    cout << endl;
}

int main() {
    // Instance 3.a (Undirected)
    int V_a = 5;
    vector<vector<Edge>> adj_a(V_a);
    auto addEdgeA = [&](char u, char v, int w) {
        adj_a[u - 'a'].push_back({v - 'a', w});
        adj_a[v - 'a'].push_back({u - 'a', w});
    };
    addEdgeA('a', 'b', 5);
    addEdgeA('a', 'e', 2);
    addEdgeA('a', 'c', 7);
    addEdgeA('b', 'e', 3);
    addEdgeA('b', 'd', 6);
    addEdgeA('c', 'e', 4);
    addEdgeA('c', 'd', 4);
    addEdgeA('e', 'd', 5);

    dijkstra(V_a, adj_a, 'a', false);

    // Instance 3.b (Directed)
    int V_b = 5;
    vector<vector<Edge>> adj_b(V_b);
    auto addEdgeB = [&](char u, char v, int w) {
        adj_b[u - 'a'].push_back({v - 'a', w});
    };
    addEdgeB('a', 'd', 7);
    addEdgeB('b', 'a', 3);
    addEdgeB('d', 'b', 2);
    addEdgeB('b', 'c', 4);
    addEdgeB('d', 'c', 5);
    addEdgeB('c', 'e', 6);
    addEdgeB('e', 'd', 4);

    dijkstra(V_b, adj_b, 'a', true);

    return 0;
}
