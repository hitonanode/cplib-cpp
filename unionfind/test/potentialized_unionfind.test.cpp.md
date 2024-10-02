---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: unionfind/potentialized_unionfind.hpp
    title: "Potentialized UnionFind \uFF08\u91CD\u307F\u4ED8\u304D UnionFind\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp
  bundledCode: "#line 2 \"unionfind/potentialized_unionfind.hpp\"\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n// Potentialized UnionFind (Weighted\
    \ UnionFind)\ntemplate <class S> struct PotentializedUnionFind {\n    std::vector<int>\
    \ par, sz;\n    std::vector<S> pot;\n    PotentializedUnionFind(int N = 0) : par(N),\
    \ sz(N, 1), pot(N) {\n        std::iota(par.begin(), par.end(), 0);\n    }\n \
    \   int find(int x) {\n        if (par[x] != x) {\n            int r = find(par[x]);\n\
    \            pot[x] = pot[x] + pot[par[x]], par[x] = r;\n        }\n        return\
    \ par[x];\n    }\n    bool unite(int s, int t, S rel_diff) {\n        // Relate\
    \ s and t by f[t] = f[s] + rel_diff\n        // Return false iff contradiction\
    \ happens.\n        rel_diff = rel_diff + weight(s) + (-weight(t));\n        if\
    \ ((s = find(s)) == (t = find(t))) return rel_diff == 0;\n        if (sz[s] <\
    \ sz[t]) std::swap(s, t), rel_diff = -rel_diff;\n        par[t] = s, sz[s] +=\
    \ sz[t], pot[t] = rel_diff;\n        return true;\n    }\n    S weight(int x)\
    \ { return find(x), pot[x]; }\n    S diff(int s, int t) { return weight(t) + (-weight(s));\
    \ } // return f[t] - f[s]\n    int count(int x) { return sz[find(x)]; }\n    bool\
    \ same(int s, int t) { return find(s) == find(t); }\n};\n#line 2 \"unionfind/test/potentialized_unionfind.test.cpp\"\
    \n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int N, Q, x, y, z;\n    cin >> N >>\
    \ Q;\n    PotentializedUnionFind<int> uf(N);\n    for (int i = 0; i < Q; i++)\
    \ {\n        int c;\n        cin >> c;\n        if (c) {\n            cin >> x\
    \ >> y;\n            if (uf.same(x, y)) {\n                cout << uf.diff(x,\
    \ y) << endl;\n            } else {\n                cout << \"?\" << endl;\n\
    \            }\n        } else {\n            cin >> x >> y >> z;\n          \
    \  uf.unite(x, y, z);\n        }\n    }\n}\n"
  code: "#include \"../potentialized_unionfind.hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int N, Q, x, y, z;\n    cin >> N >>\
    \ Q;\n    PotentializedUnionFind<int> uf(N);\n    for (int i = 0; i < Q; i++)\
    \ {\n        int c;\n        cin >> c;\n        if (c) {\n            cin >> x\
    \ >> y;\n            if (uf.same(x, y)) {\n                cout << uf.diff(x,\
    \ y) << endl;\n            } else {\n                cout << \"?\" << endl;\n\
    \            }\n        } else {\n            cin >> x >> y >> z;\n          \
    \  uf.unite(x, y, z);\n        }\n    }\n}\n"
  dependsOn:
  - unionfind/potentialized_unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/potentialized_unionfind.test.cpp
  requiredBy: []
  timestamp: '2024-10-02 23:55:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/potentialized_unionfind.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/potentialized_unionfind.test.cpp
- /verify/unionfind/test/potentialized_unionfind.test.cpp.html
title: unionfind/test/potentialized_unionfind.test.cpp
---
