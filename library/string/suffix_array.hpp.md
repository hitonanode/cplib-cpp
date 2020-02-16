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


# :heavy_check_mark: string/suffix_array.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/suffix_array.hpp">View this file on GitHub</a>
    - Last commit date: 2020-02-02 21:57:08+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/string/test/lcp.test.cpp.html">string/test/lcp.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/string/test/suffix_array.test.cpp.html">string/test/suffix_array.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <numeric>
#include <vector>

// Suffix Array / Longest Common Prefix Array Construction
// Comlexity: O(N(log N)^2)
template<typename T>
struct SuffixArray
{
    T S;                    // size: N
    std::vector<int> SA;    // Suffix Array (size: N + 1, SA[0] == N) SA[i] means S[SA[i]:]
    std::vector<int> rank;  // Rank (inverse of SA) (size: N + 1, rank[N] == 0)
    std::vector<int> lcp;   // Longest Common Prefix Array (size: N) betw. S[SA[i]:] & S[SA[i + 1]:]

    SuffixArray(const T &str, bool gen_lcp = true) : S(str) {
        int N = S.size();
        SA.resize(N + 1);
        std::iota(SA.begin(), SA.end(), 0);
        rank.assign(N + 1, -1);
        for (int i = 0; i < N; i++) rank[i] = S[i];
        int _ord_mm = 1;

        auto _comp_suffarr = [&](int i, int j) {
            if (rank[i] != rank[j])
                return rank[i] < rank[j];
            int ri = i + _ord_mm < (int)rank.size() ? rank[i + _ord_mm] : -1;
            int rj = j + _ord_mm < (int)rank.size() ? rank[j + _ord_mm] : -1;
            return ri < rj;
        };
        std::vector<int> tmp(N + 1);
        for (_ord_mm = 1; _ord_mm <= N; _ord_mm *= 2) {
            std::sort(SA.begin(), SA.end(), _comp_suffarr);
            tmp[SA[0]] = 0;
            for (int i = 1; i <= N; i++) {
                tmp[SA[i]] = tmp[SA[i - 1]] + _comp_suffarr(SA[i - 1], SA[i]);
            }
            rank = tmp;
        }
        if (!gen_lcp) return;

        lcp.assign(N, 0);
        int h = 0;
        for (int i = 0; i < N; i++) {
            int j = SA[rank[i] - 1];
            if (h) h--;
            for (; j + h < N and i + h < N; h++) if (S[j + h] != S[i + h]) break;
            lcp[rank[i] - 1] = h;
        }
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/suffix_array.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

// Suffix Array / Longest Common Prefix Array Construction
// Comlexity: O(N(log N)^2)
template<typename T>
struct SuffixArray
{
    T S;                    // size: N
    std::vector<int> SA;    // Suffix Array (size: N + 1, SA[0] == N) SA[i] means S[SA[i]:]
    std::vector<int> rank;  // Rank (inverse of SA) (size: N + 1, rank[N] == 0)
    std::vector<int> lcp;   // Longest Common Prefix Array (size: N) betw. S[SA[i]:] & S[SA[i + 1]:]

    SuffixArray(const T &str, bool gen_lcp = true) : S(str) {
        int N = S.size();
        SA.resize(N + 1);
        std::iota(SA.begin(), SA.end(), 0);
        rank.assign(N + 1, -1);
        for (int i = 0; i < N; i++) rank[i] = S[i];
        int _ord_mm = 1;

        auto _comp_suffarr = [&](int i, int j) {
            if (rank[i] != rank[j])
                return rank[i] < rank[j];
            int ri = i + _ord_mm < (int)rank.size() ? rank[i + _ord_mm] : -1;
            int rj = j + _ord_mm < (int)rank.size() ? rank[j + _ord_mm] : -1;
            return ri < rj;
        };
        std::vector<int> tmp(N + 1);
        for (_ord_mm = 1; _ord_mm <= N; _ord_mm *= 2) {
            std::sort(SA.begin(), SA.end(), _comp_suffarr);
            tmp[SA[0]] = 0;
            for (int i = 1; i <= N; i++) {
                tmp[SA[i]] = tmp[SA[i - 1]] + _comp_suffarr(SA[i - 1], SA[i]);
            }
            rank = tmp;
        }
        if (!gen_lcp) return;

        lcp.assign(N, 0);
        int h = 0;
        for (int i = 0; i < N; i++) {
            int j = SA[rank[i] - 1];
            if (h) h--;
            for (; j + h < N and i + h < N; h++) if (S[j + h] != S[i + h]) break;
            lcp[rank[i] - 1] = h;
        }
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

