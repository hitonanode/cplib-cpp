---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/bipartite_matching(slow).test.cpp
    title: graph/test/bipartite_matching(slow).test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>
  bundledCode: "#line 2 \"graph/bipartite_matching(slow).hpp\"\n#include <iostream>\n\
    #include <vector>\n\n// CUT begin\n// Bipartite matching of undirected bipartite\
    \ graph\n// <https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>\n\
    // Comprexity: O(VE)\nstruct BipartiteMatching\n{\n    int V;                \
    \               // # of vertices\n    std::vector<std::vector<int>> edges; //\
    \ Adjacency list\n    std::vector<int> match;              // match[i] = (Partner\
    \ of i'th node) or -1 (No parter)\n    std::vector<int> used;\n    int timestamp;\n\
    \    BipartiteMatching(int V = 0) : V(V), edges(V), match(V, -1), used(V, 0),\
    \ timestamp(0) {}\n\n    void add_edge(int u, int v)\n    {\n        edges[u].push_back(v);\n\
    \        edges[v].push_back(u);\n    }\n\n    bool dfs(int v)\n    {\n       \
    \ used[v] = timestamp;\n        for (auto to : edges[v])\n        {\n        \
    \    if (match[to] < 0 or (used[match[to]] != timestamp and dfs(match[to])))\n\
    \            {\n                match[v] = to;\n                match[to] = v;\n\
    \                return true;\n            }\n        }\n        return false;\n\
    \    }\n\n    int solve() // Count up newly formed pairs\n    {\n        int ret\
    \ = 0;\n        for (int v = 0; v < V; v++) if (match[v] < 0)\n        {\n   \
    \         ++timestamp;\n            ret += dfs(v);\n        }\n        return\
    \ ret;\n    }\n\n    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching\
    \ &bm)\n    {\n        os << \"{V=\" << bm.V << \":\";\n        for (int i = 0;\
    \ i < bm.V; i++) if (i < bm.match[i])\n        {\n            os << \"(\" << i\
    \ << \"-\" << bm.match[i] << \"),\";\n        }\n        os << \"}\";\n      \
    \  return os;\n    }\n};\n"
  code: "#pragma once\n#include <iostream>\n#include <vector>\n\n// CUT begin\n//\
    \ Bipartite matching of undirected bipartite graph\n// <https://ei1333.github.io/luzhiled/snippets/graph/bipartite-matching.html>\n\
    // Comprexity: O(VE)\nstruct BipartiteMatching\n{\n    int V;                \
    \               // # of vertices\n    std::vector<std::vector<int>> edges; //\
    \ Adjacency list\n    std::vector<int> match;              // match[i] = (Partner\
    \ of i'th node) or -1 (No parter)\n    std::vector<int> used;\n    int timestamp;\n\
    \    BipartiteMatching(int V = 0) : V(V), edges(V), match(V, -1), used(V, 0),\
    \ timestamp(0) {}\n\n    void add_edge(int u, int v)\n    {\n        edges[u].push_back(v);\n\
    \        edges[v].push_back(u);\n    }\n\n    bool dfs(int v)\n    {\n       \
    \ used[v] = timestamp;\n        for (auto to : edges[v])\n        {\n        \
    \    if (match[to] < 0 or (used[match[to]] != timestamp and dfs(match[to])))\n\
    \            {\n                match[v] = to;\n                match[to] = v;\n\
    \                return true;\n            }\n        }\n        return false;\n\
    \    }\n\n    int solve() // Count up newly formed pairs\n    {\n        int ret\
    \ = 0;\n        for (int v = 0; v < V; v++) if (match[v] < 0)\n        {\n   \
    \         ++timestamp;\n            ret += dfs(v);\n        }\n        return\
    \ ret;\n    }\n\n    friend std::ostream &operator<<(std::ostream &os, const BipartiteMatching\
    \ &bm)\n    {\n        os << \"{V=\" << bm.V << \":\";\n        for (int i = 0;\
    \ i < bm.V; i++) if (i < bm.match[i])\n        {\n            os << \"(\" << i\
    \ << \"-\" << bm.match[i] << \"),\";\n        }\n        os << \"}\";\n      \
    \  return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bipartite_matching(slow).hpp
  requiredBy: []
  timestamp: '2020-04-18 18:32:38+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/bipartite_matching(slow).test.cpp
documentation_of: graph/bipartite_matching(slow).hpp
layout: document
redirect_from:
- /library/graph/bipartite_matching(slow).hpp
- /library/graph/bipartite_matching(slow).hpp.html
title: graph/bipartite_matching(slow).hpp
---
