#define PROBLEM "https://yukicoder.me/problems/no/1326"
#include "../extended_block_cut_trees.hpp"
#include "../../tree/heavy_light_decomposition.hpp"

#include <atcoder/fenwicktree>

#include <iostream>

using namespace std;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges(M);
    for (auto &[u, v] : edges) cin >> u >> v, --u, --v;

    const extended_block_cut_trees bct(N, edges);

    HeavyLightDecomposition hld(bct.size());
    for (auto [i, j] : bct.get_edges()) hld.add_edge(i, j);
    hld.build();

    atcoder::fenwick_tree<int> fw(hld.V);
    for (int i = 0; i < N; ++i) fw.add(hld.aligned_id[i], 1);

    int Q;
    cin >> Q;
    while (Q--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        int ret = 0;
        if (u != v) {
            ret = -2;
            hld.for_each_vertex(u, v, [&](int a, int b) { ret += fw.sum(a, b + 1); });
        }
        cout << ret << '\n';
    }
}
