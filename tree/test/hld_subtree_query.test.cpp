#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../heavy_light_decomposition.hpp"
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

#include <atcoder/fenwicktree>

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    for (auto &x : A) cin >> x;

    vector<pair<int, int>> edges;
    for (int i = 1; i < N; ++i) {
        int p;
        cin >> p;
        edges.emplace_back(i, p);
    }

    heavy_light_decomposition hld(N, edges);
    hld.build();

    atcoder::fenwick_tree<long long> ft(N);

    A = hld.segtree_rearrange(A);
    for (int i = 0; i < N; ++i) ft.add(i, A.at(i));

    while (Q--) {
        int tp, u;
        cin >> tp >> u;
        if (tp == 0) {
            long long x;
            cin >> x;
            hld.for_vertex(u, [&](int i) { ft.add(i, x); });
        } else {
            long long ans = 0;
            hld.for_subtree(u, [&](int l, int r) { ans += ft.sum(l, r + 1); });
            cout << ans << '\n';
        }
    }
}
