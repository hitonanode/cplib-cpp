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


# :heavy_check_mark: segmenttree/test/countandsumlessthan.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#5fd93d3fa59267c091e036914d93749e">segmenttree/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/segmenttree/test/countandsumlessthan.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-15 20:16:09+09:00


* see: <a href="https://yukicoder.me/problems/no/877">https://yukicoder.me/problems/no/877</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/segmenttree/point-update-range-get_nonrecursive.hpp.html">segmenttree/point-update-range-get_nonrecursive.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#define PROBLEM "https://yukicoder.me/problems/no/877"
#include <iostream>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long int> A(N);
    for (auto &a : A) cin >> a;
    CountAndSumLessThan<long long int> segtree(A);
    while (Q--) {
        int q, l, r, x;
        cin >> q >> l >> r >> x;
        auto r1 = segtree.get(l - 1, r, x);
        auto r2 = segtree.get(l - 1, r, 1e18);
        printf("%lld\n", r2.second - r1.second - 1LL * (r2.first - r1.first) * x);
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

// CUT begin
// Nonrecursive Segment Tree (point-update, range-get)
// - Conditions for operations:
//   - datamerge: [TDATA, TDATA] -> TDATA, e(x, y) == e(y, x)
//   - data2ret: [TDATA, TQUERY] -> TRET
//   - retmerge: [TRET, TRET] -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)
//   - commutability f(e(x, y), q) == g(f(x, q), f(y, q))
template<typename TDATA, typename TRET, typename TQUERY>
struct NonrecursiveSegmentTree
{
    int N;
    TRET defaultRET;
    virtual TDATA datamerge(const TDATA &, const TDATA &) = 0;
    virtual TRET data2ret(const TDATA &, const TQUERY &) = 0;
    virtual TRET retmerge(const TRET &, const TRET &) = 0;
    std::vector<TDATA> data;
    inline TDATA& at(int i) { return data[i]; }

    inline void _merge(int i) { at(i) = datamerge(at(i << 1), at((i << 1) + 1)); }
    void initialize(const std::vector<TDATA> &seq, TRET RET_ZERO) {
        N = seq.size();
        defaultRET = RET_ZERO;
        data = seq;
        data.insert(data.end(), seq.begin(), seq.end());
        for (int i = N - 1; i; i--) _merge(i);
    }
    NonrecursiveSegmentTree() = default;
    void update(int pos, const TDATA &x) {
        assert(pos >= 0 and pos < N);
        at(pos + N) = x;
        for (int i = pos + N; i > 1;) i >>= 1, _merge(i);
    }

    // [l, r), 0-indexed
    TRET get(int l, int r, TQUERY query = NULL) {
        assert(l >= 0 and r <= N);
        TRET retl = defaultRET, retr = defaultRET;
        l += N, r += N;
        while (l < r) {
            if (l & 1) retl = retmerge(retl, data2ret(data[l++], query));
            if (r & 1) retr = retmerge(data2ret(data[--r], query), retr);
            l >>= 1, r >>= 1;
        }
        return retmerge(retl, retr);
    }

    template<typename T1, typename T2, typename T3>
    friend std::ostream &operator<<(std::ostream &os, NonrecursiveSegmentTree<T1, T2, T3> s) {
        os << "[SegmentTree (len: " << s.N << ')';
        for (int i = 0; i < s.N; i++) os << s.at(i + s.N) << ',';
        os << "]";
        return os;
    }
};


// Range Minimum Query
// - get: return min(x_l, ..., x_{r - 1})
template <typename T>
struct RangeMinimumQuery : public NonrecursiveSegmentTree<T, T, bool>
{
    using SegTree = NonrecursiveSegmentTree<T, T, bool>;
    T datamerge(const T &vl, const T &vr) override { return std::min(vl, vr); };
    T data2ret(const T &v, const bool &q) override { return v; }
    T retmerge(const T &vl, const T &vr) override { return std::min(vl, vr); };
    RangeMinimumQuery(const std::vector<T> &seq, T defaultmin) : SegTree::NonrecursiveSegmentTree() {
        SegTree::initialize(seq, defaultmin);
    };
};

// Range Maximum Query
// - get: return max(x_l, ..., x_{r - 1})
template <typename T>
struct RangeMaximumQuery : public NonrecursiveSegmentTree<T, T, bool>
{
    using SegTree = NonrecursiveSegmentTree<T, T, bool>;
    T datamerge(const T &vl, const T &vr) override { return std::max(vl, vr); };
    T data2ret(const T &v, const bool &q) override { return v; }
    T retmerge(const T &vl, const T &vr) override { return std::max(vl, vr); };
    RangeMaximumQuery(const std::vector<T> &seq, T defaultmax) : SegTree::NonrecursiveSegmentTree() {
        SegTree::initialize(seq, defaultmax);
    };
};

template<typename T>
struct PointUpdateRangeSum : public NonrecursiveSegmentTree<T, T, bool>
{
    using SegTree = NonrecursiveSegmentTree<T, T, bool>;
    T datamerge(const T &vl, const T &vr) override { return vl + vr; };
    T data2ret(const T &v, const bool &q) override { return v; }
    T retmerge(const T &vl, const T &vr) override { return vl + vr; };
    PointUpdateRangeSum(const std::vector<T> &seq, T zero) : SegTree::NonrecursiveSegmentTree() {
        SegTree::initialize(seq, zero);
    };
};

// Range Counting less than q Query
// - get: return (#{i | l <= i < r, x_i < q}, total sum of them).
template <typename T>
struct CountAndSumLessThan : public NonrecursiveSegmentTree<std::vector<std::pair<T, T>>, std::pair<int, T>, T>
{
    using TDATA = std::vector<std::pair<T, T>>;
    using TRET = std::pair<int, T>;
    using TQUERY = T;
    TDATA datamerge(const TDATA &vl, const TDATA &vr) override {
        TDATA ret = vl;
        ret.insert(ret.end(), vr.begin(), vr.end());
        std::sort(ret.begin(), ret.end());
        if (ret.size()) {
            ret[0].second = ret[0].first;
            for (size_t i = 1; i < ret.size(); i++) ret[i].second = ret[i - 1].second + ret[i].first;
        }
        return ret;
    }
    TRET data2ret(const TDATA &vec, const TQUERY &q) override {
        int i = std::lower_bound(vec.begin(), vec.end(), std::make_pair(q, q)) - vec.begin();
        if (!i) return std::make_pair(0, 0);
        else return std::make_pair(i, vec[i - 1].second);
    }
    TRET retmerge(const TRET &l, const TRET &r) override {
        return std::make_pair(l.first + r.first, l.second + r.second);
    }
    using SegTree = NonrecursiveSegmentTree<TDATA, TRET, TQUERY>;
    CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree(){
        std::vector<TDATA> init;
        for (auto x : seq) init.emplace_back(TDATA{std::pair<T, T>(x, x)});
        SegTree::initialize(init, TRET(0, 0));
    }
};
#line 2 "segmenttree/test/countandsumlessthan.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/no/877"
#line 4 "segmenttree/test/countandsumlessthan.test.cpp"
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long int> A(N);
    for (auto &a : A) cin >> a;
    CountAndSumLessThan<long long int> segtree(A);
    while (Q--) {
        int q, l, r, x;
        cin >> q >> l >> r >> x;
        auto r1 = segtree.get(l - 1, r, x);
        auto r2 = segtree.get(l - 1, r, 1e18);
        printf("%lld\n", r2.second - r1.second - 1LL * (r2.first - r1.first) * x);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>
