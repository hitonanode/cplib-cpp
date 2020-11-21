#define PROBLEM "https://judge.yosupo.jp/problem/scc"
#include "../strongly_connected_components.hpp"

#include <iostream>

int main() {
    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);

    int V, E;
    std::cin >> V >> E;
    DirectedGraphSCC graph(V);
    while (E--) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, t);
    }

    graph.FindStronglyConnectedComponents();

    int K = graph.scc_num;
    std::vector<std::vector<int>> components(K);
    for (int i = 0; i < V; i++) { components[graph.cmp[i]].emplace_back(i); }
    std::cout << K << '\n';
    for (const auto &vec : components) {
        std::cout << vec.size();
        for (auto x : vec) std::cout << ' ' << x;
        std::cout << '\n';
    }
}
