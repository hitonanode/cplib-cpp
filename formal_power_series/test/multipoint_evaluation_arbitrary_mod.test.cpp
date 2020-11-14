#define PROBLEM "https://judge.yosupo.jp/problem/multipoint_evaluation"
#include "modint.hpp"
#include "formal_power_series/formal_power_series.hpp"
#include "formal_power_series/multipoint_evaluation.hpp"
#include <iostream>
using namespace std;

using mint = ModInt<998244353>;

int main()
{
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    FormalPowerSeries<ModInt<998244353>> f(N);
    vector<mint> xs(M);
    for (auto &a : f) cin >> a;
    for (auto &x : xs) cin >> x;

    MultipointEvaluation me(xs);
    for (auto x : me.evaluate_polynomial(f)) cout << x << ' ';
    cout << '\n';
}
