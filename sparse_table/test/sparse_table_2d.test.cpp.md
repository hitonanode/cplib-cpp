---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table.hpp
    title: sparse_table/sparse_table.hpp
  - icon: ':heavy_check_mark:'
    path: sparse_table/sparse_table_2d.hpp
    title: sparse_table/sparse_table_2d.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068
  bundledCode: "#line 2 \"sparse_table/sparse_table.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Static sequence sparse table\n// Complexity: O(NlogN)\
    \ for precalculation, O(1) per query\ntemplate <typename T, typename F> struct\
    \ SparseTable {\n    int N, lgN;\n    T defaultT;\n    F func;\n    std::vector<std::vector<T>>\
    \ data;\n    std::vector<int> lgx_table;\n    SparseTable(F func) : func(func)\
    \ {}\n    SparseTable(const std::vector<T> &sequence, T defaultT, F func) : N(sequence.size()),\
    \ defaultT(defaultT), func(func) {\n        lgx_table.resize(N + 1);\n       \
    \ for (int i = 2; i < N + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n    \
    \    lgN = lgx_table[N] + 1;\n        data.assign(lgN, std::vector<T>(N, defaultT));\n\
    \        data[0] = sequence;\n        for (int d = 1; d < lgN; d++) {\n      \
    \      for (int i = 0; i + (1 << d) <= N; i++) { data[d][i] = func(data[d - 1][i],\
    \ data[d - 1][i + (1 << (d - 1))]); }\n        }\n    }\n    T get(int l, int\
    \ r) { // [l, r), 0-indexed\n        assert(l >= 0 and r <= N);\n        if (l\
    \ >= r) return defaultT;\n        int d = lgx_table[r - l];\n        return func(data[d][l],\
    \ data[d][r - (1 << d)]);\n    }\n};\n#line 5 \"sparse_table/sparse_table_2d.hpp\"\
    \n\n// CUT begin\n// Static matrix sparse table\n// Complexity; O(HWlogHlogW)\
    \ for precalculation, O(1) per query\ntemplate <typename T, typename F> struct\
    \ SparseTable2D {\n    int H, lgH, W;\n    T defaultT;\n    F func;\n    std::vector<std::vector<SparseTable<T,\
    \ F>>> data;\n    std::vector<int> lgx_table;\n    SparseTable2D(F func) : func(func)\
    \ {}\n    SparseTable2D(const std::vector<std::vector<T>> &matrix, T defaultT,\
    \ F func) : defaultT(defaultT), func(func) {\n        H = matrix.size(), W = (matrix.size()\
    \ ? matrix[0].size() : 0);\n        lgx_table.resize(H + 1);\n        for (int\
    \ i = 2; i < H + 1; i++) lgx_table[i] = lgx_table[i >> 1] + 1;\n        lgH =\
    \ lgx_table[H] + 1;\n        data.resize(lgH);\n        for (auto v : matrix)\
    \ data[0].emplace_back(SparseTable<T, F>(v, defaultT, func));\n        for (int\
    \ d = 1; d < lgH; d++) {\n            for (int i = 0; i + (1 << d) <= H; i++)\
    \ {\n                std::vector<T> v(W);\n                for (int j = 0; j <\
    \ W; j++) v[j] = func(data[d - 1][i].data[0][j], data[d - 1][i + (1 << (d - 1))].data[0][j]);\n\
    \                data[d].emplace_back(SparseTable<T, F>(v, defaultT, func));\n\
    \            }\n        }\n    }\n    T get(int xl, int xr, int yl, int yr) {\n\
    \        assert(xl >= 0 and xr <= H and yl >= 0 and yr <= W);\n        if (xl\
    \ >= xr) return defaultT;\n        int d = lgx_table[xr - xl];\n        return\
    \ func(data[d][xl].get(yl, yr), data[d][xr - (1 << d)].get(yl, yr));\n    }\n\
    };\n#line 2 \"sparse_table/test/sparse_table_2d.test.cpp\"\n#define PROBLEM \"\
    http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068\"\n// Very slow\
    \ (worst case: 6sec, memory 3GB)\n\n#include <iostream>\nusing namespace std;\n\
    \nint main() {\n    auto f = [](int l, int r) { return min(l, r); };\n    while\
    \ (true) {\n        int H, W, Q;\n        cin >> H >> W >> Q;\n        if (!H)\
    \ break;\n        vector<vector<int>> mat(H, vector<int>(W));\n        for (auto\
    \ &vec : mat)\n            for (auto &x : vec) cin >> x;\n        SparseTable2D<int,\
    \ decltype(f)> rmq(mat, (1LL << 31) - 1, f);\n        while (Q--) {\n        \
    \    int xl, yl, xr, yr;\n            cin >> xl >> yl >> xr >> yr;\n         \
    \   printf(\"%d\\n\", rmq.get(xl, xr + 1, yl, yr + 1));\n        }\n    }\n}\n"
  code: "#include \"../sparse_table_2d.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1068\"\
    \n// Very slow (worst case: 6sec, memory 3GB)\n\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    auto f = [](int l, int r) { return min(l, r); };\n\
    \    while (true) {\n        int H, W, Q;\n        cin >> H >> W >> Q;\n     \
    \   if (!H) break;\n        vector<vector<int>> mat(H, vector<int>(W));\n    \
    \    for (auto &vec : mat)\n            for (auto &x : vec) cin >> x;\n      \
    \  SparseTable2D<int, decltype(f)> rmq(mat, (1LL << 31) - 1, f);\n        while\
    \ (Q--) {\n            int xl, yl, xr, yr;\n            cin >> xl >> yl >> xr\
    \ >> yr;\n            printf(\"%d\\n\", rmq.get(xl, xr + 1, yl, yr + 1));\n  \
    \      }\n    }\n}\n"
  dependsOn:
  - sparse_table/sparse_table_2d.hpp
  - sparse_table/sparse_table.hpp
  isVerificationFile: true
  path: sparse_table/test/sparse_table_2d.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: sparse_table/test/sparse_table_2d.test.cpp
layout: document
redirect_from:
- /verify/sparse_table/test/sparse_table_2d.test.cpp
- /verify/sparse_table/test/sparse_table_2d.test.cpp.html
title: sparse_table/test/sparse_table_2d.test.cpp
---
