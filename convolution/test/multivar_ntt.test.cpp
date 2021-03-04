#define PROBLEM "https://judge.yosupo.jp/problem/multivariate_convolution"
#include "../../modint.hpp"
#include "../multivar_ntt.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int K;
    cin >> K;
    vector<int> N(K);
    for (auto &x : N) cin >> x;

    multivar_ntt<ModInt<998244353>> mvntt(N);
    vector<decltype(mvntt.invfftlen)> f(mvntt.N), g(mvntt.N);
    for (auto &x : f) cin >> x;
    for (auto &x : g) cin >> x;
    auto ret = mvntt(f, g);
    for (auto x : ret) cout << x << ' ';
    cout << '\n';
}
