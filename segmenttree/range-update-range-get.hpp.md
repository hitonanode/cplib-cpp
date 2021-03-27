---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: segmenttree/test/range-affine-range-sum.test.cpp
    title: segmenttree/test/range-affine-range-sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"segmenttree/range-update-range-get.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <tuple>\n#include <vector>\n\n// CUT begin\ntemplate\
    \ <typename TDATA, typename TLAZY, typename TRET, typename TQUERY> struct LazySegmentTree\
    \ {\n    TLAZY zero_lazy;\n    TRET zero_ret;\n    int N;\n    int head;\n   \
    \ std::vector<TDATA> data;\n    std::vector<TLAZY> lazy;\n\n    // Here, you have\
    \ to calculate data[pos] from children (data[l], data[r]),\n    // Assumptions:\
    \ `lazy[pos] = lazy[l] = lazy[r] = zero_lazy`\n    virtual void merge_data(int\
    \ pos) = 0;\n\n    // Here, you must propagate lazy[pos] and update data[pos]\
    \ by reflecting lazy[pos], without inconsistency\n    // After this, lazy[pos]\
    \ must be zero_lazy.\n    virtual void reflect_lazy(int pos) = 0;\n\n    // operate\
    \ d to lazy[pos] (merge two TLAZY's)\n    virtual void overlap_lazy(int pos, const\
    \ TLAZY &d) = 0;\n\n    // Assumption: `lazy[pos] = zero_lazy`\n    virtual TRET\
    \ data2ret(int pos, const TQUERY &query) = 0;\n\n    virtual TRET merge_ret(const\
    \ TRET &l, const TRET &r, const TQUERY &query) = 0;\n\n    ////// general description\
    \ //////\n    LazySegmentTree() = default;\n    void initialize(const std::vector<TDATA>\
    \ &data_init, const TDATA &zero_data, const TLAZY &zero_lazy_, const TRET &zero_ret_)\
    \ {\n        N = data_init.size();\n        head = 1;\n        while (head < N)\
    \ head <<= 1;\n        zero_lazy = zero_lazy_;\n        zero_ret = zero_ret_;\n\
    \        data.assign(head * 2, zero_data);\n        lazy.assign(head * 2, zero_lazy);\n\
    \        std::copy(data_init.begin(), data_init.end(), data.begin() + head);\n\
    \        for (int pos = head; --pos;) merge_data(pos);\n    }\n\n    void _update(int\
    \ begin, int end, const TLAZY &delay, int pos, int l, int r) {\n        // Operate\
    \ `delay` to the node pos\n        // After this, lazy[pos] MUST be zero so that\
    \ merge_data() works correctly\n        if (begin <= l and r <= end) { // Update\
    \ whole [l, r) by delay\n            overlap_lazy(pos, delay);\n            reflect_lazy(pos);\n\
    \        } else if (begin < r and l < end) { // Update somewhere in [l, r)\n \
    \           reflect_lazy(pos);\n            _update(begin, end, delay, pos * 2,\
    \ l, (l + r) / 2);\n            _update(begin, end, delay, pos * 2 + 1, (l + r)\
    \ / 2, r);\n            merge_data(pos);\n        } else\n            reflect_lazy(pos);\n\
    \    }\n\n    void update(int begin, int end, const TLAZY &delay) { _update(begin,\
    \ end, delay, 1, 0, head); }\n\n    TRET _get(int begin, int end, int pos, int\
    \ l, int r, const TQUERY &query) // Get value in [begin, end)\n    {\n       \
    \ reflect_lazy(pos);\n        if (begin <= l and r <= end)\n            return\
    \ data2ret(pos, query);\n        else if (begin < r and l < end) {\n         \
    \   TRET vl = _get(begin, end, pos * 2, l, (l + r) / 2, query);\n            TRET\
    \ vr = _get(begin, end, pos * 2 + 1, (l + r) / 2, r, query);\n            return\
    \ merge_ret(vl, vr, query);\n        } else\n            return zero_ret;\n  \
    \  }\n    TRET get(int begin, int end, const TQUERY &query = NULL) { return _get(begin,\
    \ end, 1, 0, head, query); }\n};\n\n// Range Update & Range Sum\n// - get(l, r):\
    \ return x_l + ... + x_{r - 1}\n// - update(l, r, val): x_l, ..., x_{r - 1} <-\
    \ val\ntemplate <typename T> struct RangeUpdateRangeSum : public LazySegmentTree<std::pair<T,\
    \ size_t>, std::pair<T, bool>, T, std::tuple<>> {\n    using TDATA = std::pair<T,\
    \ size_t>;\n    using TLAZY = std::pair<T, bool>;\n    using SegTree = LazySegmentTree<TDATA,\
    \ TLAZY, T, std::tuple<>>;\n    using SegTree::data;\n    using SegTree::lazy;\n\
    \    void merge_data(int i) override { data[i] = std::make_pair(data[i * 2].first\
    \ + data[i * 2 + 1].first, data[i * 2].second + data[i * 2 + 1].second); };\n\
    \    void reflect_lazy(int i) override {\n        if (lazy[i].second) {\n    \
    \        if (i < SegTree::head) overlap_lazy(i * 2, lazy[i]), overlap_lazy(i *\
    \ 2 + 1, lazy[i]);\n            data[i].first = lazy[i].first * data[i].second;\n\
    \        }\n        lazy[i].second = false;\n    }\n    void overlap_lazy(int\
    \ i, const TLAZY &p) override {\n        if (p.second) lazy[i] = p;\n    }\n \
    \   T data2ret(int i, const std::tuple<> &) override { return data[i].first; }\n\
    \    T merge_ret(const T &l, const T &r, const std::tuple<> &) override { return\
    \ l + r; }\n    void update(int l, int r, T val) { SegTree::update(l, r, TLAZY(val,\
    \ true)); }\n    T get(int l, int r) { return SegTree::get(l, r, {}); }\n    RangeUpdateRangeSum(const\
    \ std::vector<T> &seq) : SegTree::LazySegmentTree() {\n        std::vector<TDATA>\
    \ vec;\n        for (const auto &x : seq) vec.emplace_back(x, 1);\n        SegTree::initialize(vec,\
    \ TDATA(0, 0), TLAZY(0, false), 0);\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <iostream>\n#include <tuple>\n\
    #include <vector>\n\n// CUT begin\ntemplate <typename TDATA, typename TLAZY, typename\
    \ TRET, typename TQUERY> struct LazySegmentTree {\n    TLAZY zero_lazy;\n    TRET\
    \ zero_ret;\n    int N;\n    int head;\n    std::vector<TDATA> data;\n    std::vector<TLAZY>\
    \ lazy;\n\n    // Here, you have to calculate data[pos] from children (data[l],\
    \ data[r]),\n    // Assumptions: `lazy[pos] = lazy[l] = lazy[r] = zero_lazy`\n\
    \    virtual void merge_data(int pos) = 0;\n\n    // Here, you must propagate\
    \ lazy[pos] and update data[pos] by reflecting lazy[pos], without inconsistency\n\
    \    // After this, lazy[pos] must be zero_lazy.\n    virtual void reflect_lazy(int\
    \ pos) = 0;\n\n    // operate d to lazy[pos] (merge two TLAZY's)\n    virtual\
    \ void overlap_lazy(int pos, const TLAZY &d) = 0;\n\n    // Assumption: `lazy[pos]\
    \ = zero_lazy`\n    virtual TRET data2ret(int pos, const TQUERY &query) = 0;\n\
    \n    virtual TRET merge_ret(const TRET &l, const TRET &r, const TQUERY &query)\
    \ = 0;\n\n    ////// general description //////\n    LazySegmentTree() = default;\n\
    \    void initialize(const std::vector<TDATA> &data_init, const TDATA &zero_data,\
    \ const TLAZY &zero_lazy_, const TRET &zero_ret_) {\n        N = data_init.size();\n\
    \        head = 1;\n        while (head < N) head <<= 1;\n        zero_lazy =\
    \ zero_lazy_;\n        zero_ret = zero_ret_;\n        data.assign(head * 2, zero_data);\n\
    \        lazy.assign(head * 2, zero_lazy);\n        std::copy(data_init.begin(),\
    \ data_init.end(), data.begin() + head);\n        for (int pos = head; --pos;)\
    \ merge_data(pos);\n    }\n\n    void _update(int begin, int end, const TLAZY\
    \ &delay, int pos, int l, int r) {\n        // Operate `delay` to the node pos\n\
    \        // After this, lazy[pos] MUST be zero so that merge_data() works correctly\n\
    \        if (begin <= l and r <= end) { // Update whole [l, r) by delay\n    \
    \        overlap_lazy(pos, delay);\n            reflect_lazy(pos);\n        }\
    \ else if (begin < r and l < end) { // Update somewhere in [l, r)\n          \
    \  reflect_lazy(pos);\n            _update(begin, end, delay, pos * 2, l, (l +\
    \ r) / 2);\n            _update(begin, end, delay, pos * 2 + 1, (l + r) / 2, r);\n\
    \            merge_data(pos);\n        } else\n            reflect_lazy(pos);\n\
    \    }\n\n    void update(int begin, int end, const TLAZY &delay) { _update(begin,\
    \ end, delay, 1, 0, head); }\n\n    TRET _get(int begin, int end, int pos, int\
    \ l, int r, const TQUERY &query) // Get value in [begin, end)\n    {\n       \
    \ reflect_lazy(pos);\n        if (begin <= l and r <= end)\n            return\
    \ data2ret(pos, query);\n        else if (begin < r and l < end) {\n         \
    \   TRET vl = _get(begin, end, pos * 2, l, (l + r) / 2, query);\n            TRET\
    \ vr = _get(begin, end, pos * 2 + 1, (l + r) / 2, r, query);\n            return\
    \ merge_ret(vl, vr, query);\n        } else\n            return zero_ret;\n  \
    \  }\n    TRET get(int begin, int end, const TQUERY &query = NULL) { return _get(begin,\
    \ end, 1, 0, head, query); }\n};\n\n// Range Update & Range Sum\n// - get(l, r):\
    \ return x_l + ... + x_{r - 1}\n// - update(l, r, val): x_l, ..., x_{r - 1} <-\
    \ val\ntemplate <typename T> struct RangeUpdateRangeSum : public LazySegmentTree<std::pair<T,\
    \ size_t>, std::pair<T, bool>, T, std::tuple<>> {\n    using TDATA = std::pair<T,\
    \ size_t>;\n    using TLAZY = std::pair<T, bool>;\n    using SegTree = LazySegmentTree<TDATA,\
    \ TLAZY, T, std::tuple<>>;\n    using SegTree::data;\n    using SegTree::lazy;\n\
    \    void merge_data(int i) override { data[i] = std::make_pair(data[i * 2].first\
    \ + data[i * 2 + 1].first, data[i * 2].second + data[i * 2 + 1].second); };\n\
    \    void reflect_lazy(int i) override {\n        if (lazy[i].second) {\n    \
    \        if (i < SegTree::head) overlap_lazy(i * 2, lazy[i]), overlap_lazy(i *\
    \ 2 + 1, lazy[i]);\n            data[i].first = lazy[i].first * data[i].second;\n\
    \        }\n        lazy[i].second = false;\n    }\n    void overlap_lazy(int\
    \ i, const TLAZY &p) override {\n        if (p.second) lazy[i] = p;\n    }\n \
    \   T data2ret(int i, const std::tuple<> &) override { return data[i].first; }\n\
    \    T merge_ret(const T &l, const T &r, const std::tuple<> &) override { return\
    \ l + r; }\n    void update(int l, int r, T val) { SegTree::update(l, r, TLAZY(val,\
    \ true)); }\n    T get(int l, int r) { return SegTree::get(l, r, {}); }\n    RangeUpdateRangeSum(const\
    \ std::vector<T> &seq) : SegTree::LazySegmentTree() {\n        std::vector<TDATA>\
    \ vec;\n        for (const auto &x : seq) vec.emplace_back(x, 1);\n        SegTree::initialize(vec,\
    \ TDATA(0, 0), TLAZY(0, false), 0);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: segmenttree/range-update-range-get.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - segmenttree/test/range-affine-range-sum.test.cpp
documentation_of: segmenttree/range-update-range-get.hpp
layout: document
redirect_from:
- /library/segmenttree/range-update-range-get.hpp
- /library/segmenttree/range-update-range-get.hpp.html
title: segmenttree/range-update-range-get.hpp
---
