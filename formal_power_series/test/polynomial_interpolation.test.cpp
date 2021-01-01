#define PROBLEM "https://judge.yosupo.jp/problem/polynomial_interpolation"
#include "../../modint.hpp"
#include "../formal_power_series.hpp"
#include "../multipoint_evaluation.hpp"
#include <iostream>
using namespace std;

using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    FormalPowerSeries<mint> f(N);
    vector<mint> xs(N), ys(N);
    for (auto &x : xs) cin >> x;
    for (auto &y : ys) cin >> y;

    auto ret = MultipointEvaluation<mint>(xs).polynomial_interpolation(ys);
    ret.resize(N);
    for (auto c : ret) cout << c << ' ';
    cout << '\n';
}
