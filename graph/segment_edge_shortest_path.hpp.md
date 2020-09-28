---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://codeforces.com/contest/786/submission/93412867>
  bundledCode: "#line 2 \"graph/segment_edge_shortest_path.hpp\"\n#include <cassert>\n\
    #include <algorithm>\n#include <deque>\n#include <limits>\n#include <queue>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// \u533A\u9593\u306B\u8FBA\
    \u3092\u5F35\u3063\u3066\u6700\u77ED\u8DDD\u96E2\u554F\u984C\u3092\u89E3\u304F\
    \n// Verify: Codeforces Round #406 (Div. 1), problem: (B) Legacy <https://codeforces.com/contest/786/submission/93412867>\n\
    template <typename T = long long>\nstruct SegmentEdgeShortestPath\n{\n    int\
    \ V;\n    int h;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
    \ T>>> to;\n    SegmentEdgeShortestPath() = default;\n    SegmentEdgeShortestPath(int\
    \ V) : V(V), h(1) {\n        while (h < V) h *= 2;\n        to.resize(h * 3);\n\
    \        for (int i = 1; i < h; i++) {\n            to[i].emplace_back(i * 2,\
    \ 0);\n            to[i].emplace_back(i * 2 + 1, 0);\n            int j = i *\
    \ 2 + h * 2;\n            if (j >= h * 3) j -= h * 2;\n            to[j].emplace_back(i\
    \ + h * 2, 0);\n            to[j + 1].emplace_back(i + h * 2, 0);\n        }\n\
    \    }\n    void _add_dfs(int now, int l, int r, int begin, int end, std::vector<int>\
    \ &vec_add) {\n        if (end <= l or r <= begin) return;\n        if (l <= begin\
    \ and end <= r) {\n            vec_add.emplace_back(now);\n            return;\n\
    \        }\n        _add_dfs(now * 2, l, r, begin, (begin + end) / 2, vec_add);\n\
    \        _add_dfs(now * 2 + 1, l, r, (begin + end) / 2, end, vec_add);\n    }\n\
    \n    std::vector<int> from_vs, to_vs;\n    void add_edge(int from_l, int from_r,\
    \ int to_l, int to_r, T len) {\n        from_vs.clear(), to_vs.clear();\n    \
    \    _add_dfs(1, from_l, from_r, 0, h, from_vs);\n        _add_dfs(1, to_l, to_r,\
    \ 0, h, to_vs);\n        for (auto &x : from_vs) if (x < h) x += h * 2;\n    \
    \    for (const auto s : from_vs) {\n            for (const auto t : to_vs) {\n\
    \                to[s].emplace_back(t, len);\n            }\n        }\n    }\n\
    \    std::vector<T> dist;\n    std::vector<T> _d_tmp;\n    void solve01dfs(int\
    \ s) {\n        assert(s >= 0 and s < V);\n        s += h;\n        _d_tmp.assign(h\
    \ * 3, std::numeric_limits<T>::max() / 2);\n        _d_tmp[s] = 0;\n        std::deque<int>\
    \ q;\n        q.emplace_back(s);\n        while (q.size()) {\n            int\
    \ now = q.front();\n            q.pop_front();\n            for (const auto &p\
    \ : to[now]) {\n                const int nxt = p.first, d = p.second;\n     \
    \           if (_d_tmp[nxt] > _d_tmp[now] + d) {\n                    _d_tmp[nxt]\
    \ = _d_tmp[now] + d;\n                    if (d) q.emplace_back(nxt);\n      \
    \              else q.emplace_front(nxt);\n                }\n            }\n\
    \        }\n        dist.resize(V);\n        std::copy(_d_tmp.begin() + h, _d_tmp.begin()\
    \ + h + V, dist.begin());\n    }\n\n    void solve_dijkstra(int s) {\n       \
    \ assert(s >= 0 and s < V);\n        s += h;\n        _d_tmp.assign(h * 3, std::numeric_limits<T>::max()\
    \ / 2);\n        _d_tmp[s] = 0;\n        using P = std::pair<T, int>;\n      \
    \  std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n        pq.emplace(0,\
    \ s);\n        while (pq.size()) {\n            auto a = pq.top();\n         \
    \   pq.pop();\n            int now = a.second;\n            if (_d_tmp[now] <\
    \ a.first) continue;\n            for (const auto p : to[now])\n            {\n\
    \                int nxt = p.first;\n                T d = p.second;\n       \
    \         if (_d_tmp[nxt] > _d_tmp[now] + d) {\n                    _d_tmp[nxt]\
    \ = _d_tmp[now] + d;\n                    pq.emplace(_d_tmp[nxt], nxt);\n    \
    \            }\n            }\n        }\n        dist.resize(V);\n        std::copy(_d_tmp.begin()\
    \ + h, _d_tmp.begin() + h + V, dist.begin());\n    }\n};\n"
  code: "#pragma once\n#include <cassert>\n#include <algorithm>\n#include <deque>\n\
    #include <limits>\n#include <queue>\n#include <utility>\n#include <vector>\n\n\
    // CUT begin\n// \u533A\u9593\u306B\u8FBA\u3092\u5F35\u3063\u3066\u6700\u77ED\u8DDD\
    \u96E2\u554F\u984C\u3092\u89E3\u304F\n// Verify: Codeforces Round #406 (Div. 1),\
    \ problem: (B) Legacy <https://codeforces.com/contest/786/submission/93412867>\n\
    template <typename T = long long>\nstruct SegmentEdgeShortestPath\n{\n    int\
    \ V;\n    int h;\n    int INVALID = -1;\n    std::vector<std::vector<std::pair<int,\
    \ T>>> to;\n    SegmentEdgeShortestPath() = default;\n    SegmentEdgeShortestPath(int\
    \ V) : V(V), h(1) {\n        while (h < V) h *= 2;\n        to.resize(h * 3);\n\
    \        for (int i = 1; i < h; i++) {\n            to[i].emplace_back(i * 2,\
    \ 0);\n            to[i].emplace_back(i * 2 + 1, 0);\n            int j = i *\
    \ 2 + h * 2;\n            if (j >= h * 3) j -= h * 2;\n            to[j].emplace_back(i\
    \ + h * 2, 0);\n            to[j + 1].emplace_back(i + h * 2, 0);\n        }\n\
    \    }\n    void _add_dfs(int now, int l, int r, int begin, int end, std::vector<int>\
    \ &vec_add) {\n        if (end <= l or r <= begin) return;\n        if (l <= begin\
    \ and end <= r) {\n            vec_add.emplace_back(now);\n            return;\n\
    \        }\n        _add_dfs(now * 2, l, r, begin, (begin + end) / 2, vec_add);\n\
    \        _add_dfs(now * 2 + 1, l, r, (begin + end) / 2, end, vec_add);\n    }\n\
    \n    std::vector<int> from_vs, to_vs;\n    void add_edge(int from_l, int from_r,\
    \ int to_l, int to_r, T len) {\n        from_vs.clear(), to_vs.clear();\n    \
    \    _add_dfs(1, from_l, from_r, 0, h, from_vs);\n        _add_dfs(1, to_l, to_r,\
    \ 0, h, to_vs);\n        for (auto &x : from_vs) if (x < h) x += h * 2;\n    \
    \    for (const auto s : from_vs) {\n            for (const auto t : to_vs) {\n\
    \                to[s].emplace_back(t, len);\n            }\n        }\n    }\n\
    \    std::vector<T> dist;\n    std::vector<T> _d_tmp;\n    void solve01dfs(int\
    \ s) {\n        assert(s >= 0 and s < V);\n        s += h;\n        _d_tmp.assign(h\
    \ * 3, std::numeric_limits<T>::max() / 2);\n        _d_tmp[s] = 0;\n        std::deque<int>\
    \ q;\n        q.emplace_back(s);\n        while (q.size()) {\n            int\
    \ now = q.front();\n            q.pop_front();\n            for (const auto &p\
    \ : to[now]) {\n                const int nxt = p.first, d = p.second;\n     \
    \           if (_d_tmp[nxt] > _d_tmp[now] + d) {\n                    _d_tmp[nxt]\
    \ = _d_tmp[now] + d;\n                    if (d) q.emplace_back(nxt);\n      \
    \              else q.emplace_front(nxt);\n                }\n            }\n\
    \        }\n        dist.resize(V);\n        std::copy(_d_tmp.begin() + h, _d_tmp.begin()\
    \ + h + V, dist.begin());\n    }\n\n    void solve_dijkstra(int s) {\n       \
    \ assert(s >= 0 and s < V);\n        s += h;\n        _d_tmp.assign(h * 3, std::numeric_limits<T>::max()\
    \ / 2);\n        _d_tmp[s] = 0;\n        using P = std::pair<T, int>;\n      \
    \  std::priority_queue<P, std::vector<P>, std::greater<P>> pq;\n        pq.emplace(0,\
    \ s);\n        while (pq.size()) {\n            auto a = pq.top();\n         \
    \   pq.pop();\n            int now = a.second;\n            if (_d_tmp[now] <\
    \ a.first) continue;\n            for (const auto p : to[now])\n            {\n\
    \                int nxt = p.first;\n                T d = p.second;\n       \
    \         if (_d_tmp[nxt] > _d_tmp[now] + d) {\n                    _d_tmp[nxt]\
    \ = _d_tmp[now] + d;\n                    pq.emplace(_d_tmp[nxt], nxt);\n    \
    \            }\n            }\n        }\n        dist.resize(V);\n        std::copy(_d_tmp.begin()\
    \ + h, _d_tmp.begin() + h + V, dist.begin());\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/segment_edge_shortest_path.hpp
  requiredBy: []
  timestamp: '2020-09-21 23:10:21+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: graph/segment_edge_shortest_path.hpp
layout: document
redirect_from:
- /library/graph/segment_edge_shortest_path.hpp
- /library/graph/segment_edge_shortest_path.hpp.html
title: graph/segment_edge_shortest_path.hpp
---
