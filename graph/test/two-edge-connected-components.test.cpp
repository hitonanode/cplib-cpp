#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../lowlink.hpp"

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int V, E;
    std::cin >> V >> E;
    UndirectedGraph graph(V);
    while (E--) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, t);
    }

    graph.detectBridge();
    graph.two_edge_connected_components();

    std::vector<std::pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.is_bridge[i]) { bridges.emplace_back(graph.edges[i]); }
    }
    std::cout << graph.tecc_num << '\n';
    std::vector<std::vector<int>> vids(V);
    for (int i = 0; i < V; i++) { vids[graph.tecc_id[i]].push_back(i); }
    for (const auto &v : vids)
        if (!v.empty()) {
            std::cout << v.size();
            for (auto x : v) std::cout << ' ' << x;
            std::cout << '\n';
        }
}
