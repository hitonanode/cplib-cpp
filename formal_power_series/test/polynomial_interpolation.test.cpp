#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"
#include "modulus/modint_fixed.hpp"
#include "formal_power_series/formal_power_series.hpp"
#include "formal_power_series/multipoint_evaluation.hpp"
#include <iostream>
using namespace std;

using mint = ModInt<998244353>;

int main()
{
    cin.tie(NULL);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    FormalPowerSeries<ModInt<998244353>> f(N);
    vector<mint> xs(N), ys(N);
    for (auto &x : xs) cin >> x;
    for (auto &y : ys) cin >> y;

    auto ret = MultipointEvaluation(xs).polynomial_interpolation(ys);
    ret.resize(N);
    for (auto c : ret) std::cout << c << ' ';
    std::cout << '\n';
}
