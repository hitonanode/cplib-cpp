#pragma once

#include <algorithm>
#include <cassert>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// Minimum Steiner tree of undirected connected graph
// n vertices, m edges, k terminals
// Complexity: O(3^k n + 2^k m log m)
// Verify: https://judge.yosupo.jp/problem/minimum_steiner_tree
template <class T>
std::pair<T, std::vector<int>>
MinimumSteinerTree(int n, const std::vector<std::tuple<int, int, T>> &edges,
                   const std::vector<int> &terminals) {

    if (n <= 1 or terminals.size() <= 1) return {T{}, {}};
    assert(!edges.empty());

    std::vector<std::vector<std::tuple<int, int, T>>> to(n);
    for (int i = 0; i < (int)edges.size(); ++i) {
        auto [u, v, w] = edges[i];
        assert(w >= 0);
        to.at(u).emplace_back(v, i, w);
        to.at(v).emplace_back(u, i, w);
    }
    const int k = terminals.size();

    std::vector<T> dp(n << k);
    std::vector<int> prv(n << k, -1);

    auto f = [&](int i, int s) -> int {
        assert(0 <= s and s < (1 << k));
        return (i << k) + s;
    };

    for (int i = 0; i < n; ++i) prv.at(f(i, 0)) = f(i, 0);

    for (int j = 0; j < k; ++j) {
        const int i = terminals.at(j);
        prv.at(f(i, 1 << j)) = f(i, 0);
    }

    for (int s = 0; s < (1 << k); ++s) {
        for (int i = 0; i < n; ++i) {
            for (int t = (s - 1) & s; t; t = (t - 1) & s) {
                if (prv.at(f(i, t)) == -1) continue;
                if (prv.at(f(i, s ^ t)) == -1) continue;
                const T new_cost = dp.at(f(i, t)) + dp.at(f(i, s ^ t));
                if (new_cost < dp.at(f(i, s)) or prv.at(f(i, s)) == -1) {
                    dp.at(f(i, s)) = new_cost;
                    prv.at(f(i, s)) = f(i, t);
                    assert(s >= t);
                }
            }
        }

        using P = std::pair<T, int>;
        std::priority_queue<P, std::vector<P>, std::greater<>> pq;

        for (int i = 0; i < n; ++i) {
            if (prv.at(f(i, s)) != -1) pq.emplace(dp.at(f(i, s)), i);
        }

        while (!pq.empty()) {
            auto [cost, i] = pq.top();
            pq.pop();
            if (dp.at(f(i, s)) < cost) continue;
            for (auto [j, edge_id, w] : to.at(i)) {
                if (prv.at(f(j, s)) != -1 and dp.at(f(j, s)) <= cost + w) continue;
                dp.at(f(j, s)) = cost + w;
                prv.at(f(j, s)) = f(edge_id, s);
                pq.emplace(dp.at(f(j, s)), j);
            }
        }
    }

    T ans = dp.at(f(0, (1 << k) - 1));
    int argmin = 0;
    for (int i = 1; i < n; ++i) {
        if (dp.at(f(i, (1 << k) - 1)) < ans) {
            ans = dp.at(f(i, (1 << k) - 1));
            argmin = i;
        }
    }

    std::vector<int> used_edges;

    auto rec = [&](auto &&self, int cur) -> void {
        const int mask = cur & ((1 << k) - 1);
        if (!mask) return;
        const int i = cur >> k;
        const int prv_mask = prv.at(cur) & ((1 << k) - 1);
        if (prv_mask == 0) return;

        if (mask == prv_mask) {
            const int edge_id = prv.at(cur) >> k;
            used_edges.emplace_back(edge_id);
            const int nxt = i ^ std::get<0>(edges.at(edge_id)) ^ std::get<1>(edges.at(edge_id));
            self(self, f(nxt, mask));
        } else {
            self(self, f(i, prv_mask));
            self(self, f(i, mask ^ prv_mask));
        }
    };
    rec(rec, f(argmin, (1 << k) - 1));

    std::sort(used_edges.begin(), used_edges.end());

    return {ans, used_edges};
}
