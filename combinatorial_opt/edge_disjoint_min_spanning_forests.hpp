#pragma once
#include <algorithm>
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>

// Max size min weight two spanning forests
// Complexity: O(NM + M log M)
// Reference: https://www.slideshare.net/tmaehara/ss-17402143
// Verified:
// - https://www.codechef.com/submit/HAMEL
// - https://community.topcoder.com/stat?c=problem_statement&pm=14909&rd=17198
template <class Label, class W = int>
std::pair<std::vector<bool>, std::vector<bool>>
edge_disjoint_min_spanning_forests(const std::vector<std::pair<Label, Label>> &edges,
                                   const std::vector<W> &ws = {}) {
    assert(ws.empty() or ws.size() == edges.size());
    const int M = edges.size();
    std::vector<Label> lbl(M * 2);
    for (int e = 0; e < M; e++) lbl[e * 2] = edges[e].first, lbl[e * 2 + 1] = edges[e].second;
    std::sort(lbl.begin(), lbl.end());
    lbl.erase(std::unique(lbl.begin(), lbl.end()), lbl.end());
    const int N = lbl.size();

    std::vector<std::pair<int, int>> uvs(M);
    for (int e = 0; e < M; e++) {
        int u = std::lower_bound(lbl.begin(), lbl.end(), edges[e].first) - lbl.begin();
        int v = std::lower_bound(lbl.begin(), lbl.end(), edges[e].second) - lbl.begin();
        uvs[e] = {u, v};
    }

    std::vector<int> es(M);
    std::iota(es.begin(), es.end(), 0);
    if (!ws.empty()) std::sort(es.begin(), es.end(), [&](int i, int j) { return ws[i] < ws[j]; });

    std::vector<std::vector<bool>> I(2, std::vector<bool>(M));
    std::vector<std::vector<std::pair<int, int>>> to(N);

    int nb_accepted_edges = 0;
    auto accept_edge = [&](int e) {
        nb_accepted_edges++;
        int u = uvs[e].first, v = uvs[e].second;
        to[u].emplace_back(v, e);
        to[v].emplace_back(u, e);
    };

    auto dfs = [&](int head, const std::vector<bool> &I) -> std::vector<std::pair<int, int>> {
        std::vector<int> st{head};
        std::vector<std::pair<int, int>> prv(N, {-1, -1});
        prv[head] = {head, -1};
        while (!st.empty()) {
            int now = st.back();
            st.pop_back();
            for (auto p : to[now]) {
                int nxt = p.first, e = p.second;
                if (!I[e] or prv[nxt].first >= 0) continue;
                prv[nxt] = {now, e}, st.push_back(nxt);
            }
        }
        return prv;
    };

    std::vector<int> prveid(M, -1), visited(N);
    std::vector<std::vector<int>> L(2);
    std::vector<std::vector<std::pair<int, int>>> prv(2);
    for (const int e : es) {
        if (nb_accepted_edges > 2 * (N - 1)) break;
        const int u = uvs[e].first, v = uvs[e].second;

        bool found = false;

        for (int d = 0; d < 2; d++) {
            prv[d] = dfs(u, I[d]);
            if (prv[d][v].first < 0) {
                accept_edge(e);
                I[d][e] = 1;
                found = true;
                break;
            }
        }
        if (found) continue;

        visited.assign(N, 0);
        visited[u] = 1;
        L[0] = {e}, L[1] = {};

        int ehead = -1;
        prveid[e] = -1;
        for (int i = 0;; i ^= 1) {
            if (L[i].empty()) break;
            L[i ^ 1].clear();
            while (!L[i].empty()) {
                const int exy = L[i].back();
                L[i].pop_back();
                int x = uvs[exy].first, y = uvs[exy].second;
                if (prv[i][x].first < 0 or prv[i][y].first < 0) {
                    ehead = exy;
                    break;
                }
                if (!visited[x]) std::swap(x, y);
                while (!visited[y]) {
                    int nxty = prv[i][y].first, nxte = prv[i][y].second;
                    L[i ^ 1].push_back(nxte);
                    visited[y] = 1;
                    y = nxty;
                    prveid[nxte] = exy;
                }
            }
            if (ehead >= 0) {
                accept_edge(e);
                int c = I[0][ehead];
                for (; ehead >= 0; ehead = prveid[ehead], c ^= 1) {
                    I[c][ehead] = 1, I[c ^ 1][ehead] = 0;
                }
                break;
            }
        }
    }
    return {I[0], I[1]};
}
