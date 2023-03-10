---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.11.2/x64/lib/python3.11/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.11.2/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n  File \"/opt/hostedtoolcache/Python/3.11.2/x64/lib/python3.11/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ tsp/mst_edges.hpp: line 2: #pragma once found in a non-first line\n"
  code: "\n#pragma once\n\n#include <algorithm>\n#include <limits>\n#include <utility>\n\
    #include <vector>\n\ntemplate <class DistanceMatrix>\nstd::vector<std::pair<int,\
    \ int>> mst_edges(const DistanceMatrix &dist) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\
    \n    if (dist.n() <= 1) return {};\n\n    std::vector<T> dp(dist.n(), std::numeric_limits<T>::max());\n\
    \    std::vector<int> prv(dist.n(), -1);\n    std::vector<int> used(dist.n());\n\
    \    std::vector<std::pair<int, int>> ret(dist.n() - 1);\n\n    for (int t = 0;\
    \ t < dist.n(); ++t) {\n        int x = std::min_element(dp.cbegin(), dp.cend())\
    \ - dp.cbegin();\n        dp.at(x) = std::numeric_limits<T>::max();\n        used.at(x)\
    \ = 1;\n        if (t > 0) ret.at(t - 1) = {prv.at(x), x};\n\n        for (auto\
    \ [y, len] : dist.adjacents(x)) {\n            if (!used.at(y) and len < dp.at(y))\
    \ dp.at(y) = len, prv.at(y) = x;\n        }\n    }\n\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/mst_edges.hpp
  requiredBy: []
  timestamp: '2023-02-16 23:07:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/mst_edges.hpp
layout: document
redirect_from:
- /library/tsp/mst_edges.hpp
- /library/tsp/mst_edges.hpp.html
title: tsp/mst_edges.hpp
---
