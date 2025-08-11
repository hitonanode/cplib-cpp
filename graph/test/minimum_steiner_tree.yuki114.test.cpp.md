---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: graph/minimum_steiner_tree.hpp
    title: "Minimum Steiner tree \uFF08\u6700\u5C0F\u30B7\u30E5\u30BF\u30A4\u30CA\u30FC\
      \u6728\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/114
    links:
    - https://yukicoder.me/problems/no/114
  bundledCode: "#line 1 \"graph/test/minimum_steiner_tree.yuki114.test.cpp\"\n#define\
    \ PROBLEM \"https://yukicoder.me/problems/no/114\"\n#line 2 \"graph/minimum_steiner_tree.hpp\"\
    \n\n#include <algorithm>\n#include <cassert>\n#include <cmath>\n#include <numeric>\n\
    #include <queue>\n#include <set>\n#include <tuple>\n#include <utility>\n#include\
    \ <vector>\n\n// Minimum Steiner tree of undirected connected graph\n// n vertices,\
    \ m edges, k terminals\n// Complexity: O(3^k n + 2^k m log m)\n// Verify: https://judge.yosupo.jp/problem/minimum_steiner_tree\n\
    template <class T>\nstd::pair<T, std::vector<int>>\nMinimumSteinerTreeDP(int n,\
    \ const std::vector<std::tuple<int, int, T>> &edges,\n                     const\
    \ std::vector<int> &terminals) {\n\n    if (n <= 1 or terminals.size() <= 1) return\
    \ {T{}, {}};\n    assert(!edges.empty());\n\n    std::vector<std::vector<std::tuple<int,\
    \ int, T>>> to(n);\n    for (int i = 0; i < (int)edges.size(); ++i) {\n      \
    \  auto [u, v, w] = edges[i];\n        assert(w >= 0);\n        to.at(u).emplace_back(v,\
    \ i, w);\n        to.at(v).emplace_back(u, i, w);\n    }\n    const int k = terminals.size();\n\
    \n    std::vector<T> dp(n << k);\n    std::vector<int> prv(n << k, -1);\n\n  \
    \  auto f = [&](int i, int s) -> int {\n        assert(0 <= s and s < (1 << k));\n\
    \        return (i << k) + s;\n    };\n\n    for (int i = 0; i < n; ++i) prv.at(f(i,\
    \ 0)) = f(i, 0);\n\n    for (int j = 0; j < k; ++j) {\n        const int i = terminals.at(j);\n\
    \        prv.at(f(i, 1 << j)) = f(i, 0);\n    }\n\n    for (int s = 0; s < (1\
    \ << k); ++s) {\n        for (int i = 0; i < n; ++i) {\n            for (int t\
    \ = (s - 1) & s; t; t = (t - 1) & s) {\n                if (prv.at(f(i, t)) ==\
    \ -1) continue;\n                if (prv.at(f(i, s ^ t)) == -1) continue;\n  \
    \              const T new_cost = dp.at(f(i, t)) + dp.at(f(i, s ^ t));\n     \
    \           if (new_cost < dp.at(f(i, s)) or prv.at(f(i, s)) == -1) {\n      \
    \              dp.at(f(i, s)) = new_cost;\n                    prv.at(f(i, s))\
    \ = f(i, t);\n                    assert(s >= t);\n                }\n       \
    \     }\n        }\n\n        using P = std::pair<T, int>;\n        std::priority_queue<P,\
    \ std::vector<P>, std::greater<>> pq;\n\n        for (int i = 0; i < n; ++i) {\n\
    \            if (prv.at(f(i, s)) != -1) pq.emplace(dp.at(f(i, s)), i);\n     \
    \   }\n\n        while (!pq.empty()) {\n            auto [cost, i] = pq.top();\n\
    \            pq.pop();\n            if (dp.at(f(i, s)) < cost) continue;\n   \
    \         for (auto [j, edge_id, w] : to.at(i)) {\n                if (prv.at(f(j,\
    \ s)) != -1 and dp.at(f(j, s)) <= cost + w) continue;\n                dp.at(f(j,\
    \ s)) = cost + w;\n                prv.at(f(j, s)) = f(edge_id, s);\n        \
    \        pq.emplace(dp.at(f(j, s)), j);\n            }\n        }\n    }\n\n \
    \   T ans = dp.at(f(0, (1 << k) - 1));\n    int argmin = 0;\n    for (int i =\
    \ 1; i < n; ++i) {\n        if (dp.at(f(i, (1 << k) - 1)) < ans) {\n         \
    \   ans = dp.at(f(i, (1 << k) - 1));\n            argmin = i;\n        }\n   \
    \ }\n\n    std::vector<int> used_edges;\n\n    auto rec = [&](auto &&self, int\
    \ cur) -> void {\n        const int mask = cur & ((1 << k) - 1);\n        if (!mask)\
    \ return;\n        const int i = cur >> k;\n        const int prv_mask = prv.at(cur)\
    \ & ((1 << k) - 1);\n        if (prv_mask == 0) return;\n\n        if (mask ==\
    \ prv_mask) {\n            const int edge_id = prv.at(cur) >> k;\n           \
    \ used_edges.emplace_back(edge_id);\n            const int nxt = i ^ std::get<0>(edges.at(edge_id))\
    \ ^ std::get<1>(edges.at(edge_id));\n            self(self, f(nxt, mask));\n \
    \       } else {\n            self(self, f(i, prv_mask));\n            self(self,\
    \ f(i, mask ^ prv_mask));\n        }\n    };\n    rec(rec, f(argmin, (1 << k)\
    \ - 1));\n\n    std::sort(used_edges.begin(), used_edges.end());\n\n    return\
    \ {ans, used_edges};\n}\n\n// Complexity: O(m log m + 2^(n - k) m alpha(n))\n\
    // Verify: https://yukicoder.me/problems/no/114\ntemplate <class T>\nstd::pair<T,\
    \ std::vector<int>>\nMinimumSteinerTreeDense(int n, const std::vector<std::tuple<int,\
    \ int, T>> &edges,\n                        const std::vector<int> &terminals)\
    \ {\n    if (n <= 1 or terminals.size() <= 1) return {T{}, {}};\n\n    std::vector<int>\
    \ unfixed;\n    {\n        std::vector<int> is_unfixed(n, 1);\n        for (int\
    \ v : terminals) is_unfixed.at(v) = 0;\n        for (int i = 0; i < n; ++i) {\n\
    \            if (is_unfixed.at(i)) unfixed.emplace_back(i);\n        }\n    }\n\
    \n    struct {\n        int n;\n        std::vector<int> par, cou;\n        void\
    \ reset() {\n            par.resize(n);\n            std::iota(par.begin(), par.end(),\
    \ 0);\n            cou.assign(n, 1);\n        }\n        int find(int x) { return\
    \ (par[x] == x) ? x : (par[x] = find(par[x])); }\n        void merge(int x, int\
    \ y) {\n            x = find(x), y = find(y);\n            if (x == y) return;\n\
    \            if (cou[x] < cou[y]) std::swap(x, y);\n            par[y] = x, cou[x]\
    \ += cou[y];\n        }\n        bool same(int x, int y) { return find(x) == find(y);\
    \ }\n    } dsu{n};\n\n    auto sorted_edges = edges;\n    std::sort(sorted_edges.begin(),\
    \ sorted_edges.end(),\n              [&](const auto &l, const auto &r) { return\
    \ std::get<2>(l) < std::get<2>(r); });\n\n    std::vector<int> is_edge_used(sorted_edges.size(),\
    \ -1);\n    std::vector<int> is_banned(n, -1);\n\n    T best_cost = T{};\n   \
    \ int best_ban_set = -1;\n\n    auto solve = [&](int ban_set) -> std::pair<bool,\
    \ T> {\n        dsu.reset();\n        for (int d = 0; d < (int)unfixed.size();\
    \ ++d) {\n            if (ban_set & (1 << d)) is_banned.at(unfixed.at(d)) = ban_set;\n\
    \        }\n\n        T res{0};\n        for (int pos = 0; pos < (int)sorted_edges.size();\
    \ ++pos) {\n            auto [u, v, w] = sorted_edges.at(pos);\n            if\
    \ (is_banned.at(u) == ban_set or is_banned.at(v) == ban_set) continue;\n     \
    \       if (dsu.same(u, v)) continue;\n            dsu.merge(u, v);\n        \
    \    res += w;\n            is_edge_used.at(pos) = ban_set;\n        }\n     \
    \   for (int idx = 1; idx < (int)terminals.size(); ++idx) {\n            if (!dsu.same(terminals.at(0),\
    \ terminals.at(idx))) return {false, T{}};\n        }\n        return {true, res};\n\
    \    };\n\n    for (int ban_set = (1 << (int)unfixed.size()) - 1; ban_set >= 0;\
    \ --ban_set) {\n        if (const auto [is_valid, cost] = solve(ban_set);\n  \
    \          is_valid and (cost < best_cost or best_ban_set == -1)) {\n        \
    \    best_cost = cost;\n            best_ban_set = ban_set;\n        }\n    }\n\
    \n    if (best_ban_set == -1) return {T{}, {}}; // Infeasible\n\n    solve(best_ban_set);\n\
    \    std::set<std::tuple<int, int, T>> used_edges;\n    for (int pos = 0; pos\
    \ < (int)sorted_edges.size(); ++pos) {\n        if (is_edge_used.at(pos) == best_ban_set)\
    \ used_edges.insert(sorted_edges.at(pos));\n    }\n\n    std::vector<int> used_edge_ids;\n\
    \    for (int eid = 0; eid < (int)edges.size(); ++eid) {\n        if (used_edges.count(edges.at(eid)))\
    \ {\n            used_edge_ids.emplace_back(eid);\n            used_edges.erase(edges.at(eid));\n\
    \        }\n    }\n\n    return {best_cost, used_edge_ids};\n}\n\ntemplate <class\
    \ T>\nstd::pair<T, std::vector<int>>\nMinimumSteinerTree(int n, const std::vector<std::tuple<int,\
    \ int, T>> &edges,\n                   const std::vector<int> &terminals) {\n\
    \    const int m = edges.size(), k = terminals.size();\n    auto use_dp = [&]()\
    \ -> bool {\n        if (n - k > 30) return true;\n        if (k > 20) return\
    \ false;\n        return pow(3, k) * n + pow(2, k) * m * log(m) < pow(2, n - k)\
    \ * m;\n    };\n    return (use_dp() ? MinimumSteinerTreeDP<T>(n, edges, terminals)\n\
    \                     : MinimumSteinerTreeDense<T>(n, edges, terminals));\n}\n\
    #line 3 \"graph/test/minimum_steiner_tree.yuki114.test.cpp\"\n\n#include <iostream>\n\
    #line 7 \"graph/test/minimum_steiner_tree.yuki114.test.cpp\"\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int N, M, T;\n    cin >> N >> M >> T;\n\n    vector<tuple<int, int, int>>\
    \ edges(M);\n    for (auto &[u, v, w] : edges) cin >> u >> v >> w, --u, --v;\n\
    \n    vector<int> terminals(T);\n    for (auto &v : terminals) cin >> v, --v;\n\
    \n    const auto [cost, used_edges] = MinimumSteinerTree(N, edges, terminals);\n\
    \    cout << cost << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/114\"\n#include \"../minimum_steiner_tree.hpp\"\
    \n\n#include <iostream>\n#include <tuple>\n#include <vector>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int N, M, T;\n    cin >> N >> M >> T;\n\n    vector<tuple<int, int, int>>\
    \ edges(M);\n    for (auto &[u, v, w] : edges) cin >> u >> v >> w, --u, --v;\n\
    \n    vector<int> terminals(T);\n    for (auto &v : terminals) cin >> v, --v;\n\
    \n    const auto [cost, used_edges] = MinimumSteinerTree(N, edges, terminals);\n\
    \    cout << cost << '\\n';\n}\n"
  dependsOn:
  - graph/minimum_steiner_tree.hpp
  isVerificationFile: true
  path: graph/test/minimum_steiner_tree.yuki114.test.cpp
  requiredBy: []
  timestamp: '2025-08-11 21:45:31+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: graph/test/minimum_steiner_tree.yuki114.test.cpp
layout: document
redirect_from:
- /verify/graph/test/minimum_steiner_tree.yuki114.test.cpp
- /verify/graph/test/minimum_steiner_tree.yuki114.test.cpp.html
title: graph/test/minimum_steiner_tree.yuki114.test.cpp
---
