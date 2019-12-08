#include <iostream>
#include <utility>
#include "graph/lowlink.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

int main()
{
    int V, E;
    cin >> V >> E;
    UndirectedGraph graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        if (s > t) swap(s, t);
        graph.add_edge(s, t);
    }
    graph.dfs_lowlink(0);
    graph.detectBridge();

    vector<pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.isBridge[i]) {
            bridges.emplace_back(graph.edges[i]);
        }
    }
    sort(bridges.begin(), bridges.end());
    for (auto pa : bridges) {
        printf("%d %d\n", pa.first, pa.second);
    }
}
