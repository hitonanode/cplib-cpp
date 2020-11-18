#include "graph/incremental_bridge_connectivity.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    IncrementalBridgeConnectivity graph(V);
    while (E--) {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
    }

    vector<vector<int>> ret(V);
    for (int i = 0; i < V; i++) { ret[graph.find(i)].emplace_back(i); }
    int K = count_if(ret.begin(), ret.end(), [](const vector<int>& v) { return v.size() > 0; });
    cout << K << '\n';
    for (const auto& vec : ret) {
        if (vec.size()) {
            cout << vec.size();
            for (auto x : vec) { cout << ' ' << x; }
            cout << '\n';
        }
    }
}
