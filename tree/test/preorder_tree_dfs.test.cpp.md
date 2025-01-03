---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: tree/preorder_tree_dfs.hpp
    title: "Preorder tree DFS \uFF08\u6728\u306E\u884C\u304D\u304C\u3051\u9806 DFS\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/vertex_add_subtree_sum
    links:
    - https://judge.yosupo.jp/problem/vertex_add_subtree_sum
  bundledCode: "#line 1 \"tree/test/preorder_tree_dfs.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\n#line 2 \"tree/preorder_tree_dfs.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// Preorder tree DFS\n// \u6728\u3092\
    \ DFS \u3057\u3066\u884C\u304D\u304C\u3051\u9806\u306B\u9802\u70B9\u3092\u4FDD\
    \u6301\u3059\u308B\uFF0E\n// \u6728\u3092\u533A\u9593\u306B\u5909\u63DB\u3059\u308B\
    \uFF0E\u90E8\u5206\u6728\u3092\u69CB\u6210\u3059\u308B\u9802\u70B9\u306F\u9023\
    \u7D9A\u3057\u3066\u73FE\u308C\u308B\u306E\u3067\uFF0C\u90E8\u5206\u6728\u306E\
    \u9802\u70B9\u30AF\u30A8\u30EA\u7B49\u306B\u6709\u7528\uFF0E\n// heavy_light_decomposition\
    \ \u304C\u4E0A\u4F4D\u4E92\u63DB\nstruct preorder_tree_dfs {\n    int n; // #\
    \ of vertices of tree\n    int root;\n    std::vector<int> subtree_begin, subtree_end;\n\
    \    std::vector<int> vis_order;\n\n    void _build_dfs(int now, const std::vector<std::vector<int>>\
    \ &to) {\n        subtree_begin[now] = vis_order.size();\n        vis_order.push_back(now);\n\
    \        for (auto nxt : to[now]) {\n            if (subtree_begin[nxt] == -1)\
    \ _build_dfs(nxt, to);\n        }\n        subtree_end[now] = vis_order.size();\n\
    \    }\n\n    preorder_tree_dfs() = default;\n\n    preorder_tree_dfs(const std::vector<std::vector<int>>\
    \ &to, int root)\n        : n(to.size()), root(root), subtree_begin(n, -1), subtree_end(n,\
    \ -1) {\n        _build_dfs(root, to);\n    }\n};\n#line 4 \"tree/test/preorder_tree_dfs.test.cpp\"\
    \n#include <iostream>\n#include <atcoder/fenwicktree>\nusing namespace std;\n\n\
    int main() {\n    int N, Q;\n    cin >> N >> Q;\n    vector<long long> A(N);\n\
    \    vector<vector<int>> to(N);\n    for (auto &a : A) cin >> a;\n    for (int\
    \ i = 1; i < N; i++) {\n        int p;\n        cin >> p;\n        to.at(p).push_back(i);\n\
    \        to.at(i).push_back(p);\n    }\n\n    preorder_tree_dfs tour(to, 0);\n\
    \n    atcoder::fenwick_tree<long long> ft(N);\n    for (int i = 0; i < N; i++)\
    \ ft.add(tour.subtree_begin.at(i), A.at(i));\n\n    while (Q--) {\n        int\
    \ q;\n        cin >> q;\n        if (q) {\n            int u;\n            cin\
    \ >> u;\n            printf(\"%lld\\n\", ft.sum(tour.subtree_begin[u], tour.subtree_end[u]));\n\
    \        } else {\n            int u, x;\n            cin >> u >> x;\n       \
    \     ft.add(tour.subtree_begin[u], x);\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/vertex_add_subtree_sum\"\
    \n#include \"../preorder_tree_dfs.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #include <atcoder/fenwicktree>\nusing namespace std;\n\nint main() {\n    int\
    \ N, Q;\n    cin >> N >> Q;\n    vector<long long> A(N);\n    vector<vector<int>>\
    \ to(N);\n    for (auto &a : A) cin >> a;\n    for (int i = 1; i < N; i++) {\n\
    \        int p;\n        cin >> p;\n        to.at(p).push_back(i);\n        to.at(i).push_back(p);\n\
    \    }\n\n    preorder_tree_dfs tour(to, 0);\n\n    atcoder::fenwick_tree<long\
    \ long> ft(N);\n    for (int i = 0; i < N; i++) ft.add(tour.subtree_begin.at(i),\
    \ A.at(i));\n\n    while (Q--) {\n        int q;\n        cin >> q;\n        if\
    \ (q) {\n            int u;\n            cin >> u;\n            printf(\"%lld\\\
    n\", ft.sum(tour.subtree_begin[u], tour.subtree_end[u]));\n        } else {\n\
    \            int u, x;\n            cin >> u >> x;\n            ft.add(tour.subtree_begin[u],\
    \ x);\n        }\n    }\n}\n"
  dependsOn:
  - tree/preorder_tree_dfs.hpp
  isVerificationFile: true
  path: tree/test/preorder_tree_dfs.test.cpp
  requiredBy: []
  timestamp: '2025-01-03 09:34:57+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: tree/test/preorder_tree_dfs.test.cpp
layout: document
redirect_from:
- /verify/tree/test/preorder_tree_dfs.test.cpp
- /verify/tree/test/preorder_tree_dfs.test.cpp.html
title: tree/test/preorder_tree_dfs.test.cpp
---
