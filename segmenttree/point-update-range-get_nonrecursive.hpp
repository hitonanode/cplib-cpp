#pragma once
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
template<typename TDATA, typename TRET, typename TQUERY>
struct NonrecursiveSegmentTree
{
    int N;
    TDATA defaultDATA;
    TRET defaultRET;
    // E datamerge;
    // F data2ret;
    // G retmerge;
    virtual TDATA datamerge(const TDATA &, const TDATA &) = 0;
    virtual TRET data2ret(const TDATA &, const TQUERY &) = 0;
    virtual TRET retmerge(const TRET &, const TRET &) = 0;
    std::vector<TDATA> data;
    inline TDATA& at(int i) { return data[i]; }

    inline void _merge(int i) { at(i) = datamerge(at(i << 1), at((i << 1) + 1)); }
    void initialize(const std::vector<TDATA> &seq) {
        N = seq.size();
        data.assign(N * 2, defaultDATA);
        std::copy(seq.begin(), seq.end(), data.begin() + N);
        for (int i = N - 1; i; i--) _merge(i);
    }
    NonrecursiveSegmentTree() = default;
    NonrecursiveSegmentTree(const std::vector<TDATA> &seq, TDATA defaultDATA) : N(seq.size()), defaultDATA(defaultDATA), defaultRET(data2ret(defaultDATA, TQUERY(0)))
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

/*
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
*/

// Range Counting less than q Query
// - get: return (#{i | l <= i < r, x_i < q}, total sum of them).
template <typename T>
struct CountAndSumLessThan : public NonrecursiveSegmentTree<std::vector<std::pair<T, T>>, std::pair<int, T>, T>
{
    using TDATA = std::vector<std::pair<T, T>>;
    using TRET = std::pair<int, T>;
    using TQUERY = T;
    TDATA datamerge(const TDATA &vl, const TDATA &vr) {
        vl.insert(vl.end(), vr.begin(), vr.end());
        std::sort(vl.begin(), vl.end());
        if (vl.size()) {
            vl[0].second = vl[0].first;
            for (size_t i = 1; i < vl.size(); i++) vl[i].second = vl[i - 1].second + vl[i].first;
        }
        return vl;
    }
    TRET data2ret(const TDATA &vec, TQUERY q) {
        int i = std::lower_bound(vec.begin(), vec.end(), std::make_pair(q, q)) - vec.begin();
        if (!i) return std::make_pair(0, 0);
        else return std::make_pair(i, vec[i - 1].second);
    }
    TRET retmerge(const TRET &l, const TRET &r) {
        return std::make_pair(l.first + r.first, l.second + r.second);
    }
    using SegTree = NonrecursiveSegmentTree<TDATA, TRET, TQUERY>;
    CountAndSumLessThan(const std::vector<T> &seq) : SegTree::NonrecursiveSegmentTree()
    {
        SegTree::defaultDATA = std::make_pair(0, 0);
        std::vector<std::vector<std::pair<T, T>>> init;
        for (auto x : seq) init.emplace_back(std::vector<std::pair<T, T>>{std::pair<T, T>(x, x)});
        SegTree::initialize(init);
    }
};
