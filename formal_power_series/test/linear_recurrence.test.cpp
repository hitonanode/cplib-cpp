#include "../linear_recurrence.hpp"
#include "../../modint.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/find_linear_recurrence"
#include <iostream>
using namespace std;

using mint = ModInt<998244353>;
int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;
    vector<mint> A(N);
    for (auto &a : A) cin >> a;

    auto L_poly = find_linear_recurrence(A);
    auto L = L_poly.first;
    auto poly = L_poly.second;

    cout << L << '\n';
    for (int i = 1; i <= L; i++) cout << -poly[i] << ' ';
    cout << '\n';
}
