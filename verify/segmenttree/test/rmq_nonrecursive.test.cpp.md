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


# :x: segmenttree/test/rmq_nonrecursive.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/rmq_nonrecursive.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-02-16 16:13:35+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A</a>


## Depends on

* :x: <a href="../../../library/segmenttree/point-update-range-get_nonrecursive.hpp.html">segmenttree/point-update-range-get_nonrecursive.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N, (1LL << 31) - 1);
    RangeMinimumQuery<int> rmq(A, A[0]);
    for (int q = 0; q < Q; q++)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0) rmq.update(x, y);
        else cout << rmq.get(x, y + 1, 0) << endl;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "segmenttree/point-update-range-get_nonrecursive.hpp"
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

// Nonrecursive Segment Tree (point-update, range-get)
// - Conditions for operations:
//   - datamerge: [TDATA, TDATA] -> TDATA, e(defaultDATA, x) == x, e(x, y) == e(y, x)
//   - data2ret: [TDATA, TQUERY] -> TRET, f(defaultDATA, q) == defaultRET
//   - retmerge: [TRET, TRET] -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)
//   - commutability f(e(x, y), q) == g(f(x, q), f(y, q))
template<typename TDATA, typename TRET, typename TQUERY, typename E, typename F, typename G>
struct NonrecursiveSegmentTree
{
    int N;
    TDATA defaultDATA;
    TRET defaultRET;
    E datamerge;
    F data2ret;
    G retmerge;
    std::vector<TDATA> data;
    inline TDATA& at(int i) { return data[i]; }

    inline void _merge(int i) { at(i) = datamerge(at(i << 1), at((i << 1) + 1)); }
    void initialize(const std::vector<TDATA> &seq) {
        N = seq.size();
        data.assign(N * 2, defaultDATA);
        std::copy(seq.begin(), seq.end(), data.begin() + N);
        for (int i = N - 1; i; i--) _merge(i);
    }
    NonrecursiveSegmentTree(TDATA defaultDATA, E datamerge, F data2ret, G retmerge)
        : N(0), defaultDATA(defaultDATA), defaultRET(data2ret(defaultDATA, TQUERY(0))),
          datamerge(datamerge), data2ret(data2ret), retmerge(retmerge) {}
    NonrecursiveSegmentTree(const std::vector<TDATA> &seq, TDATA defaultDATA, E datamerge, F data2ret, G retmerge)
        : N(seq.size()), defaultDATA(defaultDATA),
          defaultRET(data2ret(defaultDATA, TQUERY(0))),
          datamerge(datamerge), data2ret(data2ret), retmerge(retmerge)
    {
        initialize(seq);
    }
    void update(int pos, const TDATA &x) {
        assert(pos >= 0 and pos < N);
        at(pos + N) = x;
        for (int i = pos + N; i > 1;) i >>= 1, _merge(i);
    }

    // [l, r), 0-indexed
    TRET get(int l, int r, TQUERY query) {
        TRET retl = defaultRET, retr = defaultRET;
        assert(l >= 0 and r <= N);
        l += N, r += N;
        while (l < r) {
            if (l & 1) retl = retmerge(retl, data2ret(data[l++], query));
            if (r & 1) retr = retmerge(data2ret(data[--r], query), retr);
            l >>= 1, r >>= 1;
        }
        return retmerge(retl, retr);
    }

    friend std::ostream &operator<<(std::ostream &os, NonrecursiveSegmentTree s) {
        os << "[SegmentTree (len: " << s.N << ')';
        for (int i = 0; i < s.N; i++) os << s.at(i + s.N) << ',';
        os << "]";
        return os;
    }
};

// Range Minimum Query
// - get: return min(x_l, ..., x_{r - 1})
auto st_op_1st = [](auto x, auto q) { return x; };
auto st_op_getmin = [](auto xl, auto xr) { return std::min(xl, xr); };
template <typename T>
struct RangeMinimumQuery : public NonrecursiveSegmentTree<T, T, int, decltype(st_op_getmin), decltype(st_op_1st), decltype(st_op_getmin)>
{
    using SegTree = NonrecursiveSegmentTree<T, T, int, decltype(st_op_getmin), decltype(st_op_1st), decltype(st_op_getmin)>;
    RangeMinimumQuery(const std::vector<T> &seq, T defaultmin) : SegTree::NonrecursiveSegmentTree(seq, defaultmin, st_op_getmin, st_op_1st, st_op_getmin) {}
};


// Range Counting less than q Query
// - get: return (#{i | l <= i < r, x_i < q}, total sum of them).
auto st_op_vecmerge = [](auto v, auto w) { 
    v.insert(v.end(), w.begin(), w.end());
    std::sort(v.begin(), v.end());
    v[0].second = v[0].first;
    for (size_t i = 1; i < v.size(); i++) v[i].second = v[i - 1].second + v[i].first;
    return v;
};
auto st_op_cntless = [](auto vec, auto q) {
    int i = std::lower_bound(vec.begin(), vec.end(), std::pair<decltype(q), decltype(q)>(q, 0)) - vec.begin();
    if (!i) return std::pair<int, decltype(q)>(0, 0);
    else return std::pair<int, decltype(q)>(i, vec[i - 1].second);
};
auto st_op_pairsum = [](auto p1, auto p2) { return std::pair<int, decltype(p1.second)>(p1.first + p2.first, p1.second + p2.second); };
template <typename T>
struct CountAndSumLessThan : public NonrecursiveSegmentTree<std::vector<std::pair<T, T>>, std::pair<int, T>, T, decltype(st_op_vecmerge), decltype(st_op_cntless), decltype(st_op_pairsum)>
{
    using SegTree = NonrecursiveSegmentTree<std::vector<std::pair<T, T>>, std::pair<int, T>, T, decltype(st_op_vecmerge), decltype(st_op_cntless), decltype(st_op_pairsum)>;
    CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree({}, st_op_vecmerge, st_op_cntless, st_op_pairsum) {
        std::vector<std::vector<std::pair<T, T>>> init;
        for (auto x : seq) init.emplace_back(std::vector<std::pair<T, T>>{std::pair<T, T>(x, x)});
        SegTree::initialize(init);
    }
};
#line 2 "segmenttree/test/rmq_nonrecursive.test.cpp"
#include <iostream>
using namespace std;
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_A"

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<int> A(N, (1LL << 31) - 1);
    RangeMinimumQuery<int> rmq(A, A[0]);
    for (int q = 0; q < Q; q++)
    {
        int c, x, y;
        cin >> c >> x >> y;
        if (c == 0) rmq.update(x, y);
        else cout << rmq.get(x, y + 1, 0) << endl;
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

