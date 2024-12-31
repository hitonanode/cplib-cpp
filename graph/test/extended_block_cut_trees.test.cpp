#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../extended_block_cut_trees.hpp"

#include <atcoder/fenwicktree>

#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges(M);
    for (auto &[u, v] : edges) cin >> u >> v;

    const extended_block_cut_trees bct(N, edges);

    cout << bct.B << '\n';
    for (const auto &g : bct.biconnected_components()) {
        cout << g.size();
        for (int v : g) cout << ' ' << v;
        cout << '\n';
    }
}
