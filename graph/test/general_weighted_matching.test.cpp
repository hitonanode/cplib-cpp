#include "../general_weighted_matching.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/general_weighted_matching"

#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int N, M;
    cin >> N >> M;
    MaxWeightedMatching g(N);
    while (M--) {
        int u, v, w;
        cin >> u >> v >> w;
        g.add_edge(u, v, w);
    }
    auto ret = g.solve();
    cout << ret.sz << ' ' << ret.solution << '\n';
    for (int i = 0; i < N; ++i) {
        if (ret.mate.at(i) > i) cout << i << ' ' << ret.mate.at(i) << '\n';
    }
}
