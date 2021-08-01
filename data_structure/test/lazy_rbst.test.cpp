#define PROBLEM "https://judge.yosupo.jp/problem/dynamic_sequence_range_affine_range_sum"
#include "../lazy_rbst.hpp"
#include "../../modint.hpp"
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

using mint = ModInt<998244353>;

struct S {
    mint sum;
    int sz;
};
using F = pair<bool, pair<mint, mint>>;
S op(S l, S r) { return S{l.sum + r.sum, l.sz + r.sz}; }
S mapping(F f, S x) {
    if (!f.first) return x;
    mint a = f.second.first, b = f.second.second;
    return {x.sum * a + b * x.sz, x.sz};
}
S reversal(S x) { return x; }
F composition(F fnew, F gold) {
    if (!fnew.first) return gold;
    if (!gold.first) return fnew;
    auto anew = fnew.second.first, bnew = fnew.second.second;
    auto aold = gold.second.first, bold = gold.second.second;
    return {true, {anew * aold, anew * bold + bnew}};
}
F id() { return {false, {1, 0}}; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<S> A(N);
    for (auto &x : A) cin >> x.sum, x.sz = 1;
    lazy_rbst<1000001, S, op, F, reversal, mapping, composition, id> rbst;

    auto root = rbst.new_tree();
    rbst.assign(root, A);
    while (Q--) {
        int tp;
        cin >> tp;
        if (tp == 0) {
            int i, x;
            cin >> i >> x;
            rbst.insert(root, i, S{x, 1});
            N++;
        } else if (tp == 1) {
            int i;
            cin >> i;
            rbst.erase(root, i);
            N--;
        } else if (tp == 2) {
            int l, r;
            cin >> l >> r;
            rbst.reverse(root, l, r);
        } else if (tp == 3) {
            int l, r, b, c;
            cin >> l >> r >> b >> c;
            rbst.apply(root, l, r, {true, {b, c}});
        } else if (tp == 4) {
            int l, r;
            cin >> l >> r;
            cout << rbst.prod(root, l, r).sum << '\n';
        }
    }
}
