#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include "../trees/range-chmin-chmax-add-range-sum.hpp"
#include <iostream>
#include <vector>
using namespace std;

using RCCARS = RangeChminChmaxAddRangeSum<long long, (1LL << 60)>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<RCCARS::S> A(N);
    for (auto &a : A) {
        long long tmp;
        cin >> tmp, a = RCCARS::Gen(tmp);
    }

    RCCARS::segtree segtree(A);

    while (Q--) {
        int q, l, r;
        long long b;
        cin >> q >> l >> r;
        if (q < 3) {
            cin >> b;
            if (q == 0) segtree.apply(l, r, RCCARS::Chmin(b));
            if (q == 1) segtree.apply(l, r, RCCARS::Chmax(b));
            if (q == 2) segtree.apply(l, r, RCCARS::Add(b));
        } else {
            long long ret = segtree.prod(l, r).sum;
            cout << ret << '\n';
        }
    }
}
