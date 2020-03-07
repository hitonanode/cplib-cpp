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


# :x: sparse_table/test/sparse_table_2d.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/sparse_table/test/sparse_table_2d.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068</a>


## Depends on

* :x: <a href="../../../library/sparse_table/sparse_table.hpp.html">sparse_table/sparse_table.hpp</a>
* :x: <a href="../../../library/sparse_table/sparse_table_2d.hpp.html">sparse_table/sparse_table_2d.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "sparse_table/sparse_table_2d.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068"
// Very slow (worst case: 6sec, memory 3GB)

#include <iostream>
using namespace std;

int main()
{
    auto f = [](int l, int r) { return min(l, r); };
    while (true) {
        int H, W, Q;
        cin >> H >> W >> Q;
        if (!H) break;
        vector<vector<int>> mat(H, vector<int>(W));
        for (auto &vec : mat) for (auto &x : vec) cin >> x;
        SparseTable2D<int, decltype(f)> rmq(mat, (1LL << 31) - 1, f);
        while (Q--) {
            int xl, yl, xr, yr;
            cin >> xl >> yl >> xr >> yr;
            printf("%d\n", rmq.get(xl, xr + 1, yl, yr + 1));
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "sparse_table/sparse_table.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Static sequence sparse table
// Complexity: O(NlogN) for precalculation, O(1) per query
template<typename T, typename F>
struct SparseTable {
    int N, lgN;
    T defaultT;
    F func;
    std::vector<std::vector<T>> data;
    std::vector<int> lgx_table;
    SparseTable(F func) : func(func) {}
    SparseTable(const std::vector<T> &sequence, T defaultT, F func) : N(sequence.size()), defaultT(defaultT), func(func)
    {
        lgx_table.resize(N + 1);
        for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgN = lgx_table[N] + 1;
        data.assign(lgN, std::vector<T>(N, defaultT));
        data[0] = sequence;
        for (int d = 1; d < lgN; d++) {
            for (int i = 0; i + (1 << d) <= N; i++) {
                data[d][i] = func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);
            }
        }
    }
    T get(int l, int r) { // [l, r), 0-indexed
        assert(l >= 0 and r <= N);
        if (l >= r) return defaultT;
        int d = lgx_table[r - l];
        return func(data[d][l], data[d][r - (1 << d)]);
    }
};
#line 3 "sparse_table/sparse_table_2d.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Static matrix sparse table
// Complexity; O(HWlogHlogW) for precalculation, O(1) per query
template<typename T, typename F>
struct SparseTable2D {
    int H, lgH, W;
    T defaultT;
    F func;
    std::vector<std::vector<SparseTable<T, F>>> data;
    std::vector<int> lgx_table;
    SparseTable2D(F func) : func(func) {}
    SparseTable2D(const std::vector<std::vector<T>> &matrix, T defaultT, F func) : defaultT(defaultT), func(func) {
        H = matrix.size(), W = (matrix.size() ? matrix[0].size() : 0);
        lgx_table.resize(H + 1);
        for (int i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;
        lgH = lgx_table[H] + 1;
        data.resize(lgH);
        for (auto v : matrix) data[0].emplace_back(SparseTable<T, F>(v, defaultT, func));
        for (int d = 1; d < lgH; d++) {
            for (int i = 0; i + (1 << d) <= H; i++) {
                std::vector<T> v(W);
                for (int j = 0; j < W; j++) v[j] = func(data[d - 1][i].data[0][j], data[d - 1][i + (1 << (d - 1))].data[0][j]);
                data[d].emplace_back(SparseTable<T, F>(v, defaultT, func));
            }
        }
    }
    T get(int xl, int xr, int yl, int yr) {
        assert(xl >= 0 and xr <= H and yl >= 0 and yr <= W);
        if (xl >= xr) return defaultT;
        int d = lgx_table[xr - xl];
        return func(data[d][xl].get(yl, yr), data[d][xr - (1 << d)].get(yl, yr));
    }
};
#line 2 "sparse_table/test/sparse_table_2d.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068"
// Very slow (worst case: 6sec, memory 3GB)

#include <iostream>
using namespace std;

int main()
{
    auto f = [](int l, int r) { return min(l, r); };
    while (true) {
        int H, W, Q;
        cin >> H >> W >> Q;
        if (!H) break;
        vector<vector<int>> mat(H, vector<int>(W));
        for (auto &vec : mat) for (auto &x : vec) cin >> x;
        SparseTable2D<int, decltype(f)> rmq(mat, (1LL << 31) - 1, f);
        while (Q--) {
            int xl, yl, xr, yr;
            cin >> xl >> yl >> xr >> yr;
            printf("%d\n", rmq.get(xl, xr + 1, yl, yr + 1));
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

