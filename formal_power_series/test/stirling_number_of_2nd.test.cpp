#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind"
#include "formal_power_series/formal_power_series.hpp"
#include "modint.hpp"
#include <iostream>
using namespace std;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    using mint = ModInt<998244353>;
    FormalPowerSeries<mint> a(N + 1);
    a[N] = mint(N).fac().inv();
    for (int i = N - 1; i >= 0; i--) {
        a[i] = a[i + 1] * (i + 1);
    }
    auto b = a;
    for (int i = 0; i <= N; i++) {
        a[i] *= mint(i).pow(N), b[i] *= (i % 2 ? -1 : 1);
    }
    a *= b;

    for (int i = 0; i <= N; i++) {
        cout << a.coeff(i) << (i == N ? '\n' : ' ');
    }
}
