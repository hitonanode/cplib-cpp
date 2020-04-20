#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"
#include <iostream>
#include "modulus/modint_fixed.hpp"
#include "formal_power_series/formal_power_series.hpp"

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, M;
    std::cin >> N >> M;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (auto &a : A) std::cin >> a;
    A.shrink();
    auto ret = A.pow(M, N);
    for (int i = 0; i < N; i++) std::cout << ret.coeff(i) << ' ';
}
