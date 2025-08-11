#pragma once

#include <algorithm>
#include <cassert>
#include <cmath>
#include <numeric>
#include <queue>
#include <set>
#include <tuple>
#include <utility>
#include <vector>

// Minimum Steiner tree of undirected connected graph
// n vertices, m edges, k terminals
// Complexity: O(3^k n + 2^k m log m)
// Verify: https://judge.yosupo.jp/problem/minimum_steiner_tree
template <class T>
std::pair<T, std::vector<int>>
MinimumSteinerTreeDP(int n, const std::vector<std::tuple<int, int, T>> &edges,
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

// Complexity: O(m log m + 2^(n - k) m alpha(n))
// Verify: https://yukicoder.me/problems/no/114
template <class T>
std::pair<T, std::vector<int>>
MinimumSteinerTreeDense(int n, const std::vector<std::tuple<int, int, T>> &edges,
                        const std::vector<int> &terminals) {
    if (n <= 1 or terminals.size() <= 1) return {T{}, {}};

    std::vector<int> unfixed;
    {
        std::vector<int> is_unfixed(n, 1);
        for (int v : terminals) is_unfixed.at(v) = 0;
        for (int i = 0; i < n; ++i) {
            if (is_unfixed.at(i)) unfixed.emplace_back(i);
        }
    }

    struct {
        int n;
        std::vector<int> par, cou;
        void reset() {
            par.resize(n);
            std::iota(par.begin(), par.end(), 0);
            cou.assign(n, 1);
        }
        int find(int x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }
        void merge(int x, int y) {
            x = find(x), y = find(y);
            if (x == y) return;
            if (cou[x] < cou[y]) std::swap(x, y);
            par[y] = x, cou[x] += cou[y];
        }
        bool same(int x, int y) { return find(x) == find(y); }
    } dsu{n};

    auto sorted_edges = edges;
    std::sort(sorted_edges.begin(), sorted_edges.end(),
              [&](const auto &l, const auto &r) { return std::get<2>(l) < std::get<2>(r); });

    std::vector<int> is_edge_used(sorted_edges.size(), -1);
    std::vector<int> is_banned(n, -1);

    T best_cost = T{};
    int best_ban_set = -1;

    auto solve = [&](int ban_set) -> std::pair<bool, T> {
        dsu.reset();
        for (int d = 0; d < (int)unfixed.size(); ++d) {
            if (ban_set & (1 << d)) is_banned.at(unfixed.at(d)) = ban_set;
        }

        T res{0};
        for (int pos = 0; pos < (int)sorted_edges.size(); ++pos) {
            auto [u, v, w] = sorted_edges.at(pos);
            if (is_banned.at(u) == ban_set or is_banned.at(v) == ban_set) continue;
            if (dsu.same(u, v)) continue;
            dsu.merge(u, v);
            res += w;
            is_edge_used.at(pos) = ban_set;
        }
        for (int idx = 1; idx < (int)terminals.size(); ++idx) {
            if (!dsu.same(terminals.at(0), terminals.at(idx))) return {false, T{}};
        }
        return {true, res};
    };

    for (int ban_set = (1 << (int)unfixed.size()) - 1; ban_set >= 0; --ban_set) {
        if (const auto [is_valid, cost] = solve(ban_set);
            is_valid and (cost < best_cost or best_ban_set == -1)) {
            best_cost = cost;
            best_ban_set = ban_set;
        }
    }

    if (best_ban_set == -1) return {T{}, {}}; // Infeasible

    solve(best_ban_set);
    std::set<std::tuple<int, int, T>> used_edges;
    for (int pos = 0; pos < (int)sorted_edges.size(); ++pos) {
        if (is_edge_used.at(pos) == best_ban_set) used_edges.insert(sorted_edges.at(pos));
    }

    std::vector<int> used_edge_ids;
    for (int eid = 0; eid < (int)edges.size(); ++eid) {
        if (used_edges.count(edges.at(eid))) {
            used_edge_ids.emplace_back(eid);
            used_edges.erase(edges.at(eid));
        }
    }

    return {best_cost, used_edge_ids};
}

template <class T>
std::pair<T, std::vector<int>>
MinimumSteinerTree(int n, const std::vector<std::tuple<int, int, T>> &edges,
                   const std::vector<int> &terminals) {
    const int m = edges.size(), k = terminals.size();
    auto use_dp = [&]() -> bool {
        if (n - k > 30) return true;
        if (k > 20) return false;
        return pow(3, k) * n + pow(2, k) * m * log(m) < pow(2, n - k) * m;
    };
    return (use_dp() ? MinimumSteinerTreeDP<T>(n, edges, terminals)
                     : MinimumSteinerTreeDense<T>(n, edges, terminals));
}
