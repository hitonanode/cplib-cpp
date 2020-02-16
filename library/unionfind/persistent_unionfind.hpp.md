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


# :warning: unionfind/persistent_unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05779a67d348d10b6c575a1ac0d9b972">unionfind</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/persistent_unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-13 17:28:13+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <map>
#include <utility>
#include <vector>

struct PersistentUnionFind
{
    std::vector<int> parsz, t_unite;
    std::vector<std::map<int, int>> size_history;
    PersistentUnionFind(int N) : parsz(N, 1), t_unite(N, 2000000000), size_history(N) {
        for (int i = 0; i < N; i++) size_history[i][-1] = 1;
    }
    int find(int x, int t) { return (t_unite[x] > t) ? x : find(parsz[x], t); } // 時刻t以下のマージ操作によって定まる親
    void unite(int x, int y, int t) {
        if ((x = find(x, t)) == (y = find(y, t))) return;
        if (parsz[x] < parsz[y]) std::swap(x, y);
        parsz[x] += parsz[y], parsz[y] = x, t_unite[y] = t;
        size_history[x][t] = parsz[x];
    }
    int size(int x, int t) { return prev(size_history[find(x, t)].upper_bound(t))->second; }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "unionfind/persistent_unionfind.hpp"
#include <map>
#include <utility>
#include <vector>

struct PersistentUnionFind
{
    std::vector<int> parsz, t_unite;
    std::vector<std::map<int, int>> size_history;
    PersistentUnionFind(int N) : parsz(N, 1), t_unite(N, 2000000000), size_history(N) {
        for (int i = 0; i < N; i++) size_history[i][-1] = 1;
    }
    int find(int x, int t) { return (t_unite[x] > t) ? x : find(parsz[x], t); } // 時刻t以下のマージ操作によって定まる親
    void unite(int x, int y, int t) {
        if ((x = find(x, t)) == (y = find(y, t))) return;
        if (parsz[x] < parsz[y]) std::swap(x, y);
        parsz[x] += parsz[y], parsz[y] = x, t_unite[y] = t;
        size_history[x][t] = parsz[x];
    }
    int size(int x, int t) { return prev(size_history[find(x, t)].upper_bound(t))->second; }
    bool same(int x, int y, int t) { return find(x, t) == find(y, t); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

