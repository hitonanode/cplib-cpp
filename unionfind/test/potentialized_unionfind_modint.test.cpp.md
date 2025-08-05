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
    PROBLEM: https://judge.yosupo.jp/problem/unionfind_with_potential
    links:
    - https://judge.yosupo.jp/problem/unionfind_with_potential
  bundledCode: "#line 1 \"unionfind/test/potentialized_unionfind_modint.test.cpp\"\
    \n#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind_with_potential\"\
    \n\n#line 2 \"unionfind/potentialized_unionfind.hpp\"\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\n// Potentialized UnionFind (Weighted UnionFind)\n\
    template <class S> struct PotentializedUnionFind {\n    std::vector<int> par,\
    \ sz;\n    std::vector<S> pot;\n    PotentializedUnionFind(int N = 0) : par(N),\
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
    \ same(int s, int t) { return find(s) == find(t); }\n};\n#line 4 \"unionfind/test/potentialized_unionfind_modint.test.cpp\"\
    \n\n#include <iostream>\nusing namespace std;\n\n#include <atcoder/modint>\nusing\
    \ mint = atcoder::modint998244353;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, Q;\n    cin >> N >> Q;\n    PotentializedUnionFind<mint> uf(N);\n\
    \n    while (Q--) {\n        int t, u, v;\n        cin >> t >> u >> v;\n     \
    \   if (t == 0) {\n            int x;\n            cin >> x;\n            if (uf.same(u,\
    \ v) and uf.diff(v, u) != x) {\n                cout << \"0\\n\";\n          \
    \  } else {\n                cout << \"1\\n\";\n                uf.unite(v, u,\
    \ x);\n            }\n        } else {\n            if (uf.same(u, v)) {\n   \
    \             cout << uf.diff(v, u).val() << '\\n';\n            } else {\n  \
    \              cout << \"-1\\n\";\n            }\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/unionfind_with_potential\"\
    \n\n#include \"../potentialized_unionfind.hpp\"\n\n#include <iostream>\nusing\
    \ namespace std;\n\n#include <atcoder/modint>\nusing mint = atcoder::modint998244353;\n\
    \nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    int\
    \ N, Q;\n    cin >> N >> Q;\n    PotentializedUnionFind<mint> uf(N);\n\n    while\
    \ (Q--) {\n        int t, u, v;\n        cin >> t >> u >> v;\n        if (t ==\
    \ 0) {\n            int x;\n            cin >> x;\n            if (uf.same(u,\
    \ v) and uf.diff(v, u) != x) {\n                cout << \"0\\n\";\n          \
    \  } else {\n                cout << \"1\\n\";\n                uf.unite(v, u,\
    \ x);\n            }\n        } else {\n            if (uf.same(u, v)) {\n   \
    \             cout << uf.diff(v, u).val() << '\\n';\n            } else {\n  \
    \              cout << \"-1\\n\";\n            }\n        }\n    }\n}\n"
  dependsOn:
  - unionfind/potentialized_unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/potentialized_unionfind_modint.test.cpp
  requiredBy: []
  timestamp: '2025-08-05 22:50:49+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/potentialized_unionfind_modint.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/potentialized_unionfind_modint.test.cpp
- /verify/unionfind/test/potentialized_unionfind_modint.test.cpp.html
title: unionfind/test/potentialized_unionfind_modint.test.cpp
---
