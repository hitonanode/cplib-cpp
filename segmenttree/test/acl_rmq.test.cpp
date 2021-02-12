#include "../acl_segtree.hpp"
#include <algorithm>
#include <iostream>
#include <limits>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"
using namespace std;

using S = int;
S op(S l, S r) { return std::min(l, r); }
S e() { return std::numeric_limits<S>::max(); }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;

    atcoder::segtree<S, op, e> segtree(N);
    while (Q--) {
        int q, x, y;
        cin >> q >> x >> y;
        if (q) {
            cout << segtree.prod(x, y + 1) << '\n';
        } else {
            segtree.set(x, y);
        }
    }
}
