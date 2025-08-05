#define PROBLEM                                                                                   \
    "https://judge.yosupo.jp/problem/rooted_tree_topological_order_with_minimum_inversions"
#include "../tree_pop_order_optimization.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<vector<int>> to(N);

    for (int i = 1; i < N; ++i) {
        int p;
        cin >> p;
        to.at(p).push_back(i);
        to.at(i).push_back(p);
    }

    vector<long long> c(N), d(N);
    for (auto &e : c) cin >> e;
    for (auto &e : d) cin >> e;

    const auto [order, ret] = Solve01OnTree(to, c, d, 0);
    cout << ret << '\n';
    for (auto e : order) cout << e << ' ';
    cout << '\n';
}
