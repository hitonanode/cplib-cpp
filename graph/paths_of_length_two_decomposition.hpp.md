---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: data_structure/light_forward_list.hpp
    title: data_structure/light_forward_list.hpp
  - icon: ':heavy_check_mark:'
    path: unionfind/unionfind.hpp
    title: unionfind/unionfind.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://atcoder.jp/contests/agc035/tasks/agc035_b
    - https://codeforces.com/contest/1519/problem/E
  bundledCode: "#line 2 \"data_structure/light_forward_list.hpp\"\n#include <vector>\n\
    \n// CUT begin\n// Simple forward_list for MLE-sensitive situations\n// Verify:\
    \ <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\ntemplate\
    \ <typename T> struct light_forward_list {\n    static std::vector<unsigned> ptr;\n\
    \    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {T()};\n\
    #line 2 \"unionfind/unionfind.hpp\"\n#include <numeric>\n#include <utility>\n\
    #line 5 \"unionfind/unionfind.hpp\"\n\n// CUT begin\n// UnionFind Tree (0-indexed),\
    \ based on size of each disjoint set\nstruct UnionFind {\n    std::vector<int>\
    \ par, cou;\n    UnionFind(int N = 0) : par(N), cou(N, 1) { iota(par.begin(),\
    \ par.end(), 0); }\n    int find(int x) { return (par[x] == x) ? x : (par[x] =\
    \ find(par[x])); }\n    bool unite(int x, int y) {\n        x = find(x), y = find(y);\n\
    \        if (x == y) return false;\n        if (cou[x] < cou[y]) std::swap(x,\
    \ y);\n        par[y] = x, cou[x] += cou[y];\n        return true;\n    }\n  \
    \  int count(int x) { return cou[find(x)]; }\n    bool same(int x, int y) { return\
    \ find(x) == find(y); }\n};\n#line 4 \"graph/paths_of_length_two_decomposition.hpp\"\
    \n#include <cassert>\n#include <tuple>\n#line 8 \"graph/paths_of_length_two_decomposition.hpp\"\
    \n\n// \u7121\u5411\u30B0\u30E9\u30D5\u3092\u9577\u30552\u306E\u9053\uFF08**\u9589\
    \u8DEF\u3092\u542B\u3080**\uFF09\u3078\u5206\u89E3\n// \u5404\u9023\u7D50\u6210\
    \u5206\u306B\u3064\u3044\u3066\uFF0C\u8FBA\u306E\u672C\u6570\u304C\u5076\u6570\
    \u306A\u3089\u5B8C\u5168\u306A\u5206\u89E3\u304C\u53EF\u80FD\n// Complexity: O(V\
    \ + E)\n// Verify: - https://codeforces.com/contest/1519/problem/E\n//       \
    \  - https://atcoder.jp/contests/agc035/tasks/agc035_b\nstruct PathsOfLength2Decomposition\
    \ {\n    int V, E;\n    std::vector<std::pair<int, int>> edges;\n    std::vector<light_forward_list<std::pair<int,\
    \ int>>> to_nonmst;\n    std::vector<light_forward_list<std::pair<int, int>>>\
    \ to_mst;\n    UnionFind uf;\n    void _init(int V_) {\n        V = V_, E = 0;\n\
    \        edges.clear();\n        to_nonmst.assign(V, {});\n        to_mst.assign(V,\
    \ {});\n        uf = UnionFind(V);\n    }\n    PathsOfLength2Decomposition(int\
    \ V = 0) { _init(V); }\n    void add_edge(int u, int v) {\n        assert(u >=\
    \ 0 and u < V);\n        assert(v >= 0 and v < V);\n        if (uf.unite(u, v))\
    \ {\n            to_mst[u].push_front({E, v}), to_mst[v].push_front({E, u});\n\
    \        } else {\n            to_nonmst[u].push_front({E, v}), to_nonmst[v].push_front({E,\
    \ u});\n        }\n        edges.emplace_back(u, v);\n        E++;\n    }\n\n\
    \    std::vector<std::pair<int, int>> _ret;\n    std::vector<char> _visited;\n\
    \    std::vector<char> _edge_used;\n    void _dfs(int now, int prv) {\n      \
    \  _visited[now] = 1;\n        int prveid = -1;\n        std::vector<int> available_edges;\n\
    \        for (auto ev : to_mst[now]) {\n            int eid, nxt;\n          \
    \  std::tie(eid, nxt) = ev;\n            if (nxt == prv)\n                prveid\
    \ = eid;\n            else {\n                _dfs(nxt, now);\n              \
    \  if (!_edge_used[eid]) available_edges.push_back(eid);\n            }\n    \
    \    }\n        for (auto ev : to_nonmst[now]) {\n            int eid, nxt;\n\
    \            std::tie(eid, nxt) = ev;\n            if (!_edge_used[eid]) available_edges.push_back(eid);\n\
    \        }\n        if ((available_edges.size() & 1) and prv != -1) available_edges.push_back(prveid);\n\
    \        for (unsigned h = 0; h + 1 < available_edges.size(); h += 2) {\n    \
    \        int e1 = available_edges[h], e2 = available_edges[h + 1];\n         \
    \   _edge_used[e1] = _edge_used[e2] = 1;\n            _ret.emplace_back(e1, e2);\n\
    \        }\n    }\n    std::vector<std::pair<int, int>> run() { // \u8FBA\u756A\
    \u53F7\uFF080-origin, \u8FFD\u52A0\u9806\uFF09\u306E\u7D44\u306E\u5217\u3092\u8FD4\
    \u3059\n        _ret.clear();\n        _visited.assign(V, 0);\n        _edge_used.assign(E,\
    \ 0);\n        for (int i = 0; i < V; i++) {\n            if (!_visited[i]) _dfs(i,\
    \ -1);\n        }\n        return _ret;\n    }\n};\n"
  code: "#pragma once\n#include \"../data_structure/light_forward_list.hpp\"\n#include\
    \ \"../unionfind/unionfind.hpp\"\n#include <cassert>\n#include <tuple>\n#include\
    \ <utility>\n#include <vector>\n\n// \u7121\u5411\u30B0\u30E9\u30D5\u3092\u9577\
    \u30552\u306E\u9053\uFF08**\u9589\u8DEF\u3092\u542B\u3080**\uFF09\u3078\u5206\u89E3\
    \n// \u5404\u9023\u7D50\u6210\u5206\u306B\u3064\u3044\u3066\uFF0C\u8FBA\u306E\u672C\
    \u6570\u304C\u5076\u6570\u306A\u3089\u5B8C\u5168\u306A\u5206\u89E3\u304C\u53EF\
    \u80FD\n// Complexity: O(V + E)\n// Verify: - https://codeforces.com/contest/1519/problem/E\n\
    //         - https://atcoder.jp/contests/agc035/tasks/agc035_b\nstruct PathsOfLength2Decomposition\
    \ {\n    int V, E;\n    std::vector<std::pair<int, int>> edges;\n    std::vector<light_forward_list<std::pair<int,\
    \ int>>> to_nonmst;\n    std::vector<light_forward_list<std::pair<int, int>>>\
    \ to_mst;\n    UnionFind uf;\n    void _init(int V_) {\n        V = V_, E = 0;\n\
    \        edges.clear();\n        to_nonmst.assign(V, {});\n        to_mst.assign(V,\
    \ {});\n        uf = UnionFind(V);\n    }\n    PathsOfLength2Decomposition(int\
    \ V = 0) { _init(V); }\n    void add_edge(int u, int v) {\n        assert(u >=\
    \ 0 and u < V);\n        assert(v >= 0 and v < V);\n        if (uf.unite(u, v))\
    \ {\n            to_mst[u].push_front({E, v}), to_mst[v].push_front({E, u});\n\
    \        } else {\n            to_nonmst[u].push_front({E, v}), to_nonmst[v].push_front({E,\
    \ u});\n        }\n        edges.emplace_back(u, v);\n        E++;\n    }\n\n\
    \    std::vector<std::pair<int, int>> _ret;\n    std::vector<char> _visited;\n\
    \    std::vector<char> _edge_used;\n    void _dfs(int now, int prv) {\n      \
    \  _visited[now] = 1;\n        int prveid = -1;\n        std::vector<int> available_edges;\n\
    \        for (auto ev : to_mst[now]) {\n            int eid, nxt;\n          \
    \  std::tie(eid, nxt) = ev;\n            if (nxt == prv)\n                prveid\
    \ = eid;\n            else {\n                _dfs(nxt, now);\n              \
    \  if (!_edge_used[eid]) available_edges.push_back(eid);\n            }\n    \
    \    }\n        for (auto ev : to_nonmst[now]) {\n            int eid, nxt;\n\
    \            std::tie(eid, nxt) = ev;\n            if (!_edge_used[eid]) available_edges.push_back(eid);\n\
    \        }\n        if ((available_edges.size() & 1) and prv != -1) available_edges.push_back(prveid);\n\
    \        for (unsigned h = 0; h + 1 < available_edges.size(); h += 2) {\n    \
    \        int e1 = available_edges[h], e2 = available_edges[h + 1];\n         \
    \   _edge_used[e1] = _edge_used[e2] = 1;\n            _ret.emplace_back(e1, e2);\n\
    \        }\n    }\n    std::vector<std::pair<int, int>> run() { // \u8FBA\u756A\
    \u53F7\uFF080-origin, \u8FFD\u52A0\u9806\uFF09\u306E\u7D44\u306E\u5217\u3092\u8FD4\
    \u3059\n        _ret.clear();\n        _visited.assign(V, 0);\n        _edge_used.assign(E,\
    \ 0);\n        for (int i = 0; i < V; i++) {\n            if (!_visited[i]) _dfs(i,\
    \ -1);\n        }\n        return _ret;\n    }\n};\n"
  dependsOn:
  - data_structure/light_forward_list.hpp
  - unionfind/unionfind.hpp
  isVerificationFile: false
  path: graph/paths_of_length_two_decomposition.hpp
  requiredBy: []
  timestamp: '2021-04-30 17:31:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/paths_of_length_two_decomposition.hpp
layout: document
title: "\u7121\u5411\u30B0\u30E9\u30D5\u306E\u9577\u3055 2 \u306E\u30D1\u30B9\u3078\
  \u306E\u5206\u89E3"
---

## 使用方法

```cpp
PathsOfLength2Decomposition graph(N);
for (int m = 0; m < M; m++) {
    int a, b;
    cin >> a >> b;
    graph.add_edge(a - 1, b - 1);
}
vector<pair<int, int>> pairs = graph.run();
```

## 背景

- まず全域森を構成する．
- 全域森に使用しなかった辺のみに着目し，各頂点の次数が 1 以下になるまで長さ 2 のパスを作れるだけ作る．
- 最後に，全域森を DFS し，葉の方から各頂点で辺を使い切る．
- この構成より，各連結成分について辺の本数が偶数なら全ての辺を使い切ることが可能（奇数なら DFS の根で辺が一つ余る）．

## 問題例

- [AtCoder Grand Contest 035 B - Even Degrees](https://atcoder.jp/contests/agc035/tasks/agc035_b)
  - 連結なので，辺の本数が偶数なら解ける．
- [Educational Codeforces Round 108 (Rated for Div. 2) E. Off by One](https://codeforces.com/contest/1519/problem/E)
