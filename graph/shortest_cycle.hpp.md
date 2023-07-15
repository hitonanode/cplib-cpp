---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: graph/test/shortest_cycle.test.cpp
    title: graph/test/shortest_cycle.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://atcoder.jp/contests/abc308/submissions/43580864
    - https://yukicoder.me/submissions/594507
  bundledCode: "#line 2 \"graph/shortest_cycle.hpp\"\n\n#include <algorithm>\n#include\
    \ <cassert>\n#include <limits>\n#include <optional>\n#include <queue>\n#include\
    \ <tuple>\n#include <utility>\n#include <vector>\n\n// Shortest cycle detection\
    \ of graphs\n// Verified:\n// - https://yukicoder.me/submissions/594507\n// -\
    \ ABC308Ex https://atcoder.jp/contests/abc308/submissions/43580864\ntemplate <bool\
    \ DIRECTED, typename T> struct shortest_cycle {\n    int V;\n    std::vector<std::vector<std::tuple<int,\
    \ int, T>>> to; // (nxt, edge_idx, weight)\n    std::vector<std::tuple<int, int,\
    \ T>> edges;\n\n    shortest_cycle(int V = 0) : V(V), to(V) {}\n\n    void add_edge(int\
    \ s, int t, T weight) {\n        static_assert(DIRECTED);\n        assert(0 <=\
    \ s and s < V);\n        assert(0 <= t and t < V);\n        assert(weight >= 0);\n\
    \        to.at(s).emplace_back(t, (int)edges.size(), weight);\n        edges.emplace_back(s,\
    \ t, weight);\n    }\n\n    void add_bi_edge(int s, int t, T weight) {\n     \
    \   static_assert(!DIRECTED);\n        assert(0 <= s and s < V);\n        assert(0\
    \ <= t and t < V);\n        assert(weight >= 0);\n        to.at(s).emplace_back(t,\
    \ (int)edges.size(), weight);\n        to.at(t).emplace_back(s, (int)edges.size(),\
    \ weight);\n        edges.emplace_back(s, t, weight);\n    }\n\n    std::vector<T>\
    \ dist;\n    std::vector<int> prv;\n\n    std::pair<T, std::pair<int, int>> Solve(const\
    \ int &r) {\n        assert(0 <= r and r < V);\n        dist.assign(V, T());\n\
    \        prv.assign(V, -1);\n        std::vector<int> prve(V, -1);\n        std::vector<int>\
    \ orig(V, -1);\n\n        auto reached = [&](int i) { return i == r or prv.at(i)\
    \ != -1; };\n\n        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T,\
    \ int>>, std::greater<>> pq;\n        pq.emplace(dist.at(r), r);\n\n        while\
    \ (!pq.empty()) {\n            const auto [d_, now] = pq.top();\n            pq.pop();\n\
    \            if (d_ > dist.at(now)) continue;\n\n            for (const auto &[nxt,\
    \ eid, w] : to[now]) {\n                if (reached(nxt) and dist.at(nxt) <= dist.at(now)\
    \ + w) continue;\n                dist.at(nxt) = dist.at(now) + w;\n         \
    \       orig.at(nxt) = orig.at(now) < 0 ? nxt : orig.at(now);\n              \
    \  prv.at(nxt) = now;\n                prve.at(nxt) = eid;\n                pq.emplace(dist.at(nxt),\
    \ nxt);\n            }\n        }\n\n        std::vector<bool> is_edge_used(edges.size());\n\
    \        for (int eid : prve) {\n            if (eid >= 0) is_edge_used.at(eid)\
    \ = true;\n        }\n\n        std::optional<T> minimum_cycle = std::nullopt;\n\
    \        int s = -1, t = -1;\n\n        for (int eid = 0; eid < (int)edges.size();\
    \ ++eid) {\n            if (is_edge_used.at(eid)) continue;\n            auto\
    \ [a, b, w] = edges.at(eid);\n            if (!reached(a) or !reached(b)) continue;\n\
    \n            if constexpr (DIRECTED) {\n                if (b != r) continue;\n\
    \            } else {\n                if (orig.at(a) == orig.at(b) and (a !=\
    \ r or b != r)) continue;\n            }\n\n            if (T L = dist.at(a) +\
    \ dist.at(b) + w;\n                !minimum_cycle.has_value() or L < minimum_cycle.value())\
    \ {\n                minimum_cycle = L;\n                s = a, t = b;\n     \
    \       }\n        }\n\n        return std::make_pair(minimum_cycle.value_or(T(-1)),\
    \ std::make_pair(s, t));\n    }\n\n    std::vector<int> retrieve_loop(const std::pair<int,\
    \ int> &ab) const {\n        if (ab.first < 0 or ab.second < 0) return {};\n \
    \       std::vector<int> ret;\n        bool initial = true;\n        for (int\
    \ cur : {ab.first, ab.second}) {\n            while (cur >= 0) {\n           \
    \     ret.push_back(cur);\n                cur = prv.at(cur);\n            }\n\
    \            if (initial) {\n                std::reverse(ret.begin(), ret.end());\n\
    \                initial = false;\n            } else {\n                ret.pop_back();\n\
    \            }\n        }\n        return ret;\n    }\n};\n"
  code: "#pragma once\n\n#include <algorithm>\n#include <cassert>\n#include <limits>\n\
    #include <optional>\n#include <queue>\n#include <tuple>\n#include <utility>\n\
    #include <vector>\n\n// Shortest cycle detection of graphs\n// Verified:\n// -\
    \ https://yukicoder.me/submissions/594507\n// - ABC308Ex https://atcoder.jp/contests/abc308/submissions/43580864\n\
    template <bool DIRECTED, typename T> struct shortest_cycle {\n    int V;\n   \
    \ std::vector<std::vector<std::tuple<int, int, T>>> to; // (nxt, edge_idx, weight)\n\
    \    std::vector<std::tuple<int, int, T>> edges;\n\n    shortest_cycle(int V =\
    \ 0) : V(V), to(V) {}\n\n    void add_edge(int s, int t, T weight) {\n       \
    \ static_assert(DIRECTED);\n        assert(0 <= s and s < V);\n        assert(0\
    \ <= t and t < V);\n        assert(weight >= 0);\n        to.at(s).emplace_back(t,\
    \ (int)edges.size(), weight);\n        edges.emplace_back(s, t, weight);\n   \
    \ }\n\n    void add_bi_edge(int s, int t, T weight) {\n        static_assert(!DIRECTED);\n\
    \        assert(0 <= s and s < V);\n        assert(0 <= t and t < V);\n      \
    \  assert(weight >= 0);\n        to.at(s).emplace_back(t, (int)edges.size(), weight);\n\
    \        to.at(t).emplace_back(s, (int)edges.size(), weight);\n        edges.emplace_back(s,\
    \ t, weight);\n    }\n\n    std::vector<T> dist;\n    std::vector<int> prv;\n\n\
    \    std::pair<T, std::pair<int, int>> Solve(const int &r) {\n        assert(0\
    \ <= r and r < V);\n        dist.assign(V, T());\n        prv.assign(V, -1);\n\
    \        std::vector<int> prve(V, -1);\n        std::vector<int> orig(V, -1);\n\
    \n        auto reached = [&](int i) { return i == r or prv.at(i) != -1; };\n\n\
    \        std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>,\
    \ std::greater<>> pq;\n        pq.emplace(dist.at(r), r);\n\n        while (!pq.empty())\
    \ {\n            const auto [d_, now] = pq.top();\n            pq.pop();\n   \
    \         if (d_ > dist.at(now)) continue;\n\n            for (const auto &[nxt,\
    \ eid, w] : to[now]) {\n                if (reached(nxt) and dist.at(nxt) <= dist.at(now)\
    \ + w) continue;\n                dist.at(nxt) = dist.at(now) + w;\n         \
    \       orig.at(nxt) = orig.at(now) < 0 ? nxt : orig.at(now);\n              \
    \  prv.at(nxt) = now;\n                prve.at(nxt) = eid;\n                pq.emplace(dist.at(nxt),\
    \ nxt);\n            }\n        }\n\n        std::vector<bool> is_edge_used(edges.size());\n\
    \        for (int eid : prve) {\n            if (eid >= 0) is_edge_used.at(eid)\
    \ = true;\n        }\n\n        std::optional<T> minimum_cycle = std::nullopt;\n\
    \        int s = -1, t = -1;\n\n        for (int eid = 0; eid < (int)edges.size();\
    \ ++eid) {\n            if (is_edge_used.at(eid)) continue;\n            auto\
    \ [a, b, w] = edges.at(eid);\n            if (!reached(a) or !reached(b)) continue;\n\
    \n            if constexpr (DIRECTED) {\n                if (b != r) continue;\n\
    \            } else {\n                if (orig.at(a) == orig.at(b) and (a !=\
    \ r or b != r)) continue;\n            }\n\n            if (T L = dist.at(a) +\
    \ dist.at(b) + w;\n                !minimum_cycle.has_value() or L < minimum_cycle.value())\
    \ {\n                minimum_cycle = L;\n                s = a, t = b;\n     \
    \       }\n        }\n\n        return std::make_pair(minimum_cycle.value_or(T(-1)),\
    \ std::make_pair(s, t));\n    }\n\n    std::vector<int> retrieve_loop(const std::pair<int,\
    \ int> &ab) const {\n        if (ab.first < 0 or ab.second < 0) return {};\n \
    \       std::vector<int> ret;\n        bool initial = true;\n        for (int\
    \ cur : {ab.first, ab.second}) {\n            while (cur >= 0) {\n           \
    \     ret.push_back(cur);\n                cur = prv.at(cur);\n            }\n\
    \            if (initial) {\n                std::reverse(ret.begin(), ret.end());\n\
    \                initial = false;\n            } else {\n                ret.pop_back();\n\
    \            }\n        }\n        return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: graph/shortest_cycle.hpp
  requiredBy: []
  timestamp: '2023-07-15 20:54:51+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - graph/test/shortest_cycle.test.cpp
documentation_of: graph/shortest_cycle.hpp
layout: document
redirect_from:
- /library/graph/shortest_cycle.hpp
- /library/graph/shortest_cycle.hpp.html
title: graph/shortest_cycle.hpp
---
