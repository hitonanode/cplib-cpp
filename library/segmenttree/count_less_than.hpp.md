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


# :warning: segmenttree/count_less_than.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4d78bd1b354012e24586b247dc164462">segmenttree</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/count_less_than.hpp">View this file on GitHub</a>
    - Last commit date: 2020-01-15 22:53:10+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Count elements in [A_begin, ..., A_{end-1}] which satisfy A_i < query
// Complexity: O(N log^2 N) for initialization, O(log^2 N) for each query
// Verified: cntLess <https://codeforces.com/contest/1288/submission/68865506>
struct CountLessThan
{
    using T = int;
    int N;
    int head;
    vector<vector<T>> x;
    inline void merge(int pos) {
        x[pos] = x[pos * 2 + 1];
        x[pos].insert(x[pos].end(), x[pos * 2 + 2].begin(), x[pos * 2 + 2].end());
        sort(x[pos].begin(), x[pos].end());
    }
    int _getless(int begin, int end, int pos, int l, int r, T query) const {
        if (r <= begin or l >= end) return 0;
        if (l >= begin and r <= end) return lower_bound(x[pos].begin(), x[pos].end(), query) - x[pos].begin();
        return _getless(begin, end, 2 * pos + 1, l, (l + r) / 2, query) + _getless(begin, end, 2 * pos + 2, (l + r) / 2, r, query);
    }
    int _getlesseq(int begin, int end, int pos, int l, int r, T query) const {
        if (r <= begin or l >= end) return 0;
        if (l >= begin and r <= end) return upper_bound(x[pos].begin(), x[pos].end(), query) - x[pos].begin();
        return _getlesseq(begin, end, 2 * pos + 1, l, (l + r) / 2, query) + _getlesseq(begin, end, 2 * pos + 2, (l + r) / 2, r, query);
    }
    CountLessThan() = default;
    CountLessThan(const vector<T> &vec) : N(vec.size()) {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.resize(N_tmp*2), head = N_tmp - 1;
        for (int i = 0; i < N; i++) x[head + i] = {vec[i]};
        for (int i = head - 1; i >= 0; i--) merge(i);
    }
    int cntLess(int begin, int end, T query) const { return _getless(begin, end, 0, 0, (int)x.size() / 2, query); }
    int cntLesseq(int begin, int end, T query) const { return _getlesseq(begin, end, 0, 0, (int)x.size() / 2, query); }
    int cntMore(int begin, int end, T query) const {
        int tot = max(0, min(end, N) - max(begin, 0));
        return tot - cntLesseq(begin, end, query);
    }
    int cntMoreeq(int begin, int end, T query) const {
        int tot = max(0, min(end, N) - max(begin, 0));
        return tot - cntLess(begin, end, query);
    }

    friend ostream &operator<<(ostream &os, const CountLessThan &clt) {
        os << '[';
        for (int i = 0; i < clt.N; i++) os << clt.x[clt.head + i][0] << ',';
        os << ']';
        return os;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/count_less_than.hpp"
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Count elements in [A_begin, ..., A_{end-1}] which satisfy A_i < query
// Complexity: O(N log^2 N) for initialization, O(log^2 N) for each query
// Verified: cntLess <https://codeforces.com/contest/1288/submission/68865506>
struct CountLessThan
{
    using T = int;
    int N;
    int head;
    vector<vector<T>> x;
    inline void merge(int pos) {
        x[pos] = x[pos * 2 + 1];
        x[pos].insert(x[pos].end(), x[pos * 2 + 2].begin(), x[pos * 2 + 2].end());
        sort(x[pos].begin(), x[pos].end());
    }
    int _getless(int begin, int end, int pos, int l, int r, T query) const {
        if (r <= begin or l >= end) return 0;
        if (l >= begin and r <= end) return lower_bound(x[pos].begin(), x[pos].end(), query) - x[pos].begin();
        return _getless(begin, end, 2 * pos + 1, l, (l + r) / 2, query) + _getless(begin, end, 2 * pos + 2, (l + r) / 2, r, query);
    }
    int _getlesseq(int begin, int end, int pos, int l, int r, T query) const {
        if (r <= begin or l >= end) return 0;
        if (l >= begin and r <= end) return upper_bound(x[pos].begin(), x[pos].end(), query) - x[pos].begin();
        return _getlesseq(begin, end, 2 * pos + 1, l, (l + r) / 2, query) + _getlesseq(begin, end, 2 * pos + 2, (l + r) / 2, r, query);
    }
    CountLessThan() = default;
    CountLessThan(const vector<T> &vec) : N(vec.size()) {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.resize(N_tmp*2), head = N_tmp - 1;
        for (int i = 0; i < N; i++) x[head + i] = {vec[i]};
        for (int i = head - 1; i >= 0; i--) merge(i);
    }
    int cntLess(int begin, int end, T query) const { return _getless(begin, end, 0, 0, (int)x.size() / 2, query); }
    int cntLesseq(int begin, int end, T query) const { return _getlesseq(begin, end, 0, 0, (int)x.size() / 2, query); }
    int cntMore(int begin, int end, T query) const {
        int tot = max(0, min(end, N) - max(begin, 0));
        return tot - cntLesseq(begin, end, query);
    }
    int cntMoreeq(int begin, int end, T query) const {
        int tot = max(0, min(end, N) - max(begin, 0));
        return tot - cntLess(begin, end, query);
    }

    friend ostream &operator<<(ostream &os, const CountLessThan &clt) {
        os << '[';
        for (int i = 0; i < clt.N; i++) os << clt.x[clt.head + i][0] << ',';
        os << ']';
        return os;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

