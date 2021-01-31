#define PROBLEM "https://yukicoder.me/problems/no/1320"

#include "../shortest_cycle_weighted.hpp"
#include "../shortest_path.hpp"

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
        vector<vector<pair<int, int>>> to(N);
        while (M--) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            to[u].emplace_back(v, w);
        }
        for (int s = 0; s < N; s++) {
            ShortestPath<long long, INF> graph(N + 1);
            for (int i = 0; i < N; i++) {
                for (auto [j, w] : to[i]) {
                    graph.add_edge(i, j, w);
                    if (j == s) graph.add_edge(i, N, w);
                }
            }
            graph.solve(s);
            ret = min(ret, graph.dist[N]);
        }
    } else {
        // Undirected graph
        ShortestCycleOfUndirectedWeighted<long long, INF> graph(N);
        while (M--) {
            int u, v, w;
            cin >> u >> v >> w;
            u--, v--;
            graph.add_edge(u, v, w);
        }
        for (int i = 0; i < N; i++) ret = min(ret, graph.Solve(i).first);
    }
    cout << (ret < INF ? ret : -1) << '\n';
}
