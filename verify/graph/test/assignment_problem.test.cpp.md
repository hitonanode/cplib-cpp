---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: graph/test/assignment_problem.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/assignment_problem.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 04:20:40+09:00


* see: <a href="https://judge.yosupo.jp/problem/assignment">https://judge.yosupo.jp/problem/assignment</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/flow_mincost.hpp.html">graph/flow_mincost.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "graph/flow_mincost.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include <algorithm>
#include <iostream>

template<typename TC>
std::pair<TC, std::vector<int>> AssignmentProblem(std::vector<std::vector<TC>> cost)
{
    int N = cost.size();
    MinCostFlow mcf(N * 2 + 2);
    int S = N * 2, T = N * 2 + 1;
    for (int i = 0; i < N; i++)
    {
        mcf.add_edge(S, i, 1, 0);
        mcf.add_edge(N + i, T, 1, 0);
        for (int j = 0; j < N; j++)
        {
            mcf.add_edge(i, N + j, 1, cost[i][j]);
        }
    }
    auto total_cost = mcf.flush(S, T, N).first;
    std::vector<int> ret;

    for (int i = 0; i < N; i++)
    {
        for (const auto &g : mcf.G[i])
        {
            if (g.to != S and !g.cap)
            {
                ret.emplace_back(g.to - N);
                break;
            }
        }
    }
    return std::make_pair(total_cost, ret);
}


int main()
{
    int N;
    std::cin >> N;
    std::vector<std::vector<long long>> A(N, std::vector<long long>(N));
    for (auto &vec : A)
    {
        for (auto &x : vec)
        {
            std::cin >> x;
        }
    }
    auto ret = AssignmentProblem(A);
    std::cout << ret.first << '\n';
    for (auto x : ret.second) std::cout << x << ' ';
    std::cout << '\n';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/flow_mincost.hpp"
#include <iostream>
#include <limits>
#include <queue>
#include <vector>

// CUT begin
/*
MinCostFlow: Minimum-cost flow problem solver WITH NO NEGATIVE CYCLE
Verified by SRM 770 Div1 Medium <https://community.topcoder.com/stat?c=problem_statement&pm=15702>
*/
struct MinCostFlow
{
    using TFLOW = long long int;
    using TCOST = long long int;
    const TCOST INF_COST = std::numeric_limits<TCOST>::max();
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
        G[from].emplace_back(edge{to, (int)G[to].size(), cap, cost});
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
            for (int v = 0; v < V; v++) h[v] += dist[v];
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
#line 2 "graph/test/assignment_problem.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/assignment"
#include <algorithm>
#line 5 "graph/test/assignment_problem.test.cpp"

template<typename TC>
std::pair<TC, std::vector<int>> AssignmentProblem(std::vector<std::vector<TC>> cost)
{
    int N = cost.size();
    MinCostFlow mcf(N * 2 + 2);
    int S = N * 2, T = N * 2 + 1;
    for (int i = 0; i < N; i++)
    {
        mcf.add_edge(S, i, 1, 0);
        mcf.add_edge(N + i, T, 1, 0);
        for (int j = 0; j < N; j++)
        {
            mcf.add_edge(i, N + j, 1, cost[i][j]);
        }
    }
    auto total_cost = mcf.flush(S, T, N).first;
    std::vector<int> ret;

    for (int i = 0; i < N; i++)
    {
        for (const auto &g : mcf.G[i])
        {
            if (g.to != S and !g.cap)
            {
                ret.emplace_back(g.to - N);
                break;
            }
        }
    }
    return std::make_pair(total_cost, ret);
}


int main()
{
    int N;
    std::cin >> N;
    std::vector<std::vector<long long>> A(N, std::vector<long long>(N));
    for (auto &vec : A)
    {
        for (auto &x : vec)
        {
            std::cin >> x;
        }
    }
    auto ret = AssignmentProblem(A);
    std::cout << ret.first << '\n';
    for (auto x : ret.second) std::cout << x << ' ';
    std::cout << '\n';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

