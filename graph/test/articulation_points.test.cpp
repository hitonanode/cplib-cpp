#include <iostream>
#include "graph/lowlink.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"

int main()
{
    int V, E;
    std::cin >> V >> E;
    UndirectedGraph graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, t);
    }
    graph.dfs_lowlink(0);
    graph.detectArticulation();
    for (int i = 0; i < V; i++) {
        if (graph.is_articulation[i]) {
            printf("%d\n", i);
        }
    }
}
