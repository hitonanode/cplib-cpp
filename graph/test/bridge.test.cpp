#include "../lowlink.hpp"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

int main() {
    int V, E;
    cin >> V >> E;
    lowlink graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        if (s > t) swap(s, t);
        graph.add_edge(s, t);
    }
    graph.build();

    vector<pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.is_bridge[i]) bridges.emplace_back(graph.edges[i]);
    }
    sort(bridges.begin(), bridges.end());
    for (auto p : bridges) cout << p.first << ' ' << p.second << '\n';
}
