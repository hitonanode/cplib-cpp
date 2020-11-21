#define PROBLEM "https://judge.yosupo.jp/problem/cycle_detection"
#include "../strongly_connected_components.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    DirectedGraphSCC graph(V);
    vector<pair<pair<int, int>, int>> edges;
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
        edges.emplace_back(make_pair(make_pair(s, t), i));
    }
    sort(edges.begin(), edges.end());

    auto cycle = graph.DetectCycle();
    if (cycle.empty()) {
        cout << "-1\n";
    } else {
        cout << cycle.size() << '\n';
        for (int i = 0; i < int(cycle.size()); i++) {
            pair<int, int> p{cycle[i], cycle[(i + 1) % cycle.size()]};
            int eid = lower_bound(edges.begin(), edges.end(), make_pair(p, 0))->second;
            cout << eid << '\n';
        }
    }
}
