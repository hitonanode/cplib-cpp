---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/diameter.hpp
    title: "Tree diameter \uFF08\u6728\u306E\u76F4\u5F84\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/tree_diameter
    links:
    - https://judge.yosupo.jp/problem/tree_diameter
  bundledCode: "#line 1 \"tree/test/diameter.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\
    \n#line 2 \"tree/diameter.hpp\"\n#include <algorithm>\n#include <cassert>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n// CUT begin\n// \u6728\u306E\
    \u76F4\u5F84\u3068\uFF0C\u3053\u308C\u3092\u306A\u3059\u30D1\u30B9\u306E\u9802\
    \u70B9\u3092\u51FA\u529B\ntemplate <class Weight> struct TreeDiameter {\n    int\
    \ n;\n    std::vector<std::vector<std::pair<int, Weight>>> to;\n    std::vector<int>\
    \ prev;\n    std::vector<Weight> dist;\n    TreeDiameter(int V) : n(V), to(V),\
    \ prev(V), dist(V) {}\n    void add_edge(int s, int t, Weight w) {\n        assert(0\
    \ <= s and s < n);\n        assert(0 <= t and t < n);\n        to[s].emplace_back(t,\
    \ w);\n        to[t].emplace_back(s, w);\n    }\n    int argdmax;\n    Weight\
    \ dmax;\n    void dfs(int now, int prv) {\n        if (dmax < dist[now]) dmax\
    \ = dist[now], argdmax = now;\n        for (auto p : to[now]) {\n            int\
    \ nxt;\n            Weight w;\n            std::tie(nxt, w) = p;\n           \
    \ if (nxt == prv) continue;\n            prev[nxt] = now;\n            dist[nxt]\
    \ = dist[now] + w;\n            dfs(nxt, now);\n        }\n    }\n    std::pair<Weight,\
    \ std::vector<int>> get_diameter_edges(int root = 0) {\n        prev[root] = -1;\n\
    \        dist[root] = 0;\n        dmax = 0, argdmax = root;\n        dfs(root,\
    \ -1);\n        dmax = 0, prev[argdmax] = -1, dist[argdmax] = 0;\n        dfs(argdmax,\
    \ -1);\n        std::vector<int> ret;\n        while (argdmax >= 0) {\n      \
    \      ret.push_back(argdmax);\n            argdmax = prev[argdmax];\n       \
    \ }\n        return {dmax, ret};\n    }\n};\n#line 3 \"tree/test/diameter.test.cpp\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n    int N;\n    cin >> N;\n    TreeDiameter<long\
    \ long> tree(N);\n    for (int i = 0; i < N - 1; i++) {\n        int a, b, c;\n\
    \        cin >> a >> b >> c;\n        tree.add_edge(a, b, c);\n    }\n    auto\
    \ ret = tree.get_diameter_edges();\n    cout << ret.first << ' ' << ret.second.size()\
    \ << '\\n';\n    for (auto x : ret.second) cout << x << ' ';\n    cout << '\\\
    n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/tree_diameter\"\n#include\
    \ \"../diameter.hpp\"\n#include <iostream>\nusing namespace std;\n\nint main()\
    \ {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n    int N;\n    cin >>\
    \ N;\n    TreeDiameter<long long> tree(N);\n    for (int i = 0; i < N - 1; i++)\
    \ {\n        int a, b, c;\n        cin >> a >> b >> c;\n        tree.add_edge(a,\
    \ b, c);\n    }\n    auto ret = tree.get_diameter_edges();\n    cout << ret.first\
    \ << ' ' << ret.second.size() << '\\n';\n    for (auto x : ret.second) cout <<\
    \ x << ' ';\n    cout << '\\n';\n}\n"
  dependsOn:
  - tree/diameter.hpp
  isVerificationFile: true
  path: tree/test/diameter.test.cpp
  requiredBy: []
  timestamp: '2021-06-09 00:31:07+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/diameter.test.cpp
layout: document
redirect_from:
- /verify/tree/test/diameter.test.cpp
- /verify/tree/test/diameter.test.cpp.html
title: tree/test/diameter.test.cpp
---
