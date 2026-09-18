---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/matroid_intersection_dijkstra.hpp
    title: Weighted matroid intersection using Dijkstra's algorithm
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/matroids/graphic_matroid.hpp
    title: "Graphic matroid \uFF08\u30B0\u30E9\u30D5\u30DE\u30C8\u30ED\u30A4\u30C9\
      \uFF09"
  - icon: ':heavy_check_mark:'
    path: combinatorial_opt/matroids/partition_matroid.hpp
    title: "Partition matroid \uFF08\u5206\u5272\u30DE\u30C8\u30ED\u30A4\u30C9\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605
  bundledCode: "#line 1 \"combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605\"\
    \n#line 2 \"combinatorial_opt/matroid_intersection_dijkstra.hpp\"\n\n#include\
    \ <cassert>\n#include <queue>\n#include <vector>\n\n// Find maximum weight size\
    \ k + 1 intersection of two matroids using Dijkstra's algorithm\n// Return `true`\
    \ iff larger intersection is found.\n// Complexity: O(Cn + nk log n) (C: circuit\
    \ query)\ntemplate <class Matroid1, class Matroid2, class T = int>\nbool augment_matroid_intersection_dijkstra(\n\
    \    Matroid1 &m1,                 // Matroid, size n, updated\n    Matroid2 &m2,\
    \                 // Matroid, size n, updated\n    std::vector<bool> &I,     \
    \    // Size k maximum weight intersection, size n, updated\n    const std::vector<T>\
    \ &weight, // Weights of elements, size n\n    std::vector<T> &potential     //\
    \ Potential, size n + 2, updated\n) {\n    const int n = I.size();\n\n    assert((int)m1.size()\
    \ == n);\n    assert((int)m2.size() == n);\n    assert((int)weight.size() == n);\n\
    \    assert(potential.empty() or ((int)potential.size() == n) or ((int)potential.size()\
    \ == n + 2));\n\n    m1.set(I);\n    m2.set(I);\n\n    potential.resize(n + 2);\n\
    \n    auto l = [&](int e) -> T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e))\
    \ : T(); };\n    auto edge_len = [&](int s, int t) -> T { return l(t) - potential.at(t)\
    \ + potential.at(s); };\n\n    if (true) { // \u81EA\u660E\u306A\u8FFD\u52A0\u304C\
    \u53EF\u80FD\u304B\u30C1\u30A7\u30C3\u30AF\uFF08\u7701\u7565\u3057\u3066\u3082\
    \u30A2\u30EB\u30B4\u30EA\u30BA\u30E0\u306F\u6B63\u5F53\uFF09\n        int max_elem\
    \ = -1;\n        for (int e = 0; e < n; ++e) {\n            if (!I.at(e) and (max_elem\
    \ < 0 or weight.at(max_elem) < weight.at(e))) max_elem = e;\n        }\n     \
    \   if (max_elem < 0) return false;\n        for (int e = 0; e < n; ++e) {\n \
    \           if (!I.at(e) and weight.at(e) == weight.at(max_elem) and m1.circuit(e).empty()\
    \ and\n                m2.circuit(e).empty()) {\n                potential.at(e)\
    \ -= l(e);\n                I.at(e) = true;\n                return true;\n  \
    \          }\n        }\n    }\n\n    // Find minimum length (& minimum num. of\
    \ vertices) gs-gt path\n    const int gs = n, gt = n + 1;\n    std::vector<std::vector<int>>\
    \ to(gt + 1);\n\n    bool has_gs_edge = false, has_gt_edge = false;\n\n    for\
    \ (int e = 0; e < n; ++e) {\n        if (I.at(e)) continue;\n\n        const auto\
    \ c1 = m1.circuit(e), c2 = m2.circuit(e);\n\n        if (c1.empty()) {\n     \
    \       to.at(e).push_back(gt);\n            if (!has_gt_edge) {\n           \
    \     has_gt_edge = true;\n                potential.at(gt) = potential.at(e);\n\
    \            }\n            if (T el = edge_len(e, gt); el < T()) potential.at(gt)\
    \ += el;\n        }\n        for (int f : c1) {\n            if (f != e) to.at(e).push_back(f);\n\
    \        }\n\n        if (c2.empty()) {\n            to.at(gs).push_back(e);\n\
    \            if (!has_gs_edge) {\n                has_gs_edge = true;\n      \
    \          potential.at(gs) = potential.at(e) - l(e);\n            }\n       \
    \     if (T el = edge_len(gs, e); el < T()) potential.at(gs) -= el;\n        }\n\
    \        for (int f : c2) {\n            if (f != e) to.at(f).push_back(e);\n\
    \        }\n    }\n\n    if (const T e0 = potential.at(gs); e0 != T()) {\n   \
    \     for (auto &p : potential) p -= e0;\n    }\n\n    if (!has_gs_edge or !has_gt_edge)\
    \ return false;\n\n    std::vector<bool> potential_fixed(gt + 1);\n\n    T potential_add_unfixed_es\
    \ = T();\n\n    auto fix_potential = [&](int e) -> void {\n        assert(!potential_fixed.at(e));\n\
    \        potential_fixed.at(e) = true;\n        potential.at(e) += potential_add_unfixed_es;\n\
    \    };\n\n    std::priority_queue<std::pair<T, int>, std::vector<std::pair<T,\
    \ int>>, std::greater<>> pq;\n    std::vector<T> dijkstra(gt + 1);\n    std::vector<int>\
    \ prv(gt + 1, -1);\n\n    pq.emplace(T(), gs);\n\n    while (!pq.empty()) {\n\
    \        const int e = pq.top().second;\n        pq.pop();\n        if (potential_fixed.at(e))\
    \ continue;\n        if (e != gs) potential_add_unfixed_es = edge_len(prv.at(e),\
    \ e);\n\n        std::vector<std::pair<int, int>> push_cands;\n\n        auto\
    \ rec = [&](auto &&self, int cur) -> bool {\n            if (cur == gt) return\
    \ true;\n            fix_potential(cur);\n\n            for (int nxt : to.at(cur))\
    \ {\n                if (potential_fixed.at(nxt)) continue;\n\n              \
    \  const T len = edge_len(cur, nxt) - potential_add_unfixed_es;\n            \
    \    // if (len < T()) std::cerr << cur << ' ' << nxt << ' ' << len << std::endl;\n\
    \                assert(len >= T());\n\n                if (len == T()) {\n  \
    \                  prv.at(nxt) = cur;\n                    if (self(self, nxt))\
    \ return true;\n                } else {\n                    if (prv.at(nxt)\
    \ == -1 or potential_add_unfixed_es + len < dijkstra.at(nxt)) {\n            \
    \            dijkstra.at(nxt) = potential_add_unfixed_es + len;\n            \
    \            prv.at(nxt) = cur;\n                        push_cands.emplace_back(nxt,\
    \ cur);\n                    }\n                }\n            }\n           \
    \ return false;\n        };\n        if (rec(rec, e)) break;\n\n        for (auto\
    \ [nxt, now] : push_cands) {\n            if (prv.at(nxt) == now) pq.emplace(dijkstra.at(nxt),\
    \ nxt);\n        }\n    }\n\n    for (int e = 0; e < gt + 1; ++e) {\n        if\
    \ (!potential_fixed.at(e)) fix_potential(e);\n    }\n\n    if (prv.at(gt) < 0)\
    \ return false;\n\n    prv.assign(gt + 1, -1);\n    std::queue<int> q;\n    q.push(gs);\n\
    \n    for (int now = q.front(); now != gt; now = q.front()) {\n        q.pop();\n\
    \        for (int nxt : to.at(now)) {\n            if (prv.at(nxt) == -1 and edge_len(now,\
    \ nxt) == T()) {\n                prv.at(nxt) = now;\n                q.push(nxt);\n\
    \            }\n        }\n    }\n\n    for (int e = prv.at(gt); e != gs; e =\
    \ prv.at(e)) {\n        potential.at(e) -= l(e);\n        I.at(e) = !I.at(e);\n\
    \    }\n\n    return true;\n}\n#line 3 \"combinatorial_opt/matroids/graphic_matroid.hpp\"\
    \n#include <utility>\n#line 5 \"combinatorial_opt/matroids/graphic_matroid.hpp\"\
    \n\n// GraphicMatroid: subgraph of undirected graphs, without loops\nclass GraphicMatroid\
    \ {\n    using Vertex = int;\n    using Element = int;\n    int M;\n    int V;\
    \ // # of vertices of graph\n    std::vector<std::vector<std::pair<Vertex, Element>>>\
    \ to;\n    std::vector<std::pair<Vertex, Vertex>> edges;\n    std::vector<Element>\
    \ backtrack;\n    std::vector<Vertex> vprev;\n    std::vector<int> depth, root;\n\
    \npublic:\n    GraphicMatroid(int V, const std::vector<std::pair<Vertex, Vertex>>\
    \ &edges_)\n        : M(edges_.size()), V(V), to(V), edges(edges_) {\n       \
    \ for (int e = 0; e < int(edges_.size()); e++) {\n            int u = edges_[e].first,\
    \ v = edges_[e].second;\n            assert(0 <= u and u < V);\n            assert(0\
    \ <= v and v < V);\n            if (u != v) {\n                to[u].emplace_back(v,\
    \ e);\n                to[v].emplace_back(u, e);\n            }\n        }\n \
    \   }\n    int size() const { return M; }\n\n    std::vector<Vertex> que;\n  \
    \  template <class State> void set(State I) {\n        assert(int(I.size()) ==\
    \ M);\n        backtrack.assign(V, -1);\n        vprev.assign(V, -1);\n      \
    \  depth.assign(V, -1);\n        root.assign(V, -1);\n        que.resize(V);\n\
    \        int qb = 0, qe = 0;\n        for (Vertex i = 0; i < V; i++) {\n     \
    \       if (backtrack[i] >= 0) continue;\n            que[qb = 0] = i, qe = 1,\
    \ depth[i] = 0;\n            while (qb < qe) {\n                Vertex now = que[qb++];\n\
    \                root[now] = i;\n                for (auto nxt : to[now]) {\n\
    \                    if (depth[nxt.first] < 0 and I[nxt.second]) {\n         \
    \               backtrack[nxt.first] = nxt.second;\n                        vprev[nxt.first]\
    \ = now;\n                        depth[nxt.first] = depth[now] + 1;\n       \
    \                 que[qe++] = nxt.first;\n                    }\n            \
    \    }\n            }\n        }\n    }\n\n    std::vector<Element> circuit(const\
    \ Element e) const {\n        assert(0 <= e and e < M);\n        Vertex s = edges[e].first,\
    \ t = edges[e].second;\n        if (root[s] != root[t]) return {};\n        std::vector<Element>\
    \ ret{e};\n        auto step = [&](Vertex &i) { ret.push_back(backtrack[i]), i\
    \ = vprev[i]; };\n        int ddepth = depth[s] - depth[t];\n        for (; ddepth\
    \ > 0; --ddepth) step(s);\n        for (; ddepth < 0; ++ddepth) step(t);\n   \
    \     while (s != t) step(s), step(t);\n        return ret;\n    }\n};\n#line\
    \ 4 \"combinatorial_opt/matroids/partition_matroid.hpp\"\n\n// Partition matroid\
    \ (partitional matroid) : direct sum of uniform matroids\nclass PartitionMatroid\
    \ {\n    using Element = int;\n    int M;\n    std::vector<std::vector<Element>>\
    \ parts;\n    std::vector<int> belong;\n    std::vector<int> R;\n    std::vector<int>\
    \ cnt;\n    std::vector<std::vector<Element>> circuits;\n\npublic:\n    // parts:\
    \ partition of [0, 1, ..., M - 1]\n    // R: only R[i] elements from parts[i]\
    \ can be chosen for each i.\n    PartitionMatroid(int M, const std::vector<std::vector<int>>\
    \ &parts_, const std::vector<int> &R_)\n        : M(M), parts(parts_), belong(M,\
    \ -1), R(R_) {\n        assert(parts.size() == R.size());\n        for (int i\
    \ = 0; i < int(parts.size()); i++) {\n            for (Element e : parts[i]) belong[e]\
    \ = i;\n        }\n        for (Element e = 0; e < M; e++) {\n            // assert(belong[e]\
    \ != -1);\n            if (belong[e] == -1) {\n                belong[e] = parts.size();\n\
    \                parts.push_back({e});\n                R.push_back(1);\n    \
    \        }\n        }\n    }\n    int size() const { return M; }\n\n    template\
    \ <class State> void set(const State &I) {\n        cnt = R;\n        for (int\
    \ e = 0; e < M; e++) {\n            if (I[e]) cnt[belong[e]]--;\n        }\n \
    \       circuits.assign(cnt.size(), {});\n        for (int e = 0; e < M; e++)\
    \ {\n            if (I[e] and cnt[belong[e]] == 0) circuits[belong[e]].push_back(e);\n\
    \        }\n    }\n\n    std::vector<Element> circuit(const Element e) const {\n\
    \        assert(0 <= e and e < M);\n        int p = belong[e];\n        if (cnt[p]\
    \ == 0) {\n            auto ret = circuits[p];\n            ret.push_back(e);\n\
    \            return ret;\n        }\n        return {};\n    }\n};\n#line 5 \"\
    combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp\"\n#include\
    \ <iostream>\n#include <numeric>\n#line 9 \"combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n\
    \    while (true) {\n        int N, M, K;\n        cin >> N >> M >> K;\n     \
    \   if (N == 0) break;\n        vector<vector<int>> partition(2);\n        vector<int>\
    \ R{K, N - 1 - K};\n        vector<pair<int, int>> edges;\n        vector<int>\
    \ weight;\n        for (int e = 0; e < M; ++e) {\n            int u, v, w;\n \
    \           char l;\n            cin >> u >> v >> w >> l;\n            --u, --v;\n\
    \            partition[l == 'B'].push_back(e);\n            edges.emplace_back(u,\
    \ v);\n            weight.push_back(-w);\n        }\n        PartitionMatroid\
    \ M1(edges.size(), partition, R);\n        GraphicMatroid M2(N, edges);\n\n  \
    \      vector<int> potential(weight.size());\n        vector<bool> ret(weight.size());\n\
    \        while (augment_matroid_intersection_dijkstra(M1, M2, ret, weight, potential))\
    \ continue;\n        int ne = accumulate(ret.begin(), ret.end(), 0);\n       \
    \ if (ne < N - 1) {\n            cout << \"-1\\n\";\n        } else {\n      \
    \      int sum = 0;\n            for (int e = 0; e < M; ++e) sum -= ret.at(e)\
    \ * weight.at(e);\n            cout << sum << '\\n';\n        }\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1605\"\
    \n#include \"../matroid_intersection_dijkstra.hpp\"\n#include \"../matroids/graphic_matroid.hpp\"\
    \n#include \"../matroids/partition_matroid.hpp\"\n#include <iostream>\n#include\
    \ <numeric>\n#include <utility>\n#include <vector>\nusing namespace std;\n\nint\
    \ main() {\n    cin.tie(nullptr);\n    ios::sync_with_stdio(false);\n    while\
    \ (true) {\n        int N, M, K;\n        cin >> N >> M >> K;\n        if (N ==\
    \ 0) break;\n        vector<vector<int>> partition(2);\n        vector<int> R{K,\
    \ N - 1 - K};\n        vector<pair<int, int>> edges;\n        vector<int> weight;\n\
    \        for (int e = 0; e < M; ++e) {\n            int u, v, w;\n           \
    \ char l;\n            cin >> u >> v >> w >> l;\n            --u, --v;\n     \
    \       partition[l == 'B'].push_back(e);\n            edges.emplace_back(u, v);\n\
    \            weight.push_back(-w);\n        }\n        PartitionMatroid M1(edges.size(),\
    \ partition, R);\n        GraphicMatroid M2(N, edges);\n\n        vector<int>\
    \ potential(weight.size());\n        vector<bool> ret(weight.size());\n      \
    \  while (augment_matroid_intersection_dijkstra(M1, M2, ret, weight, potential))\
    \ continue;\n        int ne = accumulate(ret.begin(), ret.end(), 0);\n       \
    \ if (ne < N - 1) {\n            cout << \"-1\\n\";\n        } else {\n      \
    \      int sum = 0;\n            for (int e = 0; e < M; ++e) sum -= ret.at(e)\
    \ * weight.at(e);\n            cout << sum << '\\n';\n        }\n    }\n}\n"
  dependsOn:
  - combinatorial_opt/matroid_intersection_dijkstra.hpp
  - combinatorial_opt/matroids/graphic_matroid.hpp
  - combinatorial_opt/matroids/partition_matroid.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
  requiredBy: []
  timestamp: '2023-07-23 18:47:47+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
- /verify/combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp.html
title: combinatorial_opt/test/matroid_intersection_dijkstra.aoj1605.test.cpp
---
