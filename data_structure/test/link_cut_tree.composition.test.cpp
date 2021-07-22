#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite"
#include "../link_cut_tree.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <tuple>
#include <utility>
using namespace std;

using mint = ModInt<998244353>;
using S = pair<pair<mint, mint>, pair<mint, mint>>;
using F = tuple<>;

S reversal(S x) { return {x.second, x.first}; }
pair<mint, mint> opS(pair<mint, mint> l, pair<mint, mint> r) {
    return {l.first * r.first, r.second + r.first * l.second};
}
S op(S l, S r) { return {opS(l.first, r.first), opS(r.second, l.second)}; }
S mapping(F, S x) { return x; }
F id() { return {}; }
F composition(F, F) { return id(); }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

LCT::Node* vs[200000];

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    LCT lct;
    for (int i = 0; i < N; i++) {
        mint a, b;
        cin >> a >> b;
        vs[i] = lct.make_node({{a, b}, {a, b}});
    }
    for (int e = 0; e < N - 1; e++) {
        int u, v;
        cin >> u >> v;
        lct.link(vs[u], vs[v]);
    }
    while (Q--) {
        int tp;
        cin >> tp;
        if (tp == 0) {
            int u, v, w, x;
            cin >> u >> v >> w >> x;
            lct.cut(vs[u], vs[v]);
            lct.link(vs[x], vs[w]);
        }
        if (tp == 1) {
            int p;
            mint c, d;
            cin >> p >> c >> d;
            lct.set(vs[p], {{c, d}, {c, d}});
        }
        if (tp == 2) {
            int u, v;
            mint x;
            cin >> u >> v >> x;
            auto p = lct.prod(vs[u], vs[v]).first;
            cout << x * p.first + p.second << '\n';
        }
    }
}
