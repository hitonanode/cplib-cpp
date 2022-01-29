#define PROBLEM "https://yukicoder.me/problems/no/886"

#include "../../modint.hpp"
#include "../zeta_moebius_transform.hpp"
#include <iostream>
#include <vector>
using namespace std;

using mint = ModInt<1000000007>;

int main() {
    int H, W;
    cin >> H >> W;
    int N = max(H, W);
    vector<mint> dp(N);

    auto calc = [&](int n, int W) -> mint {
        // 2 * ((W - n) + (W - 2 * n) + ...)
        mint k = W / n;
        return W * k * 2 - k * (k + 1) * n;
    };

    for (int n = 1; n < N; ++n) {
        mint n1 = calc(n, H), n2 = calc(n, W);
        dp[n] = (n1 + H) * (n2 + W) - mint(H) * W;
    }
    multiple_moebius(dp);
    cout << dp[1] / 2 << '\n';
}
