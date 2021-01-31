#pragma once
#include <cassert>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// Shortest cycle detection of UNDIRECTED SIMPLE graphs
// Verified: <https://yukicoder.me/submissions/594507>
template <typename T, T INF = std::numeric_limits<T>::max() / 2> struct ShortestCycleOfUndirectedWeighted {
    int V, E;
    std::vector<std::vector<std::pair<int, T>>> to; // (nxt, weight)
    ShortestCycleOfUndirectedWeighted() = default;
    ShortestCycleOfUndirectedWeighted(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, T len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        assert(len >= 0);
        to[s].emplace_back(t, len);
        to[t].emplace_back(s, len);
        E++;
    }

    std::vector<T> dist;
    std::vector<int> prev;
    // Find minimum length simple cycle which passes vertex `v`
    // - Complexity: O(E log V)
    // - return: (LEN, (a, b))
    //   - LEN: length of the shortest cycles if exists, INF ( = numeric_limits<int>::max() / 2 ) otherwise.
    //   - the cycle consists of vertices [v, ..., prev[prev[a]], prev[a], a, b, prev[b], prev[prev[b]], ..., v]
    std::pair<T, std::pair<int, int>> Solve(int v) {
        assert(0 <= v and v < V);
        dist.assign(V, INF), dist[v] = 0;
        prev.assign(V, -1);

        using P = std::pair<T, std::pair<int, int>>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        std::vector<std::pair<std::pair<int, int>, T>> add_edge;

        pq.emplace(0, std::make_pair(v, -1));
        while (!pq.empty()) {
            const int now = pq.top().second.first, prv = pq.top().second.second;
            pq.pop();
            for (const auto &nxt : to[now])
                if (nxt.first != prv) {
                    if (dist[nxt.first] == INF) {
                        dist[nxt.first] = dist[now] + nxt.second;
                        prev[nxt.first] = now;
                        pq.emplace(dist[nxt.first], std::make_pair(nxt.first, now));
                    } else {
                        add_edge.emplace_back(std::make_pair(now, nxt.first), nxt.second);
                    }
                }
        }
        T minimum_cycle = INF;
        int s = -1, t = -1;
        for (auto edge : add_edge) {
            int a = edge.first.first, b = edge.first.second;
            T L = dist[a] + dist[b] + edge.second;
            if (L < minimum_cycle) minimum_cycle = L, s = a, t = b;
        }
        return std::make_pair(minimum_cycle, std::make_pair(s, t));
    }
};
