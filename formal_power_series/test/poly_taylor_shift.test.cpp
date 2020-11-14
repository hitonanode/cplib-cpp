#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_taylor_shift"
#include "modulus/modint_fixed.hpp"
#include "formal_power_series/formal_power_series.hpp"
#include <iostream>
using namespace std;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, c;
    cin >> N >> c;
    FormalPowerSeries<ModInt<998244353>> f(N);
    for (auto &x : f) {
        cin >> x;
    }
    f = f.shift(c);
    for (int i = 0; i < N; i++) {
        cout << f.coeff(i) << (i < N - 1 ? ' ' : '\n');
    }
}
