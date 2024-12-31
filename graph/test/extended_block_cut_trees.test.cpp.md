---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/extended_block_cut_trees.hpp
    title: "Extended block cut tree \uFF08Block cut tree \u306E\u4E9C\u7A2E\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/biconnected_components
    links:
    - https://judge.yosupo.jp/problem/biconnected_components
  bundledCode: "#line 1 \"graph/test/extended_block_cut_trees.test.cpp\"\n#define\
    \ PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\n#line 2\
    \ \"graph/extended_block_cut_trees.hpp\"\n\n#include <cassert>\n#include <utility>\n\
    #include <vector>\n\n// Construct block cut tree (or forest) from a given graph\n\
    // Complexity: O(N + M), N = |vertices|, M = |edges|\n// based on this idea: https://x.com/noshi91/status/1529858538650374144\n\
    // based on this implementation: https://ssrs-cp.github.io/cp_library/graph/extended_block_cut_tree.hpp.html\n\
    struct extended_block_cut_trees {\n    int N;                            // number\
    \ of vertices\n    int B;                            // number of blocks\n   \
    \ std::vector<std::vector<int>> to; // (0, ..., N - 1): vertices, (N, ..., N +\
    \ B - 1): blocks\n\n    extended_block_cut_trees(int N, const std::vector<std::pair<int,\
    \ int>> &edges)\n        : N(N), B(0), to(N) {\n        std::vector<std::vector<int>>\
    \ adj(N);\n        for (auto [u, v] : edges) {\n            if (u != v) adj.at(u).push_back(v),\
    \ adj.at(v).push_back(u);\n        }\n\n        std::vector<int> dfs_next(N, -1),\
    \ dist(N, -1), back_cnt(N);\n\n        auto rec1 = [&](auto &&self, int now) ->\
    \ void {\n            for (int nxt : adj[now]) {\n                if (dist[nxt]\
    \ == -1) {\n                    dist[nxt] = dist[now] + 1;\n                 \
    \   dfs_next[now] = nxt;\n                    self(self, nxt);\n             \
    \       back_cnt[now] += back_cnt[nxt];\n                } else if (dist[nxt]\
    \ < dist[now] - 1) {\n                    ++back_cnt[now];\n                 \
    \   --back_cnt[dfs_next[nxt]];\n                }\n            }\n        };\n\
    \n        for (int i = 0; i < N; ++i) {\n            if (dist[i] == -1) dist[i]\
    \ = 0, rec1(rec1, i);\n        }\n\n        std::vector<bool> used(N);\n\n   \
    \     auto rec2 = [&](auto &&self, int now, int current_b) -> void {\n       \
    \     used[now] = true;\n            bool ok = false;\n\n            for (int\
    \ nxt : adj[now]) {\n                if (dist[nxt] == dist[now] + 1 and !used[nxt])\
    \ {\n                    if (back_cnt[nxt] > 0) {\n                        if\
    \ (!ok) {\n                            ok = true;\n                          \
    \  add_edge(now, current_b);\n                        }\n                    \
    \    self(self, nxt, current_b);\n                    } else {\n             \
    \           to.push_back({});\n                        ++B;\n                \
    \        add_edge(now, B - 1);\n                        self(self, nxt, B - 1);\n\
    \                    }\n                }\n            }\n\n            if (!ok\
    \ and dist[now] > 0) { add_edge(now, current_b); }\n        };\n\n        for\
    \ (int i = 0; i < N; ++i) {\n            if (dist[i] == 0) { rec2(rec2, i, B -\
    \ 1); }\n            if (adj[i].empty()) {\n                to.push_back({});\n\
    \                ++B;\n                add_edge(i, B - 1);\n            }\n  \
    \      }\n    }\n\n    int size() const { return N + B; }\n\n    bool is_articulation_point(int\
    \ vertex) const {\n        assert(0 <= vertex and vertex < N);\n        return\
    \ to[vertex].size() > 1;\n    }\n\n    int block_size(int block) const {\n   \
    \     assert(0 <= block and block < B);\n        return to[N + block].size();\n\
    \    }\n\n    const std::vector<int> &block_vertices(int block) const {\n    \
    \    assert(0 <= block and block < B);\n        return to[N + block];\n    }\n\
    \n    std::vector<std::vector<int>> biconnected_components() const {\n       \
    \ return std::vector<std::vector<int>>(to.begin() + N, to.end());\n    }\n\n \
    \   // first < N (vertices), second >= N (blocks)\n    std::vector<std::pair<int,\
    \ int>> get_edges() const {\n        std::vector<std::pair<int, int>> edges;\n\
    \        for (int i = 0; i < N; ++i) {\n            for (int j : to[i]) edges.emplace_back(i,\
    \ j);\n        }\n        return edges;\n    }\n\nprivate:\n    void add_edge(int\
    \ vertex, int block) {\n        assert(0 <= vertex and vertex < N);\n        assert(0\
    \ <= block and block < B);\n        to[vertex].push_back(N + block);\n       \
    \ to[N + block].push_back(vertex);\n    }\n};\n#line 3 \"graph/test/extended_block_cut_trees.test.cpp\"\
    \n\n#include <atcoder/fenwicktree>\n\n#include <iostream>\n\nusing namespace std;\n\
    \nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\n  \
    \  int N, M;\n    cin >> N >> M;\n    vector<pair<int, int>> edges(M);\n    for\
    \ (auto &[u, v] : edges) cin >> u >> v;\n\n    const extended_block_cut_trees\
    \ bct(N, edges);\n\n    cout << bct.B << '\\n';\n    for (const auto &g : bct.biconnected_components())\
    \ {\n        cout << g.size();\n        for (int v : g) cout << ' ' << v;\n  \
    \      cout << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/biconnected_components\"\
    \n#include \"../extended_block_cut_trees.hpp\"\n\n#include <atcoder/fenwicktree>\n\
    \n#include <iostream>\n\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr);\n\
    \    ios::sync_with_stdio(false);\n\n    int N, M;\n    cin >> N >> M;\n    vector<pair<int,\
    \ int>> edges(M);\n    for (auto &[u, v] : edges) cin >> u >> v;\n\n    const\
    \ extended_block_cut_trees bct(N, edges);\n\n    cout << bct.B << '\\n';\n   \
    \ for (const auto &g : bct.biconnected_components()) {\n        cout << g.size();\n\
    \        for (int v : g) cout << ' ' << v;\n        cout << '\\n';\n    }\n}\n"
  dependsOn:
  - graph/extended_block_cut_trees.hpp
  isVerificationFile: true
  path: graph/test/extended_block_cut_trees.test.cpp
  requiredBy: []
  timestamp: '2024-12-31 22:44:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/extended_block_cut_trees.test.cpp
layout: document
redirect_from:
- /verify/graph/test/extended_block_cut_trees.test.cpp
- /verify/graph/test/extended_block_cut_trees.test.cpp.html
title: graph/test/extended_block_cut_trees.test.cpp
---
