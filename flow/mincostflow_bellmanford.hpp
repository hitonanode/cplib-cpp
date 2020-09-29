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
    std::vector<COST> dual;  // dual[V]: potential
    std::vector<std::pair<int, int>> pos;

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
                    COST c = dist[v] + e.cost + dual[v] - dual[e.to];
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
                COST c = dist[v] + e.cost + dual[v] - dual[e.to];
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
        pos.emplace_back(from, g[from].size());
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
        dual.assign(V, 0);
        prevv.assign(V, -1);
        preve.assign(V, -1);
        CAP frem = f;
        while (frem > 0) {
            _calc_distance_dijkstra(s);
            if (dist[t] == INF_COST) break;
            for (int v = 0; v < V; v++) dual[v] = std::min(dual[v] + dist[v], INF_COST);
            CAP d = frem;
            for (int v = t; v != s; v = prevv[v]) {
                d = std::min(d, g[prevv[v]][preve[v]].cap);
            }
            frem -= d;
            ret += d * dual[t];
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
