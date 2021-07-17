#include "../lowest_common_ancestor.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/lca"
using namespace std;

int main() {
    cin.tie(nullptr), ios::sync_with_stdio(false);
    int N, Q, p, u, v;
    cin >> N >> Q;
    UndirectedWeightedTree<int> graph(N);
    for (int i = 1; i <= N - 1; i++) {
        cin >> p;
        graph.add_edge(i, p, 1);
    }
    graph.fix_root(0);

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        cout << graph.lowest_common_ancestor(u, v) << endl;
    }
}
