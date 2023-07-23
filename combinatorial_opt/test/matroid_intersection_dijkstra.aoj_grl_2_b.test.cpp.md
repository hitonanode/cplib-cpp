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
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B
  bundledCode: "#line 1 \"combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp\"\
    \n#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B\"\
    \n#line 2 \"combinatorial_opt/matroid_intersection_dijkstra.hpp\"\n\n#include\
    \ <cassert>\n#include <queue>\n#include <vector>\n\n// Find maximum weight size\
    \ k + 1 intersection of two matroids using Dijkstra's algorithm\n// Return `true`\
    \ iff larger intersection is found.\n// Complexity: O(Cn + nk log n) (C: circuit\
    \ query)\ntemplate <class Matroid1, class Matroid2, class T = int>\nbool augment_matroid_intersection_dijkstra(\n\
    \    Matroid1 &m1,                 // Matroid, size n, updated\n    Matroid2 &m2,\
    \                 // Matroid, size n, updated\n    std::vector<bool> &I,     \
    \    // Size k maximum weight intersection, size n, updated\n    const std::vector<T>\
    \ &weight, // Weights of elements, size n\n    std::vector<T> &potential     //\
    \ Potential, size n, updated\n) {\n    const int n = I.size();\n\n    assert((int)m1.size()\
    \ == n);\n    assert((int)m2.size() == n);\n    assert((int)weight.size() == n);\n\
    \    assert((int)potential.size() == n);\n\n    m1.set(I);\n    m2.set(I);\n\n\
    \    {\n        int arghi = -1;\n        for (int e = 0; e < n; ++e) {\n     \
    \       if (I.at(e)) continue;\n            if (arghi < 0 or weight.at(arghi)\
    \ < weight.at(e)) arghi = e;\n        }\n        if (arghi < 0) return false;\n\
    \        if (m1.circuit(arghi).empty() and m2.circuit(arghi).empty()) {\n    \
    \        I.at(arghi) = true;\n            return true;\n        }\n    }\n\n \
    \   auto l = [&](int e) -> T { return e < n ? (I.at(e) ? weight.at(e) : -weight.at(e))\
    \ : T(); };\n    auto pot = [&](int e) -> T { return e < n ? potential.at(e) :\
    \ T(); };\n    auto edge_len = [&](int s, int t) -> T { return l(t) - pot(t) +\
    \ pot(s); };\n\n    const int gs = n, gt = n + 1;\n    std::vector<int> on_set;\n\
    \    for (int e = 0; e < n; ++e) {\n        if (I.at(e)) on_set.push_back(e);\n\
    \    }\n\n    // Find minimum weight (& minimum num. of vertices) gs-gt path\n\
    \    using Dist = std::pair<T, int>; // (sum of weights, num. of vertices)\n \
    \   std::vector<Dist> dp(gt + 1, {-1, -1});\n    std::vector<int> prv(gt + 1,\
    \ -1); // prv[i] >= 0 => i is reachable (i != gs)\n\n    using Tpl = std::pair<Dist,\
    \ int>;\n    std::priority_queue<Tpl, std::vector<Tpl>, std::greater<Tpl>> pq;\
    \ // (dist, len, now)\n    std::vector<std::vector<int>> to(dp.size());\n\n  \
    \  for (int e = 0; e < n; ++e) {\n        if (I.at(e)) continue;\n\n        const\
    \ auto c1 = m1.circuit(e), c2 = m2.circuit(e);\n\n        if (c1.empty()) {\n\
    \            to.at(e).push_back(gt);\n            for (int f : on_set) to.at(e).push_back(f);\n\
    \        }\n        for (int f : c1) {\n            if (f != e) to.at(e).push_back(f);\n\
    \        }\n\n        if (c2.empty()) {\n            dp.at(e) = Dist{edge_len(gs,\
    \ e), 1};\n            prv.at(e) = gs;\n            pq.emplace(dp.at(e), e);\n\
    \        }\n        for (int f : c2) {\n            if (f != e) to.at(f).push_back(e);\n\
    \        }\n    }\n\n    while (!pq.empty()) {\n        const auto [dnow, now]\
    \ = pq.top();\n        pq.pop();\n        if (prv.at(now) >= 0 and dp.at(now)\
    \ < dnow) continue;\n\n        for (int nxt : to.at(now)) {\n            const\
    \ auto w = edge_len(now, nxt);\n            // if (w < T() and now < n and nxt\
    \ < n) assert(false); // for debug\n\n            Dist dnxt(dnow.first + w, dnow.second\
    \ + 1);\n\n            if (prv.at(nxt) < 0 or dnxt < dp.at(nxt)) {\n         \
    \       dp.at(nxt) = dnxt;\n                prv.at(nxt) = now;\n             \
    \   if (nxt != gt) pq.emplace(dnxt, nxt);\n            }\n        }\n    }\n\n\
    \    if (prv.at(gt) < 0) return false;\n\n    for (int e = 0; e < n; ++e) {\n\
    \        auto [dist, len] = dp.at(e);\n        if (len >= 0) potential.at(e) +=\
    \ dist;\n    }\n\n    for (int e = prv.at(gt); e != gs; e = prv.at(e)) {\n   \
    \     potential.at(e) -= l(e);\n        I.at(e) = !I.at(e);\n    }\n\n    return\
    \ true;\n}\n#line 3 \"combinatorial_opt/matroids/graphic_matroid.hpp\"\n#include\
    \ <utility>\n#line 5 \"combinatorial_opt/matroids/graphic_matroid.hpp\"\n\n//\
    \ GraphicMatroid: subgraph of undirected graphs, without loops\nclass GraphicMatroid\
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
    combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp\"\n\
    #include <iostream>\n#line 8 \"combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp\"\
    \nusing namespace std;\n\nint main() {\n    int V, E, r;\n    cin >> V >> E >>\
    \ r;\n    vector<vector<int>> partition(V);\n    vector<int> R(V, 1);\n    R.at(r)\
    \ = 0;\n    vector<pair<int, int>> edges;\n    vector<int> weight;\n    for (int\
    \ e = 0; e < E; ++e) {\n        int s, t, w;\n        cin >> s >> t >> w;\n  \
    \      partition.at(t).push_back(e);\n        edges.emplace_back(s, t);\n    \
    \    weight.emplace_back(-w);\n    }\n    PartitionMatroid M1(E, partition, R);\n\
    \    GraphicMatroid M2(V, edges);\n\n    vector<int> potential(weight.size());\n\
    \    vector<bool> sol(weight.size());\n    while (augment_matroid_intersection_dijkstra(M1,\
    \ M2, sol, weight, potential)) continue;\n\n    int ret = 0;\n    for (int e =\
    \ 0; e < E; ++e) ret -= sol.at(e) * weight.at(e);\n    cout << ret << '\\n';\n\
    }\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_2_B\"\
    \n#include \"../matroid_intersection_dijkstra.hpp\"\n#include \"../matroids/graphic_matroid.hpp\"\
    \n#include \"../matroids/partition_matroid.hpp\"\n#include <iostream>\n#include\
    \ <utility>\n#include <vector>\nusing namespace std;\n\nint main() {\n    int\
    \ V, E, r;\n    cin >> V >> E >> r;\n    vector<vector<int>> partition(V);\n \
    \   vector<int> R(V, 1);\n    R.at(r) = 0;\n    vector<pair<int, int>> edges;\n\
    \    vector<int> weight;\n    for (int e = 0; e < E; ++e) {\n        int s, t,\
    \ w;\n        cin >> s >> t >> w;\n        partition.at(t).push_back(e);\n   \
    \     edges.emplace_back(s, t);\n        weight.emplace_back(-w);\n    }\n   \
    \ PartitionMatroid M1(E, partition, R);\n    GraphicMatroid M2(V, edges);\n\n\
    \    vector<int> potential(weight.size());\n    vector<bool> sol(weight.size());\n\
    \    while (augment_matroid_intersection_dijkstra(M1, M2, sol, weight, potential))\
    \ continue;\n\n    int ret = 0;\n    for (int e = 0; e < E; ++e) ret -= sol.at(e)\
    \ * weight.at(e);\n    cout << ret << '\\n';\n}\n"
  dependsOn:
  - combinatorial_opt/matroid_intersection_dijkstra.hpp
  - combinatorial_opt/matroids/graphic_matroid.hpp
  - combinatorial_opt/matroids/partition_matroid.hpp
  isVerificationFile: true
  path: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
  requiredBy: []
  timestamp: '2023-07-23 15:18:37+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
- /verify/combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp.html
title: combinatorial_opt/test/matroid_intersection_dijkstra.aoj_grl_2_b.test.cpp
---
