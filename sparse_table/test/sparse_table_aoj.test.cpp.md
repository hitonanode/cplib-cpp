---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: sparse_table/rmq_sparse_table.hpp
    title: sparse_table/rmq_sparse_table.hpp
  - icon: ':x:'
    path: sparse_table/sparse_table.hpp
    title: sparse_table/sparse_table.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D
  bundledCode: "#line 2 \"sparse_table/rmq_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Range Minimum Query\
    \ for static sequence by sparse table\n// Complexity: O(NlogN) for precalculation,\
    \ O(1) per query\ntemplate <typename T> struct StaticRMQ {\n    inline T func(const\
    \ T &l, const T &r) { return std::min<T>(l, r); }\n    int N, lgN;\n    T defaultT;\n\
    \    std::vector<std::vector<T>> data;\n    std::vector<int> lgx_table;\n    StaticRMQ(const\
    \ std::vector<T> &sequence, T defaultT) : N(sequence.size()), defaultT(defaultT)\
    \ {\n        lgx_table.resize(N + 1);\n        for (int i = 2; i < N + 1; i++)\
    \ lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgN = lgx_table[N] + 1;\n   \
    \     data.assign(lgN, std::vector<T>(N, defaultT));\n        data[0] = sequence;\n\
    \        for (int d = 1; d < lgN; d++) {\n            for (int i = 0; i + (1 <<\
    \ d) <= N; i++) { data[d][i] = func(data[d - 1][i], data[d - 1][i + (1 << (d -\
    \ 1))]); }\n        }\n    }\n    T get(int l, int r) { // [l, r), 0-indexed\n\
    \        assert(l >= 0 and r <= N);\n        if (l >= r) return defaultT;\n  \
    \      int d = lgx_table[r - l];\n        return func(data[d][l], data[d][r -\
    \ (1 << d)]);\n    }\n};\n#line 4 \"sparse_table/sparse_table.hpp\"\n\n// CUT\
    \ begin\n// Static sequence sparse table\n// Complexity: O(NlogN) for precalculation,\
    \ O(1) per query\ntemplate <typename T, typename F> struct SparseTable {\n   \
    \ int N, lgN;\n    T defaultT;\n    F func;\n    std::vector<std::vector<T>> data;\n\
    \    std::vector<int> lgx_table;\n    SparseTable(F func) : func(func) {}\n  \
    \  SparseTable(const std::vector<T> &sequence, T defaultT, F func) : N(sequence.size()),\
    \ defaultT(defaultT), func(func) {\n        lgx_table.resize(N + 1);\n       \
    \ for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n    \
    \    lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N, defaultT));\n\
    \        data[0] = sequence;\n        for (int d = 1; d < lgN; d++) {\n      \
    \      for (int i = 0; i + (1 << d) <= N; i++) { data[d][i] = func(data[d - 1][i],\
    \ data[d - 1][i + (1 << (d - 1))]); }\n        }\n    }\n    T get(int l, int\
    \ r) { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n        if (l\
    \ >= r) return defaultT;\n        int d = lgx_table[r - l];\n        return func(data[d][l],\
    \ data[d][r - (1 << d)]);\n    }\n};\n#line 3 \"sparse_table/test/sparse_table_aoj.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D\"\
    \n\n#include <cstdio>\nint main() {\n    int N, L;\n    scanf(\"%d %d\", &N, &L);\n\
    \    std::vector<int> A(N);\n    for (auto &a : A) scanf(\"%d\", &a);\n    auto\
    \ f = [](int l, int r) { return std::min(l, r); };\n    SparseTable<int, decltype(f)>\
    \ sp1(A, 1e9, f);\n    StaticRMQ<int> sp2(A, 1e9);\n    for (int l = 0; l + L\
    \ <= N; l++) {\n        int a = sp1.get(l, l + L);\n        int b = sp2.get(l,\
    \ l + L);\n        assert(a == b);\n        printf(\"%d \", a);\n    }\n}\n"
  code: "#include \"sparse_table/rmq_sparse_table.hpp\"\n#include \"sparse_table/sparse_table.hpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D\"\
    \n\n#include <cstdio>\nint main() {\n    int N, L;\n    scanf(\"%d %d\", &N, &L);\n\
    \    std::vector<int> A(N);\n    for (auto &a : A) scanf(\"%d\", &a);\n    auto\
    \ f = [](int l, int r) { return std::min(l, r); };\n    SparseTable<int, decltype(f)>\
    \ sp1(A, 1e9, f);\n    StaticRMQ<int> sp2(A, 1e9);\n    for (int l = 0; l + L\
    \ <= N; l++) {\n        int a = sp1.get(l, l + L);\n        int b = sp2.get(l,\
    \ l + L);\n        assert(a == b);\n        printf(\"%d \", a);\n    }\n}\n"
  dependsOn:
  - sparse_table/rmq_sparse_table.hpp
  - sparse_table/sparse_table.hpp
  isVerificationFile: true
  path: sparse_table/test/sparse_table_aoj.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: sparse_table/test/sparse_table_aoj.test.cpp
layout: document
redirect_from:
- /verify/sparse_table/test/sparse_table_aoj.test.cpp
- /verify/sparse_table/test/sparse_table_aoj.test.cpp.html
title: sparse_table/test/sparse_table_aoj.test.cpp
---
