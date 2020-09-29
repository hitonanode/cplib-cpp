#pragma once
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// CUT begin
/*
MinCostFlow: Minimum-cost flow problem solver WITH NO NEGATIVE CYCLE (just negative cost edge is allowed)
Verified by SRM 770 Div1 Medium <https://community.topcoder.com/stat?c=problem_statement&pm=15702>
*/
template <typename CAP = long long, typename COST = long long>
struct MinCostFlow
{
    const COST INF_COST = std::numeric_limits<COST>::max() / 2;
    struct edge {
        int to, rev;
        CAP cap;
        COST cost;
        friend std::ostream &operator<<(std::ostream &os, const edge &e) {
            os << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';
            return os;
        }
    };
    int V;
    std::vector<std::vector<edge>> g;
    std::vector<COST> dist;
    std::vector<int> prevv, preve;
    std::vector<COST> h;  // h[V]: potential
    std::vector<std::pair<int, int>> einfo;

    bool _calc_distance_bellman_ford(int s) {  // O(VE), able to detect negative cycle
        dist.assign(V, INF_COST);
        dist[s] = 0;
        bool upd = true;
        int cnt = 0;
        while (upd) {
            upd = false;
            cnt++;
            if (cnt > V) return false;  // Negative cycle existence
            for (int v = 0; v < V; v++) if (dist[v] != INF_COST) {
                for (int i = 0; i < (int)g[v].size(); i++) {
                    edge &e = g[v][i];
                    COST c = dist[v] + e.cost + h[v] - h[e.to];
                    if (e.cap > 0 and dist[e.to] > c) {
                        dist[e.to] = c, prevv[e.to] = v, preve[e.to] = i;
                        upd = true;
                    }
                }
            }
        }
        return true;
    }

    bool _calc_distance_dijkstra(int s) {  // O(ElogV)
        dist.assign(V, INF_COST);
        dist[s] = 0;
        using P = std::pair<COST, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> q;
        q.emplace(0, s);
        while (!q.empty()) {
            P p = q.top();
            q.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < (int)g[v].size(); i++) {
                edge &e = g[v][i];
                COST c = dist[v] + e.cost + h[v] - h[e.to];
                if (e.cap > 0 and dist[e.to] > c) {
                    dist[e.to] = c, prevv[e.to] = v, preve[e.to] = i;
                    q.emplace(dist[e.to], e.to);
                }
            }
        }
        return true;
    }

    MinCostFlow(int V=0) : V(V), g(V) {}

    void add_edge(int from, int to, CAP cap, COST cost) {
        assert(0 <= from and from < V);
        assert(0 <= to and to < V);
        einfo.emplace_back(from, g[from].size());
        g[from].emplace_back(edge{to, (int)g[to].size() + (from == to), cap, cost});
        g[to].emplace_back(edge{from, (int)g[from].size() - 1, (CAP)0, -cost});
    }

    std::pair<CAP, COST> flow(int s, int t, const CAP &f) {
        /*
        Flush amount of `f` from `s` to `t` using the Dijkstra's algorithm
        works for graph with no negative cycles (negative cost edges are allowed)
        retval: (flow, cost)
        */
        COST ret = 0;
        h.assign(V, 0);
        prevv.assign(V, -1);
        preve.assign(V, -1);
        CAP frem = f;
        while (frem > 0) {
            _calc_distance_dijkstra(s);
            if (dist[t] == INF_COST) break;
            for (int v = 0; v < V; v++) h[v] = std::min(h[v] + dist[v], INF_COST);
            CAP d = frem;
            for (int v = t; v != s; v = prevv[v]) {
                d = std::min(d, g[prevv[v]][preve[v]].cap);
            }
            frem -= d;
            ret += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge &e = g[prevv[v]][preve[v]];
                e.cap -= d;
                g[v][e.rev].cap += d;
            }
        }
        return std::make_pair(f - frem, ret);
    }

    friend std::ostream &operator<<(std::ostream &os, const MinCostFlow &mcf) {
        os << "[MinCostFlow]V=" << mcf.V << ":";
        for (int i = 0; i < (int)mcf.g.size(); i++) for (auto &e : mcf.g[i]) {
            os << "\n" << i << "->" << e.to << ": cap=" << e.cap << ", cost=" << e.cost;
        }
        return os;
    }
};

template <typename CAP, typename COST>
struct B_Flow
{
    int N, E;
    MinCostFlow<CAP, COST> mcf;
    std::vector<CAP> b;
    COST cost_bias;
    std::vector<CAP> fbias;
    std::vector<int> fdir;
    bool infeasible;

    std::vector<CAP> f;
    const std::vector<COST> &potential;

    B_Flow(int N = 0) : N(N), E(0), mcf(N + 2), b(N), cost_bias(0), infeasible(false), potential(mcf.h) {}

    void add_supply(int v, CAP supply) { b[v] += supply; }
    void add_demand(int v, CAP demand) { b[v] -= demand; }
    void add_edge(int s, int t, CAP lower_cap, CAP upper_cap, COST cost)
    {
        assert(s >= 0 and s < N);
        assert(t >= 0 and t < N);
        if (lower_cap > upper_cap)
        {
            infeasible = true;
            return;
        }
        E++;
        if (s == t)
        {
            if (cost > 0) upper_cap = lower_cap;
            else lower_cap = upper_cap;
        }
        if (cost < 0)
        {
            fbias.emplace_back(lower_cap);
            fdir.emplace_back(-1);
            cost_bias += cost * upper_cap;
            b[s] -= upper_cap;
            b[t] += upper_cap;
            mcf.add_edge(t, s, upper_cap - lower_cap, -cost);
        }
        else
        {
            fbias.emplace_back(upper_cap);
            fdir.emplace_back(1);
            if (lower_cap < 0)
            {
                cost_bias += cost * lower_cap, b[s] -= lower_cap, b[t] += lower_cap;
                upper_cap -= lower_cap, lower_cap = 0;
            }
            if (lower_cap > 0)
            {
                cost_bias += cost * lower_cap;
                b[s] -= lower_cap;
                b[t] += lower_cap;
                upper_cap -= lower_cap;
            }
            mcf.add_edge(s, t, upper_cap, cost);
        }
    }

    std::pair<bool, COST> solve()
    {
        if (infeasible)
        {
            return std::make_pair(false, 0);
        }
        CAP bsum = 0, bsum_negative = 0;
        for (int i = 0; i < N; i++)
        {
            if (b[i] > 0)
            {
                mcf.add_edge(N, i, b[i], 0);
                bsum += b[i];
            }
            if (b[i] < 0)
            {
                mcf.add_edge(i, N + 1, -b[i], 0);
                bsum_negative -= b[i];
            }
        }
        if (bsum != bsum_negative)
        {
            return std::make_pair(false, 0);
        }
        std::fill(b.begin(), b.end(), 0);
        auto ret = mcf.flow(N, N + 1, bsum);
        COST cost_ret = cost_bias + ret.first;
        cost_bias = 0;
        bool succeeded = ret.second.first;
        f = fbias;
        for (int i = 0; i < E; i++)
        {
            std::pair<int, int> p = mcf.einfo[i];
            f[i] -= fdir[i] * mcf.g[p.first][p.second].cap;
        }
        return std::make_pair(succeeded, cost_ret);
    }
};
