#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_path_sum"
#include "../../segmenttree/point-update-range-get_nonrecursive.hpp"
#include "../heavy_light_decomposition.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q, q, u, v;
    cin >> N >> Q;

    vector<long long> A(N);
    for (auto &x : A) cin >> x;
    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++) {
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.build();
    PointUpdateRangeSum<long long> segtree(hld.segtree_rearrange(A), 0LL);

    while (Q--) {
        cin >> q >> u >> v;
        if (q) {
            long long ret = 0;
            hld.for_each_vertex(u, v, [&](int l, int r) -> void { ret += segtree.get(l, r + 1); });
            cout << ret << '\n';
        } else {
            A[u] += v;
            segtree.update(hld.aligned_id[u], A[u]);
        }
    }
}
