---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: flow/maxflow.hpp
    title: flow/maxflow.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp>
    - https://snuke.hatenablog.com/entry/2016/07/10/043918>
  bundledCode: "#line 2 \"flow/maxflow.hpp\"\n\n#include <algorithm>\n#include <cassert>\n\
    #include <limits>\n#include <vector>\n\n// CUT begin\n// MaxFlow based and AtCoder\
    \ Library, single class, no namespace, no private variables, compatible with C++11\n\
    // Reference: <https://atcoder.github.io/ac-library/production/document_ja/maxflow.html>\n\
    template <class Cap> struct mf_graph {\n    struct simple_queue_int {\n      \
    \  std::vector<int> payload;\n        int pos = 0;\n        void reserve(int n)\
    \ { payload.reserve(n); }\n        int size() const { return int(payload.size())\
    \ - pos; }\n        bool empty() const { return pos == int(payload.size()); }\n\
    \        void push(const int &t) { payload.push_back(t); }\n        int &front()\
    \ { return payload[pos]; }\n        void clear() {\n            payload.clear();\n\
    \            pos = 0;\n        }\n        void pop() { pos++; }\n    };\n\n  \
    \  mf_graph() : _n(0) {}\n    mf_graph(int n) : _n(n), g(n) {}\n\n    int add_edge(int\
    \ from, int to, Cap cap) {\n        assert(0 <= from && from < _n);\n        assert(0\
    \ <= to && to < _n);\n        assert(0 <= cap);\n        int m = int(pos.size());\n\
    \        pos.push_back({from, int(g[from].size())});\n        int from_id = int(g[from].size());\n\
    \        int to_id = int(g[to].size());\n        if (from == to) to_id++;\n  \
    \      g[from].push_back(_edge{to, to_id, cap});\n        g[to].push_back(_edge{from,\
    \ from_id, 0});\n        return m;\n    }\n\n    struct edge {\n        int from,\
    \ to;\n        Cap cap, flow;\n    };\n\n    edge get_edge(int i) {\n        int\
    \ m = int(pos.size());\n        assert(0 <= i && i < m);\n        auto _e = g[pos[i].first][pos[i].second];\n\
    \        auto _re = g[_e.to][_e.rev];\n        return edge{pos[i].first, _e.to,\
    \ _e.cap + _re.cap, _re.cap};\n    }\n    std::vector<edge> edges() {\n      \
    \  int m = int(pos.size());\n        std::vector<edge> result;\n        for (int\
    \ i = 0; i < m; i++) { result.push_back(get_edge(i)); }\n        return result;\n\
    \    }\n    void change_edge(int i, Cap new_cap, Cap new_flow) {\n        int\
    \ m = int(pos.size());\n        assert(0 <= i && i < m);\n        assert(0 <=\
    \ new_flow && new_flow <= new_cap);\n        auto &_e = g[pos[i].first][pos[i].second];\n\
    \        auto &_re = g[_e.to][_e.rev];\n        _e.cap = new_cap - new_flow;\n\
    \        _re.cap = new_flow;\n    }\n\n    std::vector<int> level, iter;\n   \
    \ simple_queue_int que;\n\n    void _bfs(int s, int t) {\n        std::fill(level.begin(),\
    \ level.end(), -1);\n        level[s] = 0;\n        que.clear();\n        que.push(s);\n\
    \        while (!que.empty()) {\n            int v = que.front();\n          \
    \  que.pop();\n            for (auto e : g[v]) {\n                if (e.cap ==\
    \ 0 || level[e.to] >= 0) continue;\n                level[e.to] = level[v] + 1;\n\
    \                if (e.to == t) return;\n                que.push(e.to);\n   \
    \         }\n        }\n    }\n    Cap _dfs(int v, int s, Cap up) {\n        if\
    \ (v == s) return up;\n        Cap res = 0;\n        int level_v = level[v];\n\
    \        for (int &i = iter[v]; i < int(g[v].size()); i++) {\n            _edge\
    \ &e = g[v][i];\n            if (level_v <= level[e.to] || g[e.to][e.rev].cap\
    \ == 0) continue;\n            Cap d = _dfs(e.to, s, std::min(up - res, g[e.to][e.rev].cap));\n\
    \            if (d <= 0) continue;\n            g[v][i].cap += d;\n          \
    \  g[e.to][e.rev].cap -= d;\n            res += d;\n            if (res == up)\
    \ return res;\n        }\n        level[v] = _n;\n        return res;\n    }\n\
    \n    Cap flow(int s, int t) { return flow(s, t, std::numeric_limits<Cap>::max());\
    \ }\n    Cap flow(int s, int t, Cap flow_limit) {\n        assert(0 <= s && s\
    \ < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n     \
    \   level.assign(_n, 0), iter.assign(_n, 0);\n        que.clear();\n\n       \
    \ Cap flow = 0;\n        while (flow < flow_limit) {\n            _bfs(s, t);\n\
    \            if (level[t] == -1) break;\n            std::fill(iter.begin(), iter.end(),\
    \ 0);\n            Cap f = _dfs(t, s, flow_limit - flow);\n            if (!f)\
    \ break;\n            flow += f;\n        }\n        return flow;\n    }\n\n \
    \   std::vector<bool> min_cut(int s) {\n        std::vector<bool> visited(_n);\n\
    \        simple_queue_int que;\n        que.push(s);\n        while (!que.empty())\
    \ {\n            int p = que.front();\n            que.pop();\n            visited[p]\
    \ = true;\n            for (auto e : g[p]) {\n                if (e.cap && !visited[e.to])\
    \ {\n                    visited[e.to] = true;\n                    que.push(e.to);\n\
    \                }\n            }\n        }\n        return visited;\n    }\n\
    \n    int _n;\n    struct _edge {\n        int to, rev;\n        Cap cap;\n  \
    \  };\n    std::vector<std::pair<int, int>> pos;\n    std::vector<std::vector<_edge>>\
    \ g;\n};\n#line 5 \"flow/maxflow_lb.hpp\"\n\n// CUT begin\n// MaxFlow with lower\
    \ bound\n// <https://snuke.hatenablog.com/entry/2016/07/10/043918>\n// <https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp>\n\
    // flush(s, t): Calculate maxflow (if solution exists), -1 (otherwise)\ntemplate\
    \ <typename Cap> struct MaxFlowLowerBound {\n    int N;\n    mf_graph<Cap> mf;\n\
    \    std::vector<Cap> in;\n    MaxFlowLowerBound(int N = 0) : N(N), mf(N + 2),\
    \ in(N) {}\n    int add_edge(int from, int to, Cap cap_lo, Cap cap_hi) {\n   \
    \     assert(0 <= from and from < N);\n        assert(0 <= to and to < N);\n \
    \       assert(0 <= cap_lo and cap_lo <= cap_hi);\n        in[from] -= cap_lo;\n\
    \        in[to] += cap_lo;\n        return mf.add_edge(from, to, cap_hi - cap_lo);\n\
    \    }\n    Cap flow(int s, int t) {\n        assert(s != t);\n        assert(0\
    \ <= s and s < N);\n        assert(0 <= t and t < N);\n        Cap sum = 0;\n\
    \        for (int i = 0; i < N; i++) {\n            if (in[i] > 0) mf.add_edge(N,\
    \ i, in[i]), sum += in[i];\n            if (in[i] < 0) mf.add_edge(i, N + 1, -in[i]);\n\
    \        }\n        auto erev = mf.add_edge(t, s, numeric_limits<Cap>::max());\n\
    \        if (mf.flow(N, N + 1) < sum) return -1;\n        return mf.get_edge(erev).flow\
    \ + mf.flow(s, t);\n    }\n};\n"
  code: "#pragma once\n#include \"flow/maxflow.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// MaxFlow with lower bound\n// <https://snuke.hatenablog.com/entry/2016/07/10/043918>\n\
    // <https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp>\n// flush(s,\
    \ t): Calculate maxflow (if solution exists), -1 (otherwise)\ntemplate <typename\
    \ Cap> struct MaxFlowLowerBound {\n    int N;\n    mf_graph<Cap> mf;\n    std::vector<Cap>\
    \ in;\n    MaxFlowLowerBound(int N = 0) : N(N), mf(N + 2), in(N) {}\n    int add_edge(int\
    \ from, int to, Cap cap_lo, Cap cap_hi) {\n        assert(0 <= from and from <\
    \ N);\n        assert(0 <= to and to < N);\n        assert(0 <= cap_lo and cap_lo\
    \ <= cap_hi);\n        in[from] -= cap_lo;\n        in[to] += cap_lo;\n      \
    \  return mf.add_edge(from, to, cap_hi - cap_lo);\n    }\n    Cap flow(int s,\
    \ int t) {\n        assert(s != t);\n        assert(0 <= s and s < N);\n     \
    \   assert(0 <= t and t < N);\n        Cap sum = 0;\n        for (int i = 0; i\
    \ < N; i++) {\n            if (in[i] > 0) mf.add_edge(N, i, in[i]), sum += in[i];\n\
    \            if (in[i] < 0) mf.add_edge(i, N + 1, -in[i]);\n        }\n      \
    \  auto erev = mf.add_edge(t, s, numeric_limits<Cap>::max());\n        if (mf.flow(N,\
    \ N + 1) < sum) return -1;\n        return mf.get_edge(erev).flow + mf.flow(s,\
    \ t);\n    }\n};\n"
  dependsOn:
  - flow/maxflow.hpp
  isVerificationFile: false
  path: flow/maxflow_lb.hpp
  requiredBy: []
  timestamp: '2020-11-18 21:07:32+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: flow/maxflow_lb.hpp
layout: document
redirect_from:
- /library/flow/maxflow_lb.hpp
- /library/flow/maxflow_lb.hpp.html
title: flow/maxflow_lb.hpp
---
