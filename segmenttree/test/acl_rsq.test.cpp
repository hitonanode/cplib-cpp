#include "../acl_segtree.hpp"
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B"
using namespace std;

using S = int;
S op(S l, S r) { return l + r; }
S e() { return 0; }

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;

    atcoder::segtree<S, op, e> segtree(N);
    while (Q--) {
        int q, x, y;
        cin >> q >> x >> y;
        x--;
        if (q) {
            cout << segtree.prod(x, y) << '\n';
        } else {
            segtree.set(x, segtree.get(x) + y);
        }
    }
}
