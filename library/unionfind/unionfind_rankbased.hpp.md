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


# :heavy_check_mark: unionfind/unionfind_rankbased.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05779a67d348d10b6c575a1ac0d9b972">unionfind</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/unionfind_rankbased.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/unionfind/test/unionfind_plain.test.cpp.html">unionfind/test/unionfind_plain.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/unionfind/test/unionfind_rankbased.test.cpp.html">unionfind/test/unionfind_rankbased.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <numeric>
#include <vector>

// CUT begin
// UnionFind Tree (0-indexed)
struct RankBasedUnionFind
{
    std::vector<int> par, rank;
    RankBasedUnionFind(int N = 0): par(N), rank(N) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) par[x] = y;
        else par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "unionfind/unionfind_rankbased.hpp"
#include <numeric>
#include <vector>

// CUT begin
// UnionFind Tree (0-indexed)
struct RankBasedUnionFind
{
    std::vector<int> par, rank;
    RankBasedUnionFind(int N = 0): par(N), rank(N) {
        iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return (par[x] == x) ? x : (par[x] = find(par[x])); }
    bool unite(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (rank[x] < rank[y]) par[x] = y;
        else par[y] = x;
        if (rank[x] == rank[y]) rank[x]++;
        return true;
    }
    bool same(int x, int y) { return find(x) == find(y); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

