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


# :warning: graph-tree/centroid_decomposition.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#aea7f79aded53b9cdf48a7ce3f3ec60e">graph-tree</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph-tree/centroid_decomposition.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-24 18:37:52+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
/*
(Recursive) Centroid Decomposition
Verification: Codeforces #190 Div.1 C <https://codeforces.com/contest/321/submission/59093583>

fix_root(int r): Build information of the tree which `r` belongs to.
detect_centroid(int r): Enumerate centroid(s) of the tree which `r` belongs to.
*/

#pragma once
#include <tuple>
#include <utility>
#include <vector>

struct Tree
{
    int NO_PARENT = -1;
    using pint = std::pair<int, int>;
    int V;
    int E;
    std::vector<std::vector<pint>> to;  // (node_id, edge_id)
    std::vector<int> par;          // parent node_id par[root] = -1
    std::vector<std::vector<int>> chi;  // children id's
    std::vector<int> subtree_size; // size of each subtree
    std::vector<int> available_edge; // If 0, ignore the corresponding edge.

    Tree() : Tree(0) {}
    Tree(int v) : V(v), E(0), to(v), par(v, NO_PARENT), chi(v), subtree_size(v) {}

    void add_edge(int v1, int v2)
    {
        to[v1].emplace_back(v2, E);
        to[v2].emplace_back(v1, E);
        E++;
        available_edge.emplace_back(1);
    }

    int _dfs_fixroot(int now, int prv)
    {
        chi[now].clear();
        subtree_size[now] = 1;
        for (auto nxt : to[now]) {
            if (nxt.first != prv and available_edge[nxt.second]) {
                par[nxt.first] = now;
                chi[now].push_back(nxt.first);
                subtree_size[now] += _dfs_fixroot(nxt.first, now);
            }
        }
        return subtree_size[now];
    }

    void fix_root(int root) {
        par[root] = NO_PARENT;
        _dfs_fixroot(root, -1);
    }

    //// Centroid Decpmposition ////
    std::vector<int> centroid_cand_tmp;
    void _dfs_detect_centroids(int now, int prv, int n)
    {
        bool is_centroid = true;
        for (auto nxt : to[now])
        {
            if (nxt.first != prv and available_edge[nxt.second])
            {
                _dfs_detect_centroids(nxt.first, now, n);
                if (subtree_size[nxt.first] > n / 2) is_centroid = false;
            }
        }
        if (n - subtree_size[now] > n / 2) is_centroid = false;
        if (is_centroid) centroid_cand_tmp.push_back(now);
    }
    pint detect_centroids(int r) // ([centroid_node_id1], ([centroid_node_id2]|-1))
    {
        centroid_cand_tmp.clear();
        while (par[r] != NO_PARENT) r = par[r];
        int n = subtree_size[r];
        _dfs_detect_centroids(r, -1, n);
        if (centroid_cand_tmp.size() == 1) return std::make_pair(centroid_cand_tmp[0], -1);
        else return std::make_pair(centroid_cand_tmp[0], centroid_cand_tmp[1]);
    }

    void centroid_decomposition(int now) {
        fix_root(now);
        now = detect_centroids(now).first;
        /*
        do something
        */
        for (auto p : to[now]) {
            int nxt, eid;
            std::tie(nxt, eid) = p;
            if (available_edge[eid] == 0) continue;
            available_edge[eid] = 0;
            centroid_decomposition(nxt);
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
Traceback (most recent call last):
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/docs.py", line 347, in write_contents
    bundled_code = language.bundle(self.file_class.file_path, basedir=self.cpp_source_path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus.py", line 68, in bundle
    bundler.update(path)
  File "/opt/hostedtoolcache/Python/3.8.2/x64/lib/python3.8/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py", line 115, in update
    raise BundleError(path, i + 1, "#pragma once found in a non-first line")
onlinejudge_verify.languages.cplusplus_bundle.BundleError: graph-tree/centroid_decomposition.hpp: line 9: #pragma once found in a non-first line

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

