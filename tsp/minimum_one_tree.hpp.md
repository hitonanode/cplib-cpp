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
  bundledCode: "#line 2 \"tsp/minimum_one_tree.hpp\"\n\n#include <numeric>\n#include\
    \ <utility>\n#include <vector>\n\ntemplate <class T, class DistanceMatrix>\nstd::pair<T,\
    \ std::vector<int>>\nminimum_one_tree(const DistanceMatrix &dist, const std::vector<T>\
    \ &pi) {\n\n    assert(dist.n() > 2);\n    std::vector<T> dp(dist.n(), std::numeric_limits<T>::max());\n\
    \    std::vector<int> prv(dist.n(), -1);\n    std::vector<int> used(dist.n());\n\
    \n    auto fix_v = [&](int x) -> void {\n        dp.at(x) = std::numeric_limits<T>::max();\n\
    \        used.at(x) = 1;\n        for (auto [y, d] : dist.adjacents(x)) {\n  \
    \          if (used.at(y)) continue;\n            if (T len = pi.at(x) + pi.at(y)\
    \ + d; len < dp.at(y)) dp.at(y) = len, prv.at(y) = x;\n        }\n    };\n\n \
    \   T W = T();\n    std::vector<int> V(dist.n(), -2);\n\n    fix_v(0);\n    for\
    \ (int t = 0; t < dist.n() - 1; ++t) {\n        int i = std::min_element(dp.cbegin(),\
    \ dp.cend()) - dp.cbegin();\n        W += dp.at(i);\n        ++V.at(i);\n    \
    \    ++V.at(prv.at(i));\n        fix_v(i);\n    }\n\n    // p.26, http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    \    T wlo = T();\n    int ilo = -1, jlo = -1;\n    for (int i = 0; i < dist.n();\
    \ ++i) {\n        if (V.at(i) != -1) continue;\n        T tmp = T();\n       \
    \ int jtmp = -1;\n        for (auto [j, d] : dist.adjacents(i)) {\n          \
    \  if (prv.at(i) == j or prv.at(j) == i or i == j) continue;\n            if (T\
    \ len = pi.at(i) + pi.at(j) + d; jtmp == -1 or tmp > len) tmp = len, jtmp = j;\n\
    \        }\n        if (jtmp != -1 and (ilo == -1 or wlo < tmp)) wlo = tmp, ilo\
    \ = i, jlo = jtmp;\n    }\n    ++V.at(ilo);\n    ++V.at(jlo);\n\n    W += wlo\
    \ - std::accumulate(pi.cbegin(), pi.cend(), T()) * 2;\n\n    return {W, V};\n\
    }\n"
  code: "#pragma once\n\n#include <numeric>\n#include <utility>\n#include <vector>\n\
    \ntemplate <class T, class DistanceMatrix>\nstd::pair<T, std::vector<int>>\nminimum_one_tree(const\
    \ DistanceMatrix &dist, const std::vector<T> &pi) {\n\n    assert(dist.n() > 2);\n\
    \    std::vector<T> dp(dist.n(), std::numeric_limits<T>::max());\n    std::vector<int>\
    \ prv(dist.n(), -1);\n    std::vector<int> used(dist.n());\n\n    auto fix_v =\
    \ [&](int x) -> void {\n        dp.at(x) = std::numeric_limits<T>::max();\n  \
    \      used.at(x) = 1;\n        for (auto [y, d] : dist.adjacents(x)) {\n    \
    \        if (used.at(y)) continue;\n            if (T len = pi.at(x) + pi.at(y)\
    \ + d; len < dp.at(y)) dp.at(y) = len, prv.at(y) = x;\n        }\n    };\n\n \
    \   T W = T();\n    std::vector<int> V(dist.n(), -2);\n\n    fix_v(0);\n    for\
    \ (int t = 0; t < dist.n() - 1; ++t) {\n        int i = std::min_element(dp.cbegin(),\
    \ dp.cend()) - dp.cbegin();\n        W += dp.at(i);\n        ++V.at(i);\n    \
    \    ++V.at(prv.at(i));\n        fix_v(i);\n    }\n\n    // p.26, http://webhotel4.ruc.dk/~keld/research/LKH/LKH-2.0/DOC/LKH_REPORT.pdf\n\
    \    T wlo = T();\n    int ilo = -1, jlo = -1;\n    for (int i = 0; i < dist.n();\
    \ ++i) {\n        if (V.at(i) != -1) continue;\n        T tmp = T();\n       \
    \ int jtmp = -1;\n        for (auto [j, d] : dist.adjacents(i)) {\n          \
    \  if (prv.at(i) == j or prv.at(j) == i or i == j) continue;\n            if (T\
    \ len = pi.at(i) + pi.at(j) + d; jtmp == -1 or tmp > len) tmp = len, jtmp = j;\n\
    \        }\n        if (jtmp != -1 and (ilo == -1 or wlo < tmp)) wlo = tmp, ilo\
    \ = i, jlo = jtmp;\n    }\n    ++V.at(ilo);\n    ++V.at(jlo);\n\n    W += wlo\
    \ - std::accumulate(pi.cbegin(), pi.cend(), T()) * 2;\n\n    return {W, V};\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: tsp/minimum_one_tree.hpp
  requiredBy: []
  timestamp: '2023-02-16 23:07:28+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: tsp/minimum_one_tree.hpp
layout: document
redirect_from:
- /library/tsp/minimum_one_tree.hpp
- /library/tsp/minimum_one_tree.hpp.html
title: tsp/minimum_one_tree.hpp
---
