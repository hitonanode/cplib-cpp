#define PROBLEM "https://judge.yosupo.jp/problem/enumerate_triangles"
#include "../enumerate_triangles.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    EnumerateTriangles graph(N);
    vector<unsigned> X(N);
    for (auto &x : X) cin >> x;
    while (M--) {
        int u, v;
        cin >> u >> v;
        graph.add_edge(u, v);
    }
    unsigned long long ret = 0;
    constexpr unsigned md = 998244353;
    auto f = [&](int i, int j, int k) {
        (ret += (unsigned long long)X[i] * X[j] % md * X[k]) %= md;
    };
    graph.run(f);
    cout << ret << '\n';
}
