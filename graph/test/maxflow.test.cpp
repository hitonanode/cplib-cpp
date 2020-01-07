#include "graph/maxflow.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"

int main()
{
    int V, E;
    std::cin >> V >> E;
    MaxFlow<int> ff(V), dinic(V);
    while (E--) {
        int u, v, c;
        std::cin >> u >> v >> c;
        ff.add_edge(u, v, c);
        dinic.add_edge(u, v, c);
    }
    int ret_ff = ff.FF(0, V - 1);
    int ret_dinic = dinic.Dinic(0, V - 1);
    assert(ret_ff == ret_dinic);
    std::cout << ret_ff << std::endl;
}
