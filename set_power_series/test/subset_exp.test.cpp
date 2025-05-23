#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_set_power_series"
#include "../../modint.hpp"
#include "../subset_convolution.hpp"
#include <iostream>
using namespace std;
using mint = ModInt<998244353>;

int main() {
    cin.tie(nullptr);
    ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<mint> f(1 << N);
    for (auto &x : f) cin >> x;
    subset_exp(f);
    for (int i = 0; i < 1 << N; i++) cout << f.at(i) << " \n"[i + 1 == 1 << N];
}
