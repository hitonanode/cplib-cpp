#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"
#include <iostream>
#include "modulus/modint_fixed.hpp"
#include "formal_power_series/formal_power_series.hpp"
using namespace std;

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);
    int N;
    cin >> N;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    A.shrink();
    auto ret = A.exp(N);
    for (int i = 0; i < N; i++) printf("%d ", ret.coeff(i).val);
}
