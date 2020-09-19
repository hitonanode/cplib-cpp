---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: unionfind/unionfind_rankbased.hpp
    title: unionfind/unionfind_rankbased.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
  bundledCode: "#line 1 \"unionfind/test/unionfind_plain.test.cpp\"\n#include <iostream>\n\
    #line 2 \"unionfind/unionfind_rankbased.hpp\"\n#include <numeric>\n#include <vector>\n\
    \n// CUT begin\n// UnionFind Tree (0-indexed)\nstruct RankBasedUnionFind\n{\n\
    \    std::vector<int> par, rank;\n    RankBasedUnionFind(int N = 0): par(N), rank(N)\
    \ {\n        iota(par.begin(), par.end(), 0);\n    }\n    int find(int x) { return\
    \ (par[x] == x) ? x : (par[x] = find(par[x])); }\n    bool unite(int x, int y)\
    \ {\n        x = find(x), y = find(y);\n        if (x == y) return false;\n  \
    \      if (rank[x] < rank[y]) par[x] = y;\n        else par[y] = x;\n        if\
    \ (rank[x] == rank[y]) rank[x]++;\n        return true;\n    }\n    bool same(int\
    \ x, int y) { return find(x) == find(y); }\n};\n#line 3 \"unionfind/test/unionfind_plain.test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp\"\
    \nusing namespace std;\n\n\nint main()\n{\n    int n, q;\n    cin >> n >> q;\n\
    \    RankBasedUnionFind uf(n);\n    for (int i = 0; i < q; i++)\n    {\n     \
    \   int c, x, y;\n        cin >> c >> x >> y;\n        if (c) cout << (int)uf.same(x,\
    \ y) << endl;\n        else uf.unite(x, y);\n    }\n}\n"
  code: "#include <iostream>\n#include \"unionfind/unionfind_rankbased.hpp\"\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp\"\
    \nusing namespace std;\n\n\nint main()\n{\n    int n, q;\n    cin >> n >> q;\n\
    \    RankBasedUnionFind uf(n);\n    for (int i = 0; i < q; i++)\n    {\n     \
    \   int c, x, y;\n        cin >> c >> x >> y;\n        if (c) cout << (int)uf.same(x,\
    \ y) << endl;\n        else uf.unite(x, y);\n    }\n}\n"
  dependsOn:
  - unionfind/unionfind_rankbased.hpp
  isVerificationFile: true
  path: unionfind/test/unionfind_plain.test.cpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/unionfind_plain.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/unionfind_plain.test.cpp
- /verify/unionfind/test/unionfind_plain.test.cpp.html
title: unionfind/test/unionfind_plain.test.cpp
---
