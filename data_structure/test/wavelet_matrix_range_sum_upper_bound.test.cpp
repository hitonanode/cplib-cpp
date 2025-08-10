#define PROBLEM "https://judge.yosupo.jp/problem/static_range_sum_with_upper_bound"
#include "../wavelet_matrix.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N);
    for (auto &a : A) cin >> a;
    const wavelet_matrix<int> wm(A);

    vector weights(wm.D(), vector<long long>(wm.N() + 1));
    for (int i = 0; i < N; ++i) {
        wm.index_apply(i, [&](int d, int idx) { weights[d][idx + 1] += A[i]; });
    }

    for (auto &v : weights) {
        for (int i = 1; i < (int)v.size(); ++i) v[i] += v[i - 1];
    }

    while (Q--) {
        int l, r, x;
        cin >> l >> r >> x;
        const int cnt = wm.range_freq(l, r, x + 1);

        long long sum = 0;
        wm.prod(l, r, x + 1, [&](int d, int L, int R) { sum += weights[d][R] - weights[d][L]; });

        cout << cnt << ' ' << sum << '\n';
    }
}
