#define PROBLEM "https://judge.yosupo.jp/problem/characteristic_polynomial"
#include "../characteristic_poly.hpp"
#include "../../modint.hpp"
#include "../hessenberg_reduction.hpp"
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
    hessenberg_reduction(M);
    auto poly = characteristic_poly_of_hessenberg<mint>(M);
    for (auto x : poly) cout << x << ' ';
    cout << '\n';
}
