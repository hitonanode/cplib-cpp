---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: segmenttree/binary_indexed_tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n\
    #include <iostream>\n#include <vector>\n\n// CUT begin\n// 0-indexed BIT (binary\
    \ indexed tree / Fenwick tree) (i : [0, len))\ntemplate <typename T> struct BIT\
    \ {\n    int n;\n    std::vector<T> data;\n    BIT(int len = 0) : n(len), data(len)\
    \ {}\n    void reset() { std::fill(data.begin(), data.end(), T(0)); }\n    void\
    \ add(int pos, T v) { // a[pos] += v\n        pos++;\n        while (pos > 0 and\
    \ pos <= n) data[pos - 1] += v, pos += pos & -pos;\n    }\n    T sum(int k) const\
    \ { // a[0] + ... + a[k - 1]\n        T res = 0;\n        while (k > 0) res +=\
    \ data[k - 1], k -= k & -k;\n        return res;\n    }\n\n    T sum(int l, int\
    \ r) const { return sum(r) - sum(l); } // a[l] + ... + a[r - 1]\n\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const BIT &bit) {\n        T prv\
    \ = 0;\n        os << '[';\n        for (int i = 1; i <= bit.n; i++) {\n     \
    \       T now = bit.sum(i);\n            os << now - prv << ',', prv = now;\n\
    \        }\n        return os << ']';\n    }\n};\n#line 3 \"segmenttree/test/point-add-range-sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n\
    // PointAddRangeSum (BIT based) 0-indexed\n// Complexity: O(lg N) for each query\n\
    template <typename T> struct PointAddRangeSum {\n    BIT<T> bit;\n    PointAddRangeSum(const\
    \ std::vector<T> &A) : bit(A.size()) {\n        for (unsigned i = 0; i < A.size();\
    \ i++) bit.add(i, A[i]);\n    }\n    void add(int i, T val) { bit.add(i, val);\
    \ }\n    // sum [l, r)\n    T get(int l, int r) const { return bit.sum(l, r);\
    \ }\n};\n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<long long> A(N);\n \
    \   for (auto &a : A) std::cin >> a;\n    PointAddRangeSum<long long> s(A);\n\
    \    while (Q--) {\n        int q, l, r;\n        std::cin >> q >> l >> r;\n \
    \       if (q) {\n            std::cout << s.get(l, r) << '\\n';\n        } else\
    \ {\n            s.add(l, r);\n        }\n    }\n}\n"
  code: "#include \"../binary_indexed_tree.hpp\"\n#include <iostream>\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n// PointAddRangeSum\
    \ (BIT based) 0-indexed\n// Complexity: O(lg N) for each query\ntemplate <typename\
    \ T> struct PointAddRangeSum {\n    BIT<T> bit;\n    PointAddRangeSum(const std::vector<T>\
    \ &A) : bit(A.size()) {\n        for (unsigned i = 0; i < A.size(); i++) bit.add(i,\
    \ A[i]);\n    }\n    void add(int i, T val) { bit.add(i, val); }\n    // sum [l,\
    \ r)\n    T get(int l, int r) const { return bit.sum(l, r); }\n};\n\nint main()\
    \ {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\n    int N,\
    \ Q;\n    std::cin >> N >> Q;\n    std::vector<long long> A(N);\n    for (auto\
    \ &a : A) std::cin >> a;\n    PointAddRangeSum<long long> s(A);\n    while (Q--)\
    \ {\n        int q, l, r;\n        std::cin >> q >> l >> r;\n        if (q) {\n\
    \            std::cout << s.get(l, r) << '\\n';\n        } else {\n          \
    \  s.add(l, r);\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: true
  path: segmenttree/test/point-add-range-sum.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/point-add-range-sum.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/point-add-range-sum.test.cpp
- /verify/segmenttree/test/point-add-range-sum.test.cpp.html
title: segmenttree/test/point-add-range-sum.test.cpp
---
