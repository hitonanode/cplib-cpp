---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: unionfind/weighted_unionfind.hpp
    title: "Weighted UnionFind \uFF08\u91CD\u307F\u4ED8\u304D UnionFind\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    ERROR: '1'
    PROBLEM: https://yukicoder.me/problems/no/1420
    links:
    - https://yukicoder.me/problems/no/1420
  bundledCode: "#line 1 \"unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1420\"\n#define ERROR 1 //\
    \ Check only whether the answer is -1 or not\n#line 2 \"unionfind/weighted_unionfind.hpp\"\
    \n#include <numeric>\n#include <utility>\n#include <vector>\n\n// CUT begin\n\
    // Weighted UnionFind\ntemplate <class S> struct WeightedUnionFind {\n    std::vector<int>\
    \ par, sz;\n    std::vector<S> pot;\n    WeightedUnionFind(int N = 0) : par(N),\
    \ sz(N, 1), pot(N) { std::iota(par.begin(), par.end(), 0); }\n    int find(int\
    \ x) {\n        if (par[x] != x) {\n            int r = find(par[x]);\n      \
    \      pot[x] = pot[x] + pot[par[x]], par[x] = r;\n        }\n        return par[x];\n\
    \    }\n    bool unite(int s, int t, S rel_diff) {\n        // Relate s and t\
    \ by t = s + rel_diff\n        // Return false iff contradiction happens.\n  \
    \      rel_diff = rel_diff + weight(s) + (-weight(t));\n        if ((s = find(s))\
    \ == (t = find(t))) return rel_diff == 0;\n        if (sz[s] < sz[t]) std::swap(s,\
    \ t), rel_diff = -rel_diff;\n        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;\n\
    \        return true;\n    }\n    S weight(int x) { return find(x), pot[x]; }\n\
    \    S diff(int s, int t) { return weight(t) + (-weight(s)); }\n    int count(int\
    \ x) { return sz[find(x)]; }\n    bool same(int s, int t) { return find(s) ==\
    \ find(t); }\n};\n\ntemplate <typename Int> struct F2vec {\n    Int val;\n   \
    \ F2vec(Int x = 0) : val(x) {}\n    F2vec operator+(const F2vec &y) const { return\
    \ F2vec(y.val ^ val); }\n    F2vec operator-() const { return *this; }\n    bool\
    \ operator==(const F2vec &x) const { return val == x.val; }\n    template <class\
    \ OStream> friend OStream &operator<<(OStream &os, const F2vec &x) { return os\
    \ << x.val; }\n};\n#line 4 \"unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M;\n    cin >> N >> M;\n\n    WeightedUnionFind<F2vec<unsigned>>\
    \ uf(N);\n    while (M--) {\n        int a, b, y;\n        cin >> a >> b >> y;\n\
    \        a--, b--;\n        if (!uf.unite(a, b, y)) {\n            cout << \"\
    -1\\n\";\n            return 0;\n        }\n    }\n    for (int i = 0; i < N;\
    \ i++) cout << uf.weight(i) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1420\"\n#define ERROR\
    \ 1 // Check only whether the answer is -1 or not\n#include \"../weighted_unionfind.hpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N, M;\n    cin >> N >> M;\n\n    WeightedUnionFind<F2vec<unsigned>>\
    \ uf(N);\n    while (M--) {\n        int a, b, y;\n        cin >> a >> b >> y;\n\
    \        a--, b--;\n        if (!uf.unite(a, b, y)) {\n            cout << \"\
    -1\\n\";\n            return 0;\n        }\n    }\n    for (int i = 0; i < N;\
    \ i++) cout << uf.weight(i) << '\\n';\n}\n"
  dependsOn:
  - unionfind/weighted_unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp
  requiredBy: []
  timestamp: '2021-07-31 00:27:36+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp
- /verify/unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp.html
title: unionfind/test/weighted_unionfind_F2.yuki1420.test.cpp
---
