#define PROBLEM "https://yukicoder.me/problems/no/1320"

#include "../shortest_cycle.hpp"

#include <iostream>
#include <vector>
using namespace std;

int main() {
    int T, N, M;
    cin >> T >> N >> M;
    const long long INF = 1LL << 60;
    long long ret = INF;

    if (T == 1) {
        // Directed graph
        shortest_cycle<true, long long> graph(N);
        while (M--) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            graph.add_edge(u, v, w);
        }
        for (int s = 0; s < N; s++) {
            auto len = graph.Solve(s).first;
            if (len >= 0) ret = min(ret, len);
        }
    } else {
        // Undirected graph
        shortest_cycle<false, long long> graph(N);
        while (M--) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            graph.add_bi_edge(u, v, w);
        }
        for (int i = 0; i < N; i++) {
            auto len = graph.Solve(i).first;
            if (len >= 0) ret = min(ret, len);
        }
    }
    cout << (ret < INF ? ret : -1) << '\n';
}
