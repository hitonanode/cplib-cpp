#define PROBLEM "https://judge.yosupo.jp/problem/minimum_steiner_tree"
#include "../minimum_steiner_tree.hpp"

#include <iostream>
#include <tuple>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;

    vector<tuple<int, int, long long>> edges(M);
    for (auto &[u, v, w] : edges) cin >> u >> v >> w;

    int K;
    cin >> K;
    vector<int> terminals(K);
    for (auto &t : terminals) cin >> t;

    const auto [cost, used_edges] = MinimumSteinerTree(N, edges, terminals);
    cout << cost << ' ' << used_edges.size() << '\n';
    for (int i = 0; i < (int)used_edges.size(); ++i) {
        cout << used_edges.at(i) << (i + 1 < (int)used_edges.size() ? ' ' : '\n');
    }
}
