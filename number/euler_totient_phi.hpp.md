---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"number/euler_totient_phi.hpp\"\n#include <numeric>\n#include\
    \ <vector>\n\n// CUT begin\n// Euler's totient function\n// Complexity: O(NlgN)\n\
    std::vector<int> euler_phi(int N) {\n    std::vector<int> ret(N + 1);\n    std::iota(ret.begin(),\
    \ ret.end(), 0);\n    for (int p = 2; p <= N; p++) {\n        if (ret[p] == p)\
    \ {\n            ret[p] = p - 1;\n            for (int i = p * 2; i <= N; i +=\
    \ p) { ret[i] = ret[i] / p * (p - 1); }\n        }\n    }\n    return ret;\n}\n"
  code: "#pragma once\n#include <numeric>\n#include <vector>\n\n// CUT begin\n// Euler's\
    \ totient function\n// Complexity: O(NlgN)\nstd::vector<int> euler_phi(int N)\
    \ {\n    std::vector<int> ret(N + 1);\n    std::iota(ret.begin(), ret.end(), 0);\n\
    \    for (int p = 2; p <= N; p++) {\n        if (ret[p] == p) {\n            ret[p]\
    \ = p - 1;\n            for (int i = p * 2; i <= N; i += p) { ret[i] = ret[i]\
    \ / p * (p - 1); }\n        }\n    }\n    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/euler_totient_phi.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/euler_totient_phi.hpp
layout: document
redirect_from:
- /library/number/euler_totient_phi.hpp
- /library/number/euler_totient_phi.hpp.html
title: number/euler_totient_phi.hpp
---
