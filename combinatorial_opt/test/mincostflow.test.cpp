#include "../mincostflow.hpp"
#include "../mincostflow_bellmanford.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"

int main() {
    int V, E, F;
    std::cin >> V >> E >> F;
    mcf_graph<long long, long long> mcf_ac(V);
    MinCostFlow<long long, long long> mcf_bf(V);
    for (int i = 0; i < E; i++) {
        int u, v, c, d;
        std::cin >> u >> v >> c >> d;
        mcf_ac.add_edge(u, v, c, d);
        mcf_bf.add_edge(u, v, c, d);
    }

    auto capcost_ac = mcf_ac.flow(0, V - 1, F);
    auto capcost_bf = mcf_bf.flow(0, V - 1, F);
    assert(capcost_ac == capcost_bf);
    std::cout << (capcost_ac.first == F ? capcost_ac.second : -1) << '\n';
}
