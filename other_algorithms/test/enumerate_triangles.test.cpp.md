---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/enumerate_triangles.hpp
    title: "\u7121\u5411\u30B0\u30E9\u30D5\u306B\u542B\u307E\u308C\u308B\u4E09\u89D2\
      \u5F62\u306E\u5217\u6319"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/enumerate_triangles
    links:
    - https://judge.yosupo.jp/problem/enumerate_triangles
  bundledCode: "#line 1 \"other_algorithms/test/enumerate_triangles.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/enumerate_triangles\"\n#line 2 \"\
    other_algorithms/enumerate_triangles.hpp\"\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// CUT begin\n// Enumerate triangles\n// Complexity: O(N\
    \ + M \\sqrt{M})\n// Reference:\n// - https://www.slideshare.net/catupper/trianguler\n\
    struct EnumerateTriangles {\n    int V;\n    std::vector<int> deg;\n    std::vector<std::vector<int>>\
    \ to;\n    std::vector<std::pair<int, int>> edges;\n    EnumerateTriangles(int\
    \ N = 0) : V(N), deg(N), to(N) {}\n    void add_edge(int s, int t) {\n       \
    \ assert(s >= 0 and s < V);\n        assert(t >= 0 and t < V);\n        assert(s\
    \ != t);\n        edges.emplace_back(s, t);\n        deg[s]++, deg[t]++;\n   \
    \ }\n    template <class F> void run(F f) {\n        auto comp = [&](int i, int\
    \ j) { return deg[i] != deg[j] ? deg[i] < deg[j] : i < j; };\n        for (auto\
    \ p : edges) {\n            int s = p.first, t = p.second;\n            if (comp(s,\
    \ t)) {\n                to[s].push_back(t);\n            } else {\n         \
    \       to[t].push_back(s);\n            }\n        }\n        std::vector<char>\
    \ flag(V);\n        for (int i = 0; i < V; i++) {\n            for (auto j : to[i])\
    \ flag[j] = 1;\n            for (auto j : to[i]) {\n                for (auto\
    \ k : to[j]) {\n                    if (flag[k]) f(i, j, k);\n               \
    \ }\n            }\n            for (auto j : to[i]) flag[j] = 0;\n        }\n\
    \    }\n};\n#line 3 \"other_algorithms/test/enumerate_triangles.test.cpp\"\n#include\
    \ <iostream>\n#line 5 \"other_algorithms/test/enumerate_triangles.test.cpp\"\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M;\n    cin >> N >> M;\n    EnumerateTriangles graph(N);\n    vector<unsigned>\
    \ X(N);\n    for (auto &x : X) cin >> x;\n    while (M--) {\n        int u, v;\n\
    \        cin >> u >> v;\n        graph.add_edge(u, v);\n    }\n    unsigned long\
    \ long ret = 0;\n    constexpr unsigned md = 998244353;\n    auto f = [&](int\
    \ i, int j, int k) {\n        (ret += (unsigned long long)X[i] * X[j] % md * X[k])\
    \ %= md;\n    };\n    graph.run(f);\n    cout << ret << '\\n';\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/enumerate_triangles\"\n\
    #include \"../enumerate_triangles.hpp\"\n#include <iostream>\n#include <vector>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \    int N, M;\n    cin >> N >> M;\n    EnumerateTriangles graph(N);\n    vector<unsigned>\
    \ X(N);\n    for (auto &x : X) cin >> x;\n    while (M--) {\n        int u, v;\n\
    \        cin >> u >> v;\n        graph.add_edge(u, v);\n    }\n    unsigned long\
    \ long ret = 0;\n    constexpr unsigned md = 998244353;\n    auto f = [&](int\
    \ i, int j, int k) {\n        (ret += (unsigned long long)X[i] * X[j] % md * X[k])\
    \ %= md;\n    };\n    graph.run(f);\n    cout << ret << '\\n';\n}\n"
  dependsOn:
  - other_algorithms/enumerate_triangles.hpp
  isVerificationFile: true
  path: other_algorithms/test/enumerate_triangles.test.cpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/enumerate_triangles.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/enumerate_triangles.test.cpp
- /verify/other_algorithms/test/enumerate_triangles.test.cpp.html
title: other_algorithms/test/enumerate_triangles.test.cpp
---
