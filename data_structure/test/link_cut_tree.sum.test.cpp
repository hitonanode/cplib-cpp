#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum"
#include "../link_cut_tree.hpp"
#include <iostream>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using S = unsigned long long;
using F = tuple<>;

F id() noexcept { return {}; }
S op(S l, S r) noexcept { return l + r; }
S mapping(F f, S x) noexcept { return x; }
S reversal(S x) noexcept { return x; }
F composition(F f, F g) noexcept { return {}; }
using LCT = lazy_linkcuttree<S, F, op, reversal, mapping, composition, id>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    LCT lct;
    vector<LCT::Node *> vs;
    vector<unsigned long long> A(N);
    for (auto &a : A) {
        cin >> a;
        vs.push_back(lct.make_node(a));
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
            lct.link(vs[w], vs[x]);
        }
        if (tp == 1) {
            int p, x;
            cin >> p >> x;
            A[p] += x;
            lct.set(vs[p], A[p]);
        }
        if (tp == 2) {
            int u, v;
            cin >> u >> v;
            cout << lct.prod(vs[u], vs[v]) << '\n';
        }
    }
}
