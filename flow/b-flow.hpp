#pragma once
#include "flow/mincostflow.hpp"
#include <algorithm>
#include <vector>


// CUT begin
template <typename CAP, typename COST>
struct B_Flow
{
    int N, E;
    COST cost_bias;
    bool infeasible;
    mcf_graph<CAP, COST> mcf;
    std::vector<CAP> b;
    std::vector<CAP> fbias;
    std::vector<int> fdir;
    std::vector<CAP> f;
    std::vector<COST> potential;

    B_Flow(int N = 0) : N(N), E(0), cost_bias(0), infeasible(false), mcf(N + 2), b(N) {}

    void add_supply(int v, CAP supply) { b[v] += supply; }
    void add_demand(int v, CAP demand) { b[v] -= demand; }
    void add_edge(int s, int t, CAP lower_cap, CAP upper_cap, COST cost) {
        assert(s >= 0 and s < N);
        assert(t >= 0 and t < N);
        if (lower_cap > upper_cap) {
            infeasible = true;
            return;
        }
        E++;
        if (s == t) {
            if (cost > 0) upper_cap = lower_cap;
            else lower_cap = upper_cap;
        }
        if (cost < 0) {
            fbias.emplace_back(lower_cap);
            fdir.emplace_back(-1);
            cost_bias += cost * upper_cap;
            b[s] -= upper_cap;
            b[t] += upper_cap;
            mcf.add_edge(t, s, upper_cap - lower_cap, -cost);
        } else {
            fbias.emplace_back(upper_cap);
            fdir.emplace_back(1);
            if (lower_cap < 0) {
                cost_bias += cost * lower_cap, b[s] -= lower_cap, b[t] += lower_cap;
                upper_cap -= lower_cap, lower_cap = 0;
            }
            if (lower_cap > 0) {
                cost_bias += cost * lower_cap;
                b[s] -= lower_cap;
                b[t] += lower_cap;
                upper_cap -= lower_cap;
            }
            mcf.add_edge(s, t, upper_cap, cost);
        }
    }

    std::pair<bool, COST> solve() {
        if (infeasible) {
            return std::make_pair(false, 0);
        }
        CAP bsum = 0, bsum_negative = 0;
        for (int i = 0; i < N; i++) {
            if (b[i] > 0) {
                mcf.add_edge(N, i, b[i], 0), bsum += b[i];
            }
            if (b[i] < 0) {
                mcf.add_edge(i, N + 1, -b[i], 0), bsum_negative -= b[i];
            }
        }
        if (bsum != bsum_negative) {
            return std::make_pair(false, 0);
        }
        std::fill(b.begin(), b.end(), 0);
        auto ret = mcf.flow(N, N + 1, bsum);
        potential = mcf.dual, potential.resize(N);
        COST cost_ret = cost_bias + ret.second;
        cost_bias = 0;
        bool succeeded = (ret.first == bsum);
        f = fbias;
        for (int i = 0; i < E; i++) {
            const std::pair<int, int> &p = mcf.pos[i];
            f[i] -= fdir[i] * mcf.g[p.first][p.second].cap;
        }
        return std::make_pair(succeeded, cost_ret);
    }
};
