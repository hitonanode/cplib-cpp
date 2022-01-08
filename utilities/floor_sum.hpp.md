---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':x:'
    path: utilities/test/floor_sum.test.cpp
    title: utilities/test/floor_sum.test.cpp
  _isVerificationFailed: true
  _pathExtension: hpp
  _verificationStatusIcon: ':x:'
  attributes:
    links: []
  bundledCode: "#line 2 \"utilities/floor_sum.hpp\"\n#include <utility>\n\n// CUT\
    \ begin\n// \\sum_{i=0}^{n-1} floor((ai + b) / m)\n// 0 <= n < 2e32\n// 1 <= m\
    \ < 2e32\n// 0 <= a, b < m\n// Complexity: O(lg(m))\nlong long floor_sum(long\
    \ long n, long long m, long long a, long long b) {\n    auto safe_mod = [](long\
    \ long x, long long m) -> long long {\n        x %= m;\n        if (x < 0) x +=\
    \ m;\n        return x;\n    };\n    auto floor_sum_unsigned = [](unsigned long\
    \ long n, unsigned long long m, unsigned long long a,\n                      \
    \           unsigned long long b) -> unsigned long long {\n        unsigned long\
    \ long ans = 0;\n        while (true) {\n            if (a >= m) {\n         \
    \       ans += n * (n - 1) / 2 * (a / m);\n                a %= m;\n         \
    \   }\n            if (b >= m) {\n                ans += n * (b / m);\n      \
    \          b %= m;\n            }\n\n            unsigned long long y_max = a\
    \ * n + b;\n            if (y_max < m) break;\n            // y_max < m * (n +\
    \ 1)\n            // floor(y_max / m) <= n\n            n = (unsigned long long)(y_max\
    \ / m);\n            b = (unsigned long long)(y_max % m);\n            std::swap(m,\
    \ a);\n        }\n        return ans;\n    };\n\n    unsigned long long ans =\
    \ 0;\n    if (a < 0) {\n        unsigned long long a2 = safe_mod(a, m);\n    \
    \    ans -= 1ULL * n * (n - 1) / 2 * ((a2 - a) / m);\n        a = a2;\n    }\n\
    \    if (b < 0) {\n        unsigned long long b2 = safe_mod(b, m);\n        ans\
    \ -= 1ULL * n * ((b2 - b) / m);\n        b = b2;\n    }\n    return ans + floor_sum_unsigned(n,\
    \ m, a, b);\n}\n"
  code: "#pragma once\n#include <utility>\n\n// CUT begin\n// \\sum_{i=0}^{n-1} floor((ai\
    \ + b) / m)\n// 0 <= n < 2e32\n// 1 <= m < 2e32\n// 0 <= a, b < m\n// Complexity:\
    \ O(lg(m))\nlong long floor_sum(long long n, long long m, long long a, long long\
    \ b) {\n    auto safe_mod = [](long long x, long long m) -> long long {\n    \
    \    x %= m;\n        if (x < 0) x += m;\n        return x;\n    };\n    auto\
    \ floor_sum_unsigned = [](unsigned long long n, unsigned long long m, unsigned\
    \ long long a,\n                                 unsigned long long b) -> unsigned\
    \ long long {\n        unsigned long long ans = 0;\n        while (true) {\n \
    \           if (a >= m) {\n                ans += n * (n - 1) / 2 * (a / m);\n\
    \                a %= m;\n            }\n            if (b >= m) {\n         \
    \       ans += n * (b / m);\n                b %= m;\n            }\n\n      \
    \      unsigned long long y_max = a * n + b;\n            if (y_max < m) break;\n\
    \            // y_max < m * (n + 1)\n            // floor(y_max / m) <= n\n  \
    \          n = (unsigned long long)(y_max / m);\n            b = (unsigned long\
    \ long)(y_max % m);\n            std::swap(m, a);\n        }\n        return ans;\n\
    \    };\n\n    unsigned long long ans = 0;\n    if (a < 0) {\n        unsigned\
    \ long long a2 = safe_mod(a, m);\n        ans -= 1ULL * n * (n - 1) / 2 * ((a2\
    \ - a) / m);\n        a = a2;\n    }\n    if (b < 0) {\n        unsigned long\
    \ long b2 = safe_mod(b, m);\n        ans -= 1ULL * n * ((b2 - b) / m);\n     \
    \   b = b2;\n    }\n    return ans + floor_sum_unsigned(n, m, a, b);\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: utilities/floor_sum.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_WA
  verifiedWith:
  - utilities/test/floor_sum.test.cpp
documentation_of: utilities/floor_sum.hpp
layout: document
title: floor sum
---

AtCoder Library のコピー．

## リンク

- [https://atcoder.github.io/ac-library/production/document_ja/math.html](https://atcoder.github.io/ac-library/production/document_ja/math.html)
