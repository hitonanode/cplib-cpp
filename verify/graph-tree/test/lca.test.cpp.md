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


# :heavy_check_mark: graph-tree/test/lca.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/graph-tree/test/lca.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-01-13 19:30:08+09:00


* see: <a href="https://judge.yosupo.jp/problem/lca">https://judge.yosupo.jp/problem/lca</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/graph-tree/lowest_common_ancestor.hpp.html">graph-tree/lowest_common_ancestor.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include "graph-tree/lowest_common_ancestor.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main()
{
    int N, Q, p, u, v;
    cin >> N >> Q;
    UndirectedWeightedTree graph(N);
    for (int i = 1; i <= N - 1; i++) {
        cin >> p;
        graph.add_edge(i, p, 1);
    }
    graph.fix_root(0);
    graph.doubling_precalc();

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        cout << graph.lowest_common_ancestor(u, v) << endl;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "graph-tree/test/lca.test.cpp"
#include <iostream>
#line 1 "graph-tree/lowest_common_ancestor.hpp"
// lowest common ancestor (LCA) class for undirected weighted tree
// 無向重み付きグラフの最小共通祖先
// <https://yukicoder.me/submissions/392383>

#include <vector>
using namespace std;

class UndirectedWeightedTree
{
    using T = long long int;   // Arbitrary data structure (operator+, operator- must be defined)
    const int INVALID = -1;
    int V, lgV;
    int E;
    int root;
    vector<vector<pair<int, int>>> adj; // (nxt_vertex, edge_id)
    // vector<pint> edge;  // edges[edge_id] = (vertex_id, vertex_id)
    vector<T> weight;  // w[edge_id]
    vector<int> par;  // parent_vertex_id[vertex_id]
    vector<int> depth;  // depth_from_root[vertex_id]
    vector<T> acc_weight;  // w_sum_from_root[vertex_id]

    void _fix_root_dfs(int now, int prv, int prv_edge_id)
    {
        par[now] = prv;
        if (prv_edge_id != INVALID) acc_weight[now] = acc_weight[prv] + weight[prv_edge_id];
        for (auto nxt : adj[now]) if (nxt.first != prv)
        {
            depth[nxt.first] = depth[now] + 1;
            _fix_root_dfs(nxt.first, now, nxt.second);
        }
    }

public:
    UndirectedWeightedTree(int N = 0): V(N), E(0), adj(N) {
        lgV = 1;
        while (1 << lgV < V) lgV++;
    }

    void add_edge(int u, int v, T w)
    {
        adj[u].emplace_back(v, E);
        adj[v].emplace_back(u, E);
        // edge.emplace_back(u, v);
        weight.emplace_back(w);
        E++;
    }

    void fix_root(int r)
    {
        root = r;
        par.resize(V);
        depth.resize(V);
        depth[r] = 0;
        acc_weight.resize(V);
        acc_weight[r] = 0;
        _fix_root_dfs(root, INVALID, INVALID);
    }

    vector<vector<int>> doubling;
    void doubling_precalc()
    {
        doubling.assign(lgV, vector<int>(V));
        doubling[0] = par;
        for (int d = 0; d < lgV - 1; d++) for (int i = 0; i < V; i++)
        {
            if (doubling[d][i] == INVALID) doubling[d + 1][i] = INVALID;
            else doubling[d + 1][i] = doubling[d][doubling[d][i]];
        }
    }

    int kth_parent(int x, int k)
    {
        for (int d = 0; d < lgV; d++)
        {
            if (x == INVALID) return INVALID;
            if (k & (1 << d)) x = doubling[d][x];
        }
        return x;
    }

    int lowest_common_ancestor(int u, int v)
    {
        if (depth[u] > depth[v]) swap(u, v);

        v = kth_parent(v, depth[v] - depth[u]);
        if (u == v) return u;
        for (int d = lgV - 1; d >= 0; d--)
        {
            if (doubling[d][u] != doubling[d][v]) u = doubling[d][u], v = doubling[d][v];
        }
        return par[u];
    }

    T path_length(int u, int v)
    {
        // Not distance, but the sum of weights
        int r = lowest_common_ancestor(u, v);
        return (acc_weight[u] - acc_weight[r]) + (acc_weight[v] - acc_weight[r]);
    }
};
#line 3 "graph-tree/test/lca.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/lca"

int main()
{
    int N, Q, p, u, v;
    cin >> N >> Q;
    UndirectedWeightedTree graph(N);
    for (int i = 1; i <= N - 1; i++) {
        cin >> p;
        graph.add_edge(i, p, 1);
    }
    graph.fix_root(0);
    graph.doubling_precalc();

    for (int i = 0; i < Q; i++) {
        cin >> u >> v;
        cout << graph.lowest_common_ancestor(u, v) << endl;
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

