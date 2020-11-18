---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: utilities/test/floor_sum.test.cpp
    title: utilities/test/floor_sum.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/floor_sum.hpp\"\n\n// CUT begin\n// \\sum_{i=0}^{n-1}\
    \ floor((ai + b) / m)\n// 0 <= n <= 1e9\n// 1 <= m <= 1e9\n// 0 <= a, b < m\n\
    // Complexity: O(lg(n + m + a + b))\nlong long floor_sum(long long n, long long\
    \ m, long long a, long long b) {\n    long long ans = 0;\n    if (a >= m) {\n\
    \        ans += (n - 1) * n * (a / m) / 2;\n        a %= m;\n    }\n    if (b\
    \ >= m) {\n        ans += n * (b / m);\n        b %= m;\n    }\n\n    long long\
    \ y_max = (a * n + b) / m, x_max = (y_max * m - b);\n    if (y_max == 0) return\
    \ ans;\n    ans += (n - (x_max + a - 1) / a) * y_max;\n    ans += floor_sum(y_max,\
    \ a, m, (a - x_max % a) % a);\n    return ans;\n}\n"
  code: "#pragma once\n\n// CUT begin\n// \\sum_{i=0}^{n-1} floor((ai + b) / m)\n\
    // 0 <= n <= 1e9\n// 1 <= m <= 1e9\n// 0 <= a, b < m\n// Complexity: O(lg(n +\
    \ m + a + b))\nlong long floor_sum(long long n, long long m, long long a, long\
    \ long b) {\n    long long ans = 0;\n    if (a >= m) {\n        ans += (n - 1)\
    \ * n * (a / m) / 2;\n        a %= m;\n    }\n    if (b >= m) {\n        ans +=\
    \ n * (b / m);\n        b %= m;\n    }\n\n    long long y_max = (a * n + b) /\
    \ m, x_max = (y_max * m - b);\n    if (y_max == 0) return ans;\n    ans += (n\
    \ - (x_max + a - 1) / a) * y_max;\n    ans += floor_sum(y_max, a, m, (a - x_max\
    \ % a) % a);\n    return ans;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/floor_sum.hpp
  requiredBy: []
  timestamp: '2020-09-29 00:37:21+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - utilities/test/floor_sum.test.cpp
documentation_of: utilities/floor_sum.hpp
layout: document
redirect_from:
- /library/utilities/floor_sum.hpp
- /library/utilities/floor_sum.hpp.html
title: utilities/floor_sum.hpp
---
