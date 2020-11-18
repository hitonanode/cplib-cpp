#include "graph/general_matching.hpp"
#include <iostream>
#include <utility>
#include <vector>
#define PROBLEM "https://judge.yosupo.jp/problem/general_matching"

using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    vector<pair<int, int>> edges;
    while (M--) {
        int u, v;
        cin >> u >> v;
        edges.emplace_back(u, v);
    }
    vector<pair<int, int>> ret = generalMatching(N, edges);
    cout << ret.size() << '\n';
    for (auto [a, b] : ret) { cout << a << ' ' << b << '\n'; }
}
