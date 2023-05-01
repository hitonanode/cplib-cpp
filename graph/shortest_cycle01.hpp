#pragma once
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
        dist[v] = 0;
        prev.assign(V, -1);
        orig.assign(V, -1);
        std::deque<std::pair<int, int>> bfsq;
        std::vector<std::pair<std::pair<int, int>, int>> add_edge;
        bfsq.emplace_back(v, -1);
        while (!bfsq.empty()) {
            int now = bfsq.front().first, prv = bfsq.front().second;
            bfsq.pop_front();
            if (prv < 0) {
                //
            } else if (prv == v) {
                orig.at(now) = now;
            } else {
                orig.at(now) = orig.at(prv);
            }
            for (auto nxt : to[now])
                if (nxt.first != prv) {
                    if (dist[nxt.first] == INF) {
                        dist[nxt.first] = dist[now] + nxt.second;
                        prev[nxt.first] = now;
                        if (nxt.second)
                            bfsq.emplace_back(nxt.first, now);
                        else
                            bfsq.emplace_front(nxt.first, now);
                    } else
                        add_edge.emplace_back(std::make_pair(now, nxt.first), nxt.second);
                }
        }
        int minimum_cycle = INF;
        int s = -1, t = -1;
        for (auto edge : add_edge) {
            int a = edge.first.first, b = edge.first.second;
            if (orig.at(a) == orig.at(b)) continue;
            int L = dist[a] + dist[b] + edge.second;
            if (L < minimum_cycle) minimum_cycle = L, s = a, t = b;
        }
        return std::make_pair(minimum_cycle, std::make_pair(s, t));
    }
};
