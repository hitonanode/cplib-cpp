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


# :x: graph-tree/test/vertex-add-subtree-sum.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#728e08a0b5b0c7a31e7e3fe276503f5d">graph-tree/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/graph-tree/test/vertex-add-subtree-sum.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-06 01:29:43+09:00


* see: <a href="https://judge.yosupo.jp/problem/vertex_add_subtree_sum">https://judge.yosupo.jp/problem/vertex_add_subtree_sum</a>


## Depends on

* :x: <a href="../../../library/graph-tree/eulertour.hpp.html">graph-tree/eulertour.hpp</a>
* :x: <a href="../../../library/segmenttree/point-update-range-get_nonrecursive.hpp.html">segmenttree/point-update-range-get_nonrecursive.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "graph-tree/eulertour.hpp"
#include "segmenttree/point-update-range-get_nonrecursive.hpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#include <cassert>
#include <iostream>
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long int> A(N);
    vector<vector<int>> to(N);
    for (auto &a : A) cin >> a;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        to[p].push_back(i);
        to[i].push_back(p);
    }

    PreorderEulerTour tour(to, 0);
    vector<long long int> v;
    for (auto i : tour.vis_order) v.push_back(A[i]);
    assert(int(v.size()) == N);
    PointUpdateRangeSum<long long int> rsq(v, 0);

    while (Q--) {
        int q;
        cin >> q;
        if (q) {
            int u;
            cin >> u;
            printf("%lld\n", rsq.get(tour.subtree_begin[u], tour.subtree_end[u]));
        }
        else {
            int u, x;
            cin >> u >> x;
            A[u] += x;
            rsq.update(tour.subtree_begin[u], A[u]);
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "graph-tree/eulertour.hpp"
#include <cassert>
#include <vector>

// CUT begin
// Preorder Euler Tour
// （行きがけ順，部分木の頂点クエリ等に有用）
struct PreorderEulerTour
{
    int V; // # of vertices of tree
    int root;
    std::vector<std::vector<int>> edges;
    std::vector<int> subtree_begin, subtree_end;
    std::vector<int> vis_order;

    void _build_dfs(int now, int prv) {
        subtree_begin[now] = vis_order.size();
        vis_order.push_back(now);
        for (auto nxt : edges[now]) if (nxt != prv) _build_dfs(nxt, now);
        subtree_end[now] = vis_order.size();
    }
    PreorderEulerTour() = default;
    PreorderEulerTour(const std::vector<std::vector<int>> &to, int root) : V(to.size()), root(root), edges(to)
    {
        assert(root >= 0 and root < V);
        subtree_begin.resize(V);
        subtree_end.resize(V);
        _build_dfs(root, -1);
    }
};
#line 2 "segmenttree/point-update-range-get_nonrecursive.hpp"
#include <algorithm>
#line 4 "segmenttree/point-update-range-get_nonrecursive.hpp"
#include <iostream>
#line 6 "segmenttree/point-update-range-get_nonrecursive.hpp"

// CUT begin
// Nonrecursive Segment Tree (point-update, range-get)
// - Conditions for operations:
//   - datamerge: [TDATA, TDATA] -> TDATA, e(x, y) == e(y, x)
//   - data2ret: [TDATA, TQUERY] -> TRET
//   - retmerge: [TRET, TRET] -> TRET, g(defaultRET, x) == x, g(x, y) = g(y, x)
//   - commutability f(e(x, y), q) == g(f(x, q), f(y, q))
template <typename TDATA, typename TRET, typename TQUERY>
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

    // Calculate smallest r that satisfies g(f(x_l, q), ..., f(x_{r - 1}, q)) >= threshold
    // Assumption: Monotonicity of g(x_l, ..., x_r) about r (l: fixed)
    // Complexity: O(log N)
    int binary_search(int l, const TRET &threshold, TQUERY query = NULL) {
        stack<int> rs;
        l += N;
        int r = N * 2;
        TRET retl = defaultRET;
        if (threshold <= retl) return l - N;
        while (l < r) {
            if (l & 1) {
                TRET ret_tmp = retmerge(retl, data2ret(data[l], query));
                if (threshold <= ret_tmp) {
                    while (l * 2 < N * 2) {
                        ret_tmp = retmerge(retl, data2ret(data[l * 2], query));
                        if (threshold <= ret_tmp) l *= 2;
                        else retl = ret_tmp, l = l * 2 + 1;
                    }
                    return l - N;
                }
                l++;
                retl = ret_tmp;
            }
            if (r & 1) rs.push(--r);
            l >>= 1, r >>= 1;
        }
        while (!rs.empty()) {
            l = rs.top();
            rs.pop();
            TRET ret_tmp = retmerge(retl, data2ret(data[l], query));
            if (threshold <= ret_tmp) {
                while (l * 2 < N * 2) {
                    ret_tmp = retmerge(retl, data2ret(data[l * 2], query));
                    if (threshold <= ret_tmp) l *= 2;
                    else retl = ret_tmp, l = l * 2 + 1;
                }
                return l - N;
            }
            retl = ret_tmp;
        }
        return N;
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

template <typename T>
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
#line 3 "graph-tree/test/vertex-add-subtree-sum.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/vertex_add_subtree_sum"
#line 6 "graph-tree/test/vertex-add-subtree-sum.test.cpp"
using namespace std;

int main()
{
    int N, Q;
    cin >> N >> Q;
    vector<long long int> A(N);
    vector<vector<int>> to(N);
    for (auto &a : A) cin >> a;
    for (int i = 1; i < N; i++) {
        int p;
        cin >> p;
        to[p].push_back(i);
        to[i].push_back(p);
    }

    PreorderEulerTour tour(to, 0);
    vector<long long int> v;
    for (auto i : tour.vis_order) v.push_back(A[i]);
    assert(int(v.size()) == N);
    PointUpdateRangeSum<long long int> rsq(v, 0);

    while (Q--) {
        int q;
        cin >> q;
        if (q) {
            int u;
            cin >> u;
            printf("%lld\n", rsq.get(tour.subtree_begin[u], tour.subtree_end[u]));
        }
        else {
            int u, x;
            cin >> u >> x;
            A[u] += x;
            rsq.update(tour.subtree_begin[u], A[u]);
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

