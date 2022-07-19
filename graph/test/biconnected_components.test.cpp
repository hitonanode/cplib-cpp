#define PROBLEM "https://judge.yosupo.jp/problem/biconnected_components"
#include "../lowlink.hpp"
#include <iostream>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, M;
    cin >> N >> M;
    lowlink graph(N);
    while (M--) {
        int a, b;
        cin >> a >> b;
        graph.add_edge(a, b);
    }

    auto ret = graph.biconnected_components_by_vertices();
    cout << ret.size() << '\n';
    for (const auto &vec : ret) {
        cout << vec.size();
        for (auto x : vec) cout << ' ' << x;
        cout << '\n';
    }
}
