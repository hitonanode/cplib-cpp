---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching.hpp
    title: graph/bipartite_matching.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/bipartitematching
    links:
    - https://judge.yosupo.jp/problem/bipartitematching
  bundledCode: "#line 2 \"graph/bipartite_matching.hpp\"\n#include <cassert>\n#include\
    \ <iostream>\n#include <vector>\n#include <queue>\n\n// CUT begin\n// Bipartite\
    \ matching of undirected bipartite graph (Hopcroft-Karp)\n// <https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html>\n\
    // Comprexity: O(EsqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching\n{\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No parter)\n  \
    \  std::vector<int> used, vv;        //\n    std::vector<int> color;         \
    \  // color of each node(checking bipartition): 0/1/-1(not determined)\n\n   \
    \ BipartiteMatching() = default;\n    BipartiteMatching(int V_) : V(V_), to(V_),\
    \ match(V_, -1), used(V_), color(V_, -1) {}\n\n    void add_edge(int u, int v)\n\
    \    {\n        assert(u >= 0 and u < V and v >= 0 and v < V and u != v);\n  \
    \      to[u].push_back(v);\n        to[v].push_back(u);\n    }\n\n    void bfs()\n\
    \    {\n        dist.assign(V, -1);\n        std::queue<int> q;\n        for (int\
    \ i = 0; i < V; i++) {\n            if (!color[i] and !used[i]) {\n          \
    \      q.emplace(i), dist[i] = 0;\n            }\n        }\n\n        while (!q.empty())\
    \ {\n            int now = q.front();\n            q.pop();\n            for (auto\
    \ nxt : to[now]) {\n                int c = match[nxt];\n                if (c\
    \ >= 0 and dist[c] == -1) {\n                    q.emplace(c), dist[c] = dist[now]\
    \ + 1;\n                }\n            }\n        }\n    }\n\n    bool dfs(int\
    \ now)\n    {\n        vv[now] = true;\n        for (auto nxt : to[now]) {\n \
    \           int c = match[nxt];\n            if (c < 0 or (!vv[c] and dist[c]\
    \ == dist[now] + 1 and dfs(c))) {\n                match[nxt] = now, match[now]\
    \ = nxt;\n                used[now] = true;\n                return true;\n  \
    \          }\n        }\n        return false;\n    }\n\n    bool _color_bfs(int\
    \ root)\n    {\n        color[root] = 0;\n        std::queue<int> q;\n       \
    \ q.emplace(root);\n        while (!q.empty()) {\n            int now = q.front(),\
    \ c = color[now];\n            q.pop();\n            for (auto nxt : to[now])\n\
    \            if (color[nxt] == -1) color[nxt] = !c, q.emplace(nxt);\n        \
    \    else if (color[nxt] == c) return false;\n        }\n        return true;\n\
    \    }\n\n    int solve()\n    {\n        for (int i = 0; i < V; i++) if (color[i]\
    \ == -1) {\n            if (!_color_bfs(i)) return -1;\n        }\n        int\
    \ ret = 0;\n        while (true) {\n            bfs();\n            vv.assign(V,\
    \ false);\n            int flow = 0;\n            for (int i = 0; i < V; i++)\
    \ if (!color[i] and !used[i] and dfs(i)) flow++;\n            if (!flow) break;\n\
    \            ret += flow;\n        }\n        return ret;\n    }\n\n    friend\
    \ std::ostream &operator<<(std::ostream &os, const BipartiteMatching &bm)\n  \
    \  {\n        os << \"{N=\" << bm.V  << ':';\n        for (int i = 0; i < bm.V;\
    \ i++) if (bm.match[i] > i)\n        {\n            os << '(' << i << '-' << bm.match[i]\
    \ << \"),\";\n        }\n        os << '}';\n        return os;\n    }\n};\n#line\
    \ 2 \"graph/test/bipartite_matching.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\
    \n\n#include <algorithm>\n#include <numeric>\n#include <random>\n\nint main()\
    \ {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\n    int L,\
    \ R, M;\n    std::cin >> L >> R >> M;\n\n    std::vector<int> perm(L + R), perm_inv(L\
    \ + R);\n    std::iota(perm.begin(), perm.end(), 0);\n    std::random_device rd;\n\
    \    std::mt19937 g(rd());\n    std::shuffle(perm.begin(), perm.end(), g);\n \
    \   for (int i = 0; i < L + R; i++) { perm_inv[perm[i]] = i; }\n\n    BipartiteMatching\
    \ bm(L + R);\n    while (M--) {\n        int a, b;\n        std::cin >> a >> b;\n\
    \        bm.add_edge(perm[a], perm[L + b]);\n    }\n\n    std::cout << bm.solve()\
    \ << '\\n';\n    for (int j = 0; j < L + R; j++)\n        if (bm.match[j] > j)\
    \ {\n            int a = perm_inv[j], b = perm_inv[bm.match[j]];\n           \
    \ if (a > b)\n                std::cout << b << ' ' << a - L << '\\n';\n     \
    \       else\n                std::cout << a << ' ' << b - L << '\\n';\n     \
    \   }\n}\n"
  code: "#include \"graph/bipartite_matching.hpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/bipartitematching\"\
    \n\n#include <algorithm>\n#include <numeric>\n#include <random>\n\nint main()\
    \ {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\n    int L,\
    \ R, M;\n    std::cin >> L >> R >> M;\n\n    std::vector<int> perm(L + R), perm_inv(L\
    \ + R);\n    std::iota(perm.begin(), perm.end(), 0);\n    std::random_device rd;\n\
    \    std::mt19937 g(rd());\n    std::shuffle(perm.begin(), perm.end(), g);\n \
    \   for (int i = 0; i < L + R; i++) { perm_inv[perm[i]] = i; }\n\n    BipartiteMatching\
    \ bm(L + R);\n    while (M--) {\n        int a, b;\n        std::cin >> a >> b;\n\
    \        bm.add_edge(perm[a], perm[L + b]);\n    }\n\n    std::cout << bm.solve()\
    \ << '\\n';\n    for (int j = 0; j < L + R; j++)\n        if (bm.match[j] > j)\
    \ {\n            int a = perm_inv[j], b = perm_inv[bm.match[j]];\n           \
    \ if (a > b)\n                std::cout << b << ' ' << a - L << '\\n';\n     \
    \       else\n                std::cout << a << ' ' << b - L << '\\n';\n     \
    \   }\n}\n"
  dependsOn:
  - graph/bipartite_matching.hpp
  isVerificationFile: true
  path: graph/test/bipartite_matching.test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/bipartite_matching.test.cpp
layout: document
redirect_from:
- /verify/graph/test/bipartite_matching.test.cpp
- /verify/graph/test/bipartite_matching.test.cpp.html
title: graph/test/bipartite_matching.test.cpp
---
