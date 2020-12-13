---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 193, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 399, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \  File \"/opt/hostedtoolcache/Python/3.9.0/x64/lib/python3.9/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 258, in _resolve\n    raise BundleErrorAt(path, -1, \"no such header\"\
    )\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt: flow/mincostflow.hpp:\
    \ line -1: no such header\n"
  code: "#pragma once\n#include \"flow/mincostflow.hpp\"\n#include <algorithm>\n#include\
    \ <vector>\n\n// CUT begin\ntemplate <typename CAP, typename COST> struct B_Flow\
    \ {\n    int N, E;\n    COST cost_bias;\n    bool infeasible;\n    mcf_graph<CAP,\
    \ COST> mcf;\n    std::vector<CAP> b;\n    std::vector<CAP> fbias;\n    std::vector<int>\
    \ fdir;\n    std::vector<CAP> f;\n    std::vector<COST> potential;\n\n    B_Flow(int\
    \ N = 0) : N(N), E(0), cost_bias(0), infeasible(false), mcf(N + 2), b(N) {}\n\n\
    \    void add_supply(int v, CAP supply) { b[v] += supply; }\n    void add_demand(int\
    \ v, CAP demand) { b[v] -= demand; }\n    void add_edge(int s, int t, CAP lower_cap,\
    \ CAP upper_cap, COST cost) {\n        assert(s >= 0 and s < N);\n        assert(t\
    \ >= 0 and t < N);\n        if (lower_cap > upper_cap) {\n            infeasible\
    \ = true;\n            return;\n        }\n        E++;\n        if (s == t) {\n\
    \            if (cost > 0)\n                upper_cap = lower_cap;\n         \
    \   else\n                lower_cap = upper_cap;\n        }\n        if (cost\
    \ < 0) {\n            fbias.emplace_back(lower_cap);\n            fdir.emplace_back(-1);\n\
    \            cost_bias += cost * upper_cap;\n            b[s] -= upper_cap;\n\
    \            b[t] += upper_cap;\n            mcf.add_edge(t, s, upper_cap - lower_cap,\
    \ -cost);\n        } else {\n            fbias.emplace_back(upper_cap);\n    \
    \        fdir.emplace_back(1);\n            if (lower_cap < 0) {\n           \
    \     cost_bias += cost * lower_cap, b[s] -= lower_cap, b[t] += lower_cap;\n \
    \               upper_cap -= lower_cap, lower_cap = 0;\n            }\n      \
    \      if (lower_cap > 0) {\n                cost_bias += cost * lower_cap;\n\
    \                b[s] -= lower_cap;\n                b[t] += lower_cap;\n    \
    \            upper_cap -= lower_cap;\n            }\n            mcf.add_edge(s,\
    \ t, upper_cap, cost);\n        }\n    }\n\n    std::pair<bool, COST> solve()\
    \ {\n        if (infeasible) { return std::make_pair(false, 0); }\n        CAP\
    \ bsum = 0, bsum_negative = 0;\n        for (int i = 0; i < N; i++) {\n      \
    \      if (b[i] > 0) { mcf.add_edge(N, i, b[i], 0), bsum += b[i]; }\n        \
    \    if (b[i] < 0) { mcf.add_edge(i, N + 1, -b[i], 0), bsum_negative -= b[i];\
    \ }\n        }\n        if (bsum != bsum_negative) { return std::make_pair(false,\
    \ 0); }\n        std::fill(b.begin(), b.end(), 0);\n        auto ret = mcf.flow(N,\
    \ N + 1, bsum);\n        potential = mcf.dual, potential.resize(N);\n        COST\
    \ cost_ret = cost_bias + ret.second;\n        cost_bias = 0;\n        bool succeeded\
    \ = (ret.first == bsum);\n        f = fbias;\n        for (int i = 0; i < E; i++)\
    \ {\n            const std::pair<int, int> &p = mcf.pos[i];\n            f[i]\
    \ -= fdir[i] * mcf.g[p.first][p.second].cap;\n        }\n        return std::make_pair(succeeded,\
    \ cost_ret);\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: combinatorial_opt/b-flow.hpp
  requiredBy: []
  timestamp: '1970-01-01 00:00:00+00:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: combinatorial_opt/b-flow.hpp
layout: document
redirect_from:
- /library/combinatorial_opt/b-flow.hpp
- /library/combinatorial_opt/b-flow.hpp.html
title: combinatorial_opt/b-flow.hpp
---
