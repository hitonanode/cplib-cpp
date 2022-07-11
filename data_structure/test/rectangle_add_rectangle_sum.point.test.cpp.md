---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: data_structure/rectangle_add_rectangle_sum.hpp
    title: "Static rectangle add rectangle sum \uFF08\u77E9\u5F62\u4E00\u69D8\u52A0\
      \u7B97\u30FB\u77E9\u5F62\u7DCF\u548C\u53D6\u5F97\uFF09"
  - icon: ':question:'
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
    PROBLEM: https://judge.yosupo.jp/problem/rectangle_sum
    links:
    - https://judge.yosupo.jp/problem/rectangle_sum
  bundledCode: "#line 1 \"data_structure/test/rectangle_add_rectangle_sum.point.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n#line 2 \"\
    segmenttree/binary_indexed_tree.hpp\"\n#include <algorithm>\n#include <vector>\n\
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
    \    }\n};\n#line 4 \"data_structure/rectangle_add_rectangle_sum.hpp\"\n#include\
    \ <tuple>\n#line 6 \"data_structure/rectangle_add_rectangle_sum.hpp\"\n\n// Static\
    \ rectangle add rectangle sum\n// Calculate sums of rectangular weights inside\
    \ the given rectangles\n// Complexity: O(q log q), q = # of rectangles / queries\n\
    template <class Int, class T> class RectangleAddRectangleSum {\n    struct AddQuery\
    \ {\n        Int xl, xr, yl, yr;\n        T val;\n    };\n    struct SumQuery\
    \ {\n        Int xl, xr, yl, yr;\n    };\n    std::vector<AddQuery> add_queries;\n\
    \    std::vector<SumQuery> sum_queries;\n\npublic:\n    RectangleAddRectangleSum()\
    \ = default;\n\n    // A[x][y] += val for (x, y) in [xl, xr) * [yl, yr)\n    void\
    \ add_rectangle(Int xl, Int xr, Int yl, Int yr, T val) {\n        add_queries.push_back(AddQuery{xl,\
    \ xr, yl, yr, val});\n    }\n\n    // Get sum of A[x][y] for (x, y) in [xl, xr)\
    \ * [yl, yr)\n    void add_query(Int xl, Int xr, Int yl, Int yr) {\n        sum_queries.push_back(SumQuery{xl,\
    \ xr, yl, yr});\n    }\n\n    std::vector<T> solve() const {\n        std::vector<Int>\
    \ ys;\n        for (const auto &a : add_queries) {\n            ys.push_back(a.yl);\n\
    \            ys.push_back(a.yr);\n        }\n        std::sort(ys.begin(), ys.end());\n\
    \        ys.erase(std::unique(ys.begin(), ys.end()), ys.end());\n\n        const\
    \ int Y = ys.size();\n\n        std::vector<std::tuple<Int, int, int>> ops;\n\
    \        for (int q = 0; q < int(sum_queries.size()); ++q) {\n            ops.emplace_back(sum_queries[q].xl,\
    \ 0, q);\n            ops.emplace_back(sum_queries[q].xr, 1, q);\n        }\n\
    \        for (int q = 0; q < int(add_queries.size()); ++q) {\n            ops.emplace_back(add_queries[q].xl,\
    \ 2, q);\n            ops.emplace_back(add_queries[q].xr, 3, q);\n        }\n\
    \        std::sort(ops.begin(), ops.end());\n\n        BIT<T> b00(Y), b01(Y),\
    \ b10(Y), b11(Y);\n        std::vector<T> ret(sum_queries.size());\n        for\
    \ (auto o : ops) {\n            int qtype = std::get<1>(o), q = std::get<2>(o);\n\
    \            if (qtype >= 2) {\n                const AddQuery &query = add_queries.at(q);\n\
    \                int i = std::lower_bound(ys.begin(), ys.end(), query.yl) - ys.begin();\n\
    \                int j = std::lower_bound(ys.begin(), ys.end(), query.yr) - ys.begin();\n\
    \                T x = std::get<0>(o);\n                T yi = query.yl, yj =\
    \ query.yr;\n                if (qtype & 1) std::swap(i, j), std::swap(yi, yj);\n\
    \n                b00.add(i, x * yi * query.val);\n                b01.add(i,\
    \ -x * query.val);\n                b10.add(i, -yi * query.val);\n           \
    \     b11.add(i, query.val);\n                b00.add(j, -x * yj * query.val);\n\
    \                b01.add(j, x * query.val);\n                b10.add(j, yj * query.val);\n\
    \                b11.add(j, -query.val);\n            } else {\n             \
    \   const SumQuery &query = sum_queries.at(q);\n                int i = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yl) - ys.begin();\n                int j = std::lower_bound(ys.begin(),\
    \ ys.end(), query.yr) - ys.begin();\n                T x = std::get<0>(o);\n \
    \               T yi = query.yl, yj = query.yr;\n                if (qtype & 1)\
    \ std::swap(i, j), std::swap(yi, yj);\n\n                ret[q] += b00.sum(i)\
    \ + b01.sum(i) * yi + b10.sum(i) * x + b11.sum(i) * x * yi;\n                ret[q]\
    \ -= b00.sum(j) + b01.sum(j) * yj + b10.sum(j) * x + b11.sum(j) * x * yj;\n  \
    \          }\n        }\n        return ret;\n    }\n};\n#line 3 \"data_structure/test/rectangle_add_rectangle_sum.point.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    RectangleAddRectangleSum<int, unsigned long\
    \ long> rect_sum;\n\n    const int bias = 500000000;\n\n    int N, Q;\n    cin\
    \ >> N >> Q;\n\n    while (N--) {\n        int x, y, w;\n        cin >> x >> y\
    \ >> w;\n        x -= bias;\n        y -= bias;\n        rect_sum.add_rectangle(x,\
    \ x + 1, y, y + 1, w);\n    }\n    while (Q--) {\n        int l, r, d, u;\n  \
    \      cin >> l >> d >> r >> u;\n        l -= bias;\n        d -= bias;\n    \
    \    r -= bias;\n        u -= bias;\n        rect_sum.add_query(l, r, d, u);\n\
    \    }\n\n    auto ret = rect_sum.solve();\n    for (auto x : ret) cout << x <<\
    \ '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rectangle_sum\"\n#include\
    \ \"../rectangle_add_rectangle_sum.hpp\"\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    RectangleAddRectangleSum<int, unsigned long long> rect_sum;\n\n    const\
    \ int bias = 500000000;\n\n    int N, Q;\n    cin >> N >> Q;\n\n    while (N--)\
    \ {\n        int x, y, w;\n        cin >> x >> y >> w;\n        x -= bias;\n \
    \       y -= bias;\n        rect_sum.add_rectangle(x, x + 1, y, y + 1, w);\n \
    \   }\n    while (Q--) {\n        int l, r, d, u;\n        cin >> l >> d >> r\
    \ >> u;\n        l -= bias;\n        d -= bias;\n        r -= bias;\n        u\
    \ -= bias;\n        rect_sum.add_query(l, r, d, u);\n    }\n\n    auto ret = rect_sum.solve();\n\
    \    for (auto x : ret) cout << x << '\\n';\n}\n"
  dependsOn:
  - data_structure/rectangle_add_rectangle_sum.hpp
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: true
  path: data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
  requiredBy: []
  timestamp: '2022-07-05 20:49:30+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
layout: document
redirect_from:
- /verify/data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
- /verify/data_structure/test/rectangle_add_rectangle_sum.point.test.cpp.html
title: data_structure/test/rectangle_add_rectangle_sum.point.test.cpp
---
