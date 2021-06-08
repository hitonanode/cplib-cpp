#pragma once
#include <algorithm>
#include <cassert>
#include <tuple>
#include <utility>
#include <vector>

// CUT begin
// 木の直径と，これをなすパスの頂点を出力
template <class Weight> struct TreeDiameter {
    int n;
    std::vector<std::vector<std::pair<int, Weight>>> to;
    std::vector<int> prev;
    std::vector<Weight> dist;
    TreeDiameter(int V) : n(V), to(V), prev(V), dist(V) {}
    void add_edge(int s, int t, Weight w) {
        assert(0 <= s and s < n);
        assert(0 <= t and t < n);
        to[s].emplace_back(t, w);
        to[t].emplace_back(s, w);
    }
    int argdmax;
    Weight dmax;
    void dfs(int now, int prv) {
        if (dmax < dist[now]) dmax = dist[now], argdmax = now;
        for (auto p : to[now]) {
            int nxt;
            Weight w;
            std::tie(nxt, w) = p;
            if (nxt == prv) continue;
            prev[nxt] = now;
            dist[nxt] = dist[now] + w;
            dfs(nxt, now);
        }
    }
    std::pair<Weight, std::vector<int>> get_diameter_edges(int root = 0) {
        prev[root] = -1;
        dist[root] = 0;
        dmax = 0, argdmax = root;
        dfs(root, -1);
        dmax = 0, prev[argdmax] = -1, dist[argdmax] = 0;
        dfs(argdmax, -1);
        std::vector<int> ret;
        while (argdmax >= 0) {
            ret.push_back(argdmax);
            argdmax = prev[argdmax];
        }
        return {dmax, ret};
    }
};
