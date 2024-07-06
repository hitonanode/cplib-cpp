#pragma once

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>

#include "graph/strongly_connected_components.hpp"

// edges[i] = (s, t) means that the edge (s, t) is added at i-th tick.
// Return the earliest tick when the edge (s, t) is included in a cycle.
// If the edge (s, t) is never included in a cycle or s == t, return M.
// Complexity: O(M log M), where M = edges.size()
// Verified: https://codeforces.com/contest/1989/submission/268026664
std::vector<int> incremental_scc(const std::vector<std::pair<int, int>> &edges) {
    int N = 1;
    for (auto [s, t] : edges) N = std::max({N, s + 1, t + 1});

    const int M = edges.size();

    std::vector<int> ret(M, M);

    std::vector<int> compressed_idx(N, -1);

    using Edges = std::vector<std::tuple<int, int, int>>;

    auto rec = [&](auto &&self, const Edges &e, int tl, int tr) -> void {
        if (e.empty() or tl + 1 == tr) return;

        int n = 0;
        for (const auto &[tick, s, t] : e) {
            if (compressed_idx.at(s) == -1) compressed_idx.at(s) = n++;
            if (compressed_idx.at(t) == -1) compressed_idx.at(t) = n++;
        }

        const int tmid = (tl + tr) / 2;

        DirectedGraphSCC scc(n);
        for (const auto &[tick, s, t] : e) {
            if (tick < tmid) scc.add_edge(compressed_idx.at(s), compressed_idx.at(t));
        }
        scc.FindStronglyConnectedComponents();

        Edges left, right;

        for (const auto &[tick, s, t] : e) {
            const int sc = compressed_idx.at(s), tc = compressed_idx.at(t);
            if (tick < tmid and scc.cmp.at(sc) == scc.cmp.at(tc)) {
                ret.at(tick) = tmid - 1;
                left.emplace_back(tick, sc, tc);
            } else {
                right.emplace_back(tick, scc.cmp.at(sc), scc.cmp.at(tc));
            }
        }

        for (auto [_, s, t] : e) compressed_idx.at(s) = compressed_idx.at(t) = -1;

        self(self, left, tl, tmid);
        self(self, right, tmid, tr);
    };

    Edges init;
    init.reserve(M);
    for (int tick = 0; tick < M; ++tick) {
        if (auto [s, t] = edges.at(tick); s != t) init.emplace_back(tick, s, t);
    }

    rec(rec, init, 0, M + 1);

    return ret;
}
