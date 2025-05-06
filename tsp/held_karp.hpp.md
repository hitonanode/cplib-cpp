---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf
  bundledCode: "Traceback (most recent call last):\n  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/documentation/build.py\"\
    , line 71, in _render_source_code_stat\n    bundled_code = language.bundle(stat.path,\
    \ basedir=basedir, options={'include_paths': [basedir]}).decode()\n          \
    \         ~~~~~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus.py\"\
    , line 187, in bundle\n    bundler.update(path)\n    ~~~~~~~~~~~~~~^^^^^^\n  File\
    \ \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 401, in update\n    self.update(self._resolve(pathlib.Path(included), included_from=path))\n\
    \    ~~~~~~~~~~~^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^\n\
    \  File \"/opt/hostedtoolcache/Python/3.13.3/x64/lib/python3.13/site-packages/onlinejudge_verify/languages/cplusplus_bundle.py\"\
    , line 312, in update\n    raise BundleErrorAt(path, i + 1, \"#pragma once found\
    \ in a non-first line\")\nonlinejudge_verify.languages.cplusplus_bundle.BundleErrorAt:\
    \ tsp/mst_edges.hpp: line 2: #pragma once found in a non-first line\n"
  code: "#pragma once\n\n#include \"tsp/csr_distance_matrix.hpp\"\n#include \"tsp/minimum_one_tree.hpp\"\
    \n\n#include <algorithm>\n#include <utility>\n#include <vector>\n\n// Held\u2013\
    Karp lower bound\n// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    // p.26, p.33\ntemplate <class DistanceMatrix> auto held_karp_lower_bound(const\
    \ DistanceMatrix &dist) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\
    \n    std::vector<T> best_pi(dist.n()), pi(dist.n());\n    std::vector<int> V;\n\
    \    T W;\n    std::tie(W, V) = minimum_one_tree(dist, pi);\n    if (std::count(V.cbegin(),\
    \ V.cend(), 0) == dist.n()) return std::make_pair(W, pi);\n\n    std::vector<int>\
    \ lastV = V;\n\n    T BestW = W;\n    const int initial_period = (dist.n() + 1)\
    \ / 2;\n    bool is_initial_phase = true;\n    int period = initial_period;\n\n\
    \    const auto sparse_subgraph = build_adjacent_info(dist, 50); // p.47\n\n \
    \   for (long long t0 = 1; t0 > 0; period /= 2, t0 /= 2) {\n        for (int p\
    \ = 1; t0 > 0 and p <= period; ++p) {\n            for (int i = 0; i < dist.n();\
    \ ++i) {\n                if (V.at(i) != 0) pi.at(i) += t0 * (7 * V.at(i) + 3\
    \ * lastV.at(i)) / 10;\n            }\n            std::swap(lastV, V);\n    \
    \        std::tie(W, V) = minimum_one_tree(sparse_subgraph, pi);\n           \
    \ if (std::count(begin(V), begin(V) + dist.n(), 0) == dist.n())\n            \
    \    return std::make_pair(W, pi);\n            if (W > BestW) {\n           \
    \     BestW = W;\n                best_pi = pi;\n                if (is_initial_phase)\
    \ t0 *= 2;\n                if (p == period) period = std::min(period * 2, initial_period);\n\
    \n            } else if (is_initial_phase and p > period / 2) {\n            \
    \    is_initial_phase = false;\n                p = 0;\n                t0 = 3\
    \ * t0 / 4;\n            }\n        }\n    }\n    BestW = minimum_one_tree(dist,\
    \ best_pi).first;\n    return std::make_pair(BestW, best_pi);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/held_karp.hpp
  requiredBy: []
  timestamp: '2023-08-30 22:52:16+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/held_karp.hpp
layout: document
redirect_from:
- /library/tsp/held_karp.hpp
- /library/tsp/held_karp.hpp.html
title: tsp/held_karp.hpp
---
