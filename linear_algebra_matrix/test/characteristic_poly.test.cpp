#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"
#include "../characteristic_poly.hpp"
#include "../../modint.hpp"
#include "../matrix.hpp"
#include <algorithm>
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    using mint = ModInt<998244353>;
    matrix<mint> M(N, N);
    cin >> M;
    auto poly = characteristic_poly<mint>(M);
    for (auto x : poly) cout << x << ' ';
    cout << '\n';
}
