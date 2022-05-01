#include "../shortest_path.hpp"
#include <iostream>
#include <vector>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_1_B"
using namespace std;

int main() {
    int V, E, r;
    cin >> V >> E >> r;
    shortest_path<long long> graph(V);
    for (int i = 0; i < E; i++) {
        int s, t, d;
        cin >> s >> t >> d;
        graph.add_edge(s, t, d);
    }

    if (!graph.bellman_ford(r, V + 1)) {
        puts("NEGATIVE CYCLE");
        return 0;
    }

    for (int i = 0; i < V; i++) {
        if (graph.dist[i] >= 1LL << 50) {
            puts("INF");
        } else {
            printf("%lld\n", graph.dist[i]);
        }
    }
}
