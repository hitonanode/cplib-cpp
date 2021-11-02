---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: sparse_table/disjoint_sparse_table.hpp
    title: Disjoint sparse table
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"sparse_table/disjoint_sparse_table.hpp\"\n#include <algorithm>\n\
    #include <cassert>\n#include <vector>\n\n// CUT begin\n// Disjoint sparse table\n\
    // https://discuss.codechef.com/t/tutorial-disjoint-sparse-table/17404\n// https://drken1215.hatenablog.com/entry/2018/09/08/162600\n\
    // Complexity: O(NlogN) for precalculation, O(1) per query\n// - get(l, r): return\
    \ op(x_l, ..., x_{r - 1})\ntemplate <class S, S (*op)(S, S)> struct disj_sparse_table\
    \ {\n    int N, sz;\n    std::vector<std::vector<S>> d;\n    static int _msb(int\
    \ x) noexcept { return x == 0 ? 0 : (__builtin_clz(x) ^ 31); }\n    disj_sparse_table()\
    \ = default;\n    disj_sparse_table(const std::vector<S> &seq) : N(seq.size())\
    \ {\n        sz = 1 << (_msb(N - 1) + 1);\n        d.assign(_msb(sz) + 1, std::vector<S>(sz));\n\
    \        std::copy(seq.begin(), seq.end(), d[0].begin());\n\n        for (int\
    \ h = 1, half = 2; half < N; ++h, half <<= 1) {\n            for (int i = half;\
    \ i < sz; i += half * 2) {\n                d[h][i - 1] = d[0][i - 1];\n     \
    \           for (int j = i - 2; j >= i - half; --j) d[h][j] = op(d[0][j], d[h][j\
    \ + 1]);\n                d[h][i] = d[0][i];\n                for (int j = i +\
    \ 1; j < i + half; ++j) d[h][j] = op(d[h][j - 1], d[0][j]);\n            }\n \
    \       }\n    }\n    // [l, r), 0-indexed\n    S prod(int l, int r) const {\n\
    \        assert(l >= 0 and r <= N and l < r);\n        if (l + 1 == r) return\
    \ d[0][l];\n        int h = _msb(l ^ (r - 1));\n        return op(d[h][l], d[h][r\
    \ - 1]);\n    }\n};\n#line 3 \"sparse_table/disjoint_sparse_table_2d.hpp\"\n\n\
    template <class S, S (*op)(S, S)> class disj_sparse_table_2d {}\n"
  code: '#pragma once

    #include "disjoint_sparse_table.hpp"


    template <class S, S (*op)(S, S)> class disj_sparse_table_2d {}

    '
  dependsOn:
  - sparse_table/disjoint_sparse_table.hpp
  isVerificationFile: false
  path: sparse_table/disjoint_sparse_table_2d.hpp
  requiredBy: []
  timestamp: '2021-11-02 23:36:31+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: sparse_table/disjoint_sparse_table_2d.hpp
layout: document
redirect_from:
- /library/sparse_table/disjoint_sparse_table_2d.hpp
- /library/sparse_table/disjoint_sparse_table_2d.hpp.html
title: sparse_table/disjoint_sparse_table_2d.hpp
---
