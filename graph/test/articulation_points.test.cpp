#include "../lowlink.hpp"
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A"

int main() {
    int V, E;
    std::cin >> V >> E;
    lowlink graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        std::cin >> s >> t;
        graph.add_edge(s, t);
    }
    graph.build();
    for (int i = 0; i < V; i++) {
        if (graph.is_articulation[i]) { printf("%d\n", i); }
    }
}
