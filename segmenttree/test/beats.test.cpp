#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include "../acl_beats.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<BNode> A(N);
    for (auto &a : A) {
        long long tmp;
        cin >> tmp, a = BNode(tmp, 1);
    }
    segtree_beats<BNode, bop, be, BF, bmapping, bcomposition, bid> segtree(A);
    while (Q--) {
        int q, l, r;
        long long b;
        cin >> q >> l >> r;
        if (q < 3) {
            cin >> b;
            if (q == 0) segtree.apply(l, r, BF::chmin(b));
            if (q == 1) segtree.apply(l, r, BF::chmax(b));
            if (q == 2) segtree.apply(l, r, BF::add(b));
        } else {
            long long ret = segtree.prod(l, r).sum;
            cout << ret << '\n';
        }
    }
}
