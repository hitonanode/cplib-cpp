#include "../static_range_inversion.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/static_range_inversions_query"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (auto &a : A) cin >> a;
    StaticRangeInversion<int> riq(A);

    while (Q--) {
        int l, r;
        cin >> l >> r;
        cout << riq.get(l, r) << '\n';
    }
}
