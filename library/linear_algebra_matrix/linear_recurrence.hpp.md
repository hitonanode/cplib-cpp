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


# :heavy_check_mark: linear_algebra_matrix/linear_recurrence.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#20f2c5d841ec31673050aaedd8b17f50">linear_algebra_matrix</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/linear_recurrence.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 19:51:42+09:00




## Required by

* :heavy_check_mark: <a href="det_of_sparse_matrix.hpp.html">linear_algebra_matrix/det_of_sparse_matrix.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp.html">linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/linear_recurrence.test.cpp.html">linear_algebra_matrix/test/linear_recurrence.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: (L=degree of minimal polynomial, C=min. poly.(size = L + 1, C[0] = 1))
// Formula: convolve(S, C)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename K>
std::pair<int, std::vector<K>> linear_recurrence(const std::vector<K> &S)
{
    int N = S.size();
    using poly = std::vector<K>;
    poly C{1}, B{1};
    int L = 0, m = 1;
    K b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, K d, K b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        K a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        K d = S[n];
        for (int i = 1; i <= L; i++) d += C[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C;
            C = adjust(C, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C = adjust(C, B, d, b, m++);
    }
    return std::make_pair(L, C);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "linear_algebra_matrix/linear_recurrence.hpp"
#include <algorithm>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: (L=degree of minimal polynomial, C=min. poly.(size = L + 1, C[0] = 1))
// Formula: convolve(S, C)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename K>
std::pair<int, std::vector<K>> linear_recurrence(const std::vector<K> &S)
{
    int N = S.size();
    using poly = std::vector<K>;
    poly C{1}, B{1};
    int L = 0, m = 1;
    K b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, K d, K b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        K a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        K d = S[n];
        for (int i = 1; i <= L; i++) d += C[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C;
            C = adjust(C, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C = adjust(C, B, d, b, m++);
    }
    return std::make_pair(L, C);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

