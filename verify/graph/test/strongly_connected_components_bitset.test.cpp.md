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


# :x: graph/test/strongly_connected_components_bitset.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/graph/test/strongly_connected_components_bitset.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C</a>


## Depends on

* :x: <a href="../../../library/graph/strongly_connected_components_bitset.hpp.html">graph/strongly_connected_components_bitset.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"
#include "graph/strongly_connected_components_bitset.hpp"

#include <cassert>
#include <stdio.h>
constexpr int VMAX = 10000;
int main()
{
    int V, E;
    scanf("%d %d", &V, &E);
    assert(V <= VMAX);
    std::vector<std::bitset<VMAX>> e(V), einv(V);
    while (E--)
    {
        int s, t;
        scanf("%d %d", &s, &t);
        e[s][t] = einv[t][s] = 1;
    }
    DirectedGraphSCC64<VMAX> graph(e, einv);

    int Q;
    scanf("%d", &Q);
    while (Q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", graph.cmp[u] == graph.cmp[v]);
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph/test/strongly_connected_components_bitset.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C"
#line 2 "graph/strongly_connected_components_bitset.hpp"
#include <bitset>
#include <vector>

// CUT begin
// Directed graph library to find strongly connected components （強連結成分分解）
// 0-indexed directed graph
// - using std::bitset
// - Fast for dense graphs
// Complexity: O(V^2/64)
// Verified: CF1268D <https://codeforces.com/contest/1268/submission/68125495>
template<int VMAX>
struct DirectedGraphSCC64 {
    int V;
    const std::vector<std::bitset<VMAX>> &e, &einv;
    std::vector<int> vs, cmp;
    std::bitset<VMAX> unvisited;
    int scc_num;
    void _dfs(int now) {
        unvisited.reset(now);
        while (true) {
            int nxt = (unvisited & e[now])._Find_first();
            if (nxt >= V) break;
            _dfs(nxt);
        }
        vs.push_back(now);
    }
    void _rdfs(int now, int k) {
        unvisited.reset(now);
        cmp[now] = k;
        while (true) {
            int nxt = (unvisited & einv[now])._Find_first();
            if (nxt >= V) break;
            _rdfs(nxt, k);
        }
    }
    // Detect strongly connected components and return # of them.
    // Also, assign each vertex `v` the scc id `cmp[v]` (0-indexed)
    DirectedGraphSCC64(const std::vector<std::bitset<VMAX>> &edge, const std::vector<std::bitset<VMAX>> &edge_inv)
        : V(edge.size()), e(edge), einv(edge_inv), cmp(edge.size()), scc_num(0)
    {
        unvisited.set();
        for (int i = 0; i < V; i++) if (unvisited[i]) _dfs(i);
        unvisited.set();
        for (int i = (int)vs.size() - 1; i >= 0; i--) if (unvisited[vs[i]]) {
            _rdfs(vs[i], scc_num++);
        }
    }
};
#line 3 "graph/test/strongly_connected_components_bitset.test.cpp"

#include <cassert>
#include <stdio.h>
constexpr int VMAX = 10000;
int main()
{
    int V, E;
    scanf("%d %d", &V, &E);
    assert(V <= VMAX);
    std::vector<std::bitset<VMAX>> e(V), einv(V);
    while (E--)
    {
        int s, t;
        scanf("%d %d", &s, &t);
        e[s][t] = einv[t][s] = 1;
    }
    DirectedGraphSCC64<VMAX> graph(e, einv);

    int Q;
    scanf("%d", &Q);
    while (Q--)
    {
        int u, v;
        scanf("%d %d", &u, &v);
        printf("%d\n", graph.cmp[u] == graph.cmp[v]);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

