#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"
#include "graph/strongly_connected_components_bitset.hpp"

#include <cassert>
#include <stdio.h>
constexpr int VMAX = 10000;
int main()
{
    int V, E;
    scanf("%d %d", &V, &E);
    assert(V < VMAX);
    std::vector<std::bitset<VMAX>> e(V), einv(V);
    while (E--)
    {
        int s, t;
        scanf("%d %d", &s, &t);
        e[s][t] = einv[t][s] = 1;
    }
    DirectedGraphSCC64<VMAX> graph(e, einv);

    int Q;
    scanf("%d", &Q);
    while (Q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", graph.cmp[u] == graph.cmp[v]);
    }
}
