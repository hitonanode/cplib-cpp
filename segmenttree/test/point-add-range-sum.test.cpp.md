---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: segmenttree/binary_indexed_tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/point_add_range_sum
    links:
    - https://judge.yosupo.jp/problem/point_add_range_sum
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <iostream>\n\
    #include <vector>\n\n// CUT begin\n// 1-indexed BIT (i : [1, len])\ntemplate <typename\
    \ T>\nstruct BIT : std::vector<T>\n{\n    BIT(int len = 0) : std::vector<T>(len\
    \ + 1) {}\n    void reset() { fill(this->begin(), this->end(), 0); }\n    void\
    \ add(int pos, T v) {\n        while (pos > 0 and pos < (int)this->size()) (*this)[pos]\
    \ += v, pos += pos & -pos;\n    }\n    T sum(int pos) const { // (0, pos]\n  \
    \      T res = 0;\n        while (pos > 0) res += (*this)[pos], pos -= pos & -pos;\n\
    \        return res;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i < (int)bit.size(); i++) {\n            T now = bit.sum(i);\n \
    \           os << now - prv << \",\";\n            prv = now;\n        }\n   \
    \     os << ']';\n        return os;\n    }\n};\n#line 3 \"segmenttree/test/point-add-range-sum.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n\
    // PointAddRangeSum (BIT based) 0-indexed\n// Complexity: O(lg N) for each query\n\
    template <typename T>\nstruct PointAddRangeSum\n{\n    BIT<T> bit;\n    PointAddRangeSum(const\
    \ std::vector<T> &A) : bit(A.size())\n    {\n        for (unsigned i = 0; i <\
    \ A.size(); i++) bit.add(i + 1, A[i]);\n    }\n    void add(int i, T val)\n  \
    \  {\n        bit.add(i + 1, val);\n    }\n    // sum [l, r)\n    T get(int l,\
    \ int r) const\n    {\n        return bit.sum(r) - bit.sum(l);\n    }\n};\n\n\
    int main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<long long> A(N);\n \
    \   for (auto &a : A)\n    {\n        std::cin >> a;\n    }\n    PointAddRangeSum<long\
    \ long> s(A);\n    while (Q--)\n    {\n        int q, l, r;\n        std::cin\
    \ >> q >> l >> r;\n        if (q)\n        {\n            std::cout << s.get(l,\
    \ r) << '\\n';\n        }\n        else\n        {\n            s.add(l, r);\n\
    \        }\n    }\n}\n"
  code: "#include \"segmenttree/binary_indexed_tree.hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/point_add_range_sum\"\n\n// PointAddRangeSum\
    \ (BIT based) 0-indexed\n// Complexity: O(lg N) for each query\ntemplate <typename\
    \ T>\nstruct PointAddRangeSum\n{\n    BIT<T> bit;\n    PointAddRangeSum(const\
    \ std::vector<T> &A) : bit(A.size())\n    {\n        for (unsigned i = 0; i <\
    \ A.size(); i++) bit.add(i + 1, A[i]);\n    }\n    void add(int i, T val)\n  \
    \  {\n        bit.add(i + 1, val);\n    }\n    // sum [l, r)\n    T get(int l,\
    \ int r) const\n    {\n        return bit.sum(r) - bit.sum(l);\n    }\n};\n\n\
    int main()\n{\n    std::cin.tie(NULL);\n    std::ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    std::cin >> N >> Q;\n    std::vector<long long> A(N);\n \
    \   for (auto &a : A)\n    {\n        std::cin >> a;\n    }\n    PointAddRangeSum<long\
    \ long> s(A);\n    while (Q--)\n    {\n        int q, l, r;\n        std::cin\
    \ >> q >> l >> r;\n        if (q)\n        {\n            std::cout << s.get(l,\
    \ r) << '\\n';\n        }\n        else\n        {\n            s.add(l, r);\n\
    \        }\n    }\n}\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: true
  path: segmenttree/test/point-add-range-sum.test.cpp
  requiredBy: []
  timestamp: '2020-04-19 16:23:43+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/point-add-range-sum.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/point-add-range-sum.test.cpp
- /verify/segmenttree/test/point-add-range-sum.test.cpp.html
title: segmenttree/test/point-add-range-sum.test.cpp
---
