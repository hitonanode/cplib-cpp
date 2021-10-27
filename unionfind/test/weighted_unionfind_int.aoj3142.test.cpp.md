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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3142
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3142
  bundledCode: "#line 1 \"unionfind/test/weighted_unionfind_int.aoj3142.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3142\"\
    \n#line 2 \"unionfind/weighted_unionfind.hpp\"\n#include <numeric>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Weighted UnionFind\ntemplate <class S> struct\
    \ WeightedUnionFind {\n    std::vector<int> par, sz;\n    std::vector<S> pot;\n\
    \    WeightedUnionFind(int N = 0) : par(N), sz(N, 1), pot(N) {\n        std::iota(par.begin(),\
    \ par.end(), 0);\n    }\n    int find(int x) {\n        if (par[x] != x) {\n \
    \           int r = find(par[x]);\n            pot[x] = pot[x] + pot[par[x]],\
    \ par[x] = r;\n        }\n        return par[x];\n    }\n    bool unite(int s,\
    \ int t, S rel_diff) {\n        // Relate s and t by f[t] = f[s] + rel_diff\n\
    \        // Return false iff contradiction happens.\n        rel_diff = rel_diff\
    \ + weight(s) + (-weight(t));\n        if ((s = find(s)) == (t = find(t))) return\
    \ rel_diff == 0;\n        if (sz[s] < sz[t]) std::swap(s, t), rel_diff = -rel_diff;\n\
    \        par[t] = s, sz[s] += sz[t], pot[t] = rel_diff;\n        return true;\n\
    \    }\n    S weight(int x) { return find(x), pot[x]; }\n    S diff(int s, int\
    \ t) { return weight(t) + (-weight(s)); } // return f[t] - f[s]\n    int count(int\
    \ x) { return sz[find(x)]; }\n    bool same(int s, int t) { return find(s) ==\
    \ find(t); }\n};\n#line 3 \"unionfind/test/weighted_unionfind_int.aoj3142.test.cpp\"\
    \n#include <algorithm>\n#include <iostream>\n#line 6 \"unionfind/test/weighted_unionfind_int.aoj3142.test.cpp\"\
    \nusing namespace std;\n\nint N;\nvector<vector<int>> to;\nvector<int> A, B;\n\
    WeightedUnionFind<long long> uf;\n\nlong long dfs(int now, int prv) {\n    long\
    \ long acc = B[now] - A[now];\n    for (auto nxt : to[now]) {\n        if (nxt\
    \ != prv) {\n            long long tmp = dfs(nxt, now);\n            uf.unite(nxt,\
    \ now, tmp);\n            acc += tmp;\n        }\n    }\n    return acc;\n}\n\n\
    int main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n    cin >>\
    \ N;\n    uf = WeightedUnionFind<long long>(N);\n    to.resize(N);\n\n    for\
    \ (int e = 0; e < N - 1; e++) {\n        int u, v;\n        cin >> u >> v;\n \
    \       u--, v--;\n        to[u].push_back(v);\n        to[v].push_back(u);\n\
    \    }\n    A.resize(N);\n    B.resize(N);\n    for (auto &x : A) cin >> x;\n\
    \    for (auto &x : B) cin >> x;\n    dfs(0, -1);\n\n    long long sum = 0, lo\
    \ = 1LL << 60;\n    for (int i = 0; i < N; i++) {\n        long long tmp = uf.diff(0,\
    \ i);\n        sum += tmp, lo = lo > tmp ? tmp : lo;\n    }\n    cout << sum -\
    \ lo * N << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=3142\"\
    \n#include \"../weighted_unionfind.hpp\"\n#include <algorithm>\n#include <iostream>\n\
    #include <vector>\nusing namespace std;\n\nint N;\nvector<vector<int>> to;\nvector<int>\
    \ A, B;\nWeightedUnionFind<long long> uf;\n\nlong long dfs(int now, int prv) {\n\
    \    long long acc = B[now] - A[now];\n    for (auto nxt : to[now]) {\n      \
    \  if (nxt != prv) {\n            long long tmp = dfs(nxt, now);\n           \
    \ uf.unite(nxt, now, tmp);\n            acc += tmp;\n        }\n    }\n    return\
    \ acc;\n}\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    cin >> N;\n    uf = WeightedUnionFind<long long>(N);\n    to.resize(N);\n\
    \n    for (int e = 0; e < N - 1; e++) {\n        int u, v;\n        cin >> u >>\
    \ v;\n        u--, v--;\n        to[u].push_back(v);\n        to[v].push_back(u);\n\
    \    }\n    A.resize(N);\n    B.resize(N);\n    for (auto &x : A) cin >> x;\n\
    \    for (auto &x : B) cin >> x;\n    dfs(0, -1);\n\n    long long sum = 0, lo\
    \ = 1LL << 60;\n    for (int i = 0; i < N; i++) {\n        long long tmp = uf.diff(0,\
    \ i);\n        sum += tmp, lo = lo > tmp ? tmp : lo;\n    }\n    cout << sum -\
    \ lo * N << '\\n';\n}\n"
  dependsOn:
  - unionfind/weighted_unionfind.hpp
  isVerificationFile: true
  path: unionfind/test/weighted_unionfind_int.aoj3142.test.cpp
  requiredBy: []
  timestamp: '2021-10-27 23:41:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: unionfind/test/weighted_unionfind_int.aoj3142.test.cpp
layout: document
redirect_from:
- /verify/unionfind/test/weighted_unionfind_int.aoj3142.test.cpp
- /verify/unionfind/test/weighted_unionfind_int.aoj3142.test.cpp.html
title: unionfind/test/weighted_unionfind_int.aoj3142.test.cpp
---
