#define PROBLEM "https://judge.yosupo.jp/problem/maximum_independent_set"
#include "graph/maximum_independent_set.hpp"

#include <cassert>
#include <iostream>
#include <vector>

int main() {
    int N, M;
    std::cin >> N >> M;
    std::vector<std::vector<int>> edges(N);
    while (M--) {
        int u, v;
        std::cin >> u >> v;
        edges[u].emplace_back(v);
        edges[v].emplace_back(u);
    }
    MaximumIndependentSet mis(edges);
    MaximumIndependentSetFast misfast(edges);
    std::cout << std::accumulate(mis.ret.begin(), mis.ret.end(), 0) << "\n";
    for (int i = 0; i < N; i++) {
        // Check whether two implementation gives same results
        assert(mis.ret[i] == ((misfast.ret >> i) & 1));

        if (mis.ret[i]) std::cout << i << " ";
    }
    std::cout << "\n";
}
