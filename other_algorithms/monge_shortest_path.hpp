#pragma once
#include <cassert>
#include <vector>

// Shortest path of Monge-weighted graph
// Variant of LARSCH Algorithm: https://noshi91.hatenablog.com/entry/2023/02/18/005856
// Complexity: O(n log n)
//
// Given a directed graph with n vertices and weighted edges
// (w(i, j) = cost_callback(i, j) (i < j)),
// this class calculates the shortest path from vertex 0 to all other vertices.
template <class Cost> struct monge_shortest_path {
    std::vector<Cost> dist; // dist[i] = shortest distance from 0 to i
    std::vector<int> amin;  // amin[i] = previous vertex of i in the shortest path

    template <class F> void _check(int i, int k, F cost_callback) {
        if (i <= k) return;
        if (Cost c = dist[k] + cost_callback(k, i); c < dist[i]) dist[i] = c, amin[i] = k;
    }

    template <class F> void _rec_solve(int l, int r, F cost_callback) {
        if (r - l == 1) return;

        const int m = (l + r) / 2;
        for (int k = amin[l]; k <= amin[r]; ++k) _check(m, k, cost_callback);

        _rec_solve(l, m, cost_callback);
        for (int k = l + 1; k <= m; ++k) _check(r, k, cost_callback);
        _rec_solve(m, r, cost_callback);
    }

    template <class F> Cost solve(int n, F cost_callback) {
        assert(n > 0);
        dist.resize(n);
        amin.assign(n, 0);

        dist[0] = Cost();
        for (int i = 1; i < n; ++i) dist[i] = cost_callback(0, i);

        _rec_solve(0, n - 1, cost_callback);

        return dist.back();
    }

    template <class F> int num_edges() const {
        int ret = 0;
        for (int c = (int)amin.size() - 1; c >= 0; c = amin[c]) ++ret;
        return ret;
    }
};

// Find shortest path length from 0 to n - 1 with k edges, min_edges <= k <= max_edges
// https://noshi91.hatenablog.com/entry/2022/01/13/001217
template <class Cost, class F>
Cost monge_shortest_path_with_specified_edges(int n, int min_edges, int max_edges,
                                              Cost max_abs_cost, F cost_callback) {

    assert(1 <= n);
    assert(0 <= min_edges);
    assert(min_edges <= max_edges);
    assert(max_edges <= n - 1);

    monge_shortest_path<Cost> msp;

    auto eval = [&](Cost p) -> Cost {
        msp.solve(n, [&](int i, int j) { return cost_callback(i, j) - p; });
        return -msp.dist.back() - p * (p < 0 ? max_edges : min_edges);
    };

    Cost lo = -max_abs_cost * 3, hi = max_abs_cost * 3;

    while (lo + 1 < hi) {
        Cost p = (lo + hi) / 2, f = eval(p), df = eval(p + 1) - f;
        if (df == Cost()) {
            return -f;
        } else {
            (df < Cost() ? lo : hi) = p;
        }
    }

    Cost flo = eval(lo), fhi = eval(hi);

    return flo < fhi ? -flo : -fhi;
}
