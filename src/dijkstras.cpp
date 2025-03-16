#include "dijkstras.h"

struct Node {
    int vertex;
    int weight;

    Node(int v, int w) : vertex(v), weight(w) {}

    bool operator>(const Node& other) const {
        return weight > other.weight;
    }
};

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.numVertices;
    vector<int> distance(n, INF);
    previous.resize(n, -1);
    vector<bool> visited(n, false);

    priority_queue<Node, vector<Node>, greater<Node>> pq;

    distance[source] = 0;
    pq.push(Node(source, 0));

    while (!pq.empty()) {
        int u = pq.top().vertex;
        pq.pop();

        if (visited[u]) continue;
        visited[u] = true;

        for (const Edge& e : G[u]) {
            int v = e.dst;
            int weight = e.weight;

            if (!visited[v] && distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push(Node(v, distance[v]));
            }
        }
    }

    return distance;
}

vector<int> extract_shortest_path(const vector<int>& distance, const vector<int>& previous, int destination) {
    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& path, int total) {
    if (path.empty()) {
        cout << "Total cost is " << total << endl;
    } else {
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i] << " ";
        }
        cout << endl;
        cout << "Total cost is " << total << endl;
    }
}