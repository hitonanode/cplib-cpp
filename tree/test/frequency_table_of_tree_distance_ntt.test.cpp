#include "../../convolution/ntt.hpp"
#include "../../modint.hpp"
#include "../../number/bare_mod_algebra.hpp"
#include "../frequency_table_of_tree_distance.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/frequency_table_of_tree_distance"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<vector<int>> to(N);
    for (int i = 0; i < N - 1; i++) {
        int s, t;
        cin >> s >> t;
        to[s].emplace_back(t), to[t].emplace_back(s);
    }

    frequency_table_of_tree_distance solver(to);

    using mint1 = ModInt<998244353>;
    using mint2 = ModInt<167772161>;
    const vector<mint1> ret1 =
        frequency_table_of_tree_distance(to).solve<mint1, nttconv<mint1>>(std::vector<mint1>(N, 1));
    const vector<mint2> ret2 =
        frequency_table_of_tree_distance(to).solve<mint2, nttconv<mint2>>(std::vector<mint2>(N, 1));
    for (int i = 1; i < N; i++) {
        auto v = crt<long long>({ret1[i].val(), ret2[i].val()}, {mint1::mod(), mint2::mod()});
        cout << v.first << ' ';
    }
    cout << '\n';
}
