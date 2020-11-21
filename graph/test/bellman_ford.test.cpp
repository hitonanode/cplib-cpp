#include "../bellman_ford.hpp"
#include "../shortest_path.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"

wedges e;

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    ShortestPath<long long> graph(V);
    e.resize(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        e[s].emplace_back(t, d);
        graph.add_edge(s, t, d);
    }
    vector<long long> ret = bellman_ford(r, e, V);

    if (!graph.BellmanFord(r, V + 1)) {
        puts("NEGATIVE CYCLE");
        return 0;
    }

    for (int i = 0; i < V; i++) {
        if (graph.dist[i] >= INF) {
            assert(ret[i] == INF);
            puts("INF");
        } else {
            assert(ret[i] == graph.dist[i]);
            printf("%lld\n", graph.dist[i]);
        }
    }
}
