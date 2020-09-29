#include <iostream>
#include "flow/mincostflow.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B"


int main()
{
    int V, E, F;
    std::cin >> V >> E >> F;
    MinCostFlow mcf(V);
    for (int i = 0; i < E; i++)
    {
        int u, v, c, d;
        std::cin >> u >> v >> c >> d;
        mcf.add_edge(u, v, c, d);
    }

    auto ret = mcf.flush(0, V - 1, F);
    std::cout << (ret.second.first ? ret.first : -1) << '\n';
}