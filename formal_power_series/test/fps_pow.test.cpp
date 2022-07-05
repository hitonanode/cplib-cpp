#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series"
#include "formal_power_series/formal_power_series.hpp"
#include "modint.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    long long M;
    cin >> N >> M;
    FormalPowerSeries<ModInt<998244353>> A(N);
    for (auto &a : A) cin >> a;
    A.shrink();
    auto ret = A.pow(M, N);
    for (int i = 0; i < N; i++) cout << ret.coeff(i) << ' ';
}
