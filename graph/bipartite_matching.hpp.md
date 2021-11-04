---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':warning:'
    path: combinatorial_opt/matroids/transversal_matroid.hpp
    title: "Transversal matroid \uFF08\u6A2A\u65AD\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
  - icon: ':heavy_check_mark:'
    path: graph/dulmage_mendelsohn_decomposition.hpp
    title: "Dulmage\u2013Mendelsohn decomposition \uFF08DM \u5206\u89E3\uFF09"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/bipartite_matching.test.cpp
    title: graph/test/bipartite_matching.test.cpp
  - icon: ':heavy_check_mark:'
    path: graph/test/dulmage_mendelsohn.yuki1615.test.cpp
    title: graph/test/dulmage_mendelsohn.yuki1615.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html
  bundledCode: "#line 2 \"graph/bipartite_matching.hpp\"\n#include <cassert>\n#include\
    \ <iostream>\n#include <vector>\n\n// Bipartite matching of undirected bipartite\
    \ graph (Hopcroft-Karp)\n// https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html\n\
    // Comprexity: O((V + E)sqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching {\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No parter)\n  \
    \  std::vector<int> used, vv;\n    std::vector<int> color; // color of each node(checking\
    \ bipartition): 0/1/-1(not determined)\n\n    BipartiteMatching() = default;\n\
    \    BipartiteMatching(int V_) : V(V_), to(V_), match(V_, -1), used(V_), color(V_,\
    \ -1) {}\n\n    void add_edge(int u, int v) {\n        assert(u >= 0 and u < V\
    \ and v >= 0 and v < V and u != v);\n        to[u].push_back(v);\n        to[v].push_back(u);\n\
    \    }\n\n    void _bfs() {\n        dist.assign(V, -1);\n        std::vector<int>\
    \ q;\n        int lq = 0;\n        for (int i = 0; i < V; i++) {\n           \
    \ if (!color[i] and !used[i]) q.push_back(i), dist[i] = 0;\n        }\n\n    \
    \    while (lq < int(q.size())) {\n            int now = q[lq++];\n          \
    \  for (auto nxt : to[now]) {\n                int c = match[nxt];\n         \
    \       if (c >= 0 and dist[c] == -1) q.push_back(c), dist[c] = dist[now] + 1;\n\
    \            }\n        }\n    }\n\n    bool _dfs(int now) {\n        vv[now]\
    \ = true;\n        for (auto nxt : to[now]) {\n            int c = match[nxt];\n\
    \            if (c < 0 or (!vv[c] and dist[c] == dist[now] + 1 and _dfs(c))) {\n\
    \                match[nxt] = now, match[now] = nxt;\n                used[now]\
    \ = true;\n                return true;\n            }\n        }\n        return\
    \ false;\n    }\n\n    bool _color_bfs(int root) {\n        color[root] = 0;\n\
    \        std::vector<int> q{root};\n        int lq = 0;\n        while (lq < int(q.size()))\
    \ {\n            int now = q[lq++], c = color[now];\n            for (auto nxt\
    \ : to[now]) {\n                if (color[nxt] == -1) {\n                    color[nxt]\
    \ = !c, q.push_back(nxt);\n                } else if (color[nxt] == c) {\n   \
    \                 return false;\n                }\n            }\n        }\n\
    \        return true;\n    }\n\n    int solve() {\n        for (int i = 0; i <\
    \ V; i++) {\n            if (color[i] == -1 and !_color_bfs(i)) return -1;\n \
    \       }\n        int ret = 0;\n        while (true) {\n            _bfs();\n\
    \            vv.assign(V, false);\n            int flow = 0;\n            for\
    \ (int i = 0; i < V; i++) {\n                if (!color[i] and !used[i] and _dfs(i))\
    \ flow++;\n            }\n            if (!flow) break;\n            ret += flow;\n\
    \        }\n        return ret;\n    }\n\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const BipartiteMatching &bm) {\n        os\
    \ << \"{N=\" << bm.V << ':';\n        for (int i = 0; i < bm.V; i++) {\n     \
    \       if (bm.match[i] > i) os << '(' << i << '-' << bm.match[i] << \"),\";\n\
    \        }\n        return os << '}';\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <iostream>\n#include <vector>\n\
    \n// Bipartite matching of undirected bipartite graph (Hopcroft-Karp)\n// https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html\n\
    // Comprexity: O((V + E)sqrtV)\n// int solve(): enumerate maximum number of matching\
    \ / return -1 (if graph is not bipartite)\nstruct BipartiteMatching {\n    int\
    \ V;\n    std::vector<std::vector<int>> to; // Adjacency list\n    std::vector<int>\
    \ dist;            // dist[i] = (Distance from i'th node)\n    std::vector<int>\
    \ match;           // match[i] = (Partner of i'th node) or -1 (No parter)\n  \
    \  std::vector<int> used, vv;\n    std::vector<int> color; // color of each node(checking\
    \ bipartition): 0/1/-1(not determined)\n\n    BipartiteMatching() = default;\n\
    \    BipartiteMatching(int V_) : V(V_), to(V_), match(V_, -1), used(V_), color(V_,\
    \ -1) {}\n\n    void add_edge(int u, int v) {\n        assert(u >= 0 and u < V\
    \ and v >= 0 and v < V and u != v);\n        to[u].push_back(v);\n        to[v].push_back(u);\n\
    \    }\n\n    void _bfs() {\n        dist.assign(V, -1);\n        std::vector<int>\
    \ q;\n        int lq = 0;\n        for (int i = 0; i < V; i++) {\n           \
    \ if (!color[i] and !used[i]) q.push_back(i), dist[i] = 0;\n        }\n\n    \
    \    while (lq < int(q.size())) {\n            int now = q[lq++];\n          \
    \  for (auto nxt : to[now]) {\n                int c = match[nxt];\n         \
    \       if (c >= 0 and dist[c] == -1) q.push_back(c), dist[c] = dist[now] + 1;\n\
    \            }\n        }\n    }\n\n    bool _dfs(int now) {\n        vv[now]\
    \ = true;\n        for (auto nxt : to[now]) {\n            int c = match[nxt];\n\
    \            if (c < 0 or (!vv[c] and dist[c] == dist[now] + 1 and _dfs(c))) {\n\
    \                match[nxt] = now, match[now] = nxt;\n                used[now]\
    \ = true;\n                return true;\n            }\n        }\n        return\
    \ false;\n    }\n\n    bool _color_bfs(int root) {\n        color[root] = 0;\n\
    \        std::vector<int> q{root};\n        int lq = 0;\n        while (lq < int(q.size()))\
    \ {\n            int now = q[lq++], c = color[now];\n            for (auto nxt\
    \ : to[now]) {\n                if (color[nxt] == -1) {\n                    color[nxt]\
    \ = !c, q.push_back(nxt);\n                } else if (color[nxt] == c) {\n   \
    \                 return false;\n                }\n            }\n        }\n\
    \        return true;\n    }\n\n    int solve() {\n        for (int i = 0; i <\
    \ V; i++) {\n            if (color[i] == -1 and !_color_bfs(i)) return -1;\n \
    \       }\n        int ret = 0;\n        while (true) {\n            _bfs();\n\
    \            vv.assign(V, false);\n            int flow = 0;\n            for\
    \ (int i = 0; i < V; i++) {\n                if (!color[i] and !used[i] and _dfs(i))\
    \ flow++;\n            }\n            if (!flow) break;\n            ret += flow;\n\
    \        }\n        return ret;\n    }\n\n    template <class OStream> friend\
    \ OStream &operator<<(OStream &os, const BipartiteMatching &bm) {\n        os\
    \ << \"{N=\" << bm.V << ':';\n        for (int i = 0; i < bm.V; i++) {\n     \
    \       if (bm.match[i] > i) os << '(' << i << '-' << bm.match[i] << \"),\";\n\
    \        }\n        return os << '}';\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/bipartite_matching.hpp
  requiredBy:
  - combinatorial_opt/matroids/transversal_matroid.hpp
  - graph/dulmage_mendelsohn_decomposition.hpp
  timestamp: '2021-11-03 21:38:41+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/bipartite_matching.test.cpp
  - graph/test/dulmage_mendelsohn.yuki1615.test.cpp
documentation_of: graph/bipartite_matching.hpp
layout: document
title: "Bipartite matching (Hopcroft\u2013Karp)"
---

与えられた二部グラフの最大マッチングを構築する．計算量は $O((N + M)\sqrt{N})$．

## 使用方法

グラフを明示的に二部グラフとして入力する必要はなく，最大マッチング構築の実行時に自動的に判定が行われる．

`solve()` 関数は与えられたグラフが二部グラフの場合は最大マッチングのサイズを，二部グラフではない場合は `-1` を返す．

```cpp
BipartiteMatching bm(N);
bm.add_edge(u, v);

int n_pair = bm.solve();

// match[i] = (頂点 i とペアになる頂点) 
//            or -1 （マッチングに使用されない場合）
int j = bm.match[i];
```

## 問題例

- [Library Checker: Matching on Bipartite Graph](https://judge.yosupo.jp/problem/bipartitematching)

## リンク

- [二部グラフの最大マッチング(Hopcroft-Karp) \| Luzhiled’s memo](https://ei1333.github.io/luzhiled/snippets/graph/hopcroft-karp.html)
