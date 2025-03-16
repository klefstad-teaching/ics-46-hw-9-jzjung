#include "dijkstras.h"

using namespace std;

int main() {
    string filename;

    cout << "Enter the graph file name (e.g., small.txt): ";
    cin >> filename;

    Graph graph;
    try {
        file_to_graph(filename, graph);
    } catch (const runtime_error& e) {
        cout << "Error reading graph: " << e.what() << endl;
        return 1;
    }

    vector<int> previous;
    vector<int> distances = dijkstra_shortest_path(graph, 0, previous);

    for (int i = 0; i < graph.numVertices; ++i) {
        if (distances[i] == INF) {
            cout << "Vertex " << i << " is unreachable from vertex 0." << endl;
        } else {
            cout << "Shortest distance to vertex " << i << ": " << distances[i] << endl;
            vector<int> path = extract_shortest_path(distances, previous, i);
            cout << "Path: ";
            print_path(path, distances[i]);
        }
    }

    return 0;
}