#define PROBLEM "https://yukicoder.me/problems/no/214"
#include "convolution/ntt.hpp"
#include "formal_power_series/monomial_mod_polynomial.hpp"
#include "modint.hpp"
using mint = ModInt<1000000007>;

#include <iostream>
#include <numeric>

std::vector<mint> gen_dp(std::vector<int> v, int n) {
    std::vector<std::vector<mint>> dp(n + 1, std::vector<mint>(v.back() * n + 1));
    dp[0][0] = 1;
    for (auto x : v) {
        for (int i = n - 1; i >= 0; i--) {
            for (int j = 0; j < dp[i].size(); j++)
                if (dp[i][j]) {
                    for (int k = 1; i + k <= n; k++) dp[i + k][j + x * k] += dp[i][j];
                }
        }
    }
    return dp.back();
}

int main() {
    long long N;
    int P, C;
    std::cin >> N >> P >> C;
    std::vector<mint> primes = gen_dp({2, 3, 5, 7, 11, 13}, P), composites = gen_dp({4, 6, 8, 9, 10, 12}, C);
    std::vector<mint> f_reversed = nttconv(primes, composites);
    std::vector<mint> dp(f_reversed.size());
    dp[0] = 1;
    for (int i = 0; i < dp.size(); i++) {
        for (int j = 1; i + j < dp.size(); j++) dp[i + j] += dp[i] * f_reversed[j];
    }

    for (auto &x : f_reversed) x = -x;
    f_reversed[0] = 1;

    std::vector<mint> g(f_reversed.size() - 1);
    g[0] = 1;
    if (N > f_reversed.size()) {
        long long d = N - f_reversed.size();
        N -= d;
        g = monomial_mod_polynomial<mint>(d, f_reversed);
    }

    auto prod_x = [&](std::vector<mint> v) -> std::vector<mint> {
        int K = v.size();
        std::vector<mint> c(K);
        c[0] = -v[K - 1] * f_reversed[K];
        for (int i = 1; i < K; i++) { c[i] = v[i - 1] - v[K - 1] * f_reversed[K - i]; }
        return c;
    };
    mint acc = 0;
    for (int i = N; i < f_reversed.size(); i++) acc += f_reversed[i];
    mint ret = 0;
    while (N) {
        mint p = std::inner_product(g.begin(), g.end(), dp.begin(), mint(0));
        ret -= acc * p;
        g = prod_x(g);
        N--;
        acc += f_reversed[N];
    }
    std::cout << ret << '\n';
}
