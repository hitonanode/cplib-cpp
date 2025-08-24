#define PROBLEM "https://yukicoder.me/problems/no/215"
#include "../coeff_of_rational_function.hpp"
#include "../../convolution/ntt.hpp"
#include "../../modint.hpp"

using mint = ModInt<1000000007>;

#include <iostream>

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
    std::vector<mint> primes = gen_dp({2, 3, 5, 7, 11, 13}, P),
                      composites = gen_dp({4, 6, 8, 9, 10, 12}, C);
    std::vector<mint> f = nttconv(primes, composites);
    std::vector<mint> denom = f;
    for (auto &x : denom) x = -x;
    denom[0] = 1;
    for (int i = f.size() - 1; i > 1; i--) f[i - 1] += f[i];
    std::cout << coefficient_of_rational_function(N, f, denom) << '\n';
}
