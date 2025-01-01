#define PROBLEM "https://judge.yosupo.jp/problem/lca"
#include "../heavy_light_decomposition.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, Q, p, u, v;
    cin >> N >> Q;
    vector<pair<int, int>> edges;
    for (int i = 1; i <= N - 1; i++) {
        cin >> p;
        edges.emplace_back(i, p);
    }

    heavy_light_decomposition hld(N, edges);
    hld.build();

    while (Q--) {
        cin >> u >> v;
        cout << hld.lowest_common_ancestor(u, v) << "\n";
    }
}
