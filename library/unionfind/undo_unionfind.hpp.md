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


# :warning: unionfind/undo_unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05779a67d348d10b6c575a1ac0d9b972">unionfind</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/undo_unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-05 20:29:36+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once 
#include <stack>
#include <vector>
#include <numeric>
#include <utility>

// CUT begin
// UnionFind, able to rewind to the previous state by undo()
// Written for Educational Codeforces 62 F, although not verified yet.
struct UndoSizeAwareUnionFind
{
    using pint = std::pair<int, int>;
    std::vector<int> par, cou;
    std::stack<std::pair<int, pint>> history;
    UndoSizeAwareUnionFind(int N) : par(N), cou(N, 1) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return (par[x] == x) ? x :find(par[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (cou[x] < cou[y]) std::swap(x, y);
        history.emplace(y, pint(par[y], cou[x]));
        if (x != y) par[y] = x, cou[x] += cou[y];
    }
    void undo() {
        cou[par[history.top().first]] = history.top().second.second;
        par[history.top().first] = history.top().second.first;
        history.pop();
    }
    void reset() {
        while (!history.empty()) undo();
    }
    int count(int x) { return cou[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "unionfind/undo_unionfind.hpp"
#include <stack>
#include <vector>
#include <numeric>
#include <utility>

// CUT begin
// UnionFind, able to rewind to the previous state by undo()
// Written for Educational Codeforces 62 F, although not verified yet.
struct UndoSizeAwareUnionFind
{
    using pint = std::pair<int, int>;
    std::vector<int> par, cou;
    std::stack<std::pair<int, pint>> history;
    UndoSizeAwareUnionFind(int N) : par(N), cou(N, 1) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) { return (par[x] == x) ? x :find(par[x]); }
    void unite(int x, int y) {
        x = find(x), y = find(y);
        if (cou[x] < cou[y]) std::swap(x, y);
        history.emplace(y, pint(par[y], cou[x]));
        if (x != y) par[y] = x, cou[x] += cou[y];
    }
    void undo() {
        cou[par[history.top().first]] = history.top().second.second;
        par[history.top().first] = history.top().second.first;
        history.pop();
    }
    void reset() {
        while (!history.empty()) undo();
    }
    int count(int x) { return cou[find(x)]; }
    bool same(int x, int y) { return find(x) == find(y); }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

