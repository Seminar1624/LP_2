#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class KruskalMST {
    int V;
    vector<vector<int>> edges;
    vector<int> parent, rank;

public:
    KruskalMST(int v) : V(v) {
        parent.resize(V);
        rank.resize(V, 0);
        for (int i = 0; i < V; ++i)
            parent[i] = i;
    }

    void addEdge(int u, int v, int wt) {
        edges.push_back({wt, u, v}); // Store as (weight, u, v)
    }

    int find(int x) {
        if (x == parent[x])
            return x;
        return parent[x] = find(parent[x]);
    }

    void unionSet(int x, int y) {
        int px = find(x);
        int py = find(y);
        if (px == py) return;
        if (rank[px] > rank[py]) parent[py] = px;
        else if (rank[px] < rank[py]) parent[px] = py;
        else {
            parent[px] = py;
            rank[py]++;
        }
    }

    int getMSTWeight() {
        sort(edges.begin(), edges.end()); // Sort by weight
        int mstWeight = 0;
        for (auto &e : edges) {
            int wt = e[0], u = e[1], v = e[2];
            if (find(u) != find(v)) {
                unionSet(u, v);
                mstWeight += wt;
                cout << "Edge included: " << u << " - " << v << " (weight " << wt << ")\n";
            }
        }
        return mstWeight;
    }
};

int main() {
    int V, E;
    cout << "Enter number of vertices and edges: ";
    cin >> V >> E;

    KruskalMST graph(V);
    cout << "Enter edges (source destination weight):\n";
    for (int i = 0; i < E; ++i) {
        int u, v, wt;
        cin >> u >> v >> wt;
        graph.addEdge(u, v, wt);
    }

    int totalWeight = graph.getMSTWeight();
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
