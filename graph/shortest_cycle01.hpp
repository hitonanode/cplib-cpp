#pragma once
#include <algorithm>
#include <cassert>
#include <deque>
#include <limits>
#include <utility>
#include <vector>

// Shortest cycle detection of UNDIRECTED SIMPLE graphs based on 01-BFS
// Assumption: only two types of edges are permitted: weight = 0 or W ( > 0)
// Complexity: O(E)
// Verified: https://codeforces.com/contest/1325/problem/E https://codeforces.com/contest/1817/problem/B
struct ShortestCycle01 {
    static constexpr int INF = std::numeric_limits<int>::max() / 2;
    int V, E;
    int INVALID = -1;
    std::vector<std::vector<std::pair<int, int>>> to; // (nxt, weight)
    ShortestCycle01() = default;
    ShortestCycle01(int V) : V(V), E(0), to(V) {}
    void add_edge(int s, int t, int len) {
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        assert(len >= 0);
        to[s].emplace_back(t, len);
        to[t].emplace_back(s, len);
        E++;
    }

    std::vector<int> dist;
    std::vector<int> prev;
    std::vector<int> orig;
    // Find minimum length simple cycle which passes vertex `v`
    // - return: (LEN, (a, b))
    //   - LEN: length of the shortest cycles if exists, INF otherwise.
    //   - the cycle consists of vertices [v, ..., prev[prev[a]], prev[a], a, b, prev[b], prev[prev[b]], ..., v]
    std::pair<int, std::pair<int, int>> Solve(int v) {
        assert(0 <= v and v < V);
        dist.assign(V, INF);
        prev.assign(V, -1);
        orig.assign(V, -1);
        std::vector<int> root_weight(V, INF);
        std::deque<int> bfsq;
        for (auto [nxt, weight] : to[v]) {
            if (weight >= dist[nxt]) continue;
            dist[nxt] = weight;
            root_weight[nxt] = weight;
            prev[nxt] = v;
            orig[nxt] = nxt;
            if (weight)
                bfsq.emplace_back(nxt);
            else
                bfsq.emplace_front(nxt);
        }
        int minimum_cycle = INF;
        int source_a = -1, source_b = -1;
        while (!bfsq.empty()) {
            int now = bfsq.front();
            bfsq.pop_front();
            for (auto [nxt, weight] : to[now]) {
                if (nxt == v) continue;
                if (orig[nxt] >= 0 and orig[now] != orig[nxt]) {
                    int length = dist[now] + dist[nxt] + weight;
                    if (length < minimum_cycle) {
                        minimum_cycle = length;
                        source_a = orig[now], source_b = orig[nxt];
                    }
                }
                int dnext = dist[now] + weight;
                if (dnext < dist[nxt]) {
                    dist[nxt] = dnext;
                    prev[nxt] = now;
                    orig[nxt] = orig[now];
                    if (weight)
                        bfsq.emplace_back(nxt);
                    else
                        bfsq.emplace_front(nxt);
                }
            }
        }
        if (source_a < 0) return std::make_pair(INF, std::make_pair(-1, -1));

        std::vector<int> path_dist(V, INF), path_prev(V, -1);
        path_dist[source_a] = 0;
        bfsq = {source_a};
        while (!bfsq.empty()) {
            int now = bfsq.front();
            bfsq.pop_front();
            for (auto [nxt, weight] : to[now]) {
                if (nxt == v) continue;
                int dnext = path_dist[now] + weight;
                if (dnext < path_dist[nxt]) {
                    path_dist[nxt] = dnext;
                    path_prev[nxt] = now;
                    if (weight)
                        bfsq.emplace_back(nxt);
                    else
                        bfsq.emplace_front(nxt);
                }
            }
        }
        std::vector<int> path;
        for (int x = source_b; x >= 0; x = path_prev[x]) {
            path.push_back(x);
            if (x == source_a) break;
        }
        std::reverse(path.begin(), path.end());
        int split = (path.size() - 1) / 2;
        prev[path.front()] = v;
        orig[path.front()] = path.front();
        dist[path.front()] = root_weight[path.front()];
        for (int i = 1; i <= split; i++) {
            prev[path[i]] = path[i - 1];
            orig[path[i]] = path.front();
        }
        prev[path.back()] = v;
        orig[path.back()] = path.back();
        dist[path.back()] = root_weight[path.back()];
        for (int i = path.size() - 2; i > split; i--) {
            prev[path[i]] = path[i + 1];
            orig[path[i]] = path.back();
        }
        minimum_cycle = root_weight[source_a] + path_dist[source_b] + root_weight[source_b];
        return std::make_pair(minimum_cycle, std::make_pair(path[split], path[split + 1]));
    }
};
