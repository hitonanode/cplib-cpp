#include "../heavy_light_decomposition.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main() {
    int N, Q, p, u, v;
    std::cin >> N >> Q;
    HeavyLightDecomposition hld(N);
    for (int i = 1; i <= N - 1; i++) {
        std::cin >> p;
        hld.add_edge(i, p);
    }
    hld.build();

    while (Q--) {
        std::cin >> u >> v;
        std::cout << hld.lowest_common_ancestor(u, v) << "\n";
    }
}
