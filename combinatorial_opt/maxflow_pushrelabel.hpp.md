---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/maxflow.pushrelabel.test.cpp
    title: combinatorial_opt/test/maxflow.pushrelabel.test.cpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
    title: combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 2 \"combinatorial_opt/maxflow_pushrelabel.hpp\"\n#include <cassert>\n\
    #include <limits>\n#include <utility>\n#include <vector>\n\n// Maxflow (push-relabel,\
    \ highest-label)\n// Complexity: O(N^2 M^(1/2))\ntemplate <class Cap, int GlobalRelabelFreq\
    \ = 5, bool UseGapRelabeling = true>\nstruct mf_pushrelabel {\n    struct pque_\
    \ {\n        std::vector<std::pair<int, int>> even_, odd_;\n        int se, so;\n\
    \        void init(int n) { even_.resize(n), odd_.resize(n), se = so = 0; };\n\
    \        void clear() { se = so = 0; }\n        bool empty() const { return se\
    \ + so == 0; }\n        void push(int i, int h) { (h & 1 ? odd_[so++] : even_[se++])\
    \ = {i, h}; }\n        int highest() const {\n            int a = se ? even_[se\
    \ - 1].second : -1, b = so ? odd_[so - 1].second : -1;\n            return a >\
    \ b ? a : b;\n        }\n        int pop() {\n            if (!se or (so and odd_[so\
    \ - 1].second > even_[se - 1].second))\n                return odd_[--so].first;\n\
    \            return even_[--se].first;\n        }\n    } pque;\n    int _n;\n\
    \    struct _edge {\n        int to, rev;\n        Cap cap;\n    };\n    std::vector<std::vector<_edge>>\
    \ g;\n    std::vector<std::pair<int, int>> pos;\n    mf_pushrelabel(int n) : _n(n),\
    \ g(n) {\n        static_assert(GlobalRelabelFreq >= 0, \"Global relabel parameter\
    \ must be nonnegative.\");\n    }\n    int add_edge(int from, int to, Cap cap)\
    \ {\n        assert(0 <= from and from < _n);\n        assert(0 <= to and to <\
    \ _n);\n        assert(0 <= cap);\n        int m = int(pos.size());\n        pos.emplace_back(from,\
    \ int(g[from].size()));\n        int from_id = g[from].size(), to_id = g[to].size()\
    \ + (from == to);\n        g[from].push_back({to, to_id, cap});\n        g[to].push_back({from,\
    \ from_id, Cap(0)});\n        return m;\n    }\n\n    struct edge {\n        int\
    \ from, to;\n        Cap cap, flow;\n    };\n\n    edge get_edge(int i) const\
    \ {\n        int m = int(pos.size());\n        assert(0 <= i and i < m);\n   \
    \     auto e = g[pos[i].first][pos[i].second], re = g[e.to][e.rev];\n        return\
    \ edge{pos[i].first, e.co, e.cap + re.cap, re.cap};\n    }\n    std::vector<edge>\
    \ edges() const {\n        std::vector<edge> ret(pos.size());\n        for (int\
    \ i = 0; i < int(pos.size()); i++) ret[i] = get_edge(i);\n        return ret;\n\
    \    }\n\n    std::vector<int> dist;\n    std::vector<int> dcnt;\n    std::vector<Cap>\
    \ excess;\n    int gap;\n    void global_relabeling(int t) {\n        dist.assign(_n,\
    \ _n), dist[t] = 0;\n        static std::vector<int> q;\n        if (q.empty())\
    \ q.resize(_n);\n        q[0] = t;\n        int qb = 0, qe = 1;\n        pque.clear();\n\
    \        if (UseGapRelabeling) gap = 1, dcnt.assign(_n + 1, 0);\n\n        while\
    \ (qb < qe) {\n            int now = q[qb++];\n            if (UseGapRelabeling)\
    \ gap = dist[now] + 1, dcnt[dist[now]]++;\n            if (excess[now] > 0) pque.push(now,\
    \ dist[now]);\n            for (const auto &e : g[now]) {\n                if\
    \ (g[e.to][e.rev].cap and dist[e.to] == _n) {\n                    dist[e.to]\
    \ = dist[now] + 1;\n                    q[qe++] = e.to;\n                }\n \
    \           }\n        }\n    }\n    Cap flow(int s, int t, bool retrieve = true)\
    \ {\n        return flow(s, t, std::numeric_limits<Cap>::max(), retrieve);\n \
    \   }\n    Cap flow(int s, int t, Cap flow_limit, bool retrieve = true) {\n  \
    \      assert(0 <= s and s < _n);\n        assert(0 <= t and t < _n);\n      \
    \  assert(s != t);\n        excess.resize(_n, 0);\n        excess[s] += flow_limit,\
    \ excess[t] -= flow_limit;\n        dist.assign(_n, 0);\n        dist[s] = _n;\n\
    \        if (UseGapRelabeling) gap = 1, dcnt.assign(_n + 1, 0), dcnt[0] = _n -\
    \ 1;\n        pque.init(_n);\n        for (auto &e : g[s]) _push(s, e);\n    \
    \    _run(t);\n        Cap ret = excess[t] + flow_limit;\n        excess[s] +=\
    \ excess[t], excess[t] = 0;\n        if (retrieve) {\n            global_relabeling(s);\n\
    \            _run(s);\n            assert(excess == std::vector<Cap>(_n, 0));\n\
    \        }\n        return ret;\n    }\n    void _run(int t) {\n        if (GlobalRelabelFreq)\
    \ global_relabeling(t);\n        int tick = pos.size() * GlobalRelabelFreq;\n\
    \        while (!pque.empty()) {\n            int i = pque.pop();\n          \
    \  if (UseGapRelabeling and dist[i] > gap) continue;\n            int dnxt = _n\
    \ * 2 - 1;\n            for (auto &e : g[i]) {\n                if (!e.cap) continue;\n\
    \                if (dist[e.to] == dist[i] - 1) {\n                    _push(i,\
    \ e);\n                    if (excess[i] == 0) break;\n                } else\
    \ {\n                    if (dist[e.to] + 1 < dnxt) dnxt = dist[e.to] + 1;\n \
    \               }\n            }\n            if (excess[i] > 0) {\n         \
    \       if (UseGapRelabeling) {\n                    if (dnxt != dist[i] and dcnt[dist[i]]\
    \ == 1 and dist[i] < gap) gap = dist[i];\n                    if (dnxt == gap)\
    \ gap++;\n                    while (pque.highest() > gap) pque.pop();\n     \
    \               if (dnxt > gap) dnxt = _n;\n                    if (dist[i] !=\
    \ dnxt) dcnt[dist[i]]--, dcnt[dnxt]++;\n                }\n                dist[i]\
    \ = dnxt;\n                if (!UseGapRelabeling or dist[i] < gap) pque.push(i,\
    \ dist[i]);\n            }\n            if (GlobalRelabelFreq and --tick == 0)\
    \ {\n                tick = pos.size() * GlobalRelabelFreq, global_relabeling(t);\n\
    \            }\n        }\n        return;\n    }\n\n    void _push(int i, _edge\
    \ &e) {\n        Cap delta = e.cap < excess[i] ? e.cap : excess[i];\n        excess[i]\
    \ -= delta, e.cap -= delta;\n        excess[e.to] += delta, g[e.to][e.rev].cap\
    \ += delta;\n        if (excess[e.to] > 0 and excess[e.to] <= delta) {\n     \
    \       if (!UseGapRelabeling or dist[e.to] <= gap) pque.push(e.to, dist[e.to]);\n\
    \        }\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\n// Maxflow (push-relabel, highest-label)\n// Complexity:\
    \ O(N^2 M^(1/2))\ntemplate <class Cap, int GlobalRelabelFreq = 5, bool UseGapRelabeling\
    \ = true>\nstruct mf_pushrelabel {\n    struct pque_ {\n        std::vector<std::pair<int,\
    \ int>> even_, odd_;\n        int se, so;\n        void init(int n) { even_.resize(n),\
    \ odd_.resize(n), se = so = 0; };\n        void clear() { se = so = 0; }\n   \
    \     bool empty() const { return se + so == 0; }\n        void push(int i, int\
    \ h) { (h & 1 ? odd_[so++] : even_[se++]) = {i, h}; }\n        int highest() const\
    \ {\n            int a = se ? even_[se - 1].second : -1, b = so ? odd_[so - 1].second\
    \ : -1;\n            return a > b ? a : b;\n        }\n        int pop() {\n \
    \           if (!se or (so and odd_[so - 1].second > even_[se - 1].second))\n\
    \                return odd_[--so].first;\n            return even_[--se].first;\n\
    \        }\n    } pque;\n    int _n;\n    struct _edge {\n        int to, rev;\n\
    \        Cap cap;\n    };\n    std::vector<std::vector<_edge>> g;\n    std::vector<std::pair<int,\
    \ int>> pos;\n    mf_pushrelabel(int n) : _n(n), g(n) {\n        static_assert(GlobalRelabelFreq\
    \ >= 0, \"Global relabel parameter must be nonnegative.\");\n    }\n    int add_edge(int\
    \ from, int to, Cap cap) {\n        assert(0 <= from and from < _n);\n       \
    \ assert(0 <= to and to < _n);\n        assert(0 <= cap);\n        int m = int(pos.size());\n\
    \        pos.emplace_back(from, int(g[from].size()));\n        int from_id = g[from].size(),\
    \ to_id = g[to].size() + (from == to);\n        g[from].push_back({to, to_id,\
    \ cap});\n        g[to].push_back({from, from_id, Cap(0)});\n        return m;\n\
    \    }\n\n    struct edge {\n        int from, to;\n        Cap cap, flow;\n \
    \   };\n\n    edge get_edge(int i) const {\n        int m = int(pos.size());\n\
    \        assert(0 <= i and i < m);\n        auto e = g[pos[i].first][pos[i].second],\
    \ re = g[e.to][e.rev];\n        return edge{pos[i].first, e.co, e.cap + re.cap,\
    \ re.cap};\n    }\n    std::vector<edge> edges() const {\n        std::vector<edge>\
    \ ret(pos.size());\n        for (int i = 0; i < int(pos.size()); i++) ret[i] =\
    \ get_edge(i);\n        return ret;\n    }\n\n    std::vector<int> dist;\n   \
    \ std::vector<int> dcnt;\n    std::vector<Cap> excess;\n    int gap;\n    void\
    \ global_relabeling(int t) {\n        dist.assign(_n, _n), dist[t] = 0;\n    \
    \    static std::vector<int> q;\n        if (q.empty()) q.resize(_n);\n      \
    \  q[0] = t;\n        int qb = 0, qe = 1;\n        pque.clear();\n        if (UseGapRelabeling)\
    \ gap = 1, dcnt.assign(_n + 1, 0);\n\n        while (qb < qe) {\n            int\
    \ now = q[qb++];\n            if (UseGapRelabeling) gap = dist[now] + 1, dcnt[dist[now]]++;\n\
    \            if (excess[now] > 0) pque.push(now, dist[now]);\n            for\
    \ (const auto &e : g[now]) {\n                if (g[e.to][e.rev].cap and dist[e.to]\
    \ == _n) {\n                    dist[e.to] = dist[now] + 1;\n                \
    \    q[qe++] = e.to;\n                }\n            }\n        }\n    }\n   \
    \ Cap flow(int s, int t, bool retrieve = true) {\n        return flow(s, t, std::numeric_limits<Cap>::max(),\
    \ retrieve);\n    }\n    Cap flow(int s, int t, Cap flow_limit, bool retrieve\
    \ = true) {\n        assert(0 <= s and s < _n);\n        assert(0 <= t and t <\
    \ _n);\n        assert(s != t);\n        excess.resize(_n, 0);\n        excess[s]\
    \ += flow_limit, excess[t] -= flow_limit;\n        dist.assign(_n, 0);\n     \
    \   dist[s] = _n;\n        if (UseGapRelabeling) gap = 1, dcnt.assign(_n + 1,\
    \ 0), dcnt[0] = _n - 1;\n        pque.init(_n);\n        for (auto &e : g[s])\
    \ _push(s, e);\n        _run(t);\n        Cap ret = excess[t] + flow_limit;\n\
    \        excess[s] += excess[t], excess[t] = 0;\n        if (retrieve) {\n   \
    \         global_relabeling(s);\n            _run(s);\n            assert(excess\
    \ == std::vector<Cap>(_n, 0));\n        }\n        return ret;\n    }\n    void\
    \ _run(int t) {\n        if (GlobalRelabelFreq) global_relabeling(t);\n      \
    \  int tick = pos.size() * GlobalRelabelFreq;\n        while (!pque.empty()) {\n\
    \            int i = pque.pop();\n            if (UseGapRelabeling and dist[i]\
    \ > gap) continue;\n            int dnxt = _n * 2 - 1;\n            for (auto\
    \ &e : g[i]) {\n                if (!e.cap) continue;\n                if (dist[e.to]\
    \ == dist[i] - 1) {\n                    _push(i, e);\n                    if\
    \ (excess[i] == 0) break;\n                } else {\n                    if (dist[e.to]\
    \ + 1 < dnxt) dnxt = dist[e.to] + 1;\n                }\n            }\n     \
    \       if (excess[i] > 0) {\n                if (UseGapRelabeling) {\n      \
    \              if (dnxt != dist[i] and dcnt[dist[i]] == 1 and dist[i] < gap) gap\
    \ = dist[i];\n                    if (dnxt == gap) gap++;\n                  \
    \  while (pque.highest() > gap) pque.pop();\n                    if (dnxt > gap)\
    \ dnxt = _n;\n                    if (dist[i] != dnxt) dcnt[dist[i]]--, dcnt[dnxt]++;\n\
    \                }\n                dist[i] = dnxt;\n                if (!UseGapRelabeling\
    \ or dist[i] < gap) pque.push(i, dist[i]);\n            }\n            if (GlobalRelabelFreq\
    \ and --tick == 0) {\n                tick = pos.size() * GlobalRelabelFreq, global_relabeling(t);\n\
    \            }\n        }\n        return;\n    }\n\n    void _push(int i, _edge\
    \ &e) {\n        Cap delta = e.cap < excess[i] ? e.cap : excess[i];\n        excess[i]\
    \ -= delta, e.cap -= delta;\n        excess[e.to] += delta, g[e.to][e.rev].cap\
    \ += delta;\n        if (excess[e.to] > 0 and excess[e.to] <= delta) {\n     \
    \       if (!UseGapRelabeling or dist[e.to] <= gap) pque.push(e.to, dist[e.to]);\n\
    \        }\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/maxflow_pushrelabel.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - combinatorial_opt/test/maxflow.pushrelabel.test.cpp
  - combinatorial_opt/test/maxflow.pushrelabel.yuki957.test.cpp
documentation_of: combinatorial_opt/maxflow_pushrelabel.hpp
layout: document
title: "Maxflow (push-relabel, Goldberg & Tarjan) \uFF08Push-relabel \u306B\u3088\u308B\
  \u6700\u5927\u6D41\uFF09"
---

Push-relabel による最大流．Highest-label rule に従うことで時間計算量は $O(n^2 \sqrt{m})$．更にいくつかのヒューリスティックを入れることで定数倍が改善される．Dinic 法の計算量が $O(n^2 m)$ であるのに対し最悪計算量はオーダーレベルで改善されているが，特殊なグラフで Dinic の計算量が更に改善される点などの事情があるため，常にこちらを使用すればよいという訳でもない．

## 使用方法

- `mf_pushrelabel<CapType, int GlobalRelabelFreq, bool UseGapRelabeling> graph(int N)` : $N$ 頂点のグラフを作成する．辺容量は整数型 `CapType`．`GlobalRelabelFreq` の値 $k$ が正の場合，グラフの辺の本数を $m$ として $km$ 回の反復毎に global relabelling heuristics を行う．また，`UseGapRelabeling` が真の場合，gap relabeling heuristics を行う．いずれかの heuristics を有効化し，かつ `flow()` の引数で `retrieve = false` を選択した場合，アルゴリズムの停止時点で変数（プリフロー）がフロー条件を必ずしも満たさないことに注意．その他インターフェースは AC Library と同様．
- `graph.add_edge(int u, int v, CapType cap)` 辺を張る．
- `CapType ret = graph.flow(s, t, flow_limit, retrieve)` 最大流を求める．

```cpp
mf_pushrelabel<int, 1 << 29, 10, true> graph(N);
while (E--) {
    int u, v, c;
    cin >> u >> v >> c;
    graph.add_edge(u, v, c);
}
int f = graph.flow(s, t);
```

## 問題例

- [No.957 植林 - yukicoder](https://yukicoder.me/problems/no/957)
- [AtCoder Library Practice Contest D - Maxflow](https://atcoder.jp/contests/practice2/tasks/practice2_d)
- [CPSCO2019 Session2 F - Treasure Collector](https://atcoder.jp/contests/cpsco2019-s2/tasks/cpsco2019_s2_f)

## リンク

- [1] A. V. Goldberg and R. E. Tarjan, "A new approach to the maximum-flow problem,"
  Journal of the ACM, 35(4), 921-940, 1988.
- [2] B. V. Cherkassky and A. V. Goldberg, "On implementing the push-relabel method for the maximum flow problem,"
  Algorithmica, 19(4), 390-410, 1997.
- [ORIE 633: Network Flows](https://people.orie.cornell.edu/dpw/orie633/)
- [ORIE 6330: Network Flows](https://people.orie.cornell.edu/dpw/orie6330/)
- [TL Issue in the #659 (Div. 1) Problem F - Codeforces](https://codeforces.com/blog/entry/80627) 時間制限が厳しい最大流の問題．
- [or-tools/max_flow.h at stable · google/or-tools](https://github.com/google/or-tools/blob/stable/ortools/graph/max_flow.h) highest-label を高速に管理するデータ構造の実装が参考になる．
