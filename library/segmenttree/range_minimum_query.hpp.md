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


# :x: segmenttree/range_minimum_query.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#4d78bd1b354012e24586b247dc164462">segmenttree</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/range_minimum_query.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Verified with

* :x: <a href="../../verify/segmenttree/test/range_minimum_query.test.cpp.html">segmenttree/test/range_minimum_query.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <iostream>
#include <vector>
using namespace std;

// CUT begin
using T = int;
struct RangeMinimumQuery
{
    int N;
    T defaultT = 1e9;
    int head;
    vector<T> x;
    T _get(int begin, int end, int pos, int l, int r) const
    {
        if (r <= begin or l >= end) return defaultT;
        if (l >= begin and r <= end) return x[pos];
        return min(_get(begin, end, 2 * pos + 1, l, (l + r) / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2, r));
    }
    RangeMinimumQuery(int N, T defaultT) : N(N), defaultT(defaultT)
    {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp*2, defaultT), head = N_tmp - 1;
    }
    void build(const vector<T> &vals)
    {
        copy(vals.begin(), vals.end(), x.begin() + head);
        for (int i = head - 1; i >= 0; i--)
        {
            x[i] = min(x[i * 2 + 1], x[i * 2 + 2]);
        }
    }
    RangeMinimumQuery(const vector<T> &vals, T defaultT) : N(vals.size()), defaultT(defaultT)
    {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp*2, defaultT), head = N_tmp - 1;
        build(vals);
    }
    RangeMinimumQuery() : RangeMinimumQuery(0, T()) {}
    void update(int pos, T val)
    {
        pos += head, x[pos] = val;
        while (pos) pos = (pos - 1) / 2, x[pos] = min(x[pos * 2 + 1], x[pos * 2 + 2]);
    }
    T get(int begin, int end) const { return _get(begin, end, 0, 0, (int)x.size() / 2); }
    friend ostream &operator<<(ostream &os, const RangeMinimumQuery &s)
    {
        os << "[";
        for (int i = 0; i < s.N; i++) os << s.get(i, i + 1) << ",";
        os << "]";
        return os;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/range_minimum_query.hpp"
#include <iostream>
#include <vector>
using namespace std;

// CUT begin
using T = int;
struct RangeMinimumQuery
{
    int N;
    T defaultT = 1e9;
    int head;
    vector<T> x;
    T _get(int begin, int end, int pos, int l, int r) const
    {
        if (r <= begin or l >= end) return defaultT;
        if (l >= begin and r <= end) return x[pos];
        return min(_get(begin, end, 2 * pos + 1, l, (l + r) / 2), _get(begin, end, 2 * pos + 2, (l + r) / 2, r));
    }
    RangeMinimumQuery(int N, T defaultT) : N(N), defaultT(defaultT)
    {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp*2, defaultT), head = N_tmp - 1;
    }
    void build(const vector<T> &vals)
    {
        copy(vals.begin(), vals.end(), x.begin() + head);
        for (int i = head - 1; i >= 0; i--)
        {
            x[i] = min(x[i * 2 + 1], x[i * 2 + 2]);
        }
    }
    RangeMinimumQuery(const vector<T> &vals, T defaultT) : N(vals.size()), defaultT(defaultT)
    {
        int N_tmp = 1; while (N_tmp < N) N_tmp <<= 1;
        x.assign(N_tmp*2, defaultT), head = N_tmp - 1;
        build(vals);
    }
    RangeMinimumQuery() : RangeMinimumQuery(0, T()) {}
    void update(int pos, T val)
    {
        pos += head, x[pos] = val;
        while (pos) pos = (pos - 1) / 2, x[pos] = min(x[pos * 2 + 1], x[pos * 2 + 2]);
    }
    T get(int begin, int end) const { return _get(begin, end, 0, 0, (int)x.size() / 2); }
    friend ostream &operator<<(ostream &os, const RangeMinimumQuery &s)
    {
        os << "[";
        for (int i = 0; i < s.N; i++) os << s.get(i, i + 1) << ",";
        os << "]";
        return os;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

