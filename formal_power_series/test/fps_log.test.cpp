#define PROBLEM "https://judge.yosupo.jp/problem/log_of_formal_power_series"
#include "formal_power_series/formal_power_series.hpp"
#include "modint.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (int i = 0; i < N; i++) cin >> A[i];
    auto ret = A.log(N);
    for (int i = 0; i < N; i++) printf("%d ", ret.coeff(i).val());
}
