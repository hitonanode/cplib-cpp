#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
#include "graph/lowlink.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B"

int main()
{
    int V, E;
    std::cin >> V >> E;
    UndirectedGraph graph(V);
    for (int i = 0; i < E; i++) {
        int s, t;
        std::cin >> s >> t;
        if (s > t) std::swap(s, t);
        graph.add_edge(s, t);
    }
    graph.detectBridge();

    std::vector<std::pair<int, int>> bridges;
    for (int i = 0; i < E; i++) {
        if (graph.is_bridge[i]) {
            bridges.emplace_back(graph.edges[i]);
        }
    }
    std::sort(bridges.begin(), bridges.end());
    for (auto pa : bridges) {
        printf("%d %d\n", pa.first, pa.second);
    }
}
