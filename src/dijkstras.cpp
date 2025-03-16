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

        if (u < 0 || u >= G.numVertices) {
            cerr << "Error: Invalid vertex index " << u << endl;
            continue;
        }

        if (G[u].empty()) {
            cerr << "Error: No edges for vertex " << u << endl;
            continue;
        }

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (v < 0 || v >= G.numVertices) {
                cerr << "Error: Invalid destination vertex " << v << endl;
                continue;
            }

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

    if (previous[destination] == -1) {
        return {};
    }

    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }

    reverse(path.begin(), path.end());
    return path;
}

void print_path(const vector<int>& v, int total) {
    vector<int> path;

    if (total == -1 || v[total] == -1) {
        cout << "No path found." << endl;
        return;
    }

    for (int at = total; at != -1; at = v[at]) {
        if (at < 0 || static_cast<size_t>(at) >= v.size()) {
            cerr << "Error: Invalid vertex index " << at << endl;
            return;
        }
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

    int totalCost = 0;
    for (size_t i = 1; i < path.size(); ++i) {
        int u = path[i - 1];
        int v = path[i];
        bool edgeFound = false;
        for (const Edge& edge : G[u]) {
            if (edge.dst == v) {
                totalCost += edge.weight;
                edgeFound = true;
                break;
            }
        }
        if (!edgeFound) {
            cerr << "Error: Edge not found between " << u << " and " << v << endl;
        }
    }
    cout << " \nTotal cost is " << totalCost << endl;
}