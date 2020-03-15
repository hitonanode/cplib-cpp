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


# :heavy_check_mark: string/test/suffix_array.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a7427d145086499c399a0f95224a581">string/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/test/suffix_array.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="https://judge.yosupo.jp/problem/suffixarray">https://judge.yosupo.jp/problem/suffixarray</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/suffix_array.hpp.html">string/suffix_array.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "string/suffix_array.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    SuffixArray<decltype(S)> sa(S, false);

    for (size_t i = 1; i <= S.length(); i++) std::cout << sa.SA[i] << ' ';
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/suffix_array.hpp"
#include <algorithm>
#include <numeric>
#include <vector>

// CUT begin
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
#line 2 "string/test/suffix_array.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/suffixarray"
#include <iostream>
#include <string>

int main()
{
    std::string S;
    std::cin >> S;
    SuffixArray<decltype(S)> sa(S, false);

    for (size_t i = 1; i <= S.length(); i++) std::cout << sa.SA[i] << ' ';
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

