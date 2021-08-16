#pragma once
#include "../data_structure/light_forward_list.hpp"
#include <cassert>
#include <limits>
#include <queue>

// Cost scaling
// https://people.orie.cornell.edu/dpw/orie633/
// Implementation idea: https://yukicoder.me/submissions/680169
template <class Cap, class Cost> struct mcf_costscaling {
    mcf_costscaling() = default;
    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {
        static_assert(std::numeric_limits<Cap>::max() > 0, "max() must be greater than 0");
    }

    int _n;
    std::vector<Cap> cap;
    std::vector<Cost> cost;
    std::vector<int> opposite;
    std::vector<light_forward_list<int>> to;
    std::vector<Cap> b;
    std::vector<Cost> p;

    void add_edge(int from_, int to_, Cap cap_, Cost cost_) {
        assert(0 <= from_ && from_ < _n);
        assert(0 <= to_ && to_ < _n);
        assert(0 <= cap_);
        assert(0 <= cost_);
        cost_ *= (_n + 1);

        int e = int(cap.size());
        to[from_].push_front(e);
        cap.push_back(cap_);
        cost.push_back(cost_);
        opposite.push_back(to_);

        to[to_].push_front(e + 1);
        cap.push_back(0);
        cost.push_back(-cost_);
        opposite.push_back(from_);
    }
    void add_supply(int v, Cap supply) { b[v] += supply; }
    void add_demand(int v, Cap demand) { add_supply(v, -demand); }

    Cost flow(int SCALING = 1) {
        Cost eps = 1;
        for (const auto c : cost) {
            while (eps <= -c) eps <<= SCALING;
        }
        for (; eps >>= SCALING;) {
            for (int e = 0; e < int(cap.size()); e += 2) {
                const int i = opposite[e ^ 1], j = opposite[e];
                const Cost cp_ij = cost[e] + p[i] - p[j];
                if (cap[e] and cp_ij < 0) {
                    b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e], cap[e] = 0;
                } else if (cap[e ^ 1] and cp_ij > 0) {
                    b[i] += cap[e ^ 1], b[j] -= cap[e ^ 1], cap[e] += cap[e ^ 1], cap[e ^ 1] = 0;
                }
            }
            std::queue<int> q;
            for (int i = 0; i < _n; i++) {
                if (b[i] > 0) q.push(i);
            }
            while (q.size()) {
                const int i = q.front();
                q.pop();
                for (auto e : to[i]) { // Push
                    if (!cap[e]) continue;
                    int j = opposite[e];
                    Cost cp_ij = cost[e] + p[i] - p[j];
                    if (cp_ij >= 0) continue;
                    Cap f = b[i] > cap[e] ? cap[e] : b[i];
                    if (b[j] <= 0 and b[j] + f > 0) q.push(j);
                    b[i] -= f, b[j] += f, cap[e] -= f, cap[e ^ 1] += f;
                    if (!b[i]) break;
                }

                if (b[i] > 0) { // Relabel
                    bool flg = false;
                    for (int e : to[i]) {
                        if (!cap[e]) continue;
                        Cost x = p[opposite[e]] - cost[e] - eps;
                        if (!flg or x > p[i]) flg = true, p[i] = x;
                    }
                    q.push(i);
                }
            }
        }
        Cost ret = 0;
        for (int e = 0; e < int(cap.size()); e += 2) ret += cost[e] * cap[e ^ 1];
        return ret / (_n + 1);
    }
};
