#include <iostream>
#include <vector>
#include "graph/bellman_ford.hpp"
#define PROBLEM http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B

wedges e;

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    e.resize(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
    }
    vector<lint> ret = bellman_ford(r, e, V);
    vector<lint> ret2 = bellman_ford(r, e, V + 1);

    for (int i = 0; i < V; i++) {
        if (ret[i] != ret2[i]) {
            puts("NEGATIVE CYCLE");
            return 0;
        }
    }

    for (int i = 0; i < V; i++) {
        if (ret[i] == INF) puts("INF");
        else printf("%lld\n", ret[i]);
    }
}