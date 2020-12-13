---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp>
    - https://snuke.hatenablog.com/entry/2016/07/10/043918>
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/maxflow.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"flow/maxflow.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// MaxFlow with lower bound\n// <https://snuke.hatenablog.com/entry/2016/07/10/043918>\n\
    // <https://ei1333.github.io/library/graph/flow/maxflow-lower-bound.cpp>\n// flush(s,\
    \ t): Calculate maxflow (if solution exists), -1 (otherwise)\ntemplate <typename\
    \ Cap> struct MaxFlowLowerBound {\n    int N;\n    mf_graph<Cap> mf;\n    std::vector<Cap>\
    \ in;\n    MaxFlowLowerBound(int N = 0) : N(N), mf(N + 2), in(N) {}\n    int add_edge(int\
    \ from, int to, Cap cap_lo, Cap cap_hi) {\n        assert(0 <= from and from <\
    \ N);\n        assert(0 <= to and to < N);\n        assert(0 <= cap_lo and cap_lo\
    \ <= cap_hi);\n        in[from] -= cap_lo;\n        in[to] += cap_lo;\n      \
    \  return mf.add_edge(from, to, cap_hi - cap_lo);\n    }\n    Cap flow(int s,\
    \ int t) {\n        assert(s != t);\n        assert(0 <= s and s < N);\n     \
    \   assert(0 <= t and t < N);\n        Cap sum = 0;\n        for (int i = 0; i\
    \ < N; i++) {\n            if (in[i] > 0) mf.add_edge(N, i, in[i]), sum += in[i];\n\
    \            if (in[i] < 0) mf.add_edge(i, N + 1, -in[i]);\n        }\n      \
    \  auto erev = mf.add_edge(t, s, numeric_limits<Cap>::max());\n        if (mf.flow(N,\
    \ N + 1) < sum) return -1;\n        return mf.get_edge(erev).flow + mf.flow(s,\
    \ t);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/maxflow_lb.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/maxflow_lb.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/maxflow_lb.hpp
- /library/combinatorial_opt/maxflow_lb.hpp.html
title: combinatorial_opt/maxflow_lb.hpp
---
