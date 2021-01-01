#define PROBLEM "https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind"
#include "../../modint.hpp"
#include "../formal_power_series.hpp"
#include <iostream>
using namespace std;

FormalPowerSeries<ModInt<998244353>> solve(int N) {
    if (N == 0) { return {1}; }
    if (N == 1) { return {0, 1}; }
    int k = N / 2;
    auto f = solve(k);
    f *= f.shift(-k);
    if (N % 2) { f *= {-(N - 1), 1}; }
    return f;
}

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    auto ret = solve(N);
    for (int i = 0; i <= N; i++) cout << ret.coeff(i) << (i == N ? '\n' : ' ');
}
