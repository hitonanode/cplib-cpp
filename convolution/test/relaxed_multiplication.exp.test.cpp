#define PROBLEM "https://judge.yosupo.jp/problem/exp_of_formal_power_series"

#include "../../modint.hpp"
#include "../relaxed_multiplication.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    relaxed_multiplication<ModInt998244353> r;

    vector<ModInt998244353> f(N), ret;

    for (auto &x : f) cin >> x;

    {
        // Relaxed exp of f(x) (f[0] = 0)
        // h = exp(f) -> h' = f' * h, h[0] = 1
        // https://hotman78.hatenablog.com/entry/2023/01/04/173507

        ModInt998244353 pre = 1;
        for (int i = 0; i < N; ++i) {
            if (i) pre = r.add(f.at(i) * i, pre) / i;
            ret.push_back(pre);
        }
    }

    for (auto x : ret) cout << x << ' ';
    cout << endl;
}
