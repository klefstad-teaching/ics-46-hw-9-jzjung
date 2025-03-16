#include "dijkstras.h"

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    vector<int> distance(G.numVertices, INF);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    previous.resize(G.numVertices, -1);

    distance[source] = 0;
    pq.push({0, source});

    while (!pq.empty()) {
        int dist = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (dist > distance[u]) continue;

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (distance[u] + weight < distance[v]) {
                distance[v] = distance[u] + weight;
                previous[v] = u;
                pq.push({distance[v], v});
            }
        }
    }
    return distance;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    if (path.empty() || previous[destination] == -1) {
        return {};
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    vector<int> path;

    for (int at = total; at != -1; at = v[at]) {
        path.push_back(at);
    }

    if (path.empty()) {
        cout << "No path found." << endl;
        return;
    }

    reverse(path.begin(), path.end());

    cout << "Path: ";
    for (size_t i = 0; i < path.size(); ++i) {
        if (i != 0) {
            cout << " -> ";
        }
        cout << path[i];
    }
    cout << endl;
}