---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/range_kth_smallest_offline.hpp
    title: data_structure/range_kth_smallest_offline.hpp
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
    PROBLEM: https://judge.yosupo.jp/problem/range_kth_smallest
    links:
    - https://judge.yosupo.jp/problem/range_kth_smallest
  bundledCode: "#line 1 \"data_structure/test/range_kth_smallest_offline.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n#line\
    \ 2 \"segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n#include <vector>\n\
    \n// CUT begin\n// 0-indexed BIT (binary indexed tree / Fenwick tree) (i : [0,\
    \ len))\ntemplate <class T> struct BIT {\n    int n;\n    std::vector<T> data;\n\
    \    BIT(int len = 0) : n(len), data(len) {}\n    void reset() { std::fill(data.begin(),\
    \ data.end(), T(0)); }\n    void add(int pos, T v) { // a[pos] += v\n        pos++;\n\
    \        while (pos > 0 and pos <= n) data[pos - 1] += v, pos += pos & -pos;\n\
    \    }\n    T sum(int k) const { // a[0] + ... + a[k - 1]\n        T res = 0;\n\
    \        while (k > 0) res += data[k - 1], k -= k & -k;\n        return res;\n\
    \    }\n\n    T sum(int l, int r) const { return sum(r) - sum(l); } // a[l] +\
    \ ... + a[r - 1]\n\n    template <class OStream> friend OStream &operator<<(OStream\
    \ &os, const BIT &bit) {\n        T prv = 0;\n        os << '[';\n        for\
    \ (int i = 1; i <= bit.n; i++) {\n            T now = bit.sum(i);\n          \
    \  os << now - prv << ',', prv = now;\n        }\n        return os << ']';\n\
    \    }\n};\n#line 4 \"data_structure/range_kth_smallest_offline.hpp\"\n#include\
    \ <cassert>\n#include <numeric>\n#line 7 \"data_structure/range_kth_smallest_offline.hpp\"\
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
    \            for (int t = 0; t < N; t++) {\n                for (auto q : vs[t])\n\
    \                    (bit.sum(QR[q]) - bit.sum(QL[q]) <= QK[q] ? lo[q] : hi[q])\
    \ = t;\n                bit.add(idx[t], 1);\n                vs[t].clear();\n\
    \            }\n        }\n        _ret_arg.resize(Q);\n        for (int i = 0;\
    \ i < Q; i++) _ret_arg[i] = idx[lo[i]];\n        return _ret_arg;\n    }\n};\n\
    #line 3 \"data_structure/test/range_kth_smallest_offline.test.cpp\"\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) cin >> x;\n    range_kth_smallest solver(A);\n    while (Q--) {\n  \
    \      int l, r, k;\n        cin >> l >> r >> k;\n        solver.add_query(l,\
    \ r, k);\n    }\n    solver.solve();\n    for (auto i : solver.solve()) cout <<\
    \ A[i] << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/range_kth_smallest\"\n\
    #include \"../range_kth_smallest_offline.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int N, Q;\n    cin >> N >> Q;\n    std::vector<int> A(N);\n    for (auto\
    \ &x : A) cin >> x;\n    range_kth_smallest solver(A);\n    while (Q--) {\n  \
    \      int l, r, k;\n        cin >> l >> r >> k;\n        solver.add_query(l,\
    \ r, k);\n    }\n    solver.solve();\n    for (auto i : solver.solve()) cout <<\
    \ A[i] << '\\n';\n}\n"
  dependsOn:
  - data_structure/range_kth_smallest_offline.hpp
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: true
  path: data_structure/test/range_kth_smallest_offline.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/range_kth_smallest_offline.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/range_kth_smallest_offline.test.cpp
- /verify/data_structure/test/range_kth_smallest_offline.test.cpp.html
title: data_structure/test/range_kth_smallest_offline.test.cpp
---
