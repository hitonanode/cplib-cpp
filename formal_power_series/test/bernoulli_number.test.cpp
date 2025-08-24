#define PROBLEM "https://judge.yosupo.jp/problem/bernoulli_number"
#include "../formal_power_series.hpp"
#include "../../modint.hpp"
#include <iostream>
using namespace std;

int main() {
    int N;
    cin >> N;
    using mint = ModInt<998244353>;
    FormalPowerSeries<mint> x({0, 1});
    FormalPowerSeries<mint> b = ((x.exp(N + 2) - 1) >> 1).inv(N + 1);
    for (int i = 0; i <= N; i++) printf("%d ", (b.coeff(i) * mint(i).fac()).val());
}
