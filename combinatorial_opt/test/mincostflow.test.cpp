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

    auto [cap_ac, cost_ac] = mcf_ac.flow(0, V - 1, F);
    auto [cap_bf, cost_bf] = mcf_bf.flow(0, V - 1, F);
    assert(cap_ac == cap_bf and cost_ac == cost_bf);
    std::cout << (cap_ac == F ? cost_ac : -1) << '\n';
}
