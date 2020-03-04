#include <cassert>
#include <iostream>
#include <vector>
#include "graph/dijkstra.hpp"
#include "graph/shortest_path.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_A"

wedges e;

int main()
{
    int V, E, r;
    cin >> V >> E >> r;
    e.resize(V);
    ShortestPath<int> graph(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
        graph.add_edge(s, t, d);
    }
    auto ret = dijkstra(V, r, e);
    graph.Dijkstra(r);

    for (int i = 0; i < V; i++) {
        if (ret.first[i] == INF) puts("INF");
        else {
            assert(ret.first[i] == graph.dist[i]);
            printf("%lld\n", ret.first[i]);
        }
    }
}