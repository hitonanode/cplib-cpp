#include "../../segmenttree/binary_indexed_tree.hpp"
#include "../guni.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    guni g(N);
    vector<int> A(N);
    for (auto &a : A) cin >> a;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        g.add_bi_edge(p, i);
    }
    BIT<long long> bit(Q);
    vector<long long> ret(Q, -1);
    vector<vector<pair<int, int>>> v2t2add(N), v2t2sol(N);

    for (int i = 0; i < N; ++i) v2t2add.at(i).emplace_back(0, A.at(i));

    for (int t = 0; t < Q; ++t) {
        int tp, u;
        cin >> tp >> u;
        if (tp == 0) {
            int x;
            cin >> x;
            v2t2add.at(u).emplace_back(t, x);
        } else {
            v2t2sol.at(u).emplace_back(t, -1);
        }
    }

    auto Add = [&](int v) {
        for (auto [t, w] : v2t2add.at(v)) bit.add(t, w);
    };

    auto Remove = [&](int v) {
        for (auto [t, w] : v2t2add.at(v)) bit.add(t, -w);
    };

    auto Solve = [&](int v) {
        for (auto [t, _] : v2t2sol.at(v)) ret.at(t) = bit.sum(0, t + 1);
    };

    g.run(0, Add, Remove, Solve);

    for (auto x : ret) {
        if (x >= 0) cout << x << '\n';
    }
}
