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


# :warning: unionfind/grid_unionfind.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#05779a67d348d10b6c575a1ac0d9b972">unionfind</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/grid_unionfind.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>
#include <iomanip>
#include <iostream>

// CUT begin
struct GridUnionFind
{
    int H, W;
    std::vector<int> par, cou;
    using P = std::pair<int, int>;
    GridUnionFind(int H_, int W_) : H(H_), W(W_), par(H * W), cou(H * W, 1) { std::iota(par.begin(), par.end(), 0); }
    inline int id_(int h, int w) { return h * W + w; }
    inline bool coordinate_valid(int h, int w) { return h >= 0 and h < H and w >= 0 and w < W; }
    int _find(int x) { return (par[x] == x) ? x : (par[x] = _find(par[x])); }
    bool _unite(int x, int y) {
        x = _find(x), y = _find(y); if (x == y) return false;
        if (cou[x] < cou[y]) std::swap(x, y); 
        par[y] = x, cou[x] += cou[y];
        return true;
    }
    int find(int h, int w) {
        assert(coordinate_valid(h, w));
        return _find(id_(h, w));
    }
    bool unite(int h, int w, int h2, int w2) {
        assert(coordinate_valid(h, w) and coordinate_valid(h2, w2));
        return _unite(id_(h, w), id_(h2, w2));
    }
    int count(int h, int w) { return cou[find(h, w)]; }
    bool same(int h, int w, int h2, int w2) { return find(h, w) == find(h2, w2); }

    int find(P p) { return find(p.first, p.second); }
    bool unite(P p, P p2) { return unite(p.first, p.second, p2.first, p2.second);  }
    int count(P p) { return count(p.first, p.second); }
    bool same(P p, P p2) { return same(p.first, p.second, p2.first, p2.second); }

    void merge_outer() {
        for (int h = 0; h < H - 1; h++) unite(h, 0, h + 1, 0), unite(h, W - 1, h + 1, W - 1);
        for (int w = 0; w < W - 1; w++) unite(0, w, 0, w + 1), unite(H - 1, w, H - 1, w + 1);
    }
    friend std::ostream &operator<<(std::ostream &os, GridUnionFind &g)
    {
        constexpr int WW = 3;
        os << "[(" << g.H << " * " << g.W << " grid)\n";
        for (int i = 0; i < g.H; i++) {
            for (int j = 0; j < g.W - 1; j++) {
                os << std::setw(WW) << g.find(i, j) << (g.same(i, j, i, j + 1) ? '-' : ' ');
            }
            os << std::setw(WW) << g.find(i, g.H - 1) << '\n';
            if (i < g.H - 1) {
                for (int j = 0; j < g.W; j++) os << std::setw(WW + 1) << (g.same(i, j, i + 1, j) ? "| " : "  ");
                os << "\n";
            }
        }
        os << "]\n";
        return os;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "unionfind/grid_unionfind.hpp"
#include <cassert>
#include <numeric>
#include <utility>
#include <vector>
#include <iomanip>
#include <iostream>

// CUT begin
struct GridUnionFind
{
    int H, W;
    std::vector<int> par, cou;
    using P = std::pair<int, int>;
    GridUnionFind(int H_, int W_) : H(H_), W(W_), par(H * W), cou(H * W, 1) { std::iota(par.begin(), par.end(), 0); }
    inline int id_(int h, int w) { return h * W + w; }
    inline bool coordinate_valid(int h, int w) { return h >= 0 and h < H and w >= 0 and w < W; }
    int _find(int x) { return (par[x] == x) ? x : (par[x] = _find(par[x])); }
    bool _unite(int x, int y) {
        x = _find(x), y = _find(y); if (x == y) return false;
        if (cou[x] < cou[y]) std::swap(x, y); 
        par[y] = x, cou[x] += cou[y];
        return true;
    }
    int find(int h, int w) {
        assert(coordinate_valid(h, w));
        return _find(id_(h, w));
    }
    bool unite(int h, int w, int h2, int w2) {
        assert(coordinate_valid(h, w) and coordinate_valid(h2, w2));
        return _unite(id_(h, w), id_(h2, w2));
    }
    int count(int h, int w) { return cou[find(h, w)]; }
    bool same(int h, int w, int h2, int w2) { return find(h, w) == find(h2, w2); }

    int find(P p) { return find(p.first, p.second); }
    bool unite(P p, P p2) { return unite(p.first, p.second, p2.first, p2.second);  }
    int count(P p) { return count(p.first, p.second); }
    bool same(P p, P p2) { return same(p.first, p.second, p2.first, p2.second); }

    void merge_outer() {
        for (int h = 0; h < H - 1; h++) unite(h, 0, h + 1, 0), unite(h, W - 1, h + 1, W - 1);
        for (int w = 0; w < W - 1; w++) unite(0, w, 0, w + 1), unite(H - 1, w, H - 1, w + 1);
    }
    friend std::ostream &operator<<(std::ostream &os, GridUnionFind &g)
    {
        constexpr int WW = 3;
        os << "[(" << g.H << " * " << g.W << " grid)\n";
        for (int i = 0; i < g.H; i++) {
            for (int j = 0; j < g.W - 1; j++) {
                os << std::setw(WW) << g.find(i, j) << (g.same(i, j, i, j + 1) ? '-' : ' ');
            }
            os << std::setw(WW) << g.find(i, g.H - 1) << '\n';
            if (i < g.H - 1) {
                for (int j = 0; j < g.W; j++) os << std::setw(WW + 1) << (g.same(i, j, i + 1, j) ? "| " : "  ");
                os << "\n";
            }
        }
        os << "]\n";
        return os;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

