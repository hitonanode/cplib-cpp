#include "../trees/acl_range-add-chmax-range-sum.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, tmp;
    cin >> N;
    vector<RangeAddChmaxRangeSum::S> A(N);
    for (auto &a : A) cin >> tmp, a = tmp;

    RangeAddChmaxRangeSum::segtree segtree(A);

    int Q, q, l, r, d;
    cin >> Q;

    while (Q--) {
        cin >> q >> l >> r >> d;
        l--;
        if (q == 1) {
            segtree.apply(l, r, RangeAddChmaxRangeSum::F::add(d));
        } else {
            auto before = segtree.prod(l, r).sum;
            auto f1 = RangeAddChmaxRangeSum::F::add(-d);
            auto f2 = RangeAddChmaxRangeSum::F::chmax(0);
            segtree.apply(l, r, RangeAddChmaxRangeSum::composition(f2, f1));
            auto after = segtree.prod(l, r).sum;
            cout << before - after << '\n';
        }
    }
}
