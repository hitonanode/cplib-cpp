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


# :heavy_check_mark: graph/test/maxflow.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#cb3e5c672d961db00b76e36ddf5c068a">graph/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/test/maxflow.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph/maxflow.hpp.html">graph/maxflow.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "graph/maxflow.hpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"

int main()
{
    int V, E;
    std::cin >> V >> E;
    MaxFlow<int> ff(V), dinic(V);
    while (E--) {
        int u, v, c;
        std::cin >> u >> v >> c;
        ff.add_edge(u, v, c);
        dinic.add_edge(u, v, c);
    }
    int ret_ff = ff.FF(0, V - 1);
    int ret_dinic = dinic.Dinic(0, V - 1);
    assert(ret_ff == ret_dinic);
    std::cout << ret_ff << std::endl;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph/maxflow.hpp"
#include <algorithm>
#include <limits>
#include <queue>
#include <vector>

// CUT begin
// MaxFlow (Dinic algorithm)
template <typename T>
struct MaxFlow
{
    struct edge { int to; T cap; int rev; };
    std::vector<std::vector<edge>> edges;
    std::vector<int> level;  // level[i] = distance between vertex S and i (Default: -1)
    std::vector<int> iter;  // iteration counter, used for Dinic's DFS
    std::vector<int> used;  // Used for Ford-Fulkerson's Algorithm

    void bfs(int s)
    {
        level.assign(edges.size(), -1);
        std::queue<int> q;
        level[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int v = q.front();
            q.pop();
            for (edge &e : edges[v]) {
                if (e.cap > 0 and level[e.to] < 0) {
                    level[e.to] = level[v] + 1;
                    q.push(e.to);
                }
            }
        }
    }
 
    T dfs_dinic(int v, int goal, T f)
    {
        if (v == goal) return f;
        for (int &i = iter[v]; i < (int)edges[v].size(); i++) {
            edge &e = edges[v][i];
            if (e.cap > 0 and level[v] < level[e.to]) {
                T d = dfs_dinic(e.to, goal, std::min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    edges[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
 
    T dfs_ff(int v, int goal, T f)
    {
        if (v == goal) return f;
        used[v] = true;
        for (edge &e : edges[v]) {
            if (e.cap > 0 && !used[e.to]) {
                T d = dfs_ff(e.to, goal, std::min(f, e.cap));
                if (d > 0) {
                    e.cap -= d;
                    edges[e.to][e.rev].cap += d;
                    return d;
                }
            }
        }
        return 0;
    }
 
public:
    MaxFlow(int N) { edges.resize(N); }
    void add_edge(int from, int to, T capacity)
    {
        edges[from].push_back(edge{to, capacity, (int)edges[to].size()});
        edges[to].push_back(edge{from, (T)0, (int)edges[from].size() - 1});
    }
 
    // Dinic algorithm
    // Complexity: O(VE)
    T Dinic(int s, int t)
    {
        constexpr T INF = std::numeric_limits<T>::max();
        T flow = 0;
        while (true) {
            bfs(s);
            if (level[t] < 0) return flow;
            iter.assign(edges.size(), 0);
            T f;
            while ((f = dfs_dinic(s, t, INF)) > 0) flow += f;
        }
    }

    // Ford-Fulkerson algorithm
    // Complexity: O(EF)
    T FF(int s, int t)
    {
        constexpr T INF = std::numeric_limits<T>::max();
        T flow = 0;
        while (true) {
            used.assign(edges.size(), 0);
            T f = dfs_ff(s, t, INF);
            if (f == 0) return flow;
            flow += f;
        }
    }
 
    void back_flow(int s, int t, int s_e, int t_e, T capacity_reduce)
    {
        int i;
        for (i=0; edges[s_e][i].to != t_e; ) i++;
        edge &e = edges[s_e][i];
 
        if (capacity_reduce <= e.cap) {
            e.cap -= capacity_reduce;
        }
        else {
            T flow = capacity_reduce - e.cap;
            e.cap = 0;
            edges[e.to][e.rev].cap -= flow;
 
            T f_sum = 0;
            while (f_sum != flow) {
                used.assign(edges.size(), 0);
                f_sum += dfs_ff(t, t_e, flow - f_sum);
            }
            f_sum = 0;
            while (f_sum != flow) {
                used.assign(edges.size(), 0);
                f_sum += dfs_ff(s_e, s, flow - f_sum);
            }
        }
    }
};
#line 2 "graph/test/maxflow.test.cpp"
#include <cassert>
#include <iostream>
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A"

int main()
{
    int V, E;
    std::cin >> V >> E;
    MaxFlow<int> ff(V), dinic(V);
    while (E--) {
        int u, v, c;
        std::cin >> u >> v >> c;
        ff.add_edge(u, v, c);
        dinic.add_edge(u, v, c);
    }
    int ret_ff = ff.FF(0, V - 1);
    int ret_dinic = dinic.Dinic(0, V - 1);
    assert(ret_ff == ret_dinic);
    std::cout << ret_ff << std::endl;
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

