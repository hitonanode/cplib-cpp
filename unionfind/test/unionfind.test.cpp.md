---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: unionfind/unionfind.hpp
    title: unionfind/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
  bundledCode: "#line 2 \"unionfind/unionfind.hpp\"\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// UnionFind Tree (0-indexed),\
    \ based on size of each disjoint set\nstruct UnionFind {\n    std::vector<int>\
    \ par, cou;\n    UnionFind(int N = 0) : par(N), cou(N, 1) { iota(par.begin(),\
    \ par.end(), 0); }\n    int find(int x) { return (par[x] == x) ? x : (par[x] =\
    \ find(par[x])); }\n    bool unite(int x, int y) {\n        x = find(x), y = find(y);\n\
    \        if (x == y) return false;\n        if (cou[x] < cou[y]) std::swap(x,\
    \ y);\n        par[y] = x, cou[x] += cou[y];\n        return true;\n    }\n  \
    \  int count(int x) { return cou[find(x)]; }\n    bool same(int x, int y) { return\
    \ find(x) == find(y); }\n};\n#line 2 \"unionfind/test/unionfind.test.cpp\"\n#include\
    \ <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n  \
    \  UnionFind uf(n);\n    for (int i = 0; i < q; i++) {\n        int c, x, y;\n\
    \        cin >> c >> x >> y;\n        if (c)\n            cout << (int)uf.same(x,\
    \ y) << endl;\n        else\n            uf.unite(x, y);\n    }\n}\n"
  code: "#include \"unionfind/unionfind.hpp\"\n#include <iostream>\n#define PROBLEM\
    \ \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n  \
    \  UnionFind uf(n);\n    for (int i = 0; i < q; i++) {\n        int c, x, y;\n\
    \        cin >> c >> x >> y;\n        if (c)\n            cout << (int)uf.same(x,\
    \ y) << endl;\n        else\n            uf.unite(x, y);\n    }\n}\n"
  dependsOn:
  - unionfind/unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/unionfind.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: unionfind/test/unionfind.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/unionfind.test.cpp
- /verify/unionfind/test/unionfind.test.cpp.html
title: unionfind/test/unionfind.test.cpp
---
