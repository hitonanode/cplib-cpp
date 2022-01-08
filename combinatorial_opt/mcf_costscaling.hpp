#pragma once
#include <cassert>
#include <vector>

// Cost scaling
// https://people.orie.cornell.edu/dpw/orie633/
template <class Cap, class Cost, int SCALING = 1, int REFINEMENT_ITER = 20>
struct mcf_costscaling {
    mcf_costscaling() = default;
    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {}

    int _n;
    std::vector<Cap> cap;
    std::vector<Cost> cost;
    std::vector<int> opposite;
    std::vector<std::vector<int>> to;
    std::vector<Cap> b;
    std::vector<Cost> p;

    int add_edge(int from_, int to_, Cap cap_, Cost cost_) {
        assert(0 <= from_ and from_ < _n);
        assert(0 <= to_ and to_ < _n);
        assert(0 <= cap_);
        cost_ *= (_n + 1);
        const int e = int(cap.size());
        to[from_].push_back(e);
        cap.push_back(cap_);
        cost.push_back(cost_);
        opposite.push_back(to_);

        to[to_].push_back(e + 1);
        cap.push_back(0);
        cost.push_back(-cost_);
        opposite.push_back(from_);
        return e / 2;
    }
    void add_supply(int v, Cap supply) { b[v] += supply; }
    void add_demand(int v, Cap demand) { add_supply(v, -demand); }

    template <typename RetCost = Cost> RetCost solve() {
        Cost eps = 1;
        std::vector<int> que;
        for (const auto c : cost) {
            while (eps <= -c) eps <<= SCALING;
        }
        for (; eps >>= SCALING;) {
            auto no_admissible_cycle = [&]() -> bool {
                for (int i = 0; i < _n; i++) {
                    if (b[i]) return false;
                }
                std::vector<Cost> pp = p;
                for (int iter = 0; iter < REFINEMENT_ITER; iter++) {
                    bool flg = false;
                    for (int e = 0; e < int(cap.size()); e++) {
                        if (!cap[e]) continue;
                        int i = opposite[e ^ 1], j = opposite[e];
                        if (pp[j] > pp[i] + cost[e] + eps)
                            pp[j] = pp[i] + cost[e] + eps, flg = true;
                    }
                    if (!flg) return p = pp, true;
                }
                return false;
            };
            if (no_admissible_cycle()) continue; // Refine

            for (int e = 0; e < int(cap.size()); e++) {
                const int i = opposite[e ^ 1], j = opposite[e];
                const Cost cp_ij = cost[e] + p[i] - p[j];
                if (cap[e] and cp_ij < 0)
                    b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e], cap[e] = 0;
            }
            que.clear();
            int qh = 0;
            for (int i = 0; i < _n; i++) {
                if (b[i] > 0) que.push_back(i);
            }
            std::vector<int> iters(_n);
            while (qh < int(que.size())) {
                const int i = que[qh++];
                for (; iters[i] < int(to[i].size()) and b[i]; ++iters[i]) { // Push
                    int e = to[i][iters[i]];
                    if (!cap[e]) continue;
                    int j = opposite[e];
                    Cost cp_ij = cost[e] + p[i] - p[j];
                    if (cp_ij >= 0) continue;
                    Cap f = b[i] > cap[e] ? cap[e] : b[i];
                    if (b[j] <= 0 and b[j] + f > 0) que.push_back(j);
                    b[i] -= f, b[j] += f, cap[e] -= f, cap[e ^ 1] += f;
                }

                if (b[i] > 0) { // Relabel
                    bool flg = false;
                    for (int e : to[i]) {
                        if (!cap[e]) continue;
                        Cost x = p[opposite[e]] - cost[e] - eps;
                        if (!flg or x > p[i]) flg = true, p[i] = x;
                    }
                    que.push_back(i), iters[i] = 0;
                }
            }
        }
        RetCost ret = 0;
        for (int e = 0; e < int(cap.size()); e += 2) ret += RetCost(cost[e]) * cap[e ^ 1];
        return ret / (_n + 1);
    }
    std::vector<Cost> potential() const {
        std::vector<Cost> ret = p, c0 = cost;
        for (auto &x : ret) x /= (_n + 1);
        for (auto &x : c0) x /= (_n + 1);
        while (true) {
            bool flg = false;
            for (int i = 0; i < _n; i++) {
                for (const auto e : to[i]) {
                    if (!cap[e]) continue;
                    int j = opposite[e];
                    auto y = ret[i] + c0[e];
                    if (ret[j] > y) ret[j] = y, flg = true;
                }
            }
            if (!flg) break;
        }
        return ret;
    }
    struct edge {
        int from, to;
        Cap cap, flow;
        Cost cost;
    };
    edge get_edge(int e) const {
        int m = cap.size() / 2;
        assert(e >= 0 and e < m);
        return {opposite[e * 2 + 1], opposite[e * 2], cap[e * 2] + cap[e * 2 + 1], cap[e * 2 + 1],
                cost[e * 2] / (_n + 1)};
    }
    std::vector<edge> edges() const {
        int m = cap.size() / 2;
        std::vector<edge> result(m);
        for (int i = 0; i < m; i++) result[i] = get_edge(i);
        return result;
    }
};
