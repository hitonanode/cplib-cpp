---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/lowlink.hpp
    title: "Lowlink \uFF08\u7121\u5411\u30B0\u30E9\u30D5\u306E DFS tree, lowlink,\
      \ \u6A4B\u30FB\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\u30FB\u95A2\u7BC0\u70B9\
      \u30FB\u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A
  bundledCode: "#line 2 \"graph/lowlink.hpp\"\n#include <algorithm>\n#include <cassert>\n\
    #include <queue>\n#include <utility>\n#include <vector>\n\nstruct lowlink {\n\
    \    int V; // # of vertices\n    int E; // # of edges\n    int k;\n    std::vector<std::vector<std::pair<int,\
    \ int>>> to;\n    std::vector<std::pair<int, int>> edges;\n    std::vector<int>\
    \ root_ids; // DFS forest\u306E\u69CB\u7BC9\u3067\u6839\u306B\u306A\u3063\u305F\
    \u9802\u70B9\n\n    std::vector<int> is_bridge;       // Whether edge i is bridge\
    \ or not, size = E\n    std::vector<int> is_articulation; // whether vertex i\
    \ is articulation point or not, size = V\n\n    // lowlink\n    std::vector<int>\
    \ order;           // visiting order of DFS tree, size = V\n    std::vector<int>\
    \ lowlink_;        // size = V\n    std::vector<int> is_dfstree_edge; // size\
    \ = E\n\n    int tecc_num;             // \u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\
    \u5206\u6570\n    std::vector<int> tecc_id; // \u5404\u9802\u70B9\u304C\u4F55\u500B\
    \u76EE\u306E\u4E8C\u91CD\u8FBA\u9023\u7D50\u6210\u5206\u304B\n\n    int tvcc_num;\
    \             // \u4E8C\u91CD\u9802\u70B9\u9023\u7D50\u6210\u5206\u6570\n    std::vector<int>\
    \ tvcc_id; // \u5404\u8FBA\u304C\u4F55\u500B\u76EE\u306E\u4E8C\u91CD\u9802\u70B9\
    \u9023\u7D50\u6210\u5206\u304B\n\n    lowlink(int V)\n        : V(V), E(0), k(0),\
    \ to(V), is_articulation(V, 0), order(V, -1), lowlink_(V, -1),\n          tecc_num(0),\
    \ tvcc_num(0) {}\n\n    void add_edge(int v1, int v2) {\n        assert(v1 >=\
    \ 0 and v1 < V);\n        assert(v2 >= 0 and v2 < V);\n        to[v1].emplace_back(v2,\
    \ E);\n        to[v2].emplace_back(v1, E);\n        edges.emplace_back(v1, v2);\n\
    \        is_bridge.push_back(0);\n        is_dfstree_edge.push_back(0);\n    \
    \    tvcc_id.push_back(-1);\n        E++;\n    }\n\n    std::vector<int> _edge_stack;\n\
    \    int _root_now;\n\n    // Build DFS tree\n    // Complexity: O(V + E)\n  \
    \  void dfs_lowlink(int now, int prv_eid = -1) {\n        if (prv_eid < 0) _root_now\
    \ = k;\n        if (prv_eid == -1) root_ids.push_back(now);\n        order[now]\
    \ = lowlink_[now] = k++;\n        for (const auto &nxt : to[now]) {\n        \
    \    if (nxt.second == prv_eid) continue;\n            if (order[nxt.first] <\
    \ order[now]) _edge_stack.push_back(nxt.second);\n            if (order[nxt.first]\
    \ >= 0) {\n                lowlink_[now] = std::min(lowlink_[now], order[nxt.first]);\n\
    \            } else {\n                is_dfstree_edge[nxt.second] = 1;\n    \
    \            dfs_lowlink(nxt.first, nxt.second);\n                lowlink_[now]\
    \ = std::min(lowlink_[now], lowlink_[nxt.first]);\n\n                if ((order[now]\
    \ == _root_now and order[nxt.first] != _root_now + 1) or\n                   \
    \ (order[now] != _root_now and lowlink_[nxt.first] >= order[now])) {\n       \
    \             is_articulation[now] = 1;\n                }\n                if\
    \ (lowlink_[nxt.first] >= order[now]) {\n                    while (true) {\n\
    \                        int e = _edge_stack.back();\n                       \
    \ tvcc_id[e] = tvcc_num;\n                        _edge_stack.pop_back();\n  \
    \                      if (e == nxt.second) break;\n                    }\n  \
    \                  tvcc_num++;\n                }\n            }\n        }\n\
    \    }\n\n    void build() {\n        for (int v = 0; v < V; ++v) {\n        \
    \    if (order[v] < 0) dfs_lowlink(v);\n        }\n\n        // Find all bridges\n\
    \        // Complexity: O(V + E)\n        for (int i = 0; i < E; i++) {\n    \
    \        int v1 = edges[i].first, v2 = edges[i].second;\n            if (order[v1]\
    \ > order[v2]) std::swap(v1, v2);\n            is_bridge[i] = order[v1] < lowlink_[v2];\n\
    \        }\n    }\n\n    // Find two-edge-connected components and classify all\
    \ vertices\n    // Complexity: O(V + E)\n    std::vector<std::vector<int>> two_edge_connected_components()\
    \ {\n        build();\n        tecc_num = 0;\n        tecc_id.assign(V, -1);\n\
    \n        std::vector<int> st;\n        for (int i = 0; i < V; i++) {\n      \
    \      if (tecc_id[i] != -1) continue;\n            tecc_id[i] = tecc_num;\n \
    \           st.push_back(i);\n            while (!st.empty()) {\n            \
    \    int now = st.back();\n                st.pop_back();\n                for\
    \ (const auto &edge : to[now]) {\n                    int nxt = edge.first;\n\
    \                    if (tecc_id[nxt] >= 0 or is_bridge[edge.second]) continue;\n\
    \                    tecc_id[nxt] = tecc_num;\n                    st.push_back(nxt);\n\
    \                }\n            }\n            ++tecc_num;\n        }\n      \
    \  std::vector<std::vector<int>> ret(tecc_num);\n        for (int i = 0; i < V;\
    \ ++i) ret[tecc_id[i]].push_back(i);\n        return ret;\n    }\n\n    // Find\
    \ biconnected components and enumerate vertices for each component.\n    // Complexity:\
    \ O(V \\log V + E)\n    std::vector<std::vector<int>> biconnected_components_by_vertices()\
    \ {\n        build();\n        std::vector<std::vector<int>> ret(tvcc_num);\n\
    \        for (int i = 0; i < E; ++i) {\n            ret[tvcc_id[i]].push_back(edges[i].first);\n\
    \            ret[tvcc_id[i]].push_back(edges[i].second);\n        }\n\n      \
    \  for (auto &vec : ret) {\n            std::sort(vec.begin(), vec.end());\n \
    \           vec.erase(std::unique(vec.begin(), vec.end()), vec.end());\n     \
    \   }\n\n        for (int i = 0; i < V; ++i) {\n            if (to[i].empty())\
    \ ret.push_back({i});\n        }\n\n        return ret;\n    }\n\n    // Find\
    \ biconnected components and classify all edges\n    // Complexity: O(V + E)\n\
    \    std::vector<std::vector<int>> biconnected_components_by_edges() {\n     \
    \   build();\n        std::vector<std::vector<int>> ret(tvcc_num);\n        for\
    \ (int i = 0; i < E; ++i) ret[tvcc_id[i]].push_back(i);\n        return ret;\n\
    \    }\n};\n#line 2 \"graph/test/articulation_points.test.cpp\"\n#include <iostream>\n\
    #define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\nint main() {\n    int V, E;\n    std::cin >> V >> E;\n    lowlink graph(V);\n\
    \    for (int i = 0; i < E; i++) {\n        int s, t;\n        std::cin >> s >>\
    \ t;\n        graph.add_edge(s, t);\n    }\n    graph.build();\n    for (int i\
    \ = 0; i < V; i++) {\n        if (graph.is_articulation[i]) { printf(\"%d\\n\"\
    , i); }\n    }\n}\n"
  code: "#include \"../lowlink.hpp\"\n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A\"\
    \n\nint main() {\n    int V, E;\n    std::cin >> V >> E;\n    lowlink graph(V);\n\
    \    for (int i = 0; i < E; i++) {\n        int s, t;\n        std::cin >> s >>\
    \ t;\n        graph.add_edge(s, t);\n    }\n    graph.build();\n    for (int i\
    \ = 0; i < V; i++) {\n        if (graph.is_articulation[i]) { printf(\"%d\\n\"\
    , i); }\n    }\n}\n"
  dependsOn:
  - graph/lowlink.hpp
  isVerificationFile: true
  path: graph/test/articulation_points.test.cpp
  requiredBy: []
  timestamp: '2022-07-19 23:53:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/articulation_points.test.cpp
layout: document
redirect_from:
- /verify/graph/test/articulation_points.test.cpp
- /verify/graph/test/articulation_points.test.cpp.html
title: graph/test/articulation_points.test.cpp
---
