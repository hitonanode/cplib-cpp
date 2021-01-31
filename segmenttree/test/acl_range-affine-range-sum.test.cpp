#include "../../modint.hpp"
#include "../trees/acl_range-affine-range-sum.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/range_affine_range_sum"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;

    vector<RangeAffineRangeSum::S> A(N);
    for (auto &a : A) cin >> a.first, a.second = 1;
    RangeAffineRangeSum::segtree segtree(A);
    while (Q--) {
        int q, l, r;
        cin >> q >> l >> r;
        if (q) {
            cout << segtree.prod(l, r).first << '\n';
        } else {
            RangeAffineRangeSum::F f;
            cin >> f.first >> f.second;
            segtree.apply(l, r, f);
        }
    }
}
