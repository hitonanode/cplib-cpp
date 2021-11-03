#pragma once
#include <cassert>
#include <iostream>
#include <vector>

// Bipartite matching of undirected bipartite graph (Hopcroft-Karp)
// https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html
// Comprexity: O((V + E)sqrtV)
// int solve(): enumerate maximum number of matching / return -1 (if graph is not bipartite)
struct BipartiteMatching {
    int V;
    std::vector<std::vector<int>> to; // Adjacency list
    std::vector<int> dist;            // dist[i] = (Distance from i'th node)
    std::vector<int> match;           // match[i] = (Partner of i'th node) or -1 (No parter)
    std::vector<int> used, vv;
    std::vector<int> color; // color of each node(checking bipartition): 0/1/-1(not determined)

    BipartiteMatching() = default;
    BipartiteMatching(int V_) : V(V_), to(V_), match(V_, -1), used(V_), color(V_, -1) {}

    void add_edge(int u, int v) {
        assert(u >= 0 and u < V and v >= 0 and v < V and u != v);
        to[u].push_back(v);
        to[v].push_back(u);
    }

    void _bfs() {
        dist.assign(V, -1);
        std::vector<int> q;
        int lq = 0;
        for (int i = 0; i < V; i++) {
            if (!color[i] and !used[i]) q.push_back(i), dist[i] = 0;
        }

        while (lq < int(q.size())) {
            int now = q[lq++];
            for (auto nxt : to[now]) {
                int c = match[nxt];
                if (c >= 0 and dist[c] == -1) q.push_back(c), dist[c] = dist[now] + 1;
            }
        }
    }

    bool _dfs(int now) {
        vv[now] = true;
        for (auto nxt : to[now]) {
            int c = match[nxt];
            if (c < 0 or (!vv[c] and dist[c] == dist[now] + 1 and _dfs(c))) {
                match[nxt] = now, match[now] = nxt;
                used[now] = true;
                return true;
            }
        }
        return false;
    }

    bool _color_bfs(int root) {
        color[root] = 0;
        std::vector<int> q{root};
        int lq = 0;
        while (lq < int(q.size())) {
            int now = q[lq++], c = color[now];
            for (auto nxt : to[now]) {
                if (color[nxt] == -1) {
                    color[nxt] = !c, q.push_back(nxt);
                } else if (color[nxt] == c) {
                    return false;
                }
            }
        }
        return true;
    }

    int solve() {
        for (int i = 0; i < V; i++) {
            if (color[i] == -1 and !_color_bfs(i)) return -1;
        }
        int ret = 0;
        while (true) {
            _bfs();
            vv.assign(V, false);
            int flow = 0;
            for (int i = 0; i < V; i++) {
                if (!color[i] and !used[i] and _dfs(i)) flow++;
            }
            if (!flow) break;
            ret += flow;
        }
        return ret;
    }

    template <class OStream> friend OStream &operator<<(OStream &os, const BipartiteMatching &bm) {
        os << "{N=" << bm.V << ':';
        for (int i = 0; i < bm.V; i++) {
            if (bm.match[i] > i) os << '(' << i << '-' << bm.match[i] << "),";
        }
        return os << '}';
    }
};
