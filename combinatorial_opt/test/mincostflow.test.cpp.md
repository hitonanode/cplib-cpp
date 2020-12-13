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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/mincostflow.hpp:\
    \ line -1: no such header\n"
  code: "#include \"flow/mincostflow.hpp\"\n#include \"flow/mincostflow_bellmanford.hpp\"\
    \n#include <cassert>\n#include <iostream>\n#define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_B\"\
    \n\nint main() {\n    int V, E, F;\n    std::cin >> V >> E >> F;\n    mcf_graph<long\
    \ long, long long> mcf_ac(V);\n    MinCostFlow<long long, long long> mcf_bf(V);\n\
    \    for (int i = 0; i < E; i++) {\n        int u, v, c, d;\n        std::cin\
    \ >> u >> v >> c >> d;\n        mcf_ac.add_edge(u, v, c, d);\n        mcf_bf.add_edge(u,\
    \ v, c, d);\n    }\n\n    auto [cap_ac, cost_ac] = mcf_ac.flow(0, V - 1, F);\n\
    \    auto [cap_bf, cost_bf] = mcf_bf.flow(0, V - 1, F);\n    assert(cap_ac ==\
    \ cap_bf and cost_ac == cost_bf);\n    std::cout << (cap_ac == F ? cost_ac : -1)\
    \ << '\\n';\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: combinatorial_opt/test/mincostflow.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: combinatorial_opt/test/mincostflow.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/mincostflow.test.cpp
- /verify/combinatorial_opt/test/mincostflow.test.cpp.html
title: combinatorial_opt/test/mincostflow.test.cpp
---
