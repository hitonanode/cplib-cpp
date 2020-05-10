#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
#include "modulus/modint_fixed.hpp"
#include "formal_power_series/formal_power_series.hpp"
#include "formal_power_series/multipoint_evaluation.hpp"
#include <iostream>

using mint = ModInt<998244353>;

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;
    FormalPowerSeries<ModInt<998244353>> f(N);
    std::vector<mint> xs(M);
    for (auto &a : f) std::cin >> a;
    for (auto &x : xs) std::cin >> x;

    MultipointEvaluation me(xs);
    for (auto x : me.evaluate_polynomial(f)) std::cout << x << ' ';
    std::cout << '\n';
}
