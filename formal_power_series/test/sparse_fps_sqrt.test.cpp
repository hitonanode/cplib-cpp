#define PROBLEM "https://judge.yosupo.jp/problem/sqrt_of_formal_power_series_sparse"
#include "../sparse_fps.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, K;
    cin >> N >> K;
    vector<mint> f(N);
    while (K--) {
        int i, a;
        cin >> i >> a;
        f.at(i) = a;
    }

    const auto ret = sparse_fps::sqrt(f, N - 1);
    if (!ret) {
        cout << -1 << '\n';
    } else {
        for (auto e : *ret) cout << e << ' ';
        cout << '\n';
    }
}
