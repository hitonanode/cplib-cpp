---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: segmenttree/binary_indexed_tree.hpp
    title: segmenttree/binary_indexed_tree.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: other_data_structures/test/range_kth_smallest_offline.test.cpp
    title: other_data_structures/test/range_kth_smallest_offline.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest>
  bundledCode: "#line 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <iostream>\n\
    #include <vector>\n\n// CUT begin\n// 1-indexed BIT (i : [1, len])\ntemplate <typename\
    \ T> struct BIT : std::vector<T> {\n    BIT(int len = 0) : std::vector<T>(len\
    \ + 1) {}\n    void reset() { fill(this->begin(), this->end(), 0); }\n    void\
    \ add(int pos, T v) {\n        while (pos > 0 and pos < (int)this->size()) (*this)[pos]\
    \ += v, pos += pos & -pos;\n    }\n    T sum(int pos) const { // (0, pos]\n  \
    \      T res = 0;\n        while (pos > 0) res += (*this)[pos], pos -= pos & -pos;\n\
    \        return res;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i < (int)bit.size(); i++) {\n            T now = bit.sum(i);\n \
    \           os << now - prv << \",\";\n            prv = now;\n        }\n   \
    \     return os << ']';\n    }\n};\n#line 3 \"other_data_structures/range_kth_smallest_offline.hpp\"\
    \n#include <algorithm>\n#include <cassert>\n#include <numeric>\n#line 7 \"other_data_structures/range_kth_smallest_offline.hpp\"\
    \n\n// Offline solver to find k-th smallest elements in continuous subsequences\n\
    // - Problem statement: <https://judge.yosupo.jp/problem/range_kth_smallest>\n\
    // - Complexity: O((N + Q) lg(N + Q))\nstruct range_kth_smallest {\n    int N;\n\
    \    std::vector<int> idx;\n    std::vector<int> QL, QR, QK;\n    template <typename\
    \ T> range_kth_smallest(const std::vector<T> A) : N(A.size()) {\n        idx.resize(N);\n\
    \        std::iota(idx.begin(), idx.end(), 0);\n        std::sort(idx.begin(),\
    \ idx.end(), [&](int l, int r) { return A[l] < A[r]; });\n    }\n\n    // Add\
    \ a query to find (k + 1)-th smallest value in [l, r)\n    void add_query(int\
    \ l, int r, int k) {\n        assert(l >= 0 and l <= r and r <= N);\n        assert(r\
    \ - l > k);\n        QL.push_back(l), QR.push_back(r), QK.push_back(k);\n    }\n\
    \n    // Solve all queries: ret[q] = (position of the K[q]-th smallest element\
    \ in [L[q], R[q]))\n    std::vector<int> _ret_arg;\n    std::vector<int> solve()\
    \ {\n        const int Q = QL.size();\n        std::vector<int> lo(Q, 0), hi(Q,\
    \ N);\n        std::vector<std::vector<int>> vs(N);\n        while (true) {\n\
    \            bool stop = true;\n            for (int q = 0; q < Q; q++) {\n  \
    \              if (lo[q] + 1 < hi[q]) {\n                    stop = false;\n \
    \                   vs[(lo[q] + hi[q]) / 2].emplace_back(q);\n               \
    \ }\n            }\n            if (stop) break;\n            BIT<int> bit(N);\n\
    \            for (int t = 0; t < N; t++) {\n                for (auto q : vs[t])\
    \ (bit.sum(QR[q]) - bit.sum(QL[q]) <= QK[q] ? lo[q] : hi[q]) = t;\n          \
    \      bit.add(idx[t] + 1, 1);\n                vs[t].clear();\n            }\n\
    \        }\n        _ret_arg.resize(Q);\n        for (int i = 0; i < Q; i++) _ret_arg[i]\
    \ = idx[lo[i]];\n        return _ret_arg;\n    }\n};\n"
  code: "#pragma once\n#include \"../segmenttree/binary_indexed_tree.hpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <numeric>\n#include <vector>\n\n//\
    \ Offline solver to find k-th smallest elements in continuous subsequences\n//\
    \ - Problem statement: <https://judge.yosupo.jp/problem/range_kth_smallest>\n\
    // - Complexity: O((N + Q) lg(N + Q))\nstruct range_kth_smallest {\n    int N;\n\
    \    std::vector<int> idx;\n    std::vector<int> QL, QR, QK;\n    template <typename\
    \ T> range_kth_smallest(const std::vector<T> A) : N(A.size()) {\n        idx.resize(N);\n\
    \        std::iota(idx.begin(), idx.end(), 0);\n        std::sort(idx.begin(),\
    \ idx.end(), [&](int l, int r) { return A[l] < A[r]; });\n    }\n\n    // Add\
    \ a query to find (k + 1)-th smallest value in [l, r)\n    void add_query(int\
    \ l, int r, int k) {\n        assert(l >= 0 and l <= r and r <= N);\n        assert(r\
    \ - l > k);\n        QL.push_back(l), QR.push_back(r), QK.push_back(k);\n    }\n\
    \n    // Solve all queries: ret[q] = (position of the K[q]-th smallest element\
    \ in [L[q], R[q]))\n    std::vector<int> _ret_arg;\n    std::vector<int> solve()\
    \ {\n        const int Q = QL.size();\n        std::vector<int> lo(Q, 0), hi(Q,\
    \ N);\n        std::vector<std::vector<int>> vs(N);\n        while (true) {\n\
    \            bool stop = true;\n            for (int q = 0; q < Q; q++) {\n  \
    \              if (lo[q] + 1 < hi[q]) {\n                    stop = false;\n \
    \                   vs[(lo[q] + hi[q]) / 2].emplace_back(q);\n               \
    \ }\n            }\n            if (stop) break;\n            BIT<int> bit(N);\n\
    \            for (int t = 0; t < N; t++) {\n                for (auto q : vs[t])\
    \ (bit.sum(QR[q]) - bit.sum(QL[q]) <= QK[q] ? lo[q] : hi[q]) = t;\n          \
    \      bit.add(idx[t] + 1, 1);\n                vs[t].clear();\n            }\n\
    \        }\n        _ret_arg.resize(Q);\n        for (int i = 0; i < Q; i++) _ret_arg[i]\
    \ = idx[lo[i]];\n        return _ret_arg;\n    }\n};\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: false
  path: other_data_structures/range_kth_smallest_offline.hpp
  requiredBy: []
  timestamp: '2020-11-19 23:44:18+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - other_data_structures/test/range_kth_smallest_offline.test.cpp
documentation_of: other_data_structures/range_kth_smallest_offline.hpp
layout: document
redirect_from:
- /library/other_data_structures/range_kth_smallest_offline.hpp
- /library/other_data_structures/range_kth_smallest_offline.hpp.html
title: other_data_structures/range_kth_smallest_offline.hpp
---
