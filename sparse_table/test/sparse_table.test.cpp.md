---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: sparse_table/rmq_sparse_table.hpp
    title: sparse_table/rmq_sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table.hpp
    title: Sparse table
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 1 \"sparse_table/test/sparse_table.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/staticrmq\"\n#line 2 \"sparse_table/sparse_table.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Static sequence sparse\
    \ table\n// Complexity: O(NlogN) for precalculation, O(1) per query\ntemplate\
    \ <class S, S (*op)(S, S), S (*e)()> struct sparse_table {\n    int N, lgN;\n\
    \    std::vector<std::vector<S>> d;\n    std::vector<int> lgx_table;\n    sparse_table()\
    \ {}\n    sparse_table(const std::vector<S> &sequence) : N(sequence.size()) {\n\
    \        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; ++i) lgx_table[i]\
    \ = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n        d.assign(lgN,\
    \ std::vector<S>(N, e()));\n        d[0] = sequence;\n        for (int h = 1;\
    \ h < lgN; ++h) {\n            for (int i = 0; i + (1 << h) <= N; ++i) {\n   \
    \             d[h][i] = op(d[h - 1][i], d[h - 1][i + (1 << (h - 1))]);\n     \
    \       }\n        }\n    }\n    S prod(int l, int r) const { // [l, r), 0-indexed\n\
    \        assert(l >= 0 and r <= N);\n        if (l >= r) return e();\n       \
    \ int h = lgx_table[r - l];\n        return op(d[h][l], d[h][r - (1 << h)]);\n\
    \    }\n};\n#line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include <algorithm>\n\
    #line 5 \"sparse_table/rmq_sparse_table.hpp\"\n\n// CUT begin\n// Range Minimum\
    \ Query for static sequence by sparse table\n// Complexity: $O(N \\log N)$ for\
    \ precalculation, $O(1)$ per query\ntemplate <typename T> struct StaticRMQ {\n\
    \    inline T func(const T &l, const T &r) const noexcept { return std::min<T>(l,\
    \ r); }\n    int N, lgN;\n    T defaultT;\n    std::vector<std::vector<T>> data;\n\
    \    std::vector<int> lgx_table;\n    StaticRMQ() = default;\n    StaticRMQ(const\
    \ std::vector<T> &sequence, T defaultT)\n        : N(sequence.size()), defaultT(defaultT)\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) {\n                data[d][i] = func(data[d - 1][i], data[d -\
    \ 1][i + (1 << (d - 1))]);\n            }\n        }\n    }\n    T get(int l,\
    \ int r) const { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n  \
    \      if (l >= r) return defaultT;\n        int d = lgx_table[r - l];\n     \
    \   return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n#line 5 \"sparse_table/test/sparse_table.test.cpp\"\
    \n#include <iostream>\n#line 7 \"sparse_table/test/sparse_table.test.cpp\"\nusing\
    \ namespace std;\n\nint op(int l, int r) { return l < r ? l : r; }\nint e() {\
    \ return 2e9; }\n\nint main() {\n    int N, Q;\n    cin >> N >> Q;\n    vector<int>\
    \ A(N);\n    for (auto &x : A) cin >> x;\n    sparse_table<int, op, e> rmq1(A);\n\
    \    StaticRMQ<int> rmq2(A, 2e9);\n    while (Q--) {\n        int l, r;\n    \
    \    cin >> l >> r;\n        int a = rmq1.prod(l, r), b = rmq2.get(l, r);\n  \
    \      assert(a == b);\n        cout << a << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n#include \"\
    ../sparse_table.hpp\"\n#include \"../rmq_sparse_table.hpp\"\n#include <cassert>\n\
    #include <iostream>\n#include <vector>\nusing namespace std;\n\nint op(int l,\
    \ int r) { return l < r ? l : r; }\nint e() { return 2e9; }\n\nint main() {\n\
    \    int N, Q;\n    cin >> N >> Q;\n    vector<int> A(N);\n    for (auto &x :\
    \ A) cin >> x;\n    sparse_table<int, op, e> rmq1(A);\n    StaticRMQ<int> rmq2(A,\
    \ 2e9);\n    while (Q--) {\n        int l, r;\n        cin >> l >> r;\n      \
    \  int a = rmq1.prod(l, r), b = rmq2.get(l, r);\n        assert(a == b);\n   \
    \     cout << a << '\\n';\n    }\n}\n"
  dependsOn:
  - sparse_table/sparse_table.hpp
  - sparse_table/rmq_sparse_table.hpp
  isVerificationFile: true
  path: sparse_table/test/sparse_table.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: sparse_table/test/sparse_table.test.cpp
layout: document
redirect_from:
- /verify/sparse_table/test/sparse_table.test.cpp
- /verify/sparse_table/test/sparse_table.test.cpp.html
title: sparse_table/test/sparse_table.test.cpp
---
