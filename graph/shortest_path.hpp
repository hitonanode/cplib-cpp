#pragma once
#include <algorithm>
#include <cassert>
#include <deque>
#include <fstream>
#include <functional>
#include <limits>
#include <queue>
#include <string>
#include <utility>
#include <vector>

// CUT begin
template <typename T, T INF = std::numeric_limits<T>::max() / 2, int INVALID = -1>
struct ShortestPath {
    int V, E;
    bool single_positive_weight;
    T wmin, wmax;
    std::vector<std::vector<std::pair<int, T>>> to;

    ShortestPath(int V = 0) : V(V), E(0), single_positive_weight(true), wmin(0), wmax(0), to(V) {}
    void add_edge(int s, int t, T w) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        to[s].emplace_back(t, w);
        E++;
        if (w > 0 and wmax > 0 and wmax != w) single_positive_weight = false;
        wmin = std::min(wmin, w);
        wmax = std::max(wmax, w);
    }

    std::vector<T> dist;
    std::vector<int> prev;

    // Dijkstra algorithm
    // Complexity: O(E log E)
    using Pque = std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,
                                     std::greater<std::pair<T, int>>>;
    template <class Heap = Pque> void Dijkstra(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, INF);
        dist[s] = 0;
        prev.assign(V, INVALID);
        Heap pq;
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

    // Dijkstra algorithm, O(V^2 + E)
    void DijkstraVquad(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, INF);
        dist[s] = 0;
        prev.assign(V, INVALID);
        std::vector<char> fixed(V, false);
        while (true) {
            int r = INVALID;
            T dr = INF;
            for (int i = 0; i < V; i++) {
                if (!fixed[i] and dist[i] < dr) r = i, dr = dist[i];
            }
            if (r == INVALID) break;
            fixed[r] = true;
            int nxt;
            T dx;
            for (auto p : to[r]) {
                std::tie(nxt, dx) = p;
                if (dist[nxt] > dist[r] + dx) dist[nxt] = dist[r] + dx, prev[nxt] = r;
            }
        }
    }

    // Bellman-Ford algorithm
    // Complexity: O(VE)
    bool BellmanFord(int s, int nb_loop) {
        assert(0 <= s and s < V);
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
        for (int l = 0; l < nb_loop; l++) {
            bool upd = false;
            for (int v = 0; v < V; v++) {
                if (dist[v] == INF) continue;
                for (auto nx : to[v]) {
                    T dnx = dist[v] + nx.second;
                    if (dist[nx.first] > dnx) dist[nx.first] = dnx, prev[nx.first] = v, upd = true;
                }
            }
            if (!upd) return true;
        }
        return false;
    }

    // Bellman-ford algorithm using queue (deque)
    // Complexity: O(VE)
    // Requirement: no negative loop
    void SPFA(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, INF);
        prev.assign(V, INVALID);
        std::deque<int> q;
        std::vector<char> in_queue(V);
        dist[s] = 0;
        q.push_back(s), in_queue[s] = 1;
        while (!q.empty()) {
            int now = q.front();
            q.pop_front(), in_queue[now] = 0;
            for (auto nx : to[now]) {
                T dnx = dist[now] + nx.second;
                int nxt = nx.first;
                if (dist[nxt] > dnx) {
                    dist[nxt] = dnx;
                    if (!in_queue[nxt]) {
                        if (q.size() and dnx < dist[q.front()]) { // Small label first optimization
                            q.push_front(nxt);
                        } else {
                            q.push_back(nxt);
                        }
                        prev[nxt] = now, in_queue[nxt] = 1;
                    }
                }
            }
        }
    }

    void ZeroOneBFS(int s) {
        assert(0 <= s and s < V);
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
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

    bool dag_solver(int s) {
        assert(0 <= s and s < V);
        std::vector<int> indeg(V, 0);
        std::queue<int> que;
        que.push(s);
        while (que.size()) {
            int now = que.front();
            que.pop();
            for (auto nx : to[now]) {
                indeg[nx.first]++;
                if (indeg[nx.first] == 1) que.push(nx.first);
            }
        }
        dist.assign(V, INF), prev.assign(V, INVALID);
        dist[s] = 0;
        que.push(s);
        while (que.size()) {
            int now = que.front();
            que.pop();
            for (auto nx : to[now]) {
                indeg[nx.first]--;
                if (dist[nx.first] > dist[now] + nx.second)
                    dist[nx.first] = dist[now] + nx.second, prev[nx.first] = now;
                if (indeg[nx.first] == 0) que.push(nx.first);
            }
        }
        return *max_element(indeg.begin(), indeg.end()) == 0;
    }

    // Retrieve a sequence of vertex ids that represents shortest path [s, ..., goal]
    // If not reachable to goal, return {}
    std::vector<int> retrieve_path(int goal) const {
        assert(int(prev.size()) == V);
        assert(0 <= goal and goal < V);
        if (dist[goal] == INF) return {};
        std::vector<int> ret{goal};
        while (prev[goal] != INVALID) {
            goal = prev[goal];
            ret.push_back(goal);
        }
        std::reverse(ret.begin(), ret.end());
        return ret;
    }

    void solve(int s) {
        if (wmin >= 0) {
            if (single_positive_weight) {
                ZeroOneBFS(s);
            } else {
                if ((long long)V * V < (E << 4)) {
                    DijkstraVquad(s);
                } else {
                    Dijkstra(s);
                }
            }
        } else {
            BellmanFord(s, V);
        }
    }

    // Warshall-Floyd algorithm
    // Complexity: O(E + V^3)
    std::vector<std::vector<T>> dist2d;
    void WarshallFloyd() {
        dist2d.assign(V, std::vector<T>(V, INF));
        for (int i = 0; i < V; i++) {
            dist2d[i][i] = 0;
            for (auto p : to[i]) dist2d[i][p.first] = std::min(dist2d[i][p.first], p.second);
        }
        for (int k = 0; k < V; k++) {
            for (int i = 0; i < V; i++) {
                if (dist2d[i][k] == INF) continue;
                for (int j = 0; j < V; j++) {
                    if (dist2d[k][j] == INF) continue;
                    dist2d[i][j] = std::min(dist2d[i][j], dist2d[i][k] + dist2d[k][j]);
                }
            }
        }
    }

    void dump_graphviz(std::string filename = "shortest_path") const {
        std::ofstream ss(filename + ".DOT");
        ss << "digraph{\n";
        for (int i = 0; i < V; i++) {
            for (const auto &e : to[i])
                ss << i << "->" << e.first << "[label=" << e.second << "];\n";
        }
        ss << "}\n";
        ss.close();
        return;
    }
};
