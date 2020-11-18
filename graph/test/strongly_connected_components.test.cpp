#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"
#include "graph/strongly_connected_components.hpp"

#include <stdio.h>

int main() {
    int V, E;
    scanf("%d %d", &V, &E);
    DirectedGraphSCC graph(V);
    while (E--) {
        int s, t;
        scanf("%d %d", &s, &t);
        graph.add_edge(s, t);
    }

    graph.FindStronglyConnectedComponents();

    int Q;
    scanf("%d", &Q);
    while (Q--) {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", graph.cmp[u] == graph.cmp[v]);
    }
}