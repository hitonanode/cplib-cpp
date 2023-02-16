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
    - http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf,
  bundledCode: "#line 2 \"tsp/calc_lkh_alpha.hpp\"\n\n#include <vector>\n\n// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf,\
    \ p.20\ntemplate <class DistanceMatrix> auto calc_lkh_alpha(const DistanceMatrix\
    \ &dist) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\n \
    \   std::vector<std::vector<int>> to(dist.n());\n\n    for (auto [s, t] : mst_edges(dist))\
    \ {\n        to.at(s).push_back(t);\n        to.at(t).push_back(s);\n    }\n\n\
    \    std::vector ret(dist.n(), std::vector<T>(dist.n()));\n\n    for (int s =\
    \ 0; s < dist.n(); ++s) {\n        auto rec = [&](auto &&self, int now, int prv,\
    \ T hi) -> void {\n            ret.at(s).at(now) = dist(s, now) - hi;\n      \
    \      for (int nxt : to.at(now)) {\n                if (nxt == prv) continue;\n\
    \                self(self, nxt, now, std::max(hi, dist(now, nxt)));\n       \
    \     }\n        };\n        rec(rec, s, -1, T());\n    }\n\n    // Determining\
    \ special node for the 1-tree\n    // Reference: p.26 of http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    \    int best_one = -1;\n    T longest_2nd_nearest = T();\n\n    for (int one\
    \ = 0; one < dist.n(); ++one) {\n        if (to.at(one).size() != 1) continue;\n\
    \        const int ng = to.at(one).front();\n        bool found = false;\n   \
    \     T second_nearest = T();\n\n        for (auto [v, len] : dist.adjacents(one))\
    \ {\n            if (v == ng) continue;\n            if (!found) {\n         \
    \       found = true, second_nearest = len;\n            } else if (len < second_nearest)\
    \ {\n                second_nearest = len;\n            }\n        }\n\n     \
    \   if (found and (best_one < 0 or second_nearest > longest_2nd_nearest))\n  \
    \          best_one = one, longest_2nd_nearest = second_nearest;\n    }\n\n  \
    \  if (best_one != -1) {\n        for (auto [v, len] : dist.adjacents(best_one))\
    \ {\n            if (v == to.at(best_one).front()) continue;\n            ret.at(best_one).at(v)\
    \ = ret.at(v).at(best_one) = len - longest_2nd_nearest;\n        }\n    }\n\n\
    \    return ret;\n}\n"
  code: "#pragma once\n\n#include <vector>\n\n// http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf,\
    \ p.20\ntemplate <class DistanceMatrix> auto calc_lkh_alpha(const DistanceMatrix\
    \ &dist) {\n    using T = decltype((*dist.adjacents(0).begin()).second);\n\n \
    \   std::vector<std::vector<int>> to(dist.n());\n\n    for (auto [s, t] : mst_edges(dist))\
    \ {\n        to.at(s).push_back(t);\n        to.at(t).push_back(s);\n    }\n\n\
    \    std::vector ret(dist.n(), std::vector<T>(dist.n()));\n\n    for (int s =\
    \ 0; s < dist.n(); ++s) {\n        auto rec = [&](auto &&self, int now, int prv,\
    \ T hi) -> void {\n            ret.at(s).at(now) = dist(s, now) - hi;\n      \
    \      for (int nxt : to.at(now)) {\n                if (nxt == prv) continue;\n\
    \                self(self, nxt, now, std::max(hi, dist(now, nxt)));\n       \
    \     }\n        };\n        rec(rec, s, -1, T());\n    }\n\n    // Determining\
    \ special node for the 1-tree\n    // Reference: p.26 of http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    \    int best_one = -1;\n    T longest_2nd_nearest = T();\n\n    for (int one\
    \ = 0; one < dist.n(); ++one) {\n        if (to.at(one).size() != 1) continue;\n\
    \        const int ng = to.at(one).front();\n        bool found = false;\n   \
    \     T second_nearest = T();\n\n        for (auto [v, len] : dist.adjacents(one))\
    \ {\n            if (v == ng) continue;\n            if (!found) {\n         \
    \       found = true, second_nearest = len;\n            } else if (len < second_nearest)\
    \ {\n                second_nearest = len;\n            }\n        }\n\n     \
    \   if (found and (best_one < 0 or second_nearest > longest_2nd_nearest))\n  \
    \          best_one = one, longest_2nd_nearest = second_nearest;\n    }\n\n  \
    \  if (best_one != -1) {\n        for (auto [v, len] : dist.adjacents(best_one))\
    \ {\n            if (v == to.at(best_one).front()) continue;\n            ret.at(best_one).at(v)\
    \ = ret.at(v).at(best_one) = len - longest_2nd_nearest;\n        }\n    }\n\n\
    \    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/calc_lkh_alpha.hpp
  requiredBy: []
  timestamp: '2023-02-16 23:07:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/calc_lkh_alpha.hpp
layout: document
redirect_from:
- /library/tsp/calc_lkh_alpha.hpp
- /library/tsp/calc_lkh_alpha.hpp.html
title: tsp/calc_lkh_alpha.hpp
---
