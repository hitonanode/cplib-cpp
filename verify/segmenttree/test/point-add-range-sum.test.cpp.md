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


# :heavy_check_mark: segmenttree/test/point-add-range-sum.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5fd93d3fa59267c091e036914d93749e">segmenttree/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/point-add-range-sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 16:23:43+09:00


* see: <a href="https://judge.yosupo.jp/problem/point_add_range_sum">https://judge.yosupo.jp/problem/point_add_range_sum</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/segmenttree/binary_indexed_tree.hpp.html">segmenttree/binary_indexed_tree.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "segmenttree/binary_indexed_tree.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

// PointAddRangeSum (BIT based) 0-indexed
// Complexity: O(lg N) for each query
template <typename T>
struct PointAddRangeSum
{
    BIT<T> bit;
    PointAddRangeSum(const std::vector<T> &A) : bit(A.size())
    {
        for (unsigned i = 0; i < A.size(); i++) bit.add(i + 1, A[i]);
    }
    void add(int i, T val)
    {
        bit.add(i + 1, val);
    }
    // sum [l, r)
    T get(int l, int r) const
    {
        return bit.sum(r) - bit.sum(l);
    }
};

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<long long> A(N);
    for (auto &a : A)
    {
        std::cin >> a;
    }
    PointAddRangeSum<long long> s(A);
    while (Q--)
    {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q)
        {
            std::cout << s.get(l, r) << '\n';
        }
        else
        {
            s.add(l, r);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/binary_indexed_tree.hpp"
#include <iostream>
#include <vector>

// CUT begin
// 1-indexed BIT (i : [1, len])
template <typename T>
struct BIT : std::vector<T>
{
    BIT(int len = 0) : std::vector<T>(len + 1) {}
    void reset() { fill(this->begin(), this->end(), 0); }
    void add(int pos, T v) {
        while (pos > 0 and pos < (int)this->size()) (*this)[pos] += v, pos += pos & -pos;
    }
    T sum(int pos) const { // (0, pos]
        T res = 0;
        while (pos > 0) res += (*this)[pos], pos -= pos & -pos;
        return res;
    }
    friend std::ostream &operator<<(std::ostream &os, const BIT &bit) {
        T prv = 0;
        os << '[';
        for (int i = 1; i < (int)bit.size(); i++) {
            T now = bit.sum(i);
            os << now - prv << ",";
            prv = now;
        }
        os << ']';
        return os;
    }
};
#line 3 "segmenttree/test/point-add-range-sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/point_add_range_sum"

// PointAddRangeSum (BIT based) 0-indexed
// Complexity: O(lg N) for each query
template <typename T>
struct PointAddRangeSum
{
    BIT<T> bit;
    PointAddRangeSum(const std::vector<T> &A) : bit(A.size())
    {
        for (unsigned i = 0; i < A.size(); i++) bit.add(i + 1, A[i]);
    }
    void add(int i, T val)
    {
        bit.add(i + 1, val);
    }
    // sum [l, r)
    T get(int l, int r) const
    {
        return bit.sum(r) - bit.sum(l);
    }
};

int main()
{
    std::cin.tie(NULL);
    std::ios::sync_with_stdio(false);

    int N, Q;
    std::cin >> N >> Q;
    std::vector<long long> A(N);
    for (auto &a : A)
    {
        std::cin >> a;
    }
    PointAddRangeSum<long long> s(A);
    while (Q--)
    {
        int q, l, r;
        std::cin >> q >> l >> r;
        if (q)
        {
            std::cout << s.get(l, r) << '\n';
        }
        else
        {
            s.add(l, r);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

