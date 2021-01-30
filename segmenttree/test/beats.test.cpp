#define PROBLEM "https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum"
#include "../acl_beats.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<RangeChMinMaxAddSum::S> A(N);
    for (auto &a : A) {
        long long tmp;
        cin >> tmp, a = {tmp, 1};
    }
    RangeChMinMaxAddSum::segtree segtree(A);
    while (Q--) {
        int q, l, r;
        long long b;
        cin >> q >> l >> r;
        if (q < 3) {
            cin >> b;
            if (q == 0) segtree.apply(l, r, RangeChMinMaxAddSum::F::chmin(b));
            if (q == 1) segtree.apply(l, r, RangeChMinMaxAddSum::F::chmax(b));
            if (q == 2) segtree.apply(l, r, RangeChMinMaxAddSum::F::add(b));
        } else {
            long long ret = segtree.prod(l, r).sum;
            cout << ret << '\n';
        }
    }
}
