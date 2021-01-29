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
  bundledCode: "#line 2 \"utilities/next_combination.hpp\"\n\n// CUT begin\n// Example:\
    \ 1 -> 2, 4 -> 8, 12(1100) -> 17(10001)\ntemplate <typename Int> Int next_combination(Int\
    \ comb) {\n    Int x = comb & -comb, y = comb + x;\n    return ((comb & ~y) /\
    \ x >> 1) | y;\n}\n"
  code: "#pragma once\n\n// CUT begin\n// Example: 1 -> 2, 4 -> 8, 12(1100) -> 17(10001)\n\
    template <typename Int> Int next_combination(Int comb) {\n    Int x = comb & -comb,\
    \ y = comb + x;\n    return ((comb & ~y) / x >> 1) | y;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/next_combination.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: utilities/next_combination.hpp
layout: document
redirect_from:
- /library/utilities/next_combination.hpp
- /library/utilities/next_combination.hpp.html
title: utilities/next_combination.hpp
---
