#include <iostream>
#include "graph/lowlink.hpp"
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B

int main()
{
    int V, E;
    cin >> V >> E;
    UndirectedGraph graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        cin >> s >> t;
        graph.add_edge(s, t);
    }
    graph.dfs_lowlink(0);
    graph.detectBridge();
    for (int i = 0; i < E; i++) {
        if (graph.isBridge[i]) {
            printf("%d %d\n", graph.edges[i].first, graph.edges[i].second);
        }
    }
}
