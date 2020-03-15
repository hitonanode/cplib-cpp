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


# :x: unionfind/test/weighted_unionfind.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#44cd2525982f578aae3dfa33b70b27d1">unionfind/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/unionfind/test/weighted_unionfind.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp</a>


## Depends on

* :x: <a href="../../../library/unionfind/weighted_unionfind.hpp.html">unionfind/weighted_unionfind.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include "unionfind/weighted_unionfind.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp"
using namespace std;

int main()
{
    int N, Q, x, y, z;
    cin >> N >> Q;
    WeightedUnionFind<int> uf(N);
    for (int i = 0; i < Q; i++)
    {
        int c;
        cin >> c;
        if (c)
        {
            cin >> x >> y;
            if (uf.same(x, y))
            {
                cout << uf.diff(x, y) << endl;
            }
            else
            {
                cout << "?" << endl;
            }
        }
        else
        {
            cin >> x >> y >> z;
            uf.unite(x, y, z);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "unionfind/test/weighted_unionfind.test.cpp"
#include <iostream>
#line 2 "unionfind/weighted_unionfind.hpp"
#include <numeric>
#include <utility>
#include <vector>

// CUT begin
// Weighted UnionFind
template<typename T>
struct WeightedUnionFind
{
    std::vector<int> par, sz;
    std::vector<T> pot;
    WeightedUnionFind(int N = 0) : par(N), sz(N, 1), pot(N) {
        std::iota(par.begin(), par.end(), 0);
    }
    int find(int x) {
        if (par[x] != x) {
            int r = find(par[x]);
            pot[x] = pot[x] + pot[par[x]], par[x] = r;
        }
        return par[x];
    }
    bool unite(int s, int t, T rel_diff) {
        // Relate s and t by t = s + rel_diff
        // Return false iff contradiction happens.
        rel_diff = rel_diff + weight(s) + (-weight(t));
        if ((s = find(s)) == (t = find(t))) return rel_diff == 0;
        if (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff; 
        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;
        return true;
    }
    T weight(int x) { find(x); return pot[x]; }
    T diff(int s, int t) { return weight(t) + (-weight(s)); }
    int count(int x) { return sz[find(x)]; }
    bool same(int s, int t) { return find(s) == find(t); }
};

// sample data structure T for WeightedUnionFind<T>
/*
struct Monoid {
    int data;
    Monoid() : data(0) {}
    Monoid(int d) : data(d) {}
    Monoid operator+(const Monoid &x) const { return Monoid(this->data + x.data); }
    Monoid operator-() const { return Monoid(-data); }
    bool operator==(const Monoid &x) const { return data == x.data; }
};
WeightedUnionFind<Monoid> wuf(10000);
*/
#line 3 "unionfind/test/weighted_unionfind.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp"
using namespace std;

int main()
{
    int N, Q, x, y, z;
    cin >> N >> Q;
    WeightedUnionFind<int> uf(N);
    for (int i = 0; i < Q; i++)
    {
        int c;
        cin >> c;
        if (c)
        {
            cin >> x >> y;
            if (uf.same(x, y))
            {
                cout << uf.diff(x, y) << endl;
            }
            else
            {
                cout << "?" << endl;
            }
        }
        else
        {
            cin >> x >> y >> z;
            uf.unite(x, y, z);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

