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
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :x: graph/strongly_connected_components_bitset.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#f8b0b924ebd7046dbfa85a856e4682c8">graph</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph/strongly_connected_components_bitset.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:40:57+09:00




## Verified with

* :x: <a href="../../verify/graph/test/strongly_connected_components_bitset.test.cpp.html">graph/test/strongly_connected_components_bitset.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

