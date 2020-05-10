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


# :warning: binary_lifting(doubling)/doubling.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#fc840529f018acf34013c4bdd67ada43">binary_lifting(doubling)</a>
* <a href="{{ site.github.repository_url }}/blob/master/binary_lifting(doubling)/doubling.hpp">View this file on GitHub</a>
    - Last commit date: 2020-05-10 23:20:50+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cstdlib>
#include <vector>

// CUT begin
// Binary lifting / `Doubling`
// Complexity: O(NlogN) precalculation / O(logN) per query
// <https://atcoder.jp/contests/arc060/submissions/7039451>
struct BinaryLifting
{
    int N, INVALID, lgD;
    std::vector<std::vector<int>> mat;
    BinaryLifting() : N(0), lgD(0) {}
    BinaryLifting(const std::vector<int> &vec_nxt, int INVALID = -1, int lgd = 0) : N(vec_nxt.size()), INVALID(INVALID), lgD(lgd)
    {
        while ((1LL << lgD) < N) lgD++;
        mat.assign(lgD, std::vector<int>(N, INVALID));
        mat[0] = vec_nxt;
        for (int i = 0; i < N; i++) if (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;
        for (int d = 0; d < lgD - 1; d++) {
            for (int i = 0; i < N; i++) if (mat[d][i] != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];
        }
    }
    int kth_next(int now, long long k)
    {
        if (k >= (1LL << lgD)) exit(8);
        for (int d = 0; k and now != INVALID; d++, k >>= 1) if (k & 1) now = mat[d][now];
        return now;
    }

    // Distance from l to [r, \infty)
    // Requirement: mat[0][i] > i for all i (monotone increasing)
    int distance(int l, int r)
    {
        if (l >= r) return 0;
        int ret = 0;
        for (int d = lgD - 1; d >= 0; d--) {
            if (mat[d][l] < r and mat[d][l] != INVALID) ret += 1 << d, l = mat[d][l];
        }
        if (mat[0][l] == INVALID or mat[0][l] >= r) return ret + 1;
        else return -1; // Unable to reach
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "binary_lifting(doubling)/doubling.hpp"
#include <cstdlib>
#include <vector>

// CUT begin
// Binary lifting / `Doubling`
// Complexity: O(NlogN) precalculation / O(logN) per query
// <https://atcoder.jp/contests/arc060/submissions/7039451>
struct BinaryLifting
{
    int N, INVALID, lgD;
    std::vector<std::vector<int>> mat;
    BinaryLifting() : N(0), lgD(0) {}
    BinaryLifting(const std::vector<int> &vec_nxt, int INVALID = -1, int lgd = 0) : N(vec_nxt.size()), INVALID(INVALID), lgD(lgd)
    {
        while ((1LL << lgD) < N) lgD++;
        mat.assign(lgD, std::vector<int>(N, INVALID));
        mat[0] = vec_nxt;
        for (int i = 0; i < N; i++) if (mat[0][i] < 0 or mat[0][i] >= N) mat[0][i] = INVALID;
        for (int d = 0; d < lgD - 1; d++) {
            for (int i = 0; i < N; i++) if (mat[d][i] != INVALID) mat[d + 1][i] = mat[d][mat[d][i]];
        }
    }
    int kth_next(int now, long long k)
    {
        if (k >= (1LL << lgD)) exit(8);
        for (int d = 0; k and now != INVALID; d++, k >>= 1) if (k & 1) now = mat[d][now];
        return now;
    }

    // Distance from l to [r, \infty)
    // Requirement: mat[0][i] > i for all i (monotone increasing)
    int distance(int l, int r)
    {
        if (l >= r) return 0;
        int ret = 0;
        for (int d = lgD - 1; d >= 0; d--) {
            if (mat[d][l] < r and mat[d][l] != INVALID) ret += 1 << d, l = mat[d][l];
        }
        if (mat[0][l] == INVALID or mat[0][l] >= r) return ret + 1;
        else return -1; // Unable to reach
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

