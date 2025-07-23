#define PROBLEM "https://yukicoder.me/problems/no/3207"
#include "../wavelet_matrix.hpp"
#include "../../number/modint_mersenne61.hpp"

#include <iostream>
using namespace std;

using mint = ModIntMersenne61;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int H, W, N;
    cin >> H >> W >> N;

    const mint Bx{31979713531853};
    const mint By{23599715123};

    vector<mint> weights(10);
    for (int v : {1, 2, 5, 8, 6, 9}) weights[v] = mint(998244353).pow(v);

    wavelet_matrix<int> wm1, wm2;

    vector<tuple<int, int, int>> points;
    for (int t = 0; t < N; ++t) {
        int i, j, x;
        cin >> i >> j >> x;
        if (x == 0) continue;
        --i, --j;

        wm1.add_point(i, j);
        wm2.add_point(H - 1 - i, W - 1 - j);

        points.emplace_back(i, j, x);
    }
    wm1.build();
    wm2.build();

    vector dp1(wm1.D(), vector<mint>(wm1.N() + 1));
    vector dp2(wm2.D(), vector<mint>(wm2.N() + 1));

    for (auto [i, j, x] : points) {
        const mint wx = weights.at(x) * Bx.pow(i) * By.pow(j);
        wm1.apply(i, j, [&dp1, &wx](int d, int idx) { dp1[d][idx + 1] += wx; });

        int y = x;
        if (x == 6 or x == 9) y = x ^ (6 ^ 9);

        const mint wy = weights.at(y) * Bx.pow(H - 1 - i) * By.pow(W - 1 - j);
        wm2.apply(H - 1 - i, W - 1 - j, [&dp2, &wy](int d, int idx) { dp2[d][idx + 1] += wy; });
    }

    for (auto &v : dp1) {
        for (int i = 1; i < (int)v.size(); ++i) v[i] += v[i - 1];
    }
    for (auto &v : dp2) {
        for (int i = 1; i < (int)v.size(); ++i) v[i] += v[i - 1];
    }

    int Q;
    cin >> Q;
    while (Q--) {
        int l, d, r, u;
        cin >> l >> d >> r >> u;
        --l, --d;

        mint ans1{0}, ans2{0};
        wm1.prod(l, r, u, [&ans1, &dp1](int d, int l0, int r0) { ans1 += dp1[d][r0] - dp1[d][l0]; });
        wm1.prod(l, r, d, [&ans1, &dp1](int d, int l0, int r0) { ans1 -= dp1[d][r0] - dp1[d][l0]; });

        wm2.prod(H - r, H - l, W - d,
                 [&ans2, &dp2](int d, int l0, int r0) { ans2 += dp2[d][r0] - dp2[d][l0]; });
        wm2.prod(H - r, H - l, W - u,
                 [&ans2, &dp2](int d, int l0, int r0) { ans2 -= dp2[d][r0] - dp2[d][l0]; });

        if (ans1 * Bx.pow(H - r) * By.pow(W - u) == ans2 * Bx.pow(l) * By.pow(d)) {
            puts("Yes");
        } else {
            puts("No");
        }
    }
}
