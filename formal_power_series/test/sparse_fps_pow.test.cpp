#define PROBLEM "https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse"
#include "../sparse_fps.hpp"
#include "../../modint.hpp"
#include <iostream>
#include <vector>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, K;
    long long M;
    cin >> N >> K >> M;
    vector<mint> f(N);
    while (K--) {
        int i, a;
        cin >> i >> a;
        f.at(i) = a;
    }

    const auto ret = sparse_fps::pow(f, N - 1, M);

    for (auto e : ret) cout << e << ' ';
    cout << '\n';
}
