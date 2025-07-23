#define PROBLEM "https://judge.yosupo.jp/problem/rectangle_sum"
#include "../wavelet_matrix.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q;
    cin >> N >> Q;

    wavelet_matrix<int> wm;
    vector<tuple<int, int, int>> points(N);
    for (auto &[i, j, x] : points) {
        cin >> i >> j >> x;
        wm.add_point(i, j);
    }

    wm.build();

    vector weights(wm.D(), vector<long long>(wm.N() + 1));
    for (auto [i, j, x] : points) {
        wm.apply(i, j, [&weights, x](int d, int idx) { weights[d][idx + 1] += x; });
    }

    for (auto &v : weights) {
        for (int i = 1; i < (int)v.size(); ++i) v[i] += v[i - 1];
    }

    while (Q--) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;

        long long ans = 0;
        wm.prod(l, r, u, [&weights, &ans](int d, int l0, int r0) {
            ans += weights[d][r0] - weights[d][l0];
        });
        wm.prod(l, r, d, [&weights, &ans](int d, int l0, int r0) {
            ans -= weights[d][r0] - weights[d][l0];
        });

        cout << ans << '\n';
    }
}
