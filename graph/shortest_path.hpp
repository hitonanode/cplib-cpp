#pragma once
#include <cassert>
#include <deque>
#include <functional>
#include <limits>
#include <queue>
#include <utility>
#include <vector>

// CUT begin
template <typename T, T INF = std::numeric_limits<T>::max() / 2> struct ShortestPath {
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, T>>> to;
    ShortestPath() = default;
    ShortestPath(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, T len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        to[s].emplace_back(t, len);
        E++;
    }

    std::vector<T> dist;
    std::vector<int> prev;
    // Dijkstra algorithm
    // Complexity: O(E log E)
    void Dijkstra(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, INF);
        dist[s] = 0;
        prev.assign(V, INVALID);
        using P = std::pair<T, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        pq.emplace(0, s);
        while (!pq.empty()) {
            T d;
            int v;
            std::tie(d, v) = pq.top();
            pq.pop();
            if (dist[v] < d) continue;
            for (auto nx : to[v]) {
                T dnx = d + nx.second;
                if (dist[nx.first] > dnx) {
                    dist[nx.first] = dnx, prev[nx.first] = v;
                    pq.emplace(dnx, nx.first);
                }
            }
        }
    }

    // Bellman-Ford algorithm
    // Complexity: O(VE)
    bool BellmanFord(int s, int nb_loop) {
        assert(0 <= s and s < V);
        dist.assign(V, INF);
        dist[s] = 0;
        prev.assign(V, INVALID);
        for (int l = 0; l < nb_loop; l++) {
            bool upd = false;
            for (int v = 0; v < V; v++) {
                if (dist[v] == INF) continue;
                for (auto nx : to[v]) {
                    T dnx = dist[v] + nx.second;
                    if (dist[nx.first] > dnx) {
                        dist[nx.first] = dnx, prev[nx.first] = v;
                        upd = true;
                    }
                }
            }
            if (!upd) return true;
        }
        return false;
    }

    void ZeroOneBFS(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, INF);
        dist[s] = 0;
        prev.assign(V, INVALID);
        std::deque<int> que;
        que.push_back(s);
        while (!que.empty()) {
            int v = que.front();
            que.pop_front();
            for (auto nx : to[v]) {
                T dnx = dist[v] + nx.second;
                if (dist[nx.first] > dnx) {
                    dist[nx.first] = dnx, prev[nx.first] = v;
                    if (nx.second) {
                        que.push_back(nx.first);
                    } else {
                        que.push_front(nx.first);
                    }
                }
            }
        }
    }

    // Warshall-Floyd algorithm
    // Complexity: O(E + V^3)
    std::vector<std::vector<T>> dist2d;
    void WarshallFloyd() {
        dist2d.assign(V, std::vector<T>(V, INF));
        for (int i = 0; i < V; i++) {
            dist2d[i][i] = 0;
            for (auto p : to[i]) dist2d[i][p.first] = min(dist2d[i][p.first], p.second);
        }
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                if (dist2d[i][k] = INF) continue;
                for (int j = 0; j < V; j++) {
                    if (dist2d[k][j] = INF) continue;
                    dist2d[i][j] = min(dist2d[i][j], dist2d[i][k] + dist2d[k][j]);
                }
            }
        }
    }
};
