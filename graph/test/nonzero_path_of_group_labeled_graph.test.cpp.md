---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/nonzero_path_of_group_labeled_graph.hpp
    title: "Shortest Non-zero Path in Group-Labeled Graphs \uFF08\u7121\u5411\u30B0\
      \u30E9\u30D5\u306E\u7FA4\u30E9\u30D9\u30EB\u5236\u7D04\u4ED8\u304D\u6700\u77ED\
      \u8DEF\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1602
    links:
    - https://yukicoder.me/problems/no/1602
  bundledCode: "#line 1 \"graph/test/nonzero_path_of_group_labeled_graph.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1602\"\n#line 2 \"graph/nonzero_path_of_group_labeled_graph.hpp\"\
    \n#include <cassert>\n#include <queue>\n#include <tuple>\n#include <vector>\n\n\
    // CUT begin\n// Single-source unorthodox shortest paths\n// Complexity: O(M log\
    \ M)\n// This implementation is based on: https://gist.github.com/wata-orz/d3037bd0b919c76dd9ddc0379e1e3192\n\
    // Reference:\n// [1] Y. Iwata and Y. Yamaguchi, \"Finding a Shortest Non-zero\
    \ Path in Group-Labeled Graphs,\"\n//     https://arxiv.org/abs/1906.04062\ntemplate\
    \ <class T, T INF, class G> struct ShortestNonzeroPath {\n    int V;\n    std::vector<std::vector<std::tuple<int,\
    \ T, G>>> to;\n    ShortestNonzeroPath(int n) : V(n), to(n) { static_assert(INF\
    \ > 0, \"INF must be positive\"); }\n    void add_bi_edge(int u, int v, T len,\
    \ G g) {\n        assert(u >= 0 and u < V);\n        assert(v >= 0 and v < V);\n\
    \        assert(len >= 0);\n        to[u].emplace_back(v, len, g);\n        to[v].emplace_back(u,\
    \ len, -g);\n    }\n\nprivate:\n    std::vector<T> dist_sp;\n    std::vector<int>\
    \ parent_sp, depth_sp;\n    std::vector<G> psi; // psi[path = v0v1...vn] = psi[v0v1]\
    \ * psi[v1v2] * ... * psi[v(n - 1)vn]\n\n    std::vector<int> uf_ps;\n    int\
    \ _find(int x) {\n        if (uf_ps[x] == -1) {\n            return x;\n     \
    \   } else {\n            return uf_ps[x] = _find(uf_ps[x]);\n        }\n    }\n\
    \    void _unite(int r, int c) { uf_ps[c] = r; }\n\npublic:\n    int s;\n    std::vector<T>\
    \ dist; // dist[i] = Shortest distance of nonzero path from s to i\n    void solve(int\
    \ s_) {\n        s = s_;\n        assert(s >= 0 and s < V);\n\n        // Solve\
    \ SSSP\n        {\n            dist_sp.assign(V, INF);\n            depth_sp.assign(V,\
    \ -1), parent_sp.assign(V, -1);\n            psi.assign(V, G());\n           \
    \ std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T,\
    \ int>>> que;\n            dist_sp[s] = 0, depth_sp[s] = 0;\n            que.emplace(0,\
    \ s);\n            while (que.size()) {\n                T d, l;\n           \
    \     int u, v;\n                G g;\n                std::tie(d, u) = que.top();\n\
    \                que.pop();\n                if (dist_sp[u] != d) continue;\n\
    \                for (const auto &p : to[u]) {\n                    std::tie(v,\
    \ l, g) = p;\n                    const auto d2 = d + l;\n                   \
    \ if (dist_sp[v] > d2) {\n                        dist_sp[v] = d2, depth_sp[v]\
    \ = depth_sp[u] + 1, parent_sp[v] = u, psi[v] = psi[u] + g;\n                \
    \        que.emplace(d2, v);\n                    }\n                }\n     \
    \       }\n        }\n\n        uf_ps.assign(V, -1);\n        using P = std::tuple<T,\
    \ int, int>;\n        std::priority_queue<P, std::vector<P>, std::greater<P>>\
    \ que;\n        for (int u = 0; u < V; u++) {\n            if (dist_sp[u] == INF)\
    \ continue;\n            for (int i = 0; i < int(to[u].size()); i++) {\n     \
    \           int v;\n                T l;\n                G g;\n             \
    \   std::tie(v, l, g) = to[u][i];\n                if (u < v and !(psi[u] + g\
    \ == psi[v])) que.emplace(dist_sp[u] + dist_sp[v] + l, u, i);\n            }\n\
    \        }\n\n        dist.assign(V, INF);\n        while (que.size()) {\n   \
    \         T h;\n            int u0, i;\n            std::tie(h, u0, i) = que.top();\n\
    \            que.pop();\n            const int v0 = std::get<0>(to[u0][i]);\n\
    \            int u = _find(u0), v = _find(v0);\n            std::vector<int> bs;\n\
    \            while (u != v) {\n                if (depth_sp[u] > depth_sp[v])\
    \ {\n                    bs.push_back(u), u = _find(parent_sp[u]);\n         \
    \       } else {\n                    bs.push_back(v), v = _find(parent_sp[v]);\n\
    \                }\n            }\n            for (const int x : bs) {\n    \
    \            _unite(u, x);\n                dist[x] = h - dist_sp[x];\n      \
    \          for (int i = 0; i < int(to[x].size()); i++) {\n                   \
    \ int y;\n                    T l;\n                    G g;\n               \
    \     std::tie(y, l, g) = to[x][i];\n                    if (psi[x] + g == psi[y])\
    \ { que.emplace(dist[x] + dist_sp[y] + l, x, i); }\n                }\n      \
    \      }\n        }\n        for (int i = 0; i < V; i++) {\n            if (!(psi[i]\
    \ == G()) and dist_sp[i] < dist[i]) dist[i] = dist_sp[i];\n        }\n    }\n\
    };\n/* Example of group G:\nstruct G {\n    unsigned g;\n    G(unsigned x = 0)\
    \ : g(x) {}\n    G operator-() const noexcept { return *this; }\n    G operator+(const\
    \ G &r) const noexcept { return G(g ^ r.g); }\n    bool operator==(const G &x)\
    \ const noexcept { return g == x.g; }\n};\n*/\n#line 3 \"graph/test/nonzero_path_of_group_labeled_graph.test.cpp\"\
    \n\nstruct G {\n    unsigned g;\n    G(unsigned x = 0) : g(x) {}\n    G operator-()\
    \ const noexcept { return *this; }\n    G operator+(const G &r) const noexcept\
    \ { return G(g ^ r.g); }\n    bool operator==(const G &x) const noexcept { return\
    \ g == x.g; }\n};\n\n#include <iostream>\n#include <string>\nusing namespace std;\n\
    constexpr long long INF = 1LL << 60;\n\nint main() {\n    int N, M, K;\n    cin\
    \ >> N >> M >> K;\n    ShortestNonzeroPath<long long, INF, G> graph(N);\n\n  \
    \  while (M--) {\n        int a, b, c;\n        string x;\n        cin >> a >>\
    \ b >> c >> x;\n        unsigned m = 0;\n        for (auto c : x) m = m * 2 +\
    \ c - '0';\n        a--, b--;\n        graph.add_bi_edge(a, b, c, m);\n    }\n\
    \    graph.solve(N - 1);\n    for (int i = 0; i < N - 1; i++) cout << (graph.dist[i]\
    \ == INF ? -1 : graph.dist[i]) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/1602\"\n#include \"../nonzero_path_of_group_labeled_graph.hpp\"\
    \n\nstruct G {\n    unsigned g;\n    G(unsigned x = 0) : g(x) {}\n    G operator-()\
    \ const noexcept { return *this; }\n    G operator+(const G &r) const noexcept\
    \ { return G(g ^ r.g); }\n    bool operator==(const G &x) const noexcept { return\
    \ g == x.g; }\n};\n\n#include <iostream>\n#include <string>\nusing namespace std;\n\
    constexpr long long INF = 1LL << 60;\n\nint main() {\n    int N, M, K;\n    cin\
    \ >> N >> M >> K;\n    ShortestNonzeroPath<long long, INF, G> graph(N);\n\n  \
    \  while (M--) {\n        int a, b, c;\n        string x;\n        cin >> a >>\
    \ b >> c >> x;\n        unsigned m = 0;\n        for (auto c : x) m = m * 2 +\
    \ c - '0';\n        a--, b--;\n        graph.add_bi_edge(a, b, c, m);\n    }\n\
    \    graph.solve(N - 1);\n    for (int i = 0; i < N - 1; i++) cout << (graph.dist[i]\
    \ == INF ? -1 : graph.dist[i]) << '\\n';\n}\n"
  dependsOn:
  - graph/nonzero_path_of_group_labeled_graph.hpp
  isVerificationFile: true
  path: graph/test/nonzero_path_of_group_labeled_graph.test.cpp
  requiredBy: []
  timestamp: '2021-07-10 17:32:41+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/nonzero_path_of_group_labeled_graph.test.cpp
layout: document
redirect_from:
- /verify/graph/test/nonzero_path_of_group_labeled_graph.test.cpp
- /verify/graph/test/nonzero_path_of_group_labeled_graph.test.cpp.html
title: graph/test/nonzero_path_of_group_labeled_graph.test.cpp
---
