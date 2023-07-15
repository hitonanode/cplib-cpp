#pragma once

#include <algorithm>
#include <cassert>
#include <limits>
#include <optional>
#include <queue>
#include <tuple>
#include <utility>
#include <vector>

// Shortest cycle detection of graphs
// Verified:
// - https://yukicoder.me/submissions/594507
// - ABC308Ex https://atcoder.jp/contests/abc308/submissions/43580864
template <bool DIRECTED, typename T> struct shortest_cycle {
    int V;
    std::vector<std::vector<std::tuple<int, int, T>>> to; // (nxt, edge_idx, weight)
    std::vector<std::tuple<int, int, T>> edges;

    shortest_cycle(int V = 0) : V(V), to(V) {}

    void add_edge(int s, int t, T weight) {
        static_assert(DIRECTED);
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        assert(weight >= 0);
        to.at(s).emplace_back(t, (int)edges.size(), weight);
        edges.emplace_back(s, t, weight);
    }

    void add_bi_edge(int s, int t, T weight) {
        static_assert(!DIRECTED);
        assert(0 <= s and s < V);
        assert(0 <= t and t < V);
        assert(weight >= 0);
        to.at(s).emplace_back(t, (int)edges.size(), weight);
        to.at(t).emplace_back(s, (int)edges.size(), weight);
        edges.emplace_back(s, t, weight);
    }

    std::vector<T> dist;
    std::vector<int> prv;

    std::pair<T, std::pair<int, int>> Solve(const int &r) {
        assert(0 <= r and r < V);
        dist.assign(V, T());
        prv.assign(V, -1);
        std::vector<int> prve(V, -1);
        std::vector<int> orig(V, -1);

        auto reached = [&](int i) { return i == r or prv.at(i) != -1; };

        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<>> pq;
        pq.emplace(dist.at(r), r);

        while (!pq.empty()) {
            const auto [d_, now] = pq.top();
            pq.pop();
            if (d_ > dist.at(now)) continue;

            for (const auto &[nxt, eid, w] : to[now]) {
                if (reached(nxt) and dist.at(nxt) <= dist.at(now) + w) continue;
                dist.at(nxt) = dist.at(now) + w;
                orig.at(nxt) = orig.at(now) < 0 ? nxt : orig.at(now);
                prv.at(nxt) = now;
                prve.at(nxt) = eid;
                pq.emplace(dist.at(nxt), nxt);
            }
        }

        std::vector<bool> is_edge_used(edges.size());
        for (int eid : prve) {
            if (eid >= 0) is_edge_used.at(eid) = true;
        }

        std::optional<T> minimum_cycle = std::nullopt;
        int s = -1, t = -1;

        for (int eid = 0; eid < (int)edges.size(); ++eid) {
            if (is_edge_used.at(eid)) continue;
            auto [a, b, w] = edges.at(eid);
            if (!reached(a) or !reached(b)) continue;

            if constexpr (DIRECTED) {
                if (b != r) continue;
            } else {
                if (orig.at(a) == orig.at(b) and (a != r or b != r)) continue;
            }

            if (T L = dist.at(a) + dist.at(b) + w;
                !minimum_cycle.has_value() or L < minimum_cycle.value()) {
                minimum_cycle = L;
                s = a, t = b;
            }
        }

        return std::make_pair(minimum_cycle.value_or(T(-1)), std::make_pair(s, t));
    }

    std::vector<int> retrieve_loop(const std::pair<int, int> &ab) const {
        if (ab.first < 0 or ab.second < 0) return {};
        std::vector<int> ret;
        bool initial = true;
        for (int cur : {ab.first, ab.second}) {
            while (cur >= 0) {
                ret.push_back(cur);
                cur = prv.at(cur);
            }
            if (initial) {
                std::reverse(ret.begin(), ret.end());
                initial = false;
            } else {
                ret.pop_back();
            }
        }
        return ret;
    }
};
