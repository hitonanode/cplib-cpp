---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/rmq_sparse_table.hpp
    title: sparse_table/rmq_sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table.hpp
    title: sparse_table/sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/staticrmq
    links:
    - https://judge.yosupo.jp/problem/staticrmq
  bundledCode: "#line 2 \"sparse_table/sparse_table.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Static sequence sparse table\n// Complexity: O(NlogN)\
    \ for precalculation, O(1) per query\ntemplate<typename T, typename F>\nstruct\
    \ SparseTable {\n    int N, lgN;\n    T defaultT;\n    F func;\n    std::vector<std::vector<T>>\
    \ data;\n    std::vector<int> lgx_table;\n    SparseTable(F func) : func(func)\
    \ {}\n    SparseTable(const std::vector<T> &sequence, T defaultT, F func) : N(sequence.size()),\
    \ defaultT(defaultT), func(func)\n    {\n        lgx_table.resize(N + 1);\n  \
    \      for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n\
    \        lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N, defaultT));\n\
    \        data[0] = sequence;\n        for (int d = 1; d < lgN; d++) {\n      \
    \      for (int i = 0; i + (1 << d) <= N; i++) {\n                data[d][i] =\
    \ func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);\n            }\n    \
    \    }\n    }\n    T get(int l, int r) { // [l, r), 0-indexed\n        assert(l\
    \ >= 0 and r <= N);\n        if (l >= r) return defaultT;\n        int d = lgx_table[r\
    \ - l];\n        return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n\
    #line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include <algorithm>\n#line 5 \"\
    sparse_table/rmq_sparse_table.hpp\"\n\n// CUT begin\n// Range Minimum Query for\
    \ static sequence by sparse table\n// Complexity: O(NlogN) for precalculation,\
    \ O(1) per query\ntemplate<typename T>\nstruct StaticRMQ {\n    inline T func(const\
    \ T &l, const T &r) {\n        return std::min<T>(l, r);\n    }\n    int N, lgN;\n\
    \    T defaultT;\n    std::vector<std::vector<T>> data;\n    std::vector<int>\
    \ lgx_table;\n    StaticRMQ(const std::vector<T> &sequence, T defaultT) : N(sequence.size()),\
    \ defaultT(defaultT)\n    {\n        lgx_table.resize(N + 1);\n        for (int\
    \ i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN =\
    \ lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N, defaultT));\n\
    \        data[0] = sequence;\n        for (int d = 1; d < lgN; d++) {\n      \
    \      for (int i = 0; i + (1 << d) <= N; i++) {\n                data[d][i] =\
    \ func(data[d - 1][i], data[d - 1][i + (1 << (d - 1))]);\n            }\n    \
    \    }\n    }\n    T get(int l, int r) { // [l, r), 0-indexed\n        assert(l\
    \ >= 0 and r <= N);\n        if (l >= r) return defaultT;\n        int d = lgx_table[r\
    \ - l];\n        return func(data[d][l], data[d][r - (1 << d)]);\n    }\n};\n\
    #line 4 \"sparse_table/test/sparse_table.test.cpp\"\n#include <cstdio>\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\n\nint main()\n{\n   \
    \ int N, Q;\n    scanf(\"%d %d\", &N, &Q);\n    std::vector<int> A(N);\n    for\
    \ (int i = 0; i < N; i++) scanf(\"%d\", &A[i]);\n    auto f = [](int l, int r)\
    \ { return std::min(l, r); };\n    SparseTable<int, decltype(f)> rmq1(A, 2e9,\
    \ f);\n    StaticRMQ<int> rmq2(A, 2e9);\n    while (Q--) {\n        int l, r;\n\
    \        scanf(\"%d %d\", &l, &r);\n        int a = rmq1.get(l, r), b = rmq2.get(l,\
    \ r);\n        assert(a == b);\n        printf(\"%d\\n\", a);\n    }\n}\n"
  code: "#include \"sparse_table/sparse_table.hpp\"\n#include \"sparse_table/rmq_sparse_table.hpp\"\
    \n#include <cassert>\n#include <cstdio>\n#define PROBLEM \"https://judge.yosupo.jp/problem/staticrmq\"\
    \n\nint main()\n{\n    int N, Q;\n    scanf(\"%d %d\", &N, &Q);\n    std::vector<int>\
    \ A(N);\n    for (int i = 0; i < N; i++) scanf(\"%d\", &A[i]);\n    auto f = [](int\
    \ l, int r) { return std::min(l, r); };\n    SparseTable<int, decltype(f)> rmq1(A,\
    \ 2e9, f);\n    StaticRMQ<int> rmq2(A, 2e9);\n    while (Q--) {\n        int l,\
    \ r;\n        scanf(\"%d %d\", &l, &r);\n        int a = rmq1.get(l, r), b = rmq2.get(l,\
    \ r);\n        assert(a == b);\n        printf(\"%d\\n\", a);\n    }\n}\n"
  dependsOn:
  - sparse_table/sparse_table.hpp
  - sparse_table/rmq_sparse_table.hpp
  isVerificationFile: true
  path: sparse_table/test/sparse_table.test.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: sparse_table/test/sparse_table.test.cpp
layout: document
redirect_from:
- /verify/sparse_table/test/sparse_table.test.cpp
- /verify/sparse_table/test/sparse_table.test.cpp.html
title: sparse_table/test/sparse_table.test.cpp
---
