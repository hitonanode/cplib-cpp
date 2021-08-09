#define PROBLEM "https://atcoder.jp/contests/arc105/tasks/arc105_f"
#include "../../modint.hpp"
#include "../subset_convolution.hpp"
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

// https://codeforces.com/blog/entry/83535?#comment-709269
int main() {
    int N, M;
    cin >> N >> M;
    vector<int> to(N);
    while (M--) {
        int a, b;
        cin >> a >> b;
        a--, b--;
        to[a] += 1 << b, to[b] += 1 << a;
    }

    const mint inv2 = mint(2).inv();
    vector<mint> pow2(N * N + 1, 1), pow2inv(N * N + 1, 1);
    for (int i = 1; i <= N * N; i++) pow2[i] = pow2[i - 1] * 2, pow2inv[i] = pow2inv[i - 1] * inv2;

    vector<int> nbe(1 << N);
    vector<mint> f(1 << N);
    for (int s = 0; s < 1 << N; s++) {
        for (int i = 0; i < N; i++) nbe[s] += __builtin_popcount(to[i] & s) * ((s >> i) & 1);
        nbe[s] /= 2;
        f[s] = pow2inv[nbe[s]];
    }
    f = subset_convolution(f, f);
    for (int s = 0; s < 1 << N; s++) f[s] *= pow2[nbe[s]];
    subset_log(f);
    cout << f.back() / 2 << '\n';
}
