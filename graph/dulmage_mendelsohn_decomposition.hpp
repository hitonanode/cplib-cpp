#pragma once
#include "bipartite_matching.hpp"
#include "strongly_connected_components.hpp"
#include <cassert>
#include <utility>
#include <vector>

// Dulmage–Mendelsohn (DM) decomposition （DM 分解）
// return: [(W+0, W-0), (W+1,W-1),...,(W+(k+1), W-(k+1))]
//         : sequence of pair (left vetrices, right vertices)
//         - |W+0| < |W-0| or both empty
//         - |W+i| = |W-i| (i = 1, ..., k)
//         - |W+(k+1)| > |W-(k+1)| or both empty
//         - W is topologically sorted
// Example:
// (2, 2, [(0,0), (0,1), (1,0)]) => [([],[]),([0,],[1,]),([1,],[0,]),([],[]),]
// Complexity: O(N + (N + M) sqrt(N))
// Verified: https://yukicoder.me/problems/no/1615
std::vector<std::pair<std::vector<int>, std::vector<int>>>
dulmage_mendelsohn(int L, int R, const std::vector<std::pair<int, int>> &edges) {
    for (auto p : edges) {
        assert(0 <= p.first and p.first < L);
        assert(0 <= p.second and p.second < R);
    }

    BipartiteMatching bm(L + R);
    for (auto p : edges) bm.add_edge(p.first, L + p.second);
    bm.solve();

    DirectedGraphSCC scc(L + R);
    for (auto p : edges) scc.add_edge(p.first, L + p.second);
    for (int l = 0; l < L; ++l) {
        if (bm.match[l] >= L) scc.add_edge(bm.match[l], l);
    }

    int nscc = scc.FindStronglyConnectedComponents();
    std::vector<int> cmp_map(nscc, -2);

    std::vector<int> vis(L + R);
    std::vector<int> st;
    for (int c = 0; c < 2; ++c) {
        std::vector<std::vector<int>> to(L + R);
        auto color = [&L](int x) { return x >= L; };
        for (auto p : edges) {
            int u = p.first, v = L + p.second;
            if (color(u) != c) std::swap(u, v);
            to[u].push_back(v);
            if (bm.match[u] == v) to[v].push_back(u);
        }
        for (int i = 0; i < L + R; ++i) {
            if (bm.match[i] >= 0 or color(i) != c or vis[i]) continue;
            vis[i] = 1, st = {i};
            while (!st.empty()) {
                int now = st.back();
                cmp_map[scc.cmp[now]] = c - 1;
                st.pop_back();
                for (int nxt : to[now]) {
                    if (!vis[nxt]) vis[nxt] = 1, st.push_back(nxt);
                }
            }
        }
    }

    int nset = 1;
    for (int n = 0; n < nscc; ++n) {
        if (cmp_map[n] == -2) cmp_map[n] = nset++;
    }
    for (auto &x : cmp_map) {
        if (x == -1) x = nset;
    }
    nset++;

    std::vector<std::pair<std::vector<int>, std::vector<int>>> groups(nset);

    for (int l = 0; l < L; ++l) {
        if (bm.match[l] < 0) continue;
        int c = cmp_map[scc.cmp[l]];
        groups[c].first.push_back(l);
        groups[c].second.push_back(bm.match[l] - L);
    }
    for (int l = 0; l < L; ++l) {
        if (bm.match[l] >= 0) continue;
        int c = cmp_map[scc.cmp[l]];
        groups[c].first.push_back(l);
    }
    for (int r = 0; r < R; ++r) {
        if (bm.match[L + r] >= 0) continue;
        int c = cmp_map[scc.cmp[L + r]];
        groups[c].second.push_back(r);
    }

    return groups;
}
