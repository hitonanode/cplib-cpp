#pragma once
#include <bitset>
#include <vector>

// CUT begin
// Directed graph library to find strongly connected components （強連結成分分解）
// 0-indexed directed graph
// - using std::bitset
// - Fast for dense graphs
// Complexity: O(V^2/64)
// Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>
template <int VMAX> struct DirectedGraphSCC64 {
    int V;
    const std::vector<std::bitset<VMAX>> &e, &einv;
    std::vector<int> vs, cmp;
    std::bitset<VMAX> unvisited;
    int scc_num;
    void _dfs(int now) {
        unvisited.reset(now);
        while (true) {
            int nxt = (unvisited & e[now])._Find_first();
            if (nxt >= V) break;
            _dfs(nxt);
        }
        vs.push_back(now);
    }
    void _rdfs(int now, int k) {
        unvisited.reset(now);
        cmp[now] = k;
        while (true) {
            int nxt = (unvisited & einv[now])._Find_first();
            if (nxt >= V) break;
            _rdfs(nxt, k);
        }
    }
    // Detect strongly connected components and return # of them.
    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)
    DirectedGraphSCC64(const std::vector<std::bitset<VMAX>> &edge,
                       const std::vector<std::bitset<VMAX>> &edge_inv)
        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()), scc_num(0) {
        unvisited.set();
        for (int i = 0; i < V; i++)
            if (unvisited[i]) _dfs(i);
        unvisited.set();
        for (int i = (int)vs.size() - 1; i >= 0; i--)
            if (unvisited[vs[i]]) { _rdfs(vs[i], scc_num++); }
    }
};
