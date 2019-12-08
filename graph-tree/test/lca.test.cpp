#include <iostream>
#include "graph-tree/lowest_common_ancestor.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main()
{
    int N, Q, p, u, v;
    cin >> N >> Q;
    UndirectedWeightedTree graph(N);
    for (int i = 1; i <= N - 1; i++) {
        cin >> p;
        graph.add_edge(i, p, 1);
    }
    graph.fix_root(0);
    graph.doubling_precalc();

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        cout << graph.lowest_common_ancestor(u, v) << endl;
    }
}
