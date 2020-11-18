#pragma once
#include <algorithm>
#include <iostream>
#include <tuple>
#include <vector>

// CUT begin
template <typename TDATA, typename TLAZY, typename TRET, typename TQUERY> struct LazySegmentTree {
    TLAZY zero_lazy;
    TRET zero_ret;
    int N;
    int head;
    std::vector<TDATA> data;
    std::vector<TLAZY> lazy;

    // Here, you have to calculate data[pos] from children (data[l], data[r]),
    // Assumptions: `lazy[pos] = lazy[l] = lazy[r] = zero_lazy`
    virtual void merge_data(int pos) = 0;

    // Here, you must propagate lazy[pos] and update data[pos] by reflecting lazy[pos], without inconsistency
    // After this, lazy[pos] must be zero_lazy.
    virtual void reflect_lazy(int pos) = 0;

    // operate d to lazy[pos] (merge two TLAZY's)
    virtual void overlap_lazy(int pos, const TLAZY &d) = 0;

    // Assumption: `lazy[pos] = zero_lazy`
    virtual TRET data2ret(int pos, const TQUERY &query) = 0;

    virtual TRET merge_ret(const TRET &l, const TRET &r, const TQUERY &query) = 0;

    ////// general description //////
    LazySegmentTree() = default;
    void initialize(const std::vector<TDATA> &data_init, const TDATA &zero_data, const TLAZY &zero_lazy_, const TRET &zero_ret_) {
        N = data_init.size();
        head = 1;
        while (head < N) head <<= 1;
        zero_lazy = zero_lazy_;
        zero_ret = zero_ret_;
        data.assign(head * 2, zero_data);
        lazy.assign(head * 2, zero_lazy);
        std::copy(data_init.begin(), data_init.end(), data.begin() + head);
        for (int pos = head; --pos;) merge_data(pos);
    }

    void _update(int begin, int end, const TLAZY &delay, int pos, int l, int r) {
        // Operate `delay` to the node pos
        // After this, lazy[pos] MUST be zero so that merge_data() works correctly
        if (begin <= l and r <= end) { // Update whole [l, r) by delay
            overlap_lazy(pos, delay);
            reflect_lazy(pos);
        } else if (begin < r and l < end) { // Update somewhere in [l, r)
            reflect_lazy(pos);
            _update(begin, end, delay, pos * 2, l, (l + r) / 2);
            _update(begin, end, delay, pos * 2 + 1, (l + r) / 2, r);
            merge_data(pos);
        } else
            reflect_lazy(pos);
    }

    void update(int begin, int end, const TLAZY &delay) { _update(begin, end, delay, 1, 0, head); }

    TRET _get(int begin, int end, int pos, int l, int r, const TQUERY &query) // Get value in [begin, end)
    {
        reflect_lazy(pos);
        if (begin <= l and r <= end)
            return data2ret(pos, query);
        else if (begin < r and l < end) {
            TRET vl = _get(begin, end, pos * 2, l, (l + r) / 2, query);
            TRET vr = _get(begin, end, pos * 2 + 1, (l + r) / 2, r, query);
            return merge_ret(vl, vr, query);
        } else
            return zero_ret;
    }
    TRET get(int begin, int end, const TQUERY &query = NULL) { return _get(begin, end, 1, 0, head, query); }
};

// Range Update & Range Sum
// - get(l, r): return x_l + ... + x_{r - 1}
// - update(l, r, val): x_l, ..., x_{r - 1} <- val
template <typename T> struct RangeUpdateRangeSum : public LazySegmentTree<std::pair<T, size_t>, std::pair<T, bool>, T, std::tuple<>> {
    using TDATA = std::pair<T, size_t>;
    using TLAZY = std::pair<T, bool>;
    using SegTree = LazySegmentTree<TDATA, TLAZY, T, std::tuple<>>;
    using SegTree::data;
    using SegTree::lazy;
    void merge_data(int i) override { data[i] = std::make_pair(data[i * 2].first + data[i * 2 + 1].first, data[i * 2].second + data[i * 2 + 1].second); };
    void reflect_lazy(int i) override {
        if (lazy[i].second) {
            if (i < SegTree::head) overlap_lazy(i * 2, lazy[i]), overlap_lazy(i * 2 + 1, lazy[i]);
            data[i].first = lazy[i].first * data[i].second;
        }
        lazy[i].second = false;
    }
    void overlap_lazy(int i, const TLAZY &p) override {
        if (p.second) lazy[i] = p;
    }
    T data2ret(int i, const std::tuple<> &) override { return data[i].first; }
    T merge_ret(const T &l, const T &r, const std::tuple<> &) override { return l + r; }
    void update(int l, int r, T val) { SegTree::update(l, r, TLAZY(val, true)); }
    T get(int l, int r) { return SegTree::get(l, r, {}); }
    RangeUpdateRangeSum(const std::vector<T> &seq) : SegTree::LazySegmentTree() {
        std::vector<TDATA> vec;
        for (const auto &x : seq) vec.emplace_back(x, 1);
        SegTree::initialize(vec, TDATA(0, 0), TLAZY(0, false), 0);
    }
};
