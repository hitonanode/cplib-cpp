#pragma once

/**
 * @file enumerate_cliques.hpp
 * @brief Enumerate all cliques of given undirected graph
 * @author hitonanode
 * @date 2023/03/10
 */

#include <algorithm>
#include <cassert>
#include <numeric>
#include <queue>
#include <utility>
#include <vector>

// Complexity: O(2^sqrt(2m) * n)
// Verify: https://judge.yosupo.jp/problem/enumerate_cliques (~1ms for n <= 100, m <= 100)
// p.15, https://www.slideshare.net/wata_orz/ss-12131479
struct enumerate_cliques {
    std::vector<std::vector<int>> to;
    std::vector<std::pair<int, int>> edges;

    int n() const { return to.size(); }
    int m() const { return edges.size(); }

    enumerate_cliques(int n_) : to(n_) {}

    void add_bi_edge(int u, int v) {
        assert(0 <= u and u < n());
        assert(0 <= v and v < n());
        if (u != v) edges.emplace_back(std::minmax(u, v));
    }

    // Build `to`
    void precalc() {
        std::sort(edges.begin(), edges.end());
        edges.erase(std::unique(edges.begin(), edges.end()), edges.end());

        for (auto &vec : to) vec.clear();
        for (auto [u, v] : edges) to.at(u).push_back(v), to.at(v).push_back(u);
        for (auto &vec : to) std::sort(vec.begin(), vec.end());
    }

    template <class F>
    void bruteforce(const std::vector<int> &cand_vs, int prefix_use, F op) const {
        const int k = cand_vs.size();
        const int mask_all = (1 << k) - 1;
        std::vector<int> ok_masks(k, mask_all);

        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < i; ++j) {
                int u = cand_vs.at(i), v = cand_vs.at(j);
                if (!std::binary_search(to.at(u).cbegin(), to.at(u).cend(), v)) {
                    ok_masks.at(i) &= ~(1 << j), ok_masks.at(j) &= ~(1 << i);
                }
            }
        }

        std::vector<int> seq;
        if (prefix_use >= 0) seq.push_back(prefix_use);
        seq.reserve(seq.size() + k);

        auto rec = [&](auto &&self, int now, const int last_mask) -> void {
            op(seq);
            seq.push_back(-1);
            for (int i = now; i < k; ++i) {
                if ((last_mask >> i) & 1) {
                    seq.back() = cand_vs.at(i);
                    self(self, i + 1, last_mask & ok_masks.at(i));
                }
            }
            seq.pop_back();
        };
        rec(rec, 0, mask_all);
        return;
    }

    template <class F> void run(F op) {
        precalc();

        std::vector<int> deg(n()), is_alive(n(), 1);
        using P = std::pair<int, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> pq;
        for (int i = 0; i < n(); ++i) deg.at(i) = to.at(i).size(), pq.emplace(deg.at(i), i);

        int rem_n = n(), rem_m = m();

        std::vector<int> cand_vs;
        while (!pq.empty()) {
            auto [di, i] = pq.top();
            pq.pop();
            if (deg.at(i) != di) continue;

            cand_vs.clear();

            if (di * di > rem_m * 2) { // Avoid "deg[i] = 0" case
                for (int i = 0; i < n(); ++i) {
                    if (is_alive.at(i)) cand_vs.push_back(i);
                }
                bruteforce(cand_vs, -1, op);
                break;
            }

            for (int j : to.at(i)) {
                if (is_alive.at(j)) cand_vs.push_back(j);
            }
            bruteforce(cand_vs, i, op);

            --rem_n, deg.at(i) = 0, is_alive.at(i) = 0;
            for (int j : cand_vs) --rem_m, --deg.at(j), pq.emplace(deg.at(j), j);
        }
    }
};
