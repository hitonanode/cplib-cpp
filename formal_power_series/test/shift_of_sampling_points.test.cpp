#define PROBLEM "https://judge.yosupo.jp/problem/shift_of_sampling_points_of_polynomial"
#include "../../modint.hpp"
#include "../factorial_power.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    using mint = ModInt<998244353>;
    int N, M, c;
    cin >> N >> M >> c;
    std::vector<mint> f(N);
    for (auto &x : f) cin >> x;
    auto ret = shift_of_sampling_points<mint>(f, c, M);
    for (auto x : ret) cout << x << ' ';
    cout << '\n';
}
