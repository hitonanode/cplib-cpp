---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
    title: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
    - https://yukicoder.me/submissions/405938>
  bundledCode: "#line 2 \"modulus/bare_mod_algebra.hpp\"\n#include <algorithm>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\nusing lint = long long;\n// Solve\
    \ ax+by=gcd(a, b)\nlint extgcd(lint a, lint b, lint &x, lint &y)\n{\n    lint\
    \ d = a;\n    if (b != 0) d = extgcd(b, a % b, y, x), y -= (a / b) * x;\n    else\
    \ x = 1, y = 0;\n    return d;\n}\n// Calc a^(-1) (MOD m)\nlint mod_inverse(lint\
    \ a, lint m)\n{\n    lint x, y;\n    extgcd(a, m, x, y);\n    return (m + x %\
    \ m) % m;\n}\n\n// \u87FB\u672C P.262\n// \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\
    \u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\u3005\u306A\u7D20\u6570\u3067\u5272\
    \u3063\u305F\u4F59\u308A\u304B\u3089\u5143\u306E\u5024\u3092\u5FA9\u5143\n// \u9023\
    \u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F A * x = B mod M \u306E\u89E3\n// Output:\
    \ x = first MOD second\nstd::pair<lint, lint> linear_congruence(const std::vector<lint>\
    \ &A, const std::vector<lint> &B, const std::vector<lint> &M)\n{\n    lint x =\
    \ 0, m = 1;\n    for (int i = 0; i < (int)A.size(); i++) {\n        lint a = A[i]\
    \ * m, b = B[i] - A[i] * x, d = std::__gcd(M[i], a);\n        if (b % d != 0)\
    \ {\n            return std::make_pair(0, -1); // \u89E3\u306A\u3057\n       \
    \ }\n        lint t = b / d * mod_inverse(a / d, M[i] / d) % (M[i] / d);\n   \
    \     x += m * t;\n        m *= M[i] / d;\n    }\n    return std::make_pair((x\
    \ < 0 ? x + m : x), m);\n}\n\nlint power(lint x, lint n, lint MOD)\n{\n    lint\
    \ ans = 1;\n    while (n > 0) {\n        if (n & 1) (ans *= x) %= MOD;\n     \
    \   (x *= x) %= MOD;\n       n >>= 1;\n    }\n   return ans;\n}\n\n// Find smallest\
    \ primitive root for given prime P \uFF08\u6700\u5C0F\u306E\u539F\u59CB\u6839\u63A2\
    \u7D22\uFF09\n// Complexity: maybe O(sqrt(p))\n// Algorithm: <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n\
    // Verified: <https://yukicoder.me/submissions/405938>\n// Sample:\n//  - 998244353\
    \ ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39 << 22) + 1 ) -> 23\n// \
    \ - 2 -> 1\n//  - 1 -> -1\n\nlint find_smallest_primitive_root(lint p)\n{\n  \
    \  std::vector<lint> fac;\n    lint v = p - 1;\n    for (lint pp = 2; pp * pp\
    \ <= v; pp++) // prime factorization of (p - 1)\n    {\n        int e = 0;\n \
    \       while (v % pp == 0) e++, v /= pp;\n        if (e) fac.push_back(pp);\n\
    \    }\n    if (v > 1) fac.push_back(v);\n\n    for (lint g = 1; g < p; g++)\n\
    \    {\n        if (power(g, p - 1, p) != 1) return -1;\n        bool ok = true;\n\
    \        for (auto pp : fac)\n        {\n            if (power(g, (p - 1) / pp,\
    \ p) == 1)\n            {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n    return -1;\n\
    }\n"
  code: "#pragma once\n#include <algorithm>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\nusing lint = long long;\n// Solve ax+by=gcd(a, b)\nlint extgcd(lint\
    \ a, lint b, lint &x, lint &y)\n{\n    lint d = a;\n    if (b != 0) d = extgcd(b,\
    \ a % b, y, x), y -= (a / b) * x;\n    else x = 1, y = 0;\n    return d;\n}\n\
    // Calc a^(-1) (MOD m)\nlint mod_inverse(lint a, lint m)\n{\n    lint x, y;\n\
    \    extgcd(a, m, x, y);\n    return (m + x % m) % m;\n}\n\n// \u87FB\u672C P.262\n\
    // \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\
    \u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\u3089\u5143\
    \u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F\
    \ A * x = B mod M \u306E\u89E3\n// Output: x = first MOD second\nstd::pair<lint,\
    \ lint> linear_congruence(const std::vector<lint> &A, const std::vector<lint>\
    \ &B, const std::vector<lint> &M)\n{\n    lint x = 0, m = 1;\n    for (int i =\
    \ 0; i < (int)A.size(); i++) {\n        lint a = A[i] * m, b = B[i] - A[i] * x,\
    \ d = std::__gcd(M[i], a);\n        if (b % d != 0) {\n            return std::make_pair(0,\
    \ -1); // \u89E3\u306A\u3057\n        }\n        lint t = b / d * mod_inverse(a\
    \ / d, M[i] / d) % (M[i] / d);\n        x += m * t;\n        m *= M[i] / d;\n\
    \    }\n    return std::make_pair((x < 0 ? x + m : x), m);\n}\n\nlint power(lint\
    \ x, lint n, lint MOD)\n{\n    lint ans = 1;\n    while (n > 0) {\n        if\
    \ (n & 1) (ans *= x) %= MOD;\n        (x *= x) %= MOD;\n       n >>= 1;\n    }\n\
    \   return ans;\n}\n\n// Find smallest primitive root for given prime P \uFF08\
    \u6700\u5C0F\u306E\u539F\u59CB\u6839\u63A2\u7D22\uFF09\n// Complexity: maybe O(sqrt(p))\n\
    // Algorithm: <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n//\
    \ Verified: <https://yukicoder.me/submissions/405938>\n// Sample:\n//  - 998244353\
    \ ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39 << 22) + 1 ) -> 23\n// \
    \ - 2 -> 1\n//  - 1 -> -1\n\nlint find_smallest_primitive_root(lint p)\n{\n  \
    \  std::vector<lint> fac;\n    lint v = p - 1;\n    for (lint pp = 2; pp * pp\
    \ <= v; pp++) // prime factorization of (p - 1)\n    {\n        int e = 0;\n \
    \       while (v % pp == 0) e++, v /= pp;\n        if (e) fac.push_back(pp);\n\
    \    }\n    if (v > 1) fac.push_back(v);\n\n    for (lint g = 1; g < p; g++)\n\
    \    {\n        if (power(g, p - 1, p) != 1) return -1;\n        bool ok = true;\n\
    \        for (auto pp : fac)\n        {\n            if (power(g, (p - 1) / pp,\
    \ p) == 1)\n            {\n                ok = false;\n                break;\n\
    \            }\n        }\n        if (ok) return g;\n    }\n    return -1;\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: modulus/bare_mod_algebra.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:54:47+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
documentation_of: modulus/bare_mod_algebra.hpp
layout: document
redirect_from:
- /library/modulus/bare_mod_algebra.hpp
- /library/modulus/bare_mod_algebra.hpp.html
title: modulus/bare_mod_algebra.hpp
---
