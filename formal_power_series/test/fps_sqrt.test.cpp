#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series"
#include <iostream>
#include "modint.hpp"
#include "formal_power_series/formal_power_series.hpp"
using namespace std;

int main()
{
    int N;
    cin >> N;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    A.shrink();
    auto ret = A.sqrt(N);
    if (ret.empty() and !A.empty()) puts("-1");
    else for (int i = 0; i < N; i++) printf("%d ", ret.coeff(i).val);
}
