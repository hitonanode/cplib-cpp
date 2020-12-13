---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes: {}
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/mincostflow_bellmanford.hpp:\
    \ line -1: no such header\n"
  code: "#include \"flow/mincostflow_bellmanford.hpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/assignment\"\
    \n#include <algorithm>\n#include <iostream>\n\ntemplate <typename TC> std::pair<TC,\
    \ std::vector<int>> AssignmentProblem(std::vector<std::vector<TC>> cost) {\n \
    \   int N = cost.size();\n    MinCostFlow<long long, long long> mcf(N * 2 + 2);\n\
    \    int S = N * 2, T = N * 2 + 1;\n    TC bias_total_cost = 0;\n    for (int\
    \ i = 0; i < N; i++) {\n        TC lo = *min_element(cost[i].begin(), cost[i].end());\n\
    \        bias_total_cost += lo;\n        mcf.add_edge(S, i, 1, 0);\n        mcf.add_edge(N\
    \ + i, T, 1, 0);\n        for (int j = 0; j < N; j++) { mcf.add_edge(i, N + j,\
    \ 1, cost[i][j] - lo); }\n    }\n    auto total_cost = mcf.flow(S, T, N).second\
    \ + bias_total_cost;\n    std::vector<int> ret;\n\n    for (int i = 0; i < N;\
    \ i++) {\n        for (const auto &g : mcf.g[i]) {\n            if (g.to != S\
    \ and !g.cap) {\n                ret.emplace_back(g.to - N);\n               \
    \ break;\n            }\n        }\n    }\n    return std::make_pair(total_cost,\
    \ ret);\n}\n\nint main() {\n    int N;\n    std::cin >> N;\n    std::vector<std::vector<long\
    \ long>> A(N, std::vector<long long>(N));\n    for (auto &vec : A) {\n       \
    \ for (auto &x : vec) { std::cin >> x; }\n    }\n    auto ret = AssignmentProblem(A);\n\
    \    std::cout << ret.first << '\\n';\n    for (auto x : ret.second) std::cout\
    \ << x << ' ';\n    std::cout << '\\n';\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: combinatorial_opt/test/assignment_problem.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: combinatorial_opt/test/assignment_problem.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/assignment_problem.test.cpp
- /verify/combinatorial_opt/test/assignment_problem.test.cpp.html
title: combinatorial_opt/test/assignment_problem.test.cpp
---
