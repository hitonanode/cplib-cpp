#define PROBLEM "https://judge.yosupo.jp/problem/two_edge_connected_components"
#include "../lowlink.hpp"
#include <iostream>
#include <vector>
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);

    int V, E;
    cin >> V >> E;
    lowlink graph(V);
    while (E--) {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
    }

    auto ret = graph.two_edge_connected_components();
    cout << ret.size() << '\n';
    for (const auto &vec : ret) {
        cout << vec.size();
        for (auto x : vec) cout << ' ' << x;
        cout << '\n';
    }
}
