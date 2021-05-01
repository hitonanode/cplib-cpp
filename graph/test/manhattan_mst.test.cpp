#define PROBLEM "https://judge.yosupo.jp/problem/manhattanmst"
#include "../../unionfind/unionfind.hpp"
#include "../manhattan_mst.hpp"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N;
    cin >> N;
    vector<int> xs(N), ys(N);
    for (int i = 0; i < N; i++) cin >> xs[i] >> ys[i];
    UnionFind uf(N);
    long long weight = 0;
    vector<pair<int, int>> edges;
    for (auto [w, i, j] : manhattan_mst(xs, ys)) {
        if (uf.unite(i, j)) {
            weight += w;
            edges.emplace_back(i, j);
        }
    }
    cout << weight << '\n';
    for (auto p : edges) cout << p.first << ' ' << p.second << '\n';
}
