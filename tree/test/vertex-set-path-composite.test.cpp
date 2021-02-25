#define PROBLEM "https://judge.yosupo.jp/problem/vertex_set_path_composite"
#include "../../modint.hpp"
#include "../../segmenttree/point-update-range-get_nonrecursive.hpp"
#include "../heavy_light_decomposition.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

using P = pair<mint, mint>;
struct PointSetRangeComposite : public NonrecursiveSegmentTree<P, P, bool> {
    using SegTree = NonrecursiveSegmentTree<P, P, bool>;
    P merge_data(const P &vl, const P &vr) override { return make_pair(vl.first * vr.first, vr.first * vl.second + vr.second); };
    P data2ret(const P &v, const bool &q) override { return v; }
    P merge_ret(const P &vl, const P &vr) override { return merge_data(vl, vr); };
    PointSetRangeComposite(const std::vector<P> &seq, P zero) : SegTree::NonrecursiveSegmentTree() { SegTree::initialize(seq, zero); };
};

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    vector<P> V(N);
    for (auto &x : V) cin >> x.first >> x.second;

    HeavyLightDecomposition hld(N);
    for (int i = 0; i < N - 1; i++) {
        int u, v;
        cin >> u >> v;
        hld.add_edge(u, v);
    }

    hld.build();
    vector<P> stinit = hld.segtree_rearrange(V);

    PointSetRangeComposite segtree(stinit, P{1, 0});
    reverse(stinit.begin(), stinit.end());
    PointSetRangeComposite segtreeinv(stinit, P{1, 0});
    while (Q--) {
        int q, u, v, x;
        cin >> q >> u >> v >> x;
        if (q == 0) {
            segtree.update(hld.aligned_id[u], P{v, x});
            segtreeinv.update(N - 1 - hld.aligned_id[u], P{v, x});
        } else {
            mint ret = x;
            hld.for_each_vertex_noncommutative(
                u, v,
                [&](int l, int r) -> void {
                    assert(0 <= l and l <= r and r < N);
                    P tmp = segtreeinv.get(N - 1 - r, N - 1 - l + 1);
                    ret = tmp.first * ret + tmp.second;
                },
                [&](int l, int r) -> void {
                    assert(0 <= l and l <= r and r < N);
                    P tmp = segtree.get(l, r + 1);
                    ret = tmp.first * ret + tmp.second;
                });
            cout << ret << '\n';
        }
    }
}