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
    - Last commit date: 2020-06-06 01:37:38+09:00




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
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: L          = degree of minimal polynomial,
//         C_reversed = monic min. polynomial (size = L + 1, reversed order, C_reversed[0] = 1))
// Formula: convolve(S, C_reversed)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename Tfield>
std::pair<int, std::vector<Tfield>> linear_recurrence(const std::vector<Tfield> &S)
{
    int N = S.size();
    using poly = std::vector<Tfield>;
    poly C_reversed{1}, B{1};
    int L = 0, m = 1;
    Tfield b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, Tfield d, Tfield b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        Tfield a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        Tfield d = S[n];
        for (int i = 1; i <= L; i++) d += C_reversed[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C_reversed;
            C_reversed = adjust(C_reversed, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C_reversed = adjust(C_reversed, B, d, b, m++);
    }
    return std::make_pair(L, C_reversed);
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "linear_algebra_matrix/linear_recurrence.hpp"
#include <algorithm>
#include <cassert>
#include <utility>
#include <vector>

// CUT begin
// Berlekamp–Massey algorithm
// <https://en.wikipedia.org/wiki/Berlekamp%E2%80%93Massey_algorithm>
// Complexity: O(N^2)
// input: S = sequence from field K
// return: L          = degree of minimal polynomial,
//         C_reversed = monic min. polynomial (size = L + 1, reversed order, C_reversed[0] = 1))
// Formula: convolve(S, C_reversed)[i] = 0 for i >= L
// Example:
// - [1, 2, 4, 8, 16]   -> (1, [1, -2])
// - [1, 1, 2, 3, 5, 8] -> (2, [1, -1, -1])
// - [0, 0, 0, 0, 1]    -> (5, [1, 0, 0, 0, 0, 998244352]) (mod 998244353)
// - []                 -> (0, [1])
// - [0, 0, 0]          -> (0, [1])
// - [-2]               -> (1, [1, 2])
template <typename Tfield>
std::pair<int, std::vector<Tfield>> linear_recurrence(const std::vector<Tfield> &S)
{
    int N = S.size();
    using poly = std::vector<Tfield>;
    poly C_reversed{1}, B{1};
    int L = 0, m = 1;
    Tfield b = 1;

    // adjust: C(x) <- C(x) - (d / b) x^m B(x)
    auto adjust = [](poly C, const poly &B, Tfield d, Tfield b, int m) -> poly {
        C.resize(std::max(C.size(), B.size() + m));
        Tfield a = d / b;
        for (unsigned i = 0; i < B.size(); i++) C[i + m] -= a * B[i];
        return C;
    };

    for (int n = 0; n < N; n++) {
        Tfield d = S[n];
        for (int i = 1; i <= L; i++) d += C_reversed[i] * S[n - i];

        if (d == 0) m++;
        else if (2 * L <= n) {
            poly T = C_reversed;
            C_reversed = adjust(C_reversed, B, d, b, m);
            L = n + 1 - L;
            B = T;
            b = d;
            m = 1;
        }
        else C_reversed = adjust(C_reversed, B, d, b, m++);
    }
    return std::make_pair(L, C_reversed);
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

