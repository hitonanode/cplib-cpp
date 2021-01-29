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
  bundledCode: "#line 2 \"number/big_combination_logarithm.hpp\"\n#include <cmath>\n\
    #include <vector>\n\nconstexpr double minusloginf = -300;\nstd::vector<double>\
    \ logfac;\nvoid facInit(int nmax) {\n    logfac.assign(nmax + 1, 0);\n    for\
    \ (int i = 2; i <= nmax; i++) { logfac[i] = logfac[i - 1] + log(i); }\n}\ndouble\
    \ lognCr(int n, int r) {\n    if (n < r or r < 0) return minusloginf;\n    return\
    \ logfac[n] - logfac[r] - logfac[n - r];\n}\n"
  code: "#pragma once\n#include <cmath>\n#include <vector>\n\nconstexpr double minusloginf\
    \ = -300;\nstd::vector<double> logfac;\nvoid facInit(int nmax) {\n    logfac.assign(nmax\
    \ + 1, 0);\n    for (int i = 2; i <= nmax; i++) { logfac[i] = logfac[i - 1] +\
    \ log(i); }\n}\ndouble lognCr(int n, int r) {\n    if (n < r or r < 0) return\
    \ minusloginf;\n    return logfac[n] - logfac[r] - logfac[n - r];\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/big_combination_logarithm.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/big_combination_logarithm.hpp
layout: document
redirect_from:
- /library/number/big_combination_logarithm.hpp
- /library/number/big_combination_logarithm.hpp.html
title: number/big_combination_logarithm.hpp
---
