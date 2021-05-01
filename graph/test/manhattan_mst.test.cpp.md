---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/manhattan_mst.hpp
    title: "Manhattan MST \uFF08\u4E8C\u6B21\u5143\u5E73\u9762\u4E0A\u306E\u9802\u70B9\
      \u305F\u3061\u306E\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u306B\u3088\
      \u308B\u6700\u5C0F\u5168\u57DF\u6728\u69CB\u6210\uFF09"
  - icon: ':heavy_check_mark:'
    path: unionfind/unionfind.hpp
    title: unionfind/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/manhattanmst
    links:
    - https://judge.yosupo.jp/problem/manhattanmst
  bundledCode: "#line 1 \"graph/test/manhattan_mst.test.cpp\"\n#define PROBLEM \"\
    https://judge.yosupo.jp/problem/manhattanmst\"\n#line 2 \"unionfind/unionfind.hpp\"\
    \n#include <numeric>\n#include <utility>\n#include <vector>\n\n// CUT begin\n\
    // UnionFind Tree (0-indexed), based on size of each disjoint set\nstruct UnionFind\
    \ {\n    std::vector<int> par, cou;\n    UnionFind(int N = 0) : par(N), cou(N,\
    \ 1) { iota(par.begin(), par.end(), 0); }\n    int find(int x) { return (par[x]\
    \ == x) ? x : (par[x] = find(par[x])); }\n    bool unite(int x, int y) {\n   \
    \     x = find(x), y = find(y);\n        if (x == y) return false;\n        if\
    \ (cou[x] < cou[y]) std::swap(x, y);\n        par[y] = x, cou[x] += cou[y];\n\
    \        return true;\n    }\n    int count(int x) { return cou[find(x)]; }\n\
    \    bool same(int x, int y) { return find(x) == find(y); }\n};\n#line 2 \"graph/manhattan_mst.hpp\"\
    \n#include <algorithm>\n#include <map>\n#include <tuple>\n#line 6 \"graph/manhattan_mst.hpp\"\
    \n\n// Manhattan MST: \u4E8C\u6B21\u5143\u5E73\u9762\u4E0A\u306E\u9802\u70B9\u305F\
    \u3061\u306E\u30DE\u30F3\u30CF\u30C3\u30BF\u30F3\u8DDD\u96E2\u306B\u3088\u308B\
    \ minimum spanning tree \u306E O(N) \u672C\u306E\u5019\u88DC\u8FBA\u3092\u5217\
    \u6319\n// Complexity: O(N log N)\n// output: [(weight_uv, u, v), ...]\n// Verified:\
    \ https://judge.yosupo.jp/problem/manhattanmst, https://www.codechef.com/problems/HKRMAN\n\
    template <typename T> std::vector<std::tuple<T, int, int>> manhattan_mst(std::vector<T>\
    \ xs, std::vector<T> ys) {\n    const int n = xs.size();\n    std::vector<int>\
    \ idx(n);\n    std::iota(idx.begin(), idx.end(), 0);\n    std::vector<std::tuple<T,\
    \ int, int>> ret;\n    for (int s = 0; s < 2; s++) {\n        for (int t = 0;\
    \ t < 2; t++) {\n            auto cmp = [&](int i, int j) { return xs[i] + ys[i]\
    \ < xs[j] + ys[j]; };\n            std::sort(idx.begin(), idx.end(), cmp);\n \
    \           std::map<T, int> sweep;\n            for (int i : idx) {\n       \
    \         for (auto it = sweep.lower_bound(-ys[i]); it != sweep.end(); it = sweep.erase(it))\
    \ {\n                    int j = it->second;\n                    if (xs[i] -\
    \ xs[j] < ys[i] - ys[j]) break;\n                    ret.emplace_back(std::abs(xs[i]\
    \ - xs[j]) + std::abs(ys[i] - ys[j]), i, j);\n                }\n            \
    \    sweep[-ys[i]] = i;\n            }\n            std::swap(xs, ys);\n     \
    \   }\n        for (auto &x : xs) x = -x;\n    }\n    std::sort(ret.begin(), ret.end());\n\
    \    return ret;\n}\n#line 4 \"graph/test/manhattan_mst.test.cpp\"\n\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<int> xs(N), ys(N);\n    for (int i = 0;\
    \ i < N; i++) cin >> xs[i] >> ys[i];\n    UnionFind uf(N);\n    long long weight\
    \ = 0;\n    vector<pair<int, int>> edges;\n    for (auto [w, i, j] : manhattan_mst(xs,\
    \ ys)) {\n        if (uf.unite(i, j)) {\n            weight += w;\n          \
    \  edges.emplace_back(i, j);\n        }\n    }\n    cout << weight << '\\n';\n\
    \    for (auto p : edges) cout << p.first << ' ' << p.second << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/manhattanmst\"\n#include\
    \ \"../../unionfind/unionfind.hpp\"\n#include \"../manhattan_mst.hpp\"\n\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N;\n    cin >> N;\n    vector<int> xs(N), ys(N);\n    for (int i = 0;\
    \ i < N; i++) cin >> xs[i] >> ys[i];\n    UnionFind uf(N);\n    long long weight\
    \ = 0;\n    vector<pair<int, int>> edges;\n    for (auto [w, i, j] : manhattan_mst(xs,\
    \ ys)) {\n        if (uf.unite(i, j)) {\n            weight += w;\n          \
    \  edges.emplace_back(i, j);\n        }\n    }\n    cout << weight << '\\n';\n\
    \    for (auto p : edges) cout << p.first << ' ' << p.second << '\\n';\n}\n"
  dependsOn:
  - unionfind/unionfind.hpp
  - graph/manhattan_mst.hpp
  isVerificationFile: true
  path: graph/test/manhattan_mst.test.cpp
  requiredBy: []
  timestamp: '2021-05-01 16:33:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/manhattan_mst.test.cpp
layout: document
redirect_from:
- /verify/graph/test/manhattan_mst.test.cpp
- /verify/graph/test/manhattan_mst.test.cpp.html
title: graph/test/manhattan_mst.test.cpp
---
