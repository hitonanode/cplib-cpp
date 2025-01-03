#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include "../preorder_tree_dfs.hpp"
#include <cassert>
#include <iostream>
#include <atcoder/fenwicktree>
using namespace std;

int main() {
    int N, Q;
    cin >> N >> Q;
    vector<long long> A(N);
    vector<vector<int>> to(N);
    for (auto &a : A) cin >> a;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        to.at(p).push_back(i);
        to.at(i).push_back(p);
    }

    preorder_tree_dfs tour(to, 0);

    atcoder::fenwick_tree<long long> ft(N);
    for (int i = 0; i < N; i++) ft.add(tour.subtree_begin.at(i), A.at(i));

    while (Q--) {
        int q;
        cin >> q;
        if (q) {
            int u;
            cin >> u;
            printf("%lld\n", ft.sum(tour.subtree_begin[u], tour.subtree_end[u]));
        } else {
            int u, x;
            cin >> u >> x;
            ft.add(tour.subtree_begin[u], x);
        }
    }
}
