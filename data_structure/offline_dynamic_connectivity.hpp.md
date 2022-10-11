---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
    title: data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/offline_dynamic_connectivity.hpp\"\n#include\
    \ <algorithm>\n#include <limits>\n#include <set>\n#include <utility>\n#include\
    \ <vector>\n\nenum class DyConOperation {\n    Begins = 1,\n    Ends = 2,\n  \
    \  Event = 3,\n};\n\ntemplate <class Tick = int> struct offline_dynamic_connectivity\
    \ {\n\n    std::vector<std::pair<Tick, int>> ops;\n\n    struct Edge {\n     \
    \   Tick since;\n        Tick until;\n        int edge_id;\n    };\n    std::vector<Edge>\
    \ edges;\n\n    offline_dynamic_connectivity() = default;\n\n    void add_observation(Tick\
    \ clk, int event_id) { ops.emplace_back(clk, event_id); }\n\n    void apply_time_range(Tick\
    \ since, Tick until, int edge_id) {\n        edges.push_back(Edge{since, until,\
    \ edge_id});\n    }\n\n    struct Procedure {\n        DyConOperation op;\n  \
    \      int id_;\n    };\n\n    std::vector<std::vector<Procedure>> nodes;\n  \
    \  std::vector<Procedure> ret_;\n\n    void rec(int now) {\n        ret_.insert(ret_.end(),\
    \ nodes[now].cbegin(), nodes[now].cend());\n        if (now * 2 < int(nodes.size()))\
    \ rec(now * 2);\n        if (now * 2 + 1 < int(nodes.size())) rec(now * 2 + 1);\n\
    \n        for (auto itr = nodes[now].rbegin(); itr != nodes[now].rend(); ++itr)\
    \ {\n            if (itr->op == DyConOperation::Begins) {\n                ret_.push_back(Procedure{DyConOperation::Ends,\
    \ itr->id_});\n            }\n        }\n    }\n\n    std::vector<Procedure> generate()\
    \ {\n        if (ops.empty()) return {};\n\n        std::vector<Tick> query_ts;\n\
    \        {\n            query_ts.reserve(ops.size());\n            for (const\
    \ auto &p : ops) query_ts.push_back(p.first);\n            std::sort(query_ts.begin(),\
    \ query_ts.end());\n            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()),\
    \ query_ts.end());\n\n            std::vector<int> t_use(query_ts.size() + 1);\n\
    \            t_use.at(0) = 1;\n\n            for (const Edge &e : edges) {\n \
    \               t_use[std::lower_bound(query_ts.begin(), query_ts.end(), e.since)\
    \ - query_ts.begin()] =\n                    1;\n                t_use[std::lower_bound(query_ts.begin(),\
    \ query_ts.end(), e.until) - query_ts.begin()] =\n                    1;\n   \
    \         }\n            for (int i = 1; i < int(query_ts.size()); ++i) {\n  \
    \              if (!t_use[i]) query_ts[i] = query_ts[i - 1];\n            }\n\n\
    \            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()), query_ts.end());\n\
    \        }\n\n        const int N = query_ts.size();\n        int D = 1;\n   \
    \     while (D < int(query_ts.size())) D *= 2;\n\n        nodes.assign(D + N,\
    \ {});\n\n        for (const Edge &e : edges) {\n            int l =\n       \
    \         D + (std::lower_bound(query_ts.begin(), query_ts.end(), e.since) - query_ts.begin());\n\
    \            int r =\n                D + (std::lower_bound(query_ts.begin(),\
    \ query_ts.end(), e.until) - query_ts.begin());\n\n            while (l < r) {\n\
    \                if (l & 1) nodes[l++].push_back(Procedure{DyConOperation::Begins,\
    \ e.edge_id});\n                if (r & 1) nodes[--r].push_back(Procedure{DyConOperation::Begins,\
    \ e.edge_id});\n                l >>= 1, r >>= 1;\n            }\n        }\n\n\
    \        for (const auto &op : ops) {\n            int clk = op.first, qid = op.second;\n\
    \            int t =\n                D + (std::upper_bound(query_ts.begin(),\
    \ query_ts.end(), clk) - query_ts.begin()) - 1;\n            nodes[t].push_back(Procedure{DyConOperation::Event,\
    \ qid});\n        }\n        ret_.clear();\n        rec(1);\n        return ret_;\n\
    \    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <limits>\n#include <set>\n#include\
    \ <utility>\n#include <vector>\n\nenum class DyConOperation {\n    Begins = 1,\n\
    \    Ends = 2,\n    Event = 3,\n};\n\ntemplate <class Tick = int> struct offline_dynamic_connectivity\
    \ {\n\n    std::vector<std::pair<Tick, int>> ops;\n\n    struct Edge {\n     \
    \   Tick since;\n        Tick until;\n        int edge_id;\n    };\n    std::vector<Edge>\
    \ edges;\n\n    offline_dynamic_connectivity() = default;\n\n    void add_observation(Tick\
    \ clk, int event_id) { ops.emplace_back(clk, event_id); }\n\n    void apply_time_range(Tick\
    \ since, Tick until, int edge_id) {\n        edges.push_back(Edge{since, until,\
    \ edge_id});\n    }\n\n    struct Procedure {\n        DyConOperation op;\n  \
    \      int id_;\n    };\n\n    std::vector<std::vector<Procedure>> nodes;\n  \
    \  std::vector<Procedure> ret_;\n\n    void rec(int now) {\n        ret_.insert(ret_.end(),\
    \ nodes[now].cbegin(), nodes[now].cend());\n        if (now * 2 < int(nodes.size()))\
    \ rec(now * 2);\n        if (now * 2 + 1 < int(nodes.size())) rec(now * 2 + 1);\n\
    \n        for (auto itr = nodes[now].rbegin(); itr != nodes[now].rend(); ++itr)\
    \ {\n            if (itr->op == DyConOperation::Begins) {\n                ret_.push_back(Procedure{DyConOperation::Ends,\
    \ itr->id_});\n            }\n        }\n    }\n\n    std::vector<Procedure> generate()\
    \ {\n        if (ops.empty()) return {};\n\n        std::vector<Tick> query_ts;\n\
    \        {\n            query_ts.reserve(ops.size());\n            for (const\
    \ auto &p : ops) query_ts.push_back(p.first);\n            std::sort(query_ts.begin(),\
    \ query_ts.end());\n            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()),\
    \ query_ts.end());\n\n            std::vector<int> t_use(query_ts.size() + 1);\n\
    \            t_use.at(0) = 1;\n\n            for (const Edge &e : edges) {\n \
    \               t_use[std::lower_bound(query_ts.begin(), query_ts.end(), e.since)\
    \ - query_ts.begin()] =\n                    1;\n                t_use[std::lower_bound(query_ts.begin(),\
    \ query_ts.end(), e.until) - query_ts.begin()] =\n                    1;\n   \
    \         }\n            for (int i = 1; i < int(query_ts.size()); ++i) {\n  \
    \              if (!t_use[i]) query_ts[i] = query_ts[i - 1];\n            }\n\n\
    \            query_ts.erase(std::unique(query_ts.begin(), query_ts.end()), query_ts.end());\n\
    \        }\n\n        const int N = query_ts.size();\n        int D = 1;\n   \
    \     while (D < int(query_ts.size())) D *= 2;\n\n        nodes.assign(D + N,\
    \ {});\n\n        for (const Edge &e : edges) {\n            int l =\n       \
    \         D + (std::lower_bound(query_ts.begin(), query_ts.end(), e.since) - query_ts.begin());\n\
    \            int r =\n                D + (std::lower_bound(query_ts.begin(),\
    \ query_ts.end(), e.until) - query_ts.begin());\n\n            while (l < r) {\n\
    \                if (l & 1) nodes[l++].push_back(Procedure{DyConOperation::Begins,\
    \ e.edge_id});\n                if (r & 1) nodes[--r].push_back(Procedure{DyConOperation::Begins,\
    \ e.edge_id});\n                l >>= 1, r >>= 1;\n            }\n        }\n\n\
    \        for (const auto &op : ops) {\n            int clk = op.first, qid = op.second;\n\
    \            int t =\n                D + (std::upper_bound(query_ts.begin(),\
    \ query_ts.end(), clk) - query_ts.begin()) - 1;\n            nodes[t].push_back(Procedure{DyConOperation::Event,\
    \ qid});\n        }\n        ret_.clear();\n        rec(1);\n        return ret_;\n\
    \    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/offline_dynamic_connectivity.hpp
  requiredBy: []
  timestamp: '2022-10-11 22:40:37+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - data_structure/test/dynamic_graph_vertex_add_component_sum.test.cpp
documentation_of: data_structure/offline_dynamic_connectivity.hpp
layout: document
title: Offline dynamic connectivity
---

オフライン版の dynamic connectivity （の抽象化実装）．

以下の性質を満たす何らかのオブジェクト $x$ と，$x$ に対するさまざまな作用たち $f\_i$ を考えたい：

- 作用たちは可換．すなわち任意の作用 $f, g$ について $f \circ g = g \circ f$ が常に成立．
- 作用を及ぼした後の $x$ の計算と，直近に及ぼした作用の undo 操作が（十分高速に）可能．

このとき、本コードは以下のオフラインクエリ群の高速処理をサポートする．

- $l \leq t < r$ を満たす時刻 $t$ においてのみ $x$ に対して作用 $f$ を及ぼす．
- ある時刻 $t$ における $x$ の何らかの特徴量を取得する．

汎用化のため具体的なオブジェクト $x$ や作用 $f$ たちの管理は本コードでは行っておらず，実装者が UnionFind などを別途用意する必要がある．

## 原理

入力に登場する時刻 $t$ を列挙し二分木を構築する．作用クエリをセグメント木の要領で頂点に効率的に配置し，二分木を DFS しながら作用の演算・undo 操作・特徴量取得を行えばよい．

## 使用方法

```cpp
offline_dynamic_connectivity<int> dc;

dc.apply_time_range(0, 100, 1);  // 時刻 [0, 100) の範囲で辺番号 1 を追加
dc.add_observation(50, 2);  // 時刻 50 に取得クエリ 2 を追加

for (auto p : dc.generate()) {
    if (p.op == DyConOperation::Begins) {
        int edge_id = p.id_;
        // 辺番号 edge_id を張る
    } else if (p.op == DyConOperation::Ends) {
        // undo 操作を一回行う
    } else if (p.op == DyConOperation::Event) {
        int query_id = p.id_;
        // 取得クエリ query_id を行う
    }
}
```

### 具体例：無向グラフの連結成分に関する情報取得

オブジェクト $x$ を $n$ 頂点の無向グラフとして，作用として

- 2 頂点間の辺追加操作
- ある頂点の重み更新

の 2 つ，特徴量として「連結成分の頂点重み和」を考えると，これは undo 可能 UnionFind で効率的に処理できる．よって本ライブラリを利用することで高速に解ける（「問題例」の "Dynamic Graph Vertex Add Component Sum" が該当）．

## 問題例

- [Library Checker: Dynamic Graph Vertex Add Component Sum](https://judge.yosupo.jp/problem/dynamic_graph_vertex_add_component_sum)
- [Educational Codeforces Round 38 (Rated for Div. 2) G. Shortest Path Queries](https://codeforces.com/contest/938/problem/G)
