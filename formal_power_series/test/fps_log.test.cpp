#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"
#include <iostream>
#include "modulus/modint_fixed.hpp"
#include "formal_power_series/formal_power_series.hpp"
using namespace std;

int main()
{
    int N;
    cin >> N;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    A.shrink();
    auto ret = A.log(N);
    for (int i = 0; i < N; i++) printf("%d ", ret.coeff(i).val);
}
