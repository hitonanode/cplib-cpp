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
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B
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
    \        }\n        return os << ']';\n    }\n};\n#line 2 \"segmenttree/test/binary_indexed_tree.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n#line 4 \"segmenttree/test/binary_indexed_tree.test.cpp\"\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N, Q;\n    cin >> N >> Q;\n    BIT<int> bit(N);\n    while (Q--) {\n       \
    \ int c, x, y;\n        cin >> c >> x >> y;\n        if (c) {\n            cout\
    \ << bit.sum(x - 1, y) << '\\n';\n        } else {\n            bit.add(x - 1,\
    \ y);\n        }\n    }\n}\n"
  code: "#include \"../binary_indexed_tree.hpp\"\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_B\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N, Q;\n    cin >> N >> Q;\n    BIT<int>\
    \ bit(N);\n    while (Q--) {\n        int c, x, y;\n        cin >> c >> x >> y;\n\
    \        if (c) {\n            cout << bit.sum(x - 1, y) << '\\n';\n        }\
    \ else {\n            bit.add(x - 1, y);\n        }\n    }\n}\n"
  dependsOn:
  - segmenttree/binary_indexed_tree.hpp
  isVerificationFile: true
  path: segmenttree/test/binary_indexed_tree.test.cpp
  requiredBy: []
  timestamp: '2021-01-01 16:52:32+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: segmenttree/test/binary_indexed_tree.test.cpp
layout: document
redirect_from:
- /verify/segmenttree/test/binary_indexed_tree.test.cpp
- /verify/segmenttree/test/binary_indexed_tree.test.cpp.html
title: segmenttree/test/binary_indexed_tree.test.cpp
---
