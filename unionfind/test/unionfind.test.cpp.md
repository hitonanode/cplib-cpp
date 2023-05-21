---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: unionfind/unionfind.hpp
    title: unionfind/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp
  bundledCode: "#line 2 \"unionfind/unionfind.hpp\"\n#include <algorithm>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// UnionFind\
    \ Tree (0-indexed), based on size of each disjoint set\nstruct UnionFind {\n \
    \   std::vector<int> par, cou;\n    UnionFind(int N = 0) : par(N), cou(N, 1) {\
    \ iota(par.begin(), par.end(), 0); }\n    int find(int x) { return (par[x] ==\
    \ x) ? x : (par[x] = find(par[x])); }\n    bool unite(int x, int y) {\n      \
    \  x = find(x), y = find(y);\n        if (x == y) return false;\n        if (cou[x]\
    \ < cou[y]) std::swap(x, y);\n        par[y] = x, cou[x] += cou[y];\n        return\
    \ true;\n    }\n    int count(int x) { return cou[find(x)]; }\n    bool same(int\
    \ x, int y) { return find(x) == find(y); }\n    std::vector<std::vector<int>>\
    \ groups() {\n        std::vector<std::vector<int>> ret(par.size());\n       \
    \ for (int i = 0; i < int(par.size()); ++i) ret[find(i)].push_back(i);\n     \
    \   ret.erase(std::remove_if(ret.begin(), ret.end(),\n                       \
    \          [&](const std::vector<int> &v) { return v.empty(); }),\n          \
    \        ret.end());\n        return ret;\n    }\n};\n#line 2 \"unionfind/test/unionfind.test.cpp\"\
    \n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n  \
    \  UnionFind uf(n);\n    for (int i = 0; i < q; i++) {\n        int c, x, y;\n\
    \        cin >> c >> x >> y;\n        if (c)\n            cout << (int)uf.same(x,\
    \ y) << endl;\n        else\n            uf.unite(x, y);\n    }\n}\n"
  code: "#include \"../unionfind.hpp\"\n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_A&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int n, q;\n    cin >> n >> q;\n  \
    \  UnionFind uf(n);\n    for (int i = 0; i < q; i++) {\n        int c, x, y;\n\
    \        cin >> c >> x >> y;\n        if (c)\n            cout << (int)uf.same(x,\
    \ y) << endl;\n        else\n            uf.unite(x, y);\n    }\n}\n"
  dependsOn:
  - unionfind/unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/unionfind.test.cpp
  requiredBy: []
  timestamp: '2022-04-30 19:41:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/unionfind.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/unionfind.test.cpp
- /verify/unionfind/test/unionfind.test.cpp.html
title: unionfind/test/unionfind.test.cpp
---
