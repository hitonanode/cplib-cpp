---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"flow/maxflow_acl.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <limits>\n#include <queue>\n#include <vector>\n\n//CUT begin\n\
    template <class T>\nstruct simple_queue\n{\n    std::vector<T> payload;\n    int\
    \ pos = 0;\n    void reserve(int n) { payload.reserve(n); }\n    int size() const\
    \ { return int(payload.size()) - pos; }\n    bool empty() const { return pos ==\
    \ int(payload.size()); }\n    void push(const T &t) { payload.push_back(t); }\n\
    \    T &front() { return payload[pos]; }\n    void clear()\n    {\n        payload.clear();\n\
    \        pos = 0;\n    }\n    void pop() { pos++; }\n};\ntemplate <class Cap>\n\
    struct mf_graph\n{\npublic:\n    mf_graph() : _n(0) {}\n    mf_graph(int n) :\
    \ _n(n), g(n) {}\n\n    int add_edge(int from, int to, Cap cap)\n    {\n     \
    \   assert(0 <= from && from < _n);\n        assert(0 <= to && to < _n);\n   \
    \     assert(0 <= cap);\n        int m = int(pos.size());\n        pos.push_back({from,\
    \ int(g[from].size())});\n        int from_id = int(g[from].size());\n       \
    \ int to_id = int(g[to].size());\n        if (from == to)\n            to_id++;\n\
    \        g[from].push_back(_edge{to, to_id, cap});\n        g[to].push_back(_edge{from,\
    \ from_id, 0});\n        return m;\n    }\n\n    struct edge\n    {\n        int\
    \ from, to;\n        Cap cap, flow;\n    };\n\n    edge get_edge(int i)\n    {\n\
    \        int m = int(pos.size());\n        assert(0 <= i && i < m);\n        auto\
    \ _e = g[pos[i].first][pos[i].second];\n        auto _re = g[_e.to][_e.rev];\n\
    \        return edge{pos[i].first, _e.to, _e.cap + _re.cap, _re.cap};\n    }\n\
    \    std::vector<edge> edges()\n    {\n        int m = int(pos.size());\n    \
    \    std::vector<edge> result;\n        for (int i = 0; i < m; i++)\n        {\n\
    \            result.push_back(get_edge(i));\n        }\n        return result;\n\
    \    }\n    void change_edge(int i, Cap new_cap, Cap new_flow)\n    {\n      \
    \  int m = int(pos.size());\n        assert(0 <= i && i < m);\n        assert(0\
    \ <= new_flow && new_flow <= new_cap);\n        auto &_e = g[pos[i].first][pos[i].second];\n\
    \        auto &_re = g[_e.to][_e.rev];\n        _e.cap = new_cap - new_flow;\n\
    \        _re.cap = new_flow;\n    }\n\n    Cap flow(int s, int t)\n    {\n   \
    \     return flow(s, t, std::numeric_limits<Cap>::max());\n    }\n    Cap flow(int\
    \ s, int t, Cap flow_limit)\n    {\n        assert(0 <= s && s < _n);\n      \
    \  assert(0 <= t && t < _n);\n        assert(s != t);\n\n        std::vector<int>\
    \ level(_n), iter(_n);\n        simple_queue<int> que;\n\n        auto bfs = [&]()\
    \ {\n            std::fill(level.begin(), level.end(), -1);\n            level[s]\
    \ = 0;\n            que.clear();\n            que.push(s);\n            while\
    \ (!que.empty())\n            {\n                int v = que.front();\n      \
    \          que.pop();\n                for (auto e : g[v])\n                {\n\
    \                    if (e.cap == 0 || level[e.to] >= 0)\n                   \
    \     continue;\n                    level[e.to] = level[v] + 1;\n           \
    \         if (e.to == t)\n                        return;\n                  \
    \  que.push(e.to);\n                }\n            }\n        };\n        auto\
    \ dfs = [&](auto self, int v, Cap up) {\n            if (v == s)\n           \
    \     return up;\n            Cap res = 0;\n            int level_v = level[v];\n\
    \            for (int &i = iter[v]; i < int(g[v].size()); i++)\n            {\n\
    \                _edge &e = g[v][i];\n                if (level_v <= level[e.to]\
    \ || g[e.to][e.rev].cap == 0)\n                    continue;\n               \
    \ Cap d =\n                    self(self, e.to, std::min(up - res, g[e.to][e.rev].cap));\n\
    \                if (d <= 0)\n                    continue;\n                g[v][i].cap\
    \ += d;\n                g[e.to][e.rev].cap -= d;\n                res += d;\n\
    \                if (res == up)\n                    break;\n            }\n \
    \           return res;\n        };\n\n        Cap flow = 0;\n        while (flow\
    \ < flow_limit)\n        {\n            bfs();\n            if (level[t] == -1)\n\
    \                break;\n            std::fill(iter.begin(), iter.end(), 0);\n\
    \            while (flow < flow_limit)\n            {\n                Cap f =\
    \ dfs(dfs, t, flow_limit - flow);\n                if (!f)\n                 \
    \   break;\n                flow += f;\n            }\n        }\n        return\
    \ flow;\n    }\n\n    std::vector<bool> min_cut(int s)\n    {\n        std::vector<bool>\
    \ visited(_n);\n        simple_queue<int> que;\n        que.push(s);\n       \
    \ while (!que.empty())\n        {\n            int p = que.front();\n        \
    \    que.pop();\n            visited[p] = true;\n            for (auto e : g[p])\n\
    \            {\n                if (e.cap && !visited[e.to])\n               \
    \ {\n                    visited[e.to] = true;\n                    que.push(e.to);\n\
    \                }\n            }\n        }\n        return visited;\n    }\n\
    \nprivate:\n    int _n;\n    struct _edge\n    {\n        int to, rev;\n     \
    \   Cap cap;\n    };\n    std::vector<std::pair<int, int>> pos;\n    std::vector<std::vector<_edge>>\
    \ g;\n};\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n\
    #include <queue>\n#include <vector>\n\n//CUT begin\ntemplate <class T>\nstruct\
    \ simple_queue\n{\n    std::vector<T> payload;\n    int pos = 0;\n    void reserve(int\
    \ n) { payload.reserve(n); }\n    int size() const { return int(payload.size())\
    \ - pos; }\n    bool empty() const { return pos == int(payload.size()); }\n  \
    \  void push(const T &t) { payload.push_back(t); }\n    T &front() { return payload[pos];\
    \ }\n    void clear()\n    {\n        payload.clear();\n        pos = 0;\n   \
    \ }\n    void pop() { pos++; }\n};\ntemplate <class Cap>\nstruct mf_graph\n{\n\
    public:\n    mf_graph() : _n(0) {}\n    mf_graph(int n) : _n(n), g(n) {}\n\n \
    \   int add_edge(int from, int to, Cap cap)\n    {\n        assert(0 <= from &&\
    \ from < _n);\n        assert(0 <= to && to < _n);\n        assert(0 <= cap);\n\
    \        int m = int(pos.size());\n        pos.push_back({from, int(g[from].size())});\n\
    \        int from_id = int(g[from].size());\n        int to_id = int(g[to].size());\n\
    \        if (from == to)\n            to_id++;\n        g[from].push_back(_edge{to,\
    \ to_id, cap});\n        g[to].push_back(_edge{from, from_id, 0});\n        return\
    \ m;\n    }\n\n    struct edge\n    {\n        int from, to;\n        Cap cap,\
    \ flow;\n    };\n\n    edge get_edge(int i)\n    {\n        int m = int(pos.size());\n\
    \        assert(0 <= i && i < m);\n        auto _e = g[pos[i].first][pos[i].second];\n\
    \        auto _re = g[_e.to][_e.rev];\n        return edge{pos[i].first, _e.to,\
    \ _e.cap + _re.cap, _re.cap};\n    }\n    std::vector<edge> edges()\n    {\n \
    \       int m = int(pos.size());\n        std::vector<edge> result;\n        for\
    \ (int i = 0; i < m; i++)\n        {\n            result.push_back(get_edge(i));\n\
    \        }\n        return result;\n    }\n    void change_edge(int i, Cap new_cap,\
    \ Cap new_flow)\n    {\n        int m = int(pos.size());\n        assert(0 <=\
    \ i && i < m);\n        assert(0 <= new_flow && new_flow <= new_cap);\n      \
    \  auto &_e = g[pos[i].first][pos[i].second];\n        auto &_re = g[_e.to][_e.rev];\n\
    \        _e.cap = new_cap - new_flow;\n        _re.cap = new_flow;\n    }\n\n\
    \    Cap flow(int s, int t)\n    {\n        return flow(s, t, std::numeric_limits<Cap>::max());\n\
    \    }\n    Cap flow(int s, int t, Cap flow_limit)\n    {\n        assert(0 <=\
    \ s && s < _n);\n        assert(0 <= t && t < _n);\n        assert(s != t);\n\n\
    \        std::vector<int> level(_n), iter(_n);\n        simple_queue<int> que;\n\
    \n        auto bfs = [&]() {\n            std::fill(level.begin(), level.end(),\
    \ -1);\n            level[s] = 0;\n            que.clear();\n            que.push(s);\n\
    \            while (!que.empty())\n            {\n                int v = que.front();\n\
    \                que.pop();\n                for (auto e : g[v])\n           \
    \     {\n                    if (e.cap == 0 || level[e.to] >= 0)\n           \
    \             continue;\n                    level[e.to] = level[v] + 1;\n   \
    \                 if (e.to == t)\n                        return;\n          \
    \          que.push(e.to);\n                }\n            }\n        };\n   \
    \     auto dfs = [&](auto self, int v, Cap up) {\n            if (v == s)\n  \
    \              return up;\n            Cap res = 0;\n            int level_v =\
    \ level[v];\n            for (int &i = iter[v]; i < int(g[v].size()); i++)\n \
    \           {\n                _edge &e = g[v][i];\n                if (level_v\
    \ <= level[e.to] || g[e.to][e.rev].cap == 0)\n                    continue;\n\
    \                Cap d =\n                    self(self, e.to, std::min(up - res,\
    \ g[e.to][e.rev].cap));\n                if (d <= 0)\n                    continue;\n\
    \                g[v][i].cap += d;\n                g[e.to][e.rev].cap -= d;\n\
    \                res += d;\n                if (res == up)\n                 \
    \   break;\n            }\n            return res;\n        };\n\n        Cap\
    \ flow = 0;\n        while (flow < flow_limit)\n        {\n            bfs();\n\
    \            if (level[t] == -1)\n                break;\n            std::fill(iter.begin(),\
    \ iter.end(), 0);\n            while (flow < flow_limit)\n            {\n    \
    \            Cap f = dfs(dfs, t, flow_limit - flow);\n                if (!f)\n\
    \                    break;\n                flow += f;\n            }\n     \
    \   }\n        return flow;\n    }\n\n    std::vector<bool> min_cut(int s)\n \
    \   {\n        std::vector<bool> visited(_n);\n        simple_queue<int> que;\n\
    \        que.push(s);\n        while (!que.empty())\n        {\n            int\
    \ p = que.front();\n            que.pop();\n            visited[p] = true;\n \
    \           for (auto e : g[p])\n            {\n                if (e.cap && !visited[e.to])\n\
    \                {\n                    visited[e.to] = true;\n              \
    \      que.push(e.to);\n                }\n            }\n        }\n        return\
    \ visited;\n    }\n\nprivate:\n    int _n;\n    struct _edge\n    {\n        int\
    \ to, rev;\n        Cap cap;\n    };\n    std::vector<std::pair<int, int>> pos;\n\
    \    std::vector<std::vector<_edge>> g;\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: flow/maxflow_acl.hpp
  requiredBy: []
  timestamp: '2020-09-29 02:28:46+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: flow/maxflow_acl.hpp
layout: document
redirect_from:
- /library/flow/maxflow_acl.hpp
- /library/flow/maxflow_acl.hpp.html
title: flow/maxflow_acl.hpp
---
