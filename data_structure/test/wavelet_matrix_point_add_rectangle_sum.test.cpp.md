---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/wavelet_matrix.hpp
    title: "Wavelet matrix \uFF08\u30A6\u30A7\u30FC\u30D6\u30EC\u30C3\u30C8\u884C\u5217\
      \uFF09"
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: "Binary indexed tree / Fenwick tree \uFF08BIT\u30FB\u30D5\u30A7\u30CB\u30C3\
      \u30AF\u6728\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_rectangle_sum
  bundledCode: "#line 1 \"data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\n\
    #line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n#include\
    \ <vector>\n\n// CUT begin\n// 0-indexed BIT (binary indexed tree / Fenwick tree)\
    \ (i : [0, len))\ntemplate <class T> struct BIT {\n    int n;\n    std::vector<T>\
    \ data;\n    BIT(int len = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(),\
    \ data.end(), T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n\
    \        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n\
    \    }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n\
    \        while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i <= bit.n; i++) {\n            T now = bit.sum(i);\n          \
    \  os << now - prv << ',', prv = now;\n        }\n        return os << ']';\n\
    \    }\n};\n#line 3 \"data_structure/wavelet_matrix.hpp\"\n#include <bit>\n#include\
    \ <cassert>\n#include <cstdint>\n#include <optional>\n#line 8 \"data_structure/wavelet_matrix.hpp\"\
    \n\ntemplate <class Int> class wavelet_matrix {\n\n    class bit_vector {\n  \
    \      static constexpr int WSIZE = 64;\n        int n = 0;\n        int cnt0\
    \ = 0;\n        std::vector<uint64_t> bits;\n        std::vector<int> count_cumsum;\
    \ // need build()\n\n    public:\n        bit_vector(int n_) : n(n_), cnt0(n_)\
    \ {\n            assert(n >= 0);\n            bits.assign((n + WSIZE - 1) / WSIZE,\
    \ 0);\n        }\n\n        int size() const { return n; }\n\n        void set(int\
    \ i) {\n            assert(0 <= i and i < n);\n            bits[i / WSIZE] |=\
    \ (1ULL << (i % WSIZE));\n        }\n\n        void reset(int i) {\n         \
    \   assert(0 <= i and i < n);\n            bits[i / WSIZE] &= ~(1ULL << (i % WSIZE));\n\
    \        }\n\n        void build() {\n            cnt0 = n;\n            for (int\
    \ i = 0; i < (int)bits.size(); ++i) cnt0 -= std::popcount(bits[i]);\n        \
    \    count_cumsum.assign(bits.size(), 0);\n            for (int i = 1; i < (int)bits.size();\
    \ ++i) {\n                count_cumsum[i] = count_cumsum[i - 1] + std::popcount(bits[i\
    \ - 1]);\n            }\n        }\n\n        int count0() const { return cnt0;\
    \ }\n\n        int count1() const { return n - cnt0; }\n\n        // get i-th\
    \ bit\n        bool access(int i) const {\n            assert(0 <= i and i < n);\n\
    \            return bits[i / WSIZE] & (1ULL << (i % WSIZE));\n        }\n\n  \
    \      // count of 0s in [0, i)\n        int rank0(int i) const {\n          \
    \  assert(0 <= i and i <= n);\n            return i - rank1(i);\n        }\n\n\
    \        // count of 1s in [0, i)\n        int rank1(int i) const {\n        \
    \    assert(0 <= i and i <= n);\n            if (i == n) return count1();\n  \
    \          return count_cumsum[i / WSIZE] +\n                   std::popcount(bits[i\
    \ / WSIZE] & ((1ULL << (i % WSIZE)) - 1));\n        }\n\n        // get the position\
    \ of i-th element after stable sort\n        int sorted_pos(int i) const { return\
    \ access(i) ? (rank1(i) + count0()) : rank0(i); }\n\n        template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const bit_vector &bv) {\n          \
    \  os << \"bit_vector[\" << bv.n << \"]: \";\n            for (int i = 0; i <\
    \ bv.n; ++i) {\n                os << (bv.bits[i / WSIZE] & (1ULL << (i % WSIZE))\
    \ ? '1' : '0');\n            }\n            os << \" (cnt0: \" << bv.cnt0 << \"\
    )\";\n            return os;\n        }\n    };\n\n    std::vector<bit_vector>\
    \ bits;\n\n    std::vector<std::pair<Int, Int>> points;\n    std::vector<Int>\
    \ distinct_ys;\n\n    int to_index_x(Int x) const {\n        return std::lower_bound(points.cbegin(),\
    \ points.cend(), std::make_pair(x, Int{}),\n                                [](const\
    \ auto &l, const auto &r) { return l.first < r.first; }) -\n               points.cbegin();\n\
    \    }\n\n    int to_index_y(Int y) const {\n        return std::lower_bound(distinct_ys.cbegin(),\
    \ distinct_ys.cend(), y) - distinct_ys.cbegin();\n    }\n\n    bool is_built()\
    \ const { return !bits.empty(); }\n\npublic:\n    wavelet_matrix() = default;\n\
    \n    wavelet_matrix(const std::vector<Int> &ys) {\n        for (int x = 0; x\
    \ < (int)ys.size(); ++x) {\n            assert(ys[x] >= 0);\n            add_point(x,\
    \ ys[x]);\n        }\n        build();\n    }\n\n    void add_point(Int x, Int\
    \ y) {\n        assert(bits.empty()); // confirm that build() is not called yet\n\
    \        points.emplace_back(x, y);\n        distinct_ys.emplace_back(y);\n  \
    \  }\n\n    void build() {\n        std::sort(points.begin(), points.end());\n\
    \        points.erase(std::unique(points.begin(), points.end()), points.end());\n\
    \n        std::sort(distinct_ys.begin(), distinct_ys.end());\n        distinct_ys.erase(std::unique(distinct_ys.begin(),\
    \ distinct_ys.end()), distinct_ys.end());\n\n        int d = 1;\n        while\
    \ ((1 << d) < (int)distinct_ys.size()) ++d;\n        bits.assign(d, bit_vector(N()));\n\
    \n        std::vector<int> a;\n        for (auto p : points) a.push_back(to_index_y(p.second));\n\
    \        auto nxt = a;\n\n        for (int d = D() - 1; d >= 0; --d) {\n     \
    \       for (int i = 0; i < N(); ++i) {\n                if ((a[i] >> d) & 1)\
    \ bits[d].set(i);\n            }\n            bits[d].build();\n\n           \
    \ for (int i = 0; i < N(); ++i) nxt[bits[d].sorted_pos(i)] = a[i];\n\n       \
    \     std::swap(a, nxt);\n        }\n    }\n\n    int N() const { return points.size();\
    \ }\n\n    int D() const { return bits.size(); }\n\n    // get v_i\n    int index_access(int\
    \ i) const {\n        assert(0 <= i and i < N());\n        assert(is_built());\n\
    \n        int ret = 0;\n        for (int d = D() - 1; d >= 0; --d) {\n       \
    \     ret |= (int)bits[d].access(i) << d;\n            i = bits[d].sorted_pos(i);\n\
    \        }\n        return ret;\n    }\n\n    Int access(int i) const {\n    \
    \    assert(0 <= i and i < N());\n        assert(is_built());\n        return\
    \ distinct_ys.at(index_access(i));\n    }\n\n    // callback(d, i) means \"update\
    \ d-th segment's i-th element\"\n    void index_apply(int i, auto callback) const\
    \ {\n        assert(0 <= i and i < N());\n        assert(is_built());\n\n    \
    \    for (int d = D() - 1; d >= 0; --d) {\n            i = bits[d].sorted_pos(i);\n\
    \            callback(d, i);\n        }\n    }\n\n    // Update weight associated\
    \ to point (x, y)\n    // callback(d, i) means \"update d-th segment's i-th element\"\
    \n    void apply(Int x, Int y, auto callback) const {\n        const int i = std::lower_bound(points.cbegin(),\
    \ points.cend(), std::make_pair(x, y)) -\n                      points.cbegin();\n\
    \        assert(i < N() and points[i] == std::make_pair(x, y));\n        index_apply(i,\
    \ callback);\n    }\n\n    void index_prod(int l, int r, int yr, auto callback)\
    \ const {\n        assert(0 <= l and l <= r and r <= N());\n        assert(0 <=\
    \ yr and yr <= (int)distinct_ys.size());\n        assert(is_built());\n\n    \
    \    if (yr & (1 << D())) {\n            const int d = D() - 1;\n            const\
    \ int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);\n            callback(d, l0,\
    \ r0);\n            const int l1 = bits[d].rank1(l) + bits[d].count0();\n    \
    \        const int r1 = bits[d].rank1(r) + bits[d].count0();\n            callback(d,\
    \ l1, r1);\n            return;\n        }\n\n        for (int d = D() - 1; d\
    \ >= 0; --d) {\n            if (l == r) break;\n            const int l0 = bits[d].rank0(l),\
    \ r0 = bits[d].rank0(r);\n            if ((yr >> d) & 1) {\n                callback(d,\
    \ l0, r0);\n                // l = bits[d].rank1(l) + bits[d].count0();\n    \
    \            l += bits[d].count0() - l0;\n                // r = bits[d].rank1(r)\
    \ + bits[d].count0();\n                r += bits[d].count0() - r0;\n         \
    \   } else {\n                l = l0, r = r0;\n            }\n        }\n    }\n\
    \n    // Get product of weights associated to elements in [xl, xr) * [-inf, yr)\n\
    \    // callback(d, l, r) means \"use d-th segment's [l, r) elements\"\n    void\
    \ prod(Int xl, Int xr, Int yr, auto callback) const {\n        index_prod(to_index_x(xl),\
    \ to_index_x(xr), to_index_y(yr), callback);\n    }\n\n    // Get k-th smallest\
    \ v_i, i in [l, r) (0-indexed, duplicates are counted)]\n    int index_kth_smallest(int\
    \ l, int r, int k) const {\n        assert(0 <= l and l <= r and r <= N());\n\
    \        assert(0 <= k and k < r - l);\n        assert(is_built());\n\n      \
    \  int ret = 0;\n        for (int d = D() - 1; d >= 0; --d) {\n            const\
    \ int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);\n            if (k < r0 -\
    \ l0) {\n                l = l0, r = r0;\n            } else {\n             \
    \   k -= r0 - l0;\n                ret |= 1 << d;\n                l = bits[d].rank1(l)\
    \ + bits[d].count0();\n                r = bits[d].rank1(r) + bits[d].count0();\n\
    \            }\n        }\n\n        return ret;\n    }\n\n    // Get k-th largest\
    \ v_i, i in [l, r) (0-indexed, duplicates are counted)\n    int index_kth_largest(int\
    \ l, int r, int k) const {\n        assert(0 <= l and l <= r and r <= N());\n\
    \        assert(0 <= k and k < r - l);\n        return index_kth_smallest(l, r,\
    \ (r - l - 1) - k);\n    }\n\n    // count i s.t. i in [l, r) and v_i < upper_bound\n\
    \    int index_range_freq(int l, int r, int upper_bound) const {\n        assert(0\
    \ <= l and l <= r and r <= N());\n        assert(is_built());\n        if (upper_bound\
    \ <= 0) return 0;\n        if (upper_bound >= (int)distinct_ys.size()) return\
    \ r - l;\n\n        int ret = 0;\n        for (int d = D() - 1; d >= 0; --d) {\n\
    \            const int l0 = bits[d].rank0(l), r0 = bits[d].rank0(r);\n       \
    \     if ((upper_bound >> d) & 1) {\n                ret += r0 - l0;\n       \
    \         l = bits[d].rank1(l) + bits[d].count0();\n                r = bits[d].rank1(r)\
    \ + bits[d].count0();\n            } else {\n                l = l0, r = r0;\n\
    \            }\n        }\n\n        return ret;\n    }\n\n    // Get k-th smallest\
    \ y in [xl, xr) (0-indexed, duplicates are counted)\n    std::optional<Int> kth_smallest(Int\
    \ xl, Int xr, int k) const {\n        const int l = to_index_x(xl), r = to_index_x(xr);\n\
    \        if (k < 0 or k >= r - l) return std::nullopt;\n        return distinct_ys.at(index_kth_smallest(l,\
    \ r, k));\n    }\n\n    // Get k-th largest y in [xl, xr) (0-indexed, duplicates\
    \ are counted)\n    std::optional<Int> kth_largest(Int xl, Int xr, int k) const\
    \ {\n        const int l = to_index_x(xl), r = to_index_x(xr);\n        if (k\
    \ < 0 or k >= r - l) return std::nullopt;\n        return distinct_ys.at(index_kth_largest(l,\
    \ r, k));\n    }\n\n    // count points in [xl, xr) * [-inf, yr)\n    int range_freq(Int\
    \ xl, Int xr, Int yr) const {\n        return index_range_freq(to_index_x(xl),\
    \ to_index_x(xr), to_index_y(yr));\n    }\n\n    // max v_i s.t. i in [l, r),\
    \ v_i < upper_bound\n    std::optional<int> index_prev_value(int l, int r, int\
    \ upper_bound) const {\n        assert(0 <= l and l <= r and r <= N());\n    \
    \    assert(is_built());\n        if (upper_bound <= 0) return std::nullopt;\n\
    \n        const int n = index_range_freq(l, r, upper_bound);\n        return n\
    \ == 0 ? std::nullopt : index_kth_smallest(l, r, n - 1);\n    }\n\n    // max\
    \ y s.t. x in [xl, xr), y < yr\n    std::optional<Int> prev_value(Int xl, Int\
    \ xr, Int yr) const {\n        const int l = to_index_x(xl), r = to_index_x(xr),\
    \ ub = to_index_y(yr);\n        const auto idx = index_prev_value(l, r, ub);\n\
    \        return idx ? distinct_ys.at(*idx) : std::nullopt;\n    }\n\n    // min\
    \ v_i s.t. i in [l, r), v_i >= lower_bound\n    std::optional<int> index_next_value(int\
    \ l, int r, int lower_bound) const {\n        assert(0 <= l and l <= r and r <=\
    \ N());\n        assert(is_built());\n        if (lower_bound >= (int)distinct_ys.size())\
    \ return std::nullopt;\n        const int n = index_range_freq(l, r, lower_bound);\n\
    \        return n >= (r - l) ? std::nullopt : index_kth_smallest(l, r, n);\n \
    \   }\n\n    // min y s.t. x in [xl, xr), y >= yl\n    std::optional<Int> next_value(Int\
    \ l, Int r, Int yl) const {\n        const int xl = to_index_x(l), xr = to_index_x(r),\
    \ yl_idx = to_index_y(yl);\n        const auto idx = index_next_value(xl, xr,\
    \ yl_idx);\n        return idx ? distinct_ys.at(*idx) : std::nullopt;\n    }\n\
    };\n/* Sample usage:\nwavelet_matrix<int> wm;\n\nwm.build();\nvector tmp(wm.D(),\
    \ vector<BIT<T>>(wm.N()));\nwm.apply(i, j, [&](int d, int idx) { tmp[d].add(idx,\
    \ wx); });  // point add\nT ret{};\nwm.prod(l, r, u, [&](int d, int l0, int r0)\
    \ { ret += tmp[d].sum(l0, r0); }); // range sum\n*/\n#line 4 \"data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, Q;\n    cin >> N >> Q;\n\n    wavelet_matrix<int>\
    \ wm;\n    vector<tuple<int, int, int>> points(N);\n    vector<tuple<int, int,\
    \ int, int, int>> queries(Q);\n\n    for (auto &[i, j, x] : points) {\n      \
    \  cin >> i >> j >> x;\n        wm.add_point(i, j);\n    }\n\n    for (auto &[tp,\
    \ a, b, c, d] : queries) {\n        cin >> tp;\n        if (tp == 0) {\n     \
    \       cin >> a >> b >> c;\n            d = -1;\n            wm.add_point(a,\
    \ b);\n        } else {\n            cin >> a >> b >> c >> d;\n        }\n   \
    \ }\n\n    wm.build();\n\n    vector weights(wm.D(), BIT<long long>(wm.N()));\n\
    \n    for (auto [i, j, x] : points) {\n        wm.apply(i, j, [&weights, x](int\
    \ d, int idx) { weights[d].add(idx, x); });\n    }\n\n    for (auto [tp, l, d,\
    \ r, u] : queries) {\n        if (tp == 0) {\n            wm.apply(l, d, [&weights,\
    \ r](int d, int idx) { weights[d].add(idx, r); });\n        } else {\n       \
    \     long long ans = 0;\n            wm.prod(l, r, u,\n                    [&weights,\
    \ &ans](int d, int l0, int r0) { ans += weights[d].sum(l0, r0); });\n        \
    \    wm.prod(l, r, d,\n                    [&weights, &ans](int d, int l0, int\
    \ r0) { ans -= weights[d].sum(l0, r0); });\n            cout << ans << '\\n';\n\
    \        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_rectangle_sum\"\
    \n#include \"../../segmenttree/binary_indexed_tree.hpp\"\n#include \"../wavelet_matrix.hpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, Q;\n    cin >> N >> Q;\n\n    wavelet_matrix<int>\
    \ wm;\n    vector<tuple<int, int, int>> points(N);\n    vector<tuple<int, int,\
    \ int, int, int>> queries(Q);\n\n    for (auto &[i, j, x] : points) {\n      \
    \  cin >> i >> j >> x;\n        wm.add_point(i, j);\n    }\n\n    for (auto &[tp,\
    \ a, b, c, d] : queries) {\n        cin >> tp;\n        if (tp == 0) {\n     \
    \       cin >> a >> b >> c;\n            d = -1;\n            wm.add_point(a,\
    \ b);\n        } else {\n            cin >> a >> b >> c >> d;\n        }\n   \
    \ }\n\n    wm.build();\n\n    vector weights(wm.D(), BIT<long long>(wm.N()));\n\
    \n    for (auto [i, j, x] : points) {\n        wm.apply(i, j, [&weights, x](int\
    \ d, int idx) { weights[d].add(idx, x); });\n    }\n\n    for (auto [tp, l, d,\
    \ r, u] : queries) {\n        if (tp == 0) {\n            wm.apply(l, d, [&weights,\
    \ r](int d, int idx) { weights[d].add(idx, r); });\n        } else {\n       \
    \     long long ans = 0;\n            wm.prod(l, r, u,\n                    [&weights,\
    \ &ans](int d, int l0, int r0) { ans += weights[d].sum(l0, r0); });\n        \
    \    wm.prod(l, r, d,\n                    [&weights, &ans](int d, int l0, int\
    \ r0) { ans -= weights[d].sum(l0, r0); });\n            cout << ans << '\\n';\n\
    \        }\n    }\n}\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  - data_structure/wavelet_matrix.hpp
  isVerificationFile: true
  path: data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp
  requiredBy: []
  timestamp: '2025-07-23 23:51:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp
- /verify/data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp.html
title: data_structure/test/wavelet_matrix_point_add_rectangle_sum.test.cpp
---
