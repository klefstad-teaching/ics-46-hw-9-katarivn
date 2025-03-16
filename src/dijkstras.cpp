#include "dijkstras.h"
#include <algorithm>

using namespace std;

vector<int> dijkstra_shortest_path(const Graph& G, int source, vector<int>& previous) {
    int n = G.size();
    vector<int> distances(n, INF);
    previous.assign(n, -1);

    auto cmp = [](const pair<int, int>& a, const pair<int, int>& b) {
        return a.second > b.second;
    };
    priority_queue<pair<int, int>, vector<pair<int, int>>, decltype(cmp)> pq(cmp);

    pq.push({source, 0});
    distances[source] = 0;

    while (!pq.empty()) {
        int u = pq.top().first;
        pq.pop();

        for (const Edge& edge : G[u]) {
            int v = edge.dst;
            int weight = edge.weight;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({v, distances[v]});
            }
        }
    }
    return distances;
}

vector<int> extract_shortest_path(const vector<int>& /*distances*/, const vector<int>& previous, int destination) {
    vector<int> path;
    if (previous[destination] == -1) {
        return path;
    }
    for (int v = destination; v != -1; v = previous[v]) {
        path.push_back(v);
    }
    reverse(path.begin(), path.end());
    return path;
}



void print_path(const vector<int>& path, int total) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size()) {
            cout << " ";
        }
    }
    cout << "\nTotal cost is " << total << endl;
}
