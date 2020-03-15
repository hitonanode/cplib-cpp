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


# :heavy_check_mark: sparse_table/test/sparse_table_aoj.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#a966236a3b794cca2d3eef6875f0f6b3">sparse_table/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/sparse_table/test/sparse_table_aoj.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/sparse_table/rmq_sparse_table.hpp.html">sparse_table/rmq_sparse_table.hpp</a>
* :heavy_check_mark: <a href="../../../library/sparse_table/sparse_table.hpp.html">sparse_table/sparse_table.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "sparse_table/sparse_table.hpp"
#include "sparse_table/rmq_sparse_table.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <cstdio>
int main()
{
    int N, L;
    scanf("%d %d", &N, &L);
    std::vector<int> A(N);
    for (auto &a : A) scanf("%d", &a);
    auto f = [](int l, int r) { return std::min(l, r); };
    SparseTable<int, decltype(f)> sp1(A, 1e9, f);
    StaticRMQ<int> sp2(A, 1e9);
    for (int l = 0; l + L <= N; l++) {
        int a = sp1.get(l, l + L);
        int b = sp2.get(l, l + L);
        assert(a == b);
        printf("%d ", a);
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "sparse_table/sparse_table.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Static sequence sparse table
// Complexity: O(NlogN) for precalculation, O(1) per query
template<typename T, typename F>
struct SparseTable {
    int N, lgN;
    T defaultT;
    F func;
    std::vector<std::vector<T>> data;
    std::vector<int> lgx_table;
    SparseTable(F func) : func(func) {}
    SparseTable(const std::vector<T> &sequence, T defaultT, F func) : N(sequence.size()), defaultT(defaultT), func(func)
    {
        lgx_table.resize(N + 1);
        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgN = lgx_table[N] + 1;
        data.assign(lgN, std::vector<T>(N, defaultT));
        data[0] = sequence;
        for (int d = 1; d < lgN; d++) {
            for (int i = 0; i + (1 << d) <= N; i++) {
                data[d][i] = func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);
            }
        }
    }
    T get(int l, int r) { // [l, r), 0-indexed
        assert(l >= 0 and r <= N);
        if (l >= r) return defaultT;
        int d = lgx_table[r - l];
        return func(data[d][l], data[d][r - (1 << d)]);
    }
};
#line 2 "sparse_table/rmq_sparse_table.hpp"
#include <algorithm>
#line 5 "sparse_table/rmq_sparse_table.hpp"

// CUT begin
// Range Minimum Query for static sequence by sparse table
// Complexity: O(NlogN) for precalculation, O(1) per query
template<typename T>
struct StaticRMQ {
    inline T func(const T &l, const T &r) {
        return std::min<T>(l, r);
    }
    int N, lgN;
    T defaultT;
    std::vector<std::vector<T>> data;
    std::vector<int> lgx_table;
    StaticRMQ(const std::vector<T> &sequence, T defaultT) : N(sequence.size()), defaultT(defaultT)
    {
        lgx_table.resize(N + 1);
        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgN = lgx_table[N] + 1;
        data.assign(lgN, std::vector<T>(N, defaultT));
        data[0] = sequence;
        for (int d = 1; d < lgN; d++) {
            for (int i = 0; i + (1 << d) <= N; i++) {
                data[d][i] = func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);
            }
        }
    }
    T get(int l, int r) { // [l, r), 0-indexed
        assert(l >= 0 and r <= N);
        if (l >= r) return defaultT;
        int d = lgx_table[r - l];
        return func(data[d][l], data[d][r - (1 << d)]);
    }
};
#line 3 "sparse_table/test/sparse_table_aoj.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D"

#include <cstdio>
int main()
{
    int N, L;
    scanf("%d %d", &N, &L);
    std::vector<int> A(N);
    for (auto &a : A) scanf("%d", &a);
    auto f = [](int l, int r) { return std::min(l, r); };
    SparseTable<int, decltype(f)> sp1(A, 1e9, f);
    StaticRMQ<int> sp2(A, 1e9);
    for (int l = 0; l + L <= N; l++) {
        int a = sp1.get(l, l + L);
        int b = sp2.get(l, l + L);
        assert(a == b);
        printf("%d ", a);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

