---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: unionfind/weighted_unionfind.hpp
    title: unionfind/weighted_unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp
  bundledCode: "#line 2 \"unionfind/weighted_unionfind.hpp\"\n#include <numeric>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Weighted UnionFind\n\
    template <typename T> struct WeightedUnionFind {\n    std::vector<int> par, sz;\n\
    \    std::vector<T> pot;\n    WeightedUnionFind(int N = 0) : par(N), sz(N, 1),\
    \ pot(N) { std::iota(par.begin(), par.end(), 0); }\n    int find(int x) {\n  \
    \      if (par[x] != x) {\n            int r = find(par[x]);\n            pot[x]\
    \ = pot[x] + pot[par[x]], par[x] = r;\n        }\n        return par[x];\n   \
    \ }\n    bool unite(int s, int t, T rel_diff) {\n        // Relate s and t by\
    \ t = s + rel_diff\n        // Return false iff contradiction happens.\n     \
    \   rel_diff = rel_diff + weight(s) + (-weight(t));\n        if ((s = find(s))\
    \ == (t = find(t))) return rel_diff == 0;\n        if (sz[s] < sz[t]) std::swap(s,\
    \ t), rel_diff = -rel_diff;\n        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;\n\
    \        return true;\n    }\n    T weight(int x) {\n        find(x);\n      \
    \  return pot[x];\n    }\n    T diff(int s, int t) { return weight(t) + (-weight(s));\
    \ }\n    int count(int x) { return sz[find(x)]; }\n    bool same(int s, int t)\
    \ { return find(s) == find(t); }\n};\n\n// sample data structure T for WeightedUnionFind<T>\n\
    /*\nstruct Monoid {\n    int data;\n    Monoid() : data(0) {}\n    Monoid(int\
    \ d) : data(d) {}\n    Monoid operator+(const Monoid &x) const { return Monoid(this->data\
    \ + x.data); }\n    Monoid operator-() const { return Monoid(-data); }\n    bool\
    \ operator==(const Monoid &x) const { return data == x.data; }\n};\nWeightedUnionFind<Monoid>\
    \ wuf(10000);\n*/\n#line 2 \"unionfind/test/weighted_unionfind.test.cpp\"\n#include\
    \ <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int N, Q, x, y, z;\n    cin >> N >>\
    \ Q;\n    WeightedUnionFind<int> uf(N);\n    for (int i = 0; i < Q; i++) {\n \
    \       int c;\n        cin >> c;\n        if (c) {\n            cin >> x >> y;\n\
    \            if (uf.same(x, y)) {\n                cout << uf.diff(x, y) << endl;\n\
    \            } else {\n                cout << \"?\" << endl;\n            }\n\
    \        } else {\n            cin >> x >> y >> z;\n            uf.unite(x, y,\
    \ z);\n        }\n    }\n}\n"
  code: "#include \"unionfind/weighted_unionfind.hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_1_B&lang=jp\"\
    \nusing namespace std;\n\nint main() {\n    int N, Q, x, y, z;\n    cin >> N >>\
    \ Q;\n    WeightedUnionFind<int> uf(N);\n    for (int i = 0; i < Q; i++) {\n \
    \       int c;\n        cin >> c;\n        if (c) {\n            cin >> x >> y;\n\
    \            if (uf.same(x, y)) {\n                cout << uf.diff(x, y) << endl;\n\
    \            } else {\n                cout << \"?\" << endl;\n            }\n\
    \        } else {\n            cin >> x >> y >> z;\n            uf.unite(x, y,\
    \ z);\n        }\n    }\n}\n"
  dependsOn:
  - unionfind/weighted_unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/weighted_unionfind.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/weighted_unionfind.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/weighted_unionfind.test.cpp
- /verify/unionfind/test/weighted_unionfind.test.cpp.html
title: unionfind/test/weighted_unionfind.test.cpp
---
