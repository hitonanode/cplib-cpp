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
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/maxflow.hpp:\
    \ line -1: no such header\n"
  code: "#include \"flow/maxflow.hpp\"\n#include <cassert>\n#include <iostream>\n\
    #define PROBLEM \"http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A\"\
    \n\nint main() {\n    int V, E;\n    std::cin >> V >> E;\n    mf_graph<int> graph(V);\n\
    \    while (E--) {\n        int u, v, c;\n        std::cin >> u >> v >> c;\n \
    \       graph.add_edge(u, v, c);\n    }\n    std::cout << graph.flow(0, V - 1)\
    \ << std::endl;\n}\n"
  dependsOn: []
  isVerificationFile: true
  path: combinatorial_opt/test/maxflow.test.cpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: combinatorial_opt/test/maxflow.test.cpp
layout: document
redirect_from:
- /verify/combinatorial_opt/test/maxflow.test.cpp
- /verify/combinatorial_opt/test/maxflow.test.cpp.html
title: combinatorial_opt/test/maxflow.test.cpp
---
