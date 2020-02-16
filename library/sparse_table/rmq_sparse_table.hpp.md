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


# :heavy_check_mark: sparse_table/rmq_sparse_table.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#cb323a14df0a258a78d4acbe3d02dfda">sparse_table</a>
* <a href="{{ site.github.repository_url }}/blob/master/sparse_table/rmq_sparse_table.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-15 16:40:57+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/sparse_table/test/sparse_table.test.cpp.html">sparse_table/test/sparse_table.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/sparse_table/test/sparse_table_aoj.test.cpp.html">sparse_table/test/sparse_table_aoj.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <cassert>
#include <vector>

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

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "sparse_table/rmq_sparse_table.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

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

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

