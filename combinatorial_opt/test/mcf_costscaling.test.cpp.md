---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/maxflow.hpp
    title: combinatorial_opt/maxflow.hpp
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/mcf_costscaling.hpp
    title: "Cost scaling minimum cost flow (Goldberg, Tarjan) \uFF08\u30B3\u30B9\u30C8\
      \u30B9\u30B1\u30FC\u30EA\u30F3\u30B0\u306B\u3088\u308B\u6700\u5C0F\u8CBB\u7528\
      \u6D41\uFF09"
  - icon: ':heavy_check_mark:'
    path: data_structure/light_forward_list.hpp
    title: data_structure/light_forward_list.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
    links:
    - http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B
  bundledCode: "#line 1 \"combinatorial_opt/test/mcf_costscaling.test.cpp\"\n#define\
    \ PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n#line 2 \"data_structure/light_forward_list.hpp\"\n#include <vector>\n\n// CUT\
    \ begin\n// Simple forward_list for MLE-sensitive situations\n// Verify: <http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D>\n\
    template <typename T> struct light_forward_list {\n    static std::vector<unsigned>\
    \ ptr;\n    static std::vector<T> val;\n    unsigned head;\n    light_forward_list()\
    \ : head(0) {}\n    void push_front(T x) {\n        ptr.push_back(head), val.push_back(x);\n\
    \        head = ptr.size() - 1;\n    }\n    struct iterator {\n        unsigned\
    \ p;\n        iterator operator++() { return {p = ptr[p]}; }\n        T &operator*()\
    \ { return val[p]; }\n        bool operator!=(const iterator &rhs) { return p\
    \ != rhs.p; }\n    };\n    iterator begin() { return {head}; }\n    iterator end()\
    \ { return {0}; }\n};\ntemplate <typename T> std::vector<unsigned> light_forward_list<T>::ptr\
    \ = {0};\ntemplate <typename T> std::vector<T> light_forward_list<T>::val = {T()};\n\
    #line 3 \"combinatorial_opt/mcf_costscaling.hpp\"\n#include <cassert>\n#include\
    \ <limits>\n#include <queue>\n\n// Cost scaling\n// https://people.orie.cornell.edu/dpw/orie633/\n\
    // Implementation idea: https://yukicoder.me/submissions/680169\ntemplate <class\
    \ Cap, class Cost> struct mcf_costscaling {\n    mcf_costscaling() = default;\n\
    \    mcf_costscaling(int n) : _n(n), to(n), b(n), p(n) {\n        static_assert(std::numeric_limits<Cap>::max()\
    \ > 0, \"max() must be greater than 0\");\n    }\n\n    int _n;\n    std::vector<Cap>\
    \ cap;\n    std::vector<Cost> cost;\n    std::vector<int> opposite;\n    std::vector<light_forward_list<int>>\
    \ to;\n    std::vector<Cap> b;\n    std::vector<Cost> p;\n\n    void add_edge(int\
    \ from_, int to_, Cap cap_, Cost cost_) {\n        assert(0 <= from_ && from_\
    \ < _n);\n        assert(0 <= to_ && to_ < _n);\n        assert(0 <= cap_);\n\
    \        assert(0 <= cost_);\n        cost_ *= (_n + 1);\n\n        int e = int(cap.size());\n\
    \        to[from_].push_front(e);\n        cap.push_back(cap_);\n        cost.push_back(cost_);\n\
    \        opposite.push_back(to_);\n\n        to[to_].push_front(e + 1);\n    \
    \    cap.push_back(0);\n        cost.push_back(-cost_);\n        opposite.push_back(from_);\n\
    \    }\n    void add_supply(int v, Cap supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, Cap demand) { add_supply(v, -demand); }\n\n    Cost flow(int SCALING = 1)\
    \ {\n        Cost eps = 1;\n        for (const auto c : cost) {\n            while\
    \ (eps <= -c) eps <<= SCALING;\n        }\n        for (; eps >>= SCALING;) {\n\
    \            for (int e = 0; e < int(cap.size()); e += 2) {\n                const\
    \ int i = opposite[e ^ 1], j = opposite[e];\n                const Cost cp_ij\
    \ = cost[e] + p[i] - p[j];\n                if (cap[e] and cp_ij < 0) {\n    \
    \                b[i] -= cap[e], b[j] += cap[e], cap[e ^ 1] += cap[e], cap[e]\
    \ = 0;\n                } else if (cap[e ^ 1] and cp_ij > 0) {\n             \
    \       b[i] += cap[e ^ 1], b[j] -= cap[e ^ 1], cap[e] += cap[e ^ 1], cap[e ^\
    \ 1] = 0;\n                }\n            }\n            std::queue<int> q;\n\
    \            for (int i = 0; i < _n; i++) {\n                if (b[i] > 0) q.push(i);\n\
    \            }\n            while (q.size()) {\n                const int i =\
    \ q.front();\n                q.pop();\n                for (auto e : to[i]) {\
    \ // Push\n                    if (!cap[e]) continue;\n                    int\
    \ j = opposite[e];\n                    Cost cp_ij = cost[e] + p[i] - p[j];\n\
    \                    if (cp_ij >= 0) continue;\n                    Cap f = b[i]\
    \ > cap[e] ? cap[e] : b[i];\n                    if (b[j] <= 0 and b[j] + f >\
    \ 0) q.push(j);\n                    b[i] -= f, b[j] += f, cap[e] -= f, cap[e\
    \ ^ 1] += f;\n                    if (!b[i]) break;\n                }\n\n   \
    \             if (b[i] > 0) { // Relabel\n                    bool flg = false;\n\
    \                    for (int e : to[i]) {\n                        if (!cap[e])\
    \ continue;\n                        Cost x = p[opposite[e]] - cost[e] - eps;\n\
    \                        if (!flg or x > p[i]) flg = true, p[i] = x;\n       \
    \             }\n                    q.push(i);\n                }\n         \
    \   }\n        }\n        Cost ret = 0;\n        for (int e = 0; e < int(cap.size());\
    \ e += 2) ret += cost[e] * cap[e ^ 1];\n        return ret / (_n + 1);\n    }\n\
    };\n#line 2 \"combinatorial_opt/maxflow.hpp\"\n\n#include <algorithm>\n#line 5\
    \ \"combinatorial_opt/maxflow.hpp\"\n#include <fstream>\n#line 7 \"combinatorial_opt/maxflow.hpp\"\
    \n#include <string>\n#line 9 \"combinatorial_opt/maxflow.hpp\"\n\n// CUT begin\n\
    // MaxFlow based and AtCoder Library, single class, no namespace, no private variables,\
    \ compatible with C++11\n// Reference: <https://atcoder.github.io/ac-library/production/document_ja/maxflow.html>\n\
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
    \n    void dump_graphviz(std::string filename = \"maxflow\") const {\n       \
    \ std::ofstream ss(filename + \".DOT\");\n        ss << \"digraph{\\n\";\n   \
    \     for (int i = 0; i < _n; i++) {\n            for (const auto &e : g[i]) {\n\
    \                if (e.cap > 0) ss << i << \"->\" << e.to << \"[label=\" << e.cap\
    \ << \"];\\n\";\n            }\n        }\n        ss << \"}\\n\";\n        ss.close();\n\
    \        return;\n    }\n\n    int _n;\n    struct _edge {\n        int to, rev;\n\
    \        Cap cap;\n    };\n    std::vector<std::pair<int, int>> pos;\n    std::vector<std::vector<_edge>>\
    \ g;\n};\n#line 4 \"combinatorial_opt/test/mcf_costscaling.test.cpp\"\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    int V, E, F;\n    cin\
    \ >> V >> E >> F;\n    mcf_costscaling<int, long long> mcf(V);\n    mf_graph<int>\
    \ mf(V);\n    while (E--) {\n        int u, v, c, d;\n        cin >> u >> v >>\
    \ c >> d;\n        mcf.add_edge(u, v, c, d);\n        mf.add_edge(u, v, c);\n\
    \    }\n\n    mcf.add_supply(0, F), mcf.add_supply(V - 1, -F);\n    if (mf.flow(0,\
    \ V - 1) < F) {\n        cout << \"-1\" << '\\n';\n    } else {\n        cout\
    \ << mcf.flow() << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n#include \"../mcf_costscaling.hpp\"\n#include \"../maxflow.hpp\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    int V, E, F;\n    cin >> V >> E >> F;\n\
    \    mcf_costscaling<int, long long> mcf(V);\n    mf_graph<int> mf(V);\n    while\
    \ (E--) {\n        int u, v, c, d;\n        cin >> u >> v >> c >> d;\n       \
    \ mcf.add_edge(u, v, c, d);\n        mf.add_edge(u, v, c);\n    }\n\n    mcf.add_supply(0,\
    \ F), mcf.add_supply(V - 1, -F);\n    if (mf.flow(0, V - 1) < F) {\n        cout\
    \ << \"-1\" << '\\n';\n    } else {\n        cout << mcf.flow() << '\\n';\n  \
    \  }\n}\n"
  dependsOn:
  - combinatorial_opt/mcf_costscaling.hpp
  - data_structure/light_forward_list.hpp
  - combinatorial_opt/maxflow.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/mcf_costscaling.test.cpp
  requiredBy: []
  timestamp: '2021-08-17 02:37:56+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/mcf_costscaling.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/mcf_costscaling.test.cpp
- /verify/combinatorial_opt/test/mcf_costscaling.test.cpp.html
title: combinatorial_opt/test/mcf_costscaling.test.cpp
---
