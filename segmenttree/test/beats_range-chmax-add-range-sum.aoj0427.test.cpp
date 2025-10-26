#include "../trees/range-chmax-add-range-sum.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=0427"
#include <iostream>
using namespace std;

using RCARS = RangeChmaxAddRangeSum<long long, (1LL << 60)>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, tmp;
    cin >> N;
    vector<RCARS::S> A(N);
    for (auto &a : A) cin >> tmp, a = RCARS::Gen(tmp);

    RCARS::segtree segtree(A);

    int Q, q, l, r, d;
    cin >> Q;

    while (Q--) {
        cin >> q >> l >> r >> d;
        l--;
        if (q == 1) {
            segtree.apply(l, r, RCARS::Add(d));
        } else {
            auto before = segtree.prod(l, r).sum;
            auto f1 = RCARS::Add(-d);
            auto f2 = RCARS::Chmax(0);
            segtree.apply(l, r, RCARS::composition(f2, f1));
            auto after = segtree.prod(l, r).sum;
            cout << before - after << '\n';
        }
    }
}
