#include "flow/maxflow.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"

int main() {
    int V, E;
    std::cin >> V >> E;
    mf_graph<int> graph(V);
    while (E--) {
        int u, v, c;
        std::cin >> u >> v >> c;
        graph.add_edge(u, v, c);
    }
    std::cout << graph.flow(0, V - 1) << std::endl;
}
