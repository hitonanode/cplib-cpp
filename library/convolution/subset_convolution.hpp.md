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


# :heavy_check_mark: convolution/subset_convolution.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a9595c1c24c33b16056d2ad07e71682d">convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/convolution/subset_convolution.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 21:06:32+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/convolution/test/subset_convolution.test.cpp.html">convolution/test/subset_convolution.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <vector>

// CUT begin
// Subset sum (fast zeta transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void subset_sum(std::vector<T> &f)
{
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (S & (1 << d)) f[S] += f[S ^ (1 << d)];
    }
}
// Inverse of subset sum (fast moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void subset_sum_inv(std::vector<T> &g)
{
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];
    }
}

// Superset sum / its inverse (fast zeta/moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void superset_sum(std::vector<T> &f)
{
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (!(S & (1 << d))) f[S] += f[S | (1 << d)];
    }
}
template <typename T>
void superset_sum_inv(std::vector<T> &g)
{
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (!(S & (1 << d))) g[S] -= g[S | (1 << d)];
    }
}


// Subset convolution
// h[S] = \sum_T f[T] * g[S - T]
// Complexity: O(N^2 2^N) for arrays of size 2^N
template <typename T>
std::vector<T> subset_convolution(std::vector<T> f, std::vector<T> g)
{
    const int sz = f.size(), m = __builtin_ctz(sz) + 1;
    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());

    std::vector<std::vector<T>> ff(m, std::vector<T>(sz)), fg(m, std::vector<T>(sz));
    for (int i = 0; i < sz; i++) {
        int pc = __builtin_popcount(i);
        ff[pc][i] += f[i], fg[pc][i] += g[i];
    }
    for (auto &vec : ff) subset_sum(vec);
    for (auto &vec : fg) subset_sum(vec);

    std::vector<std::vector<T>> fh(m, std::vector<T>(sz));
    for (int d = 0; d < m; d++) {
        for (int e = 0; d + e < m; e++) {
            for (int i = 0; i < sz; i++) fh[d + e][i] += ff[d][i] * fg[e][i];
        }
    }
    for (auto &vec : fh) subset_sum_inv(vec);
    std::vector<T> ret(sz);
    for (int i = 0; i < sz; i++) ret[i] = fh[__builtin_popcount(i)][i];
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "convolution/subset_convolution.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Subset sum (fast zeta transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void subset_sum(std::vector<T> &f)
{
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (S & (1 << d)) f[S] += f[S ^ (1 << d)];
    }
}
// Inverse of subset sum (fast moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void subset_sum_inv(std::vector<T> &g)
{
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (S & (1 << d)) g[S] -= g[S ^ (1 << d)];
    }
}

// Superset sum / its inverse (fast zeta/moebius transform)
// Complexity: O(N 2^N) for array of size 2^N
template <typename T>
void superset_sum(std::vector<T> &f)
{
    const int sz = f.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (!(S & (1 << d))) f[S] += f[S | (1 << d)];
    }
}
template <typename T>
void superset_sum_inv(std::vector<T> &g)
{
    const int sz = g.size(), n = __builtin_ctz(sz);
    assert(__builtin_popcount(sz) == 1);
    for (int d = 0; d < n; d++) {
        for (int S = 0; S < 1 << n; S++) if (!(S & (1 << d))) g[S] -= g[S | (1 << d)];
    }
}


// Subset convolution
// h[S] = \sum_T f[T] * g[S - T]
// Complexity: O(N^2 2^N) for arrays of size 2^N
template <typename T>
std::vector<T> subset_convolution(std::vector<T> f, std::vector<T> g)
{
    const int sz = f.size(), m = __builtin_ctz(sz) + 1;
    assert(__builtin_popcount(sz) == 1 and f.size() == g.size());

    std::vector<std::vector<T>> ff(m, std::vector<T>(sz)), fg(m, std::vector<T>(sz));
    for (int i = 0; i < sz; i++) {
        int pc = __builtin_popcount(i);
        ff[pc][i] += f[i], fg[pc][i] += g[i];
    }
    for (auto &vec : ff) subset_sum(vec);
    for (auto &vec : fg) subset_sum(vec);

    std::vector<std::vector<T>> fh(m, std::vector<T>(sz));
    for (int d = 0; d < m; d++) {
        for (int e = 0; d + e < m; e++) {
            for (int i = 0; i < sz; i++) fh[d + e][i] += ff[d][i] * fg[e][i];
        }
    }
    for (auto &vec : fh) subset_sum_inv(vec);
    std::vector<T> ret(sz);
    for (int i = 0; i < sz; i++) ret[i] = fh[__builtin_popcount(i)][i];
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

