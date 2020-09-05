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


# :heavy_check_mark: sparse_table/test/disjoint_sparse_table_rmq.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#a966236a3b794cca2d3eef6875f0f6b3">sparse_table/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/sparse_table/test/disjoint_sparse_table_rmq.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-09-05 12:07:40+09:00


* see: <a href="https://judge.yosupo.jp/problem/staticrmq">https://judge.yosupo.jp/problem/staticrmq</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/sparse_table/disjoint_sparse_table.hpp.html">sparse_table/disjoint_sparse_table.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "sparse_table/disjoint_sparse_table.hpp"
#include <cassert>
#include <cstdio>
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    std::vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
    auto f = [](int l, int r) { return std::min(l, r); };
    DisjointSparseTable<int, decltype(f)> rmq(A, f);
    while (Q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        int a = rmq.get(l, r);
        printf("%d\n", a);
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "sparse_table/disjoint_sparse_table.hpp"
#include <cassert>
#include <algorithm>
#include <vector>

// CUT begin
// Disjoint sparse table
// <https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404>
// <https://drken1215.hatenablog.com/entry/2018/09/08/162600>
// Complexity: O(NlogN) for precalculation, O(1) per query
// - get(l, r): return op(x_l, ..., x_{r - 1})
template <typename T, typename F>
struct DisjointSparseTable
{
    int N, sz;
    F f;
    std::vector<std::vector<T>> data;
    static int _msb(int x) noexcept
    {
        return x == 0 ? 0 : (__builtin_clz(x) ^ 31);
    }
    DisjointSparseTable() = default;
    DisjointSparseTable(const std::vector<T> &seq, F op) : N(seq.size()), f(op)
    {
        sz = 1 << (_msb(N - 1) + 1);
        data.assign(_msb(sz) + 1, std::vector<T>(sz));
        std::copy(seq.begin(), seq.end(), data[0].begin());

        for (int h = 1, half = 2; half < N; h++, half <<= 1)
        {
            for (int i = half; i < sz; i += half * 2)
            {
                data[h][i - 1] = data[0][i - 1];
                for (int j = i - 2; j >= i - half; j--)
                {
                    data[h][j] = f(data[0][j], data[h][j + 1]);
                }
                data[h][i] = data[0][i];
                for (int j = i + 1; j < i + half; j++)
                {
                    data[h][j] = f(data[h][j - 1], data[0][j]);
                }
            }
        }
    }
    // [l, r), 0-indexed
    T get(int l, int r)
    {
        assert(l >= 0 and r <= N and l < r);
        if (l + 1 == r) return data[0][l];
        int h = _msb(l ^ (r - 1));
        return f(data[h][l], data[h][r - 1]);
    }
};
#line 3 "sparse_table/test/disjoint_sparse_table_rmq.test.cpp"
#include <cstdio>
#define PROBLEM "https://judge.yosupo.jp/problem/staticrmq"

int main()
{
    int N, Q;
    scanf("%d %d", &N, &Q);
    std::vector<int> A(N);
    for (int i = 0; i < N; i++)
    {
        scanf("%d", &A[i]);
    }
    auto f = [](int l, int r) { return std::min(l, r); };
    DisjointSparseTable<int, decltype(f)> rmq(A, f);
    while (Q--)
    {
        int l, r;
        scanf("%d %d", &l, &r);
        int a = rmq.get(l, r);
        printf("%d\n", a);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

