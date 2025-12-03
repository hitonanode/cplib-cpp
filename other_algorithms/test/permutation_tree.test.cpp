#define PROBLEM "https://judge.yosupo.jp/problem/common_interval_decomposition_tree"
#include "../permutation_tree.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N;
    cin >> N;

    vector<int> P(N);
    for (auto &p : P) cin >> p;

    const permutation_tree pt(P);

    cout << pt.nodes.size() << '\n';

    for (const auto &node : pt.nodes) {
        cout << node.par_id << ' ' << node.L << ' ' << node.R - 1 << ' '
             << (node.tp == permutation_tree::Cut ? "prime" : "linear") << '\n';
    }
}
