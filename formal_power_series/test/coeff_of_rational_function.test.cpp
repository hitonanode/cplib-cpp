#define PROBLEM "https://yukicoder.me/problems/no/215"
#include "modulus/modint_fixed.hpp"
#include "convolution/ntt.hpp"
#include "formal_power_series/coeff_of_rational_function.hpp"

using mint = ModInt<1000000007>;

#include <iostream>

using namespace std;
vector<mint> gen_dp(vector<int> v, int n)
{
    vector<vector<mint>> dp(n + 1, vector<mint>(v.back() * n + 1));
    dp[0][0] = 1;
    for (auto x : v)
    {
        for (int i = n - 1; i >= 0; i--)
        {
            for (int j = 0; j < dp[i].size(); j++) if (dp[i][j])
            {
                for (int k = 1; i + k <= n; k++) dp[i + k][j + x * k] += dp[i][j];
            }
        }
    }
    return dp.back();
}

int main()
{
    long long N;
    int P, C;
    cin >> N >> P >> C;
    vector<mint> primes = gen_dp({2, 3, 5, 7, 11, 13}, P), composites = gen_dp({4, 6, 8, 9, 10, 12}, C);
    vector<mint> f = nttconv(primes, composites);
    vector<mint> denom = f;
    for (auto &x : denom) x = -x;
    denom[0] = 1;
    for (int i = f.size() - 1; i > 1; i--) f[i - 1] += f[i];
    cout << coefficient_of_rational_function(N, f, denom) << '\n';
}
