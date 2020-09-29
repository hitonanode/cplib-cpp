#include <iostream>
#include "flow/mincostflow_acl.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"


int main()
{
    int V, E, F;
    std::cin >> V >> E >> F;
    mcf_graph<long long, long long> mcf(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, c, d;
        std::cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, c, d);
    }

    auto [cap, cost] = mcf.flow(0, V - 1, F);
    std::cout << (cap == F ? cost : -1) << '\n';
}
