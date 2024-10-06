---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: other_algorithms/monge_shortest_path.hpp
    title: Shortest path of DAG with Monge weights
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/705
    links:
    - https://yukicoder.me/problems/no/705
  bundledCode: "#line 1 \"other_algorithms/test/monge_shortest_path.yuki705.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/705\"\n#line 2 \"other_algorithms/monge_shortest_path.hpp\"\
    \n#include <cassert>\n#include <vector>\n\n// Shortest path of Monge-weighted\
    \ graph\n// Variant of LARSCH Algorithm: https://noshi91.hatenablog.com/entry/2023/02/18/005856\n\
    // Complexity: O(n log n)\n//\n// Given a directed graph with n vertices and weighted\
    \ edges\n// (w(i, j) = cost_callback(i, j) (i < j)),\n// this class calculates\
    \ the shortest path from vertex 0 to all other vertices.\ntemplate <class Cost>\
    \ struct monge_shortest_path {\n    std::vector<Cost> dist; // dist[i] = shortest\
    \ distance from 0 to i\n    std::vector<int> amin;  // amin[i] = previous vertex\
    \ of i in the shortest path\n\n    template <class F> void _check(int i, int k,\
    \ F cost_callback) {\n        if (i <= k) return;\n        if (Cost c = dist[k]\
    \ + cost_callback(k, i); c < dist[i]) dist[i] = c, amin[i] = k;\n    }\n\n   \
    \ template <class F> void _rec_solve(int l, int r, F cost_callback) {\n      \
    \  if (r - l == 1) return;\n\n        const int m = (l + r) / 2;\n        for\
    \ (int k = amin[l]; k <= amin[r]; ++k) _check(m, k, cost_callback);\n\n      \
    \  _rec_solve(l, m, cost_callback);\n        for (int k = l + 1; k <= m; ++k)\
    \ _check(r, k, cost_callback);\n        _rec_solve(m, r, cost_callback);\n   \
    \ }\n\n    template <class F> Cost solve(int n, F cost_callback) {\n        assert(n\
    \ > 0);\n        dist.resize(n);\n        amin.assign(n, 0);\n\n        dist[0]\
    \ = Cost();\n        for (int i = 1; i < n; ++i) dist[i] = cost_callback(0, i);\n\
    \n        _rec_solve(0, n - 1, cost_callback);\n\n        return dist.back();\n\
    \    }\n\n    template <class F> int num_edges() const {\n        int ret = 0;\n\
    \        for (int c = (int)amin.size() - 1; c >= 0; c = amin[c]) ++ret;\n    \
    \    return ret;\n    }\n};\n\n// Find shortest path length from 0 to n - 1 with\
    \ k edges, min_edges <= k <= max_edges\n// https://noshi91.hatenablog.com/entry/2022/01/13/001217\n\
    template <class Cost, class F>\nCost monge_shortest_path_with_specified_edges(int\
    \ n, int min_edges, int max_edges,\n                                         \
    \     Cost max_abs_cost, F cost_callback) {\n\n    assert(1 <= n);\n    assert(0\
    \ <= min_edges);\n    assert(min_edges <= max_edges);\n    assert(max_edges <=\
    \ n - 1);\n\n    monge_shortest_path<Cost> msp;\n\n    auto eval = [&](Cost p)\
    \ -> Cost {\n        msp.solve(n, [&](int i, int j) { return cost_callback(i,\
    \ j) - p; });\n        return -msp.dist.back() - p * (p < 0 ? max_edges : min_edges);\n\
    \    };\n\n    Cost lo = -max_abs_cost * 3, hi = max_abs_cost * 3;\n\n    while\
    \ (lo + 1 < hi) {\n        Cost p = (lo + hi) / 2, f = eval(p), df = eval(p +\
    \ 1) - f;\n        if (df == Cost()) {\n            return -f;\n        } else\
    \ {\n            (df < Cost() ? lo : hi) = p;\n        }\n    }\n\n    Cost flo\
    \ = eval(lo), fhi = eval(hi);\n\n    return flo < fhi ? -flo : -fhi;\n}\n#line\
    \ 3 \"other_algorithms/test/monge_shortest_path.yuki705.test.cpp\"\n\n#line 5\
    \ \"other_algorithms/test/monge_shortest_path.yuki705.test.cpp\"\n#include <cmath>\n\
    #include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N;\n    cin >> N;\n    vector<int> A(N),\
    \ X(N), Y(N);\n    for (auto &a : A) cin >> a;\n    for (auto &x : X) cin >> x;\n\
    \    for (auto &y : Y) cin >> y;\n\n    auto weight = [&](int j, int i) {\n  \
    \      assert(j < i);\n        --i;\n        const long long dx = abs(A.at(i)\
    \ - X.at(j)), dy = Y.at(j);\n        return dx * dx * dx + dy * dy * dy;\n   \
    \ };\n\n    monge_shortest_path<long long> msp;\n    cout << msp.solve(N + 1,\
    \ weight) << '\\n';\n}\n"
  code: "#define PROBLEM \"https://yukicoder.me/problems/no/705\"\n#include \"../monge_shortest_path.hpp\"\
    \n\n#include <cassert>\n#include <cmath>\n#include <iostream>\nusing namespace\
    \ std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\n\
    \    int N;\n    cin >> N;\n    vector<int> A(N), X(N), Y(N);\n    for (auto &a\
    \ : A) cin >> a;\n    for (auto &x : X) cin >> x;\n    for (auto &y : Y) cin >>\
    \ y;\n\n    auto weight = [&](int j, int i) {\n        assert(j < i);\n      \
    \  --i;\n        const long long dx = abs(A.at(i) - X.at(j)), dy = Y.at(j);\n\
    \        return dx * dx * dx + dy * dy * dy;\n    };\n\n    monge_shortest_path<long\
    \ long> msp;\n    cout << msp.solve(N + 1, weight) << '\\n';\n}\n"
  dependsOn:
  - other_algorithms/monge_shortest_path.hpp
  isVerificationFile: true
  path: other_algorithms/test/monge_shortest_path.yuki705.test.cpp
  requiredBy: []
  timestamp: '2024-10-06 15:03:01+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: other_algorithms/test/monge_shortest_path.yuki705.test.cpp
layout: document
redirect_from:
- /verify/other_algorithms/test/monge_shortest_path.yuki705.test.cpp
- /verify/other_algorithms/test/monge_shortest_path.yuki705.test.cpp.html
title: other_algorithms/test/monge_shortest_path.yuki705.test.cpp
---
