---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/bipartite_matching(slow).hpp
    title: graph/bipartite_matching(slow).hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A
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
    \  return os;\n    }\n};\n#line 3 \"graph/test/bipartite_matching(slow).test.cpp\"\
    \n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A\"\
    \n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \n    int X, Y, E;\n    std::cin >> X >> Y >> E;\n    BipartiteMatching graph(X\
    \ + Y);\n    while (E--) {\n        int s, t;\n        std::cin >> s >> t;\n \
    \       graph.add_edge(s, X + t);\n    }\n    std::cout << graph.solve() << '\\\
    n';\n}\n"
  code: "#include \"graph/bipartite_matching(slow).hpp\"\n#include <iostream>\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_7_A\"\
    \n\nint main() {\n    std::cin.tie(nullptr), std::ios::sync_with_stdio(false);\n\
    \n    int X, Y, E;\n    std::cin >> X >> Y >> E;\n    BipartiteMatching graph(X\
    \ + Y);\n    while (E--) {\n        int s, t;\n        std::cin >> s >> t;\n \
    \       graph.add_edge(s, X + t);\n    }\n    std::cout << graph.solve() << '\\\
    n';\n}\n"
  dependsOn:
  - graph/bipartite_matching(slow).hpp
  isVerificationFile: true
  path: graph/test/bipartite_matching(slow).test.cpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/bipartite_matching(slow).test.cpp
layout: document
redirect_from:
- /verify/graph/test/bipartite_matching(slow).test.cpp
- /verify/graph/test/bipartite_matching(slow).test.cpp.html
title: graph/test/bipartite_matching(slow).test.cpp
---
