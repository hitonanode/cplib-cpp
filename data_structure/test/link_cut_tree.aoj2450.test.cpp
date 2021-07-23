#define PROBLEM "https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2450"
#include "../link_cut_tree.hpp"
#include <algorithm>
#include <iostream>
#include <utility>
using namespace std;

struct S {
    int sz, sum, lhi, rhi, inhi;
    S(int x) : sz(1), sum(x), lhi(x), rhi(x), inhi(x) {}
    S(int sz_, int sum_, int lhi_, int rhi_, int inhi_)
        : sz(sz_), sum(sum_), lhi(lhi_), rhi(rhi_), inhi(inhi_) {}
};
using F = pair<bool, int>;
S op(S l, S r) {
    return S(l.sz + r.sz, l.sum + r.sum, max(l.sum + r.lhi, l.lhi), max(l.rhi + r.sum, r.rhi), max<int>({l.inhi, r.inhi, l.rhi + r.lhi}));
}
S reversal(S x) { return S(x.sz, x.sum, x.rhi, x.lhi, x.inhi); }
S mapping(F f, S x) {
    if (f.first) {
        auto v = f.second;
        auto sum = x.sz * v;
        return S{x.sz, sum, max(v, sum), max(v, sum), max(v, sum)};
    } else {
        return x;
    }
}
F composition(F fnew, F gold) { return fnew.first ? fnew : gold; }
F id() { return {false, 0}; }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;
LCT::Node* vs[200000];

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    LCT tree;
    for (int i = 0; i < N; i++) {
        int w;
        cin >> w;
        vs[i] = tree.make_node(w);
    }
    for (int e = 0; e < N - 1; e++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        tree.link(vs[u], vs[v]);
    }
    while (Q--) {
        int t, a, b, c;
        cin >> t >> a >> b >> c;
        a--, b--;
        if (t == 1) tree.apply(vs[a], vs[b], {true, c});
        if (t == 2) cout << tree.prod(vs[a], vs[b]).inhi << '\n';
    }
}
