#pragma once
#include <cassert>
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// CUT begin
/*
MinCostFlow: Minimum-cost flow problem solver WITH NO NEGATIVE CYCLE
Verified by SRM 770 Div1 Medium <https://community.topcoder.com/stat?c=problem_statement&pm=15702>
*/
template <typename TFLOW = long long, typename TCOST = long long>
struct MinCostFlow
{
    const TCOST INF_COST = std::numeric_limits<TCOST>::max() / 2;
    struct edge {
        int to, rev;
        TFLOW cap;
        TCOST cost;
        friend std::ostream &operator<<(std::ostream &os, const edge &e) {
            os << '(' << e.to << ',' << e.rev << ',' << e.cap << ',' << e.cost << ')';
            return os;
        }
    };
    int V;
    std::vector<std::vector<edge>> G;
    std::vector<TCOST> dist;
    std::vector<int> prevv, preve;
    std::vector<TCOST> h;  // h[V]: potential
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
                for (int i = 0; i < (int)G[v].size(); i++) {
                    edge &e = G[v][i];
                    TCOST c = dist[v] + e.cost + h[v] - h[e.to];
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
        using P = std::pair<TCOST, int>;
        std::priority_queue<P, std::vector<P>, std::greater<P>> q;
        q.emplace(0, s);
        while (!q.empty()) {
            P p = q.top();
            q.pop();
            int v = p.second;
            if (dist[v] < p.first) continue;
            for (int i = 0; i < (int)G[v].size(); i++) {
                edge &e = G[v][i];
                TCOST c = dist[v] + e.cost + h[v] - h[e.to];
                if (e.cap > 0 and dist[e.to] > c) {
                    dist[e.to] = c, prevv[e.to] = v, preve[e.to] = i;
                    q.emplace(dist[e.to], e.to);
                }
            }
        }
        return true;
    }

    MinCostFlow(int V=0) : V(V), G(V) {}

    void add_edge(int from, int to, TFLOW cap, TCOST cost) {
        einfo.emplace_back(from, G[from].size());
        G[from].emplace_back(edge{to, (int)G[to].size() + (from == to), cap, cost});
        G[to].emplace_back(edge{from, (int)G[from].size() - 1, (TFLOW)0, -cost});
    }

    std::pair<TCOST, std::pair<bool, TFLOW>> flush(int s, int t, TFLOW f) {
        /*
        Flush amount of `f` from `s` to `t` using the Dijkstra's algorithm
        works for graph with no negative cycles (negative cost edges are allowed)
        retval: (min_flow, ([succeeded or not], residue flow))
        [Example] Succeeded: `([mincost], (true, 0))`
        */
        TCOST ret = 0;
        h.assign(V, 0);
        prevv.assign(V, -1);
        preve.assign(V, -1);
        while (f > 0) {
            _calc_distance_dijkstra(s);
            if (dist[t] == INF_COST) return std::make_pair(ret, std::make_pair(false, f));
            for (int v = 0; v < V; v++) h[v] = std::min(h[v] + dist[v], INF_COST);
            TFLOW d = f;
            for (int v = t; v != s; v = prevv[v]) {
                d = std::min(d, G[prevv[v]][preve[v]].cap);
            }
            f -= d;
            ret += d * h[t];
            for (int v = t; v != s; v = prevv[v]) {
                edge &e = G[prevv[v]][preve[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
        return std::make_pair(ret, std::make_pair(true, 0));
    }

    friend std::ostream &operator<<(std::ostream &os, const MinCostFlow &mcf) {
        os << "[MinCostFlow]V=" << mcf.V << ":";
        for (int i = 0; i < (int)mcf.G.size(); i++) for (auto &e : mcf.G[i]) {
            os << "\n" << i << "->" << e.to << ": cap=" << e.cap << ", cost=" << e.cost;
        }
        return os;
    }
};

template <typename TFLOW = long long, typename TCOST = long long>
struct B_Flow
{
    int N, E;
    MinCostFlow<TFLOW, TCOST> mcf;
    std::vector<TFLOW> b;
    TCOST cost_bias;
    std::vector<TFLOW> fbias;
    std::vector<int> fdir;
    bool infeasible;
    B_Flow(int N = 0) : N(N), E(0), mcf(N + 2), b(N), cost_bias(0), infeasible(false) {}

    void add_supply(int v, TFLOW supply) { b[v] += supply; }
    void add_demand(int v, TFLOW demand) { b[v] -= demand; }
    void add_edge(int s, int t, TFLOW lower_cap, TFLOW upper_cap, TCOST cost)
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

    std::vector<TFLOW> f;
    std::pair<bool, TCOST> solve()
    {
        if (infeasible)
        {
            return std::make_pair(false, 0);
        }
        TFLOW bsum = 0, bsum_negative = 0;
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
        auto ret = mcf.flush(N, N + 1, bsum);
        TCOST cost_ret = cost_bias + ret.first;
        bool succeeded = ret.second.first;
        f = fbias;
        for (int i = 0; i < E; i++)
        {
            std::pair<int, int> p = mcf.einfo[i];
            f[i] -= fdir[i] * mcf.G[p.first][p.second].cap;
        }
        return std::make_pair(succeeded, cost_ret);
    }
};
