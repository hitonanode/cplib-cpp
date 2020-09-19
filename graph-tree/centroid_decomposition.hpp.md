---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - https://codeforces.com/contest/321/submission/59093583>
  bundledCode: "#line 2 \"graph-tree/centroid_decomposition.hpp\"\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n/*\n(Recursive) Centroid\
    \ Decomposition\nVerification: Codeforces #190 Div.1 C <https://codeforces.com/contest/321/submission/59093583>\n\
    \nfix_root(int r): Build information of the tree which `r` belongs to.\ndetect_centroid(int\
    \ r): Enumerate centroid(s) of the tree which `r` belongs to.\n*/\nstruct Tree\n\
    {\n    int NO_PARENT = -1;\n    using pint = std::pair<int, int>;\n    int V;\n\
    \    int E;\n    std::vector<std::vector<pint>> to;  // (node_id, edge_id)\n \
    \   std::vector<int> par;          // parent node_id par[root] = -1\n    std::vector<std::vector<int>>\
    \ chi;  // children id's\n    std::vector<int> subtree_size; // size of each subtree\n\
    \    std::vector<int> available_edge; // If 0, ignore the corresponding edge.\n\
    \n    Tree() : Tree(0) {}\n    Tree(int v) : V(v), E(0), to(v), par(v, NO_PARENT),\
    \ chi(v), subtree_size(v) {}\n\n    void add_edge(int v1, int v2)\n    {\n   \
    \     to[v1].emplace_back(v2, E);\n        to[v2].emplace_back(v1, E);\n     \
    \   E++;\n        available_edge.emplace_back(1);\n    }\n\n    int _dfs_fixroot(int\
    \ now, int prv)\n    {\n        chi[now].clear();\n        subtree_size[now] =\
    \ 1;\n        for (auto nxt : to[now]) {\n            if (nxt.first != prv and\
    \ available_edge[nxt.second]) {\n                par[nxt.first] = now;\n     \
    \           chi[now].push_back(nxt.first);\n                subtree_size[now]\
    \ += _dfs_fixroot(nxt.first, now);\n            }\n        }\n        return subtree_size[now];\n\
    \    }\n\n    void fix_root(int root) {\n        par[root] = NO_PARENT;\n    \
    \    _dfs_fixroot(root, -1);\n    }\n\n    //// Centroid Decpmposition ////\n\
    \    std::vector<int> centroid_cand_tmp;\n    void _dfs_detect_centroids(int now,\
    \ int prv, int n)\n    {\n        bool is_centroid = true;\n        for (auto\
    \ nxt : to[now])\n        {\n            if (nxt.first != prv and available_edge[nxt.second])\n\
    \            {\n                _dfs_detect_centroids(nxt.first, now, n);\n  \
    \              if (subtree_size[nxt.first] > n / 2) is_centroid = false;\n   \
    \         }\n        }\n        if (n - subtree_size[now] > n / 2) is_centroid\
    \ = false;\n        if (is_centroid) centroid_cand_tmp.push_back(now);\n    }\n\
    \    pint detect_centroids(int r) // ([centroid_node_id1], ([centroid_node_id2]|-1))\n\
    \    {\n        centroid_cand_tmp.clear();\n        while (par[r] != NO_PARENT)\
    \ r = par[r];\n        int n = subtree_size[r];\n        _dfs_detect_centroids(r,\
    \ -1, n);\n        if (centroid_cand_tmp.size() == 1) return std::make_pair(centroid_cand_tmp[0],\
    \ -1);\n        else return std::make_pair(centroid_cand_tmp[0], centroid_cand_tmp[1]);\n\
    \    }\n\n    void centroid_decomposition(int now) {\n        fix_root(now);\n\
    \        now = detect_centroids(now).first;\n        /*\n        do something\n\
    \        */\n        for (auto p : to[now]) {\n            int nxt, eid;\n   \
    \         std::tie(nxt, eid) = p;\n            if (available_edge[eid] == 0) continue;\n\
    \            available_edge[eid] = 0;\n            centroid_decomposition(nxt);\n\
    \        }\n    }\n};\n"
  code: "#pragma once\n#include <tuple>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n/*\n(Recursive) Centroid Decomposition\nVerification: Codeforces\
    \ #190 Div.1 C <https://codeforces.com/contest/321/submission/59093583>\n\nfix_root(int\
    \ r): Build information of the tree which `r` belongs to.\ndetect_centroid(int\
    \ r): Enumerate centroid(s) of the tree which `r` belongs to.\n*/\nstruct Tree\n\
    {\n    int NO_PARENT = -1;\n    using pint = std::pair<int, int>;\n    int V;\n\
    \    int E;\n    std::vector<std::vector<pint>> to;  // (node_id, edge_id)\n \
    \   std::vector<int> par;          // parent node_id par[root] = -1\n    std::vector<std::vector<int>>\
    \ chi;  // children id's\n    std::vector<int> subtree_size; // size of each subtree\n\
    \    std::vector<int> available_edge; // If 0, ignore the corresponding edge.\n\
    \n    Tree() : Tree(0) {}\n    Tree(int v) : V(v), E(0), to(v), par(v, NO_PARENT),\
    \ chi(v), subtree_size(v) {}\n\n    void add_edge(int v1, int v2)\n    {\n   \
    \     to[v1].emplace_back(v2, E);\n        to[v2].emplace_back(v1, E);\n     \
    \   E++;\n        available_edge.emplace_back(1);\n    }\n\n    int _dfs_fixroot(int\
    \ now, int prv)\n    {\n        chi[now].clear();\n        subtree_size[now] =\
    \ 1;\n        for (auto nxt : to[now]) {\n            if (nxt.first != prv and\
    \ available_edge[nxt.second]) {\n                par[nxt.first] = now;\n     \
    \           chi[now].push_back(nxt.first);\n                subtree_size[now]\
    \ += _dfs_fixroot(nxt.first, now);\n            }\n        }\n        return subtree_size[now];\n\
    \    }\n\n    void fix_root(int root) {\n        par[root] = NO_PARENT;\n    \
    \    _dfs_fixroot(root, -1);\n    }\n\n    //// Centroid Decpmposition ////\n\
    \    std::vector<int> centroid_cand_tmp;\n    void _dfs_detect_centroids(int now,\
    \ int prv, int n)\n    {\n        bool is_centroid = true;\n        for (auto\
    \ nxt : to[now])\n        {\n            if (nxt.first != prv and available_edge[nxt.second])\n\
    \            {\n                _dfs_detect_centroids(nxt.first, now, n);\n  \
    \              if (subtree_size[nxt.first] > n / 2) is_centroid = false;\n   \
    \         }\n        }\n        if (n - subtree_size[now] > n / 2) is_centroid\
    \ = false;\n        if (is_centroid) centroid_cand_tmp.push_back(now);\n    }\n\
    \    pint detect_centroids(int r) // ([centroid_node_id1], ([centroid_node_id2]|-1))\n\
    \    {\n        centroid_cand_tmp.clear();\n        while (par[r] != NO_PARENT)\
    \ r = par[r];\n        int n = subtree_size[r];\n        _dfs_detect_centroids(r,\
    \ -1, n);\n        if (centroid_cand_tmp.size() == 1) return std::make_pair(centroid_cand_tmp[0],\
    \ -1);\n        else return std::make_pair(centroid_cand_tmp[0], centroid_cand_tmp[1]);\n\
    \    }\n\n    void centroid_decomposition(int now) {\n        fix_root(now);\n\
    \        now = detect_centroids(now).first;\n        /*\n        do something\n\
    \        */\n        for (auto p : to[now]) {\n            int nxt, eid;\n   \
    \         std::tie(nxt, eid) = p;\n            if (available_edge[eid] == 0) continue;\n\
    \            available_edge[eid] = 0;\n            centroid_decomposition(nxt);\n\
    \        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph-tree/centroid_decomposition.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph-tree/centroid_decomposition.hpp
layout: document
redirect_from:
- /library/graph-tree/centroid_decomposition.hpp
- /library/graph-tree/centroid_decomposition.hpp.html
title: graph-tree/centroid_decomposition.hpp
---
