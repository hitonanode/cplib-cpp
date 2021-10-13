---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/linalg_longlong.hpp
    title: linear_algebra_matrix/linalg_longlong.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_ll_det.test.cpp
    title: linear_algebra_matrix/test/linalg_ll_det.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_longlong.test.cpp
    title: linear_algebra_matrix/test/linalg_longlong.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_longlong_matmul.test.cpp
    title: linear_algebra_matrix/test/linalg_longlong_matmul.test.cpp
  - icon: ':heavy_check_mark:'
    path: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
    title: linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  - icon: ':heavy_check_mark:'
    path: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
    title: tree/test/frequency_table_of_tree_distance_ntt.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
    - https://yukicoder.me/submissions/405938>
  bundledCode: "#line 2 \"number/bare_mod_algebra.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <tuple>\n#include <utility>\n#include <vector>\n\n// CUT\
    \ begin\n// Solve ax+by=gcd(a, b)\ntemplate <typename Int> Int extgcd(Int a, Int\
    \ b, Int &x, Int &y) {\n    Int d = a;\n    if (b != 0) {\n        d = extgcd(b,\
    \ a % b, y, x), y -= (a / b) * x;\n    } else {\n        x = 1, y = 0;\n    }\n\
    \    return d;\n}\n// Calculate a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate\
    \ x s.t. ax == gcd(a, m) MOD m\ntemplate <typename Int> Int mod_inverse(Int a,\
    \ Int m) {\n    Int x, y;\n    extgcd<Int>(a, m, x, y);\n    x %= m;\n    return\
    \ x + (x < 0) * m;\n}\n\n// Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a,\
    \ b), xa = g MOD b, 0 <= x < b/g\ntemplate <typename Int> /* constexpr */ std::pair<Int,\
    \ Int> inv_gcd(Int a, Int b) {\n    a %= b;\n    if (a < 0) a += b;\n    if (a\
    \ == 0) return {b, 0};\n    Int s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n\
    \        Int u = s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp =\
    \ s;\n        s = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0\
    \ < 0) m0 += b / s;\n    return {s, m0};\n}\n\ntemplate <typename Int>\n/* constexpr\
    \ */ std::pair<Int, Int> crt(const std::vector<Int> &r, const std::vector<Int>\
    \ &m) {\n    assert(r.size() == m.size());\n    int n = int(r.size());\n    //\
    \ Contracts: 0 <= r0 < m0\n    Int r0 = 0, m0 = 1;\n    for (int i = 0; i < n;\
    \ i++) {\n        assert(1 <= m[i]);\n        Int r1 = r[i] % m[i], m1 = m[i];\n\
    \        if (r1 < 0) r1 += m1;\n        if (m0 < m1) {\n            std::swap(r0,\
    \ r1);\n            std::swap(m0, m1);\n        }\n        if (m0 % m1 == 0) {\n\
    \            if (r0 % m1 != r1) return {0, 0};\n            continue;\n      \
    \  }\n        Int g, im;\n        std::tie(g, im) = inv_gcd<Int>(m0, m1);\n\n\
    \        Int u1 = m1 / g;\n        if ((r1 - r0) % g) return {0, 0};\n\n     \
    \   Int x = (r1 - r0) / g % u1 * im % u1;\n        r0 += x * m0;\n        m0 *=\
    \ u1;\n        if (r0 < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\n// \u87FB\
    \u672C P.262\n// \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\
    \uFF0C\u8272\u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\
    \u3089\u5143\u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\
    \u5F0F A * x = B mod M \u306E\u89E3\n// Requirement: M[i] > 0\n// Output: x =\
    \ first MOD second (if solution exists), (0, 0) (otherwise)\ntemplate <typename\
    \ Int>\nstd::pair<Int, Int> linear_congruence(const std::vector<Int> &A, const\
    \ std::vector<Int> &B, const std::vector<Int> &M) {\n    Int r = 0, m = 1;\n \
    \   assert(A.size() == M.size());\n    assert(B.size() == M.size());\n    for\
    \ (int i = 0; i < (int)A.size(); i++) {\n        assert(M[i] > 0);\n        const\
    \ Int ai = A[i] % M[i];\n        Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i],\
    \ a);\n        if (b % d != 0) {\n            return std::make_pair(0, 0); //\
    \ \u89E3\u306A\u3057\n        }\n        Int t = b / d * mod_inverse<Int>(a /\
    \ d, M[i] / d) % (M[i] / d);\n        r += m * t;\n        m *= M[i] / d;\n  \
    \  }\n    return std::make_pair((r < 0 ? r + m : r), m);\n}\n\ntemplate <typename\
    \ Int> Int power(Int x, Int n, Int MOD) {\n    Int ans = 1;\n    while (n > 0)\
    \ {\n        if (n & 1) (ans *= x) %= MOD;\n        (x *= x) %= MOD;\n       \
    \ n >>= 1;\n    }\n    return ans;\n}\n\n// Find smallest primitive root for given\
    \ prime P \uFF08\u6700\u5C0F\u306E\u539F\u59CB\u6839\u63A2\u7D22\uFF09\n// Complexity:\
    \ maybe O(sqrt(p))\n// Algorithm: <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n\
    // Verified: <https://yukicoder.me/submissions/405938>\n// Sample:\n//  - 998244353\
    \ ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39 << 22) + 1 ) -> 23\n// \
    \ - 2 -> 1\n//  - 1 -> -1\ntemplate <typename Int = long long> Int find_smallest_primitive_root(Int\
    \ p) {\n    std::vector<Int> fac;\n    Int v = p - 1;\n    for (Int pp = 2; pp\
    \ * pp <= v; pp++) { // prime factorization of (p - 1)\n        int e = 0;\n \
    \       while (v % pp == 0) e++, v /= pp;\n        if (e) fac.push_back(pp);\n\
    \    }\n    if (v > 1) fac.push_back(v);\n\n    for (Int g = 1; g < p; g++) {\n\
    \        if (power<Int>(g, p - 1, p) != 1) return -1;\n        bool ok = true;\n\
    \        for (auto pp : fac) {\n            if (power<Int>(g, (p - 1) / pp, p)\
    \ == 1) {\n                ok = false;\n                break;\n            }\n\
    \        }\n        if (ok) return g;\n    }\n    return -1;\n}\n"
  code: "#pragma once\n#include <algorithm>\n#include <cassert>\n#include <tuple>\n\
    #include <utility>\n#include <vector>\n\n// CUT begin\n// Solve ax+by=gcd(a, b)\n\
    template <typename Int> Int extgcd(Int a, Int b, Int &x, Int &y) {\n    Int d\
    \ = a;\n    if (b != 0) {\n        d = extgcd(b, a % b, y, x), y -= (a / b) *\
    \ x;\n    } else {\n        x = 1, y = 0;\n    }\n    return d;\n}\n// Calculate\
    \ a^(-1) (MOD m) s if gcd(a, m) == 1\n// Calculate x s.t. ax == gcd(a, m) MOD\
    \ m\ntemplate <typename Int> Int mod_inverse(Int a, Int m) {\n    Int x, y;\n\
    \    extgcd<Int>(a, m, x, y);\n    x %= m;\n    return x + (x < 0) * m;\n}\n\n\
    // Require: 1 <= b\n// return: (g, x) s.t. g = gcd(a, b), xa = g MOD b, 0 <= x\
    \ < b/g\ntemplate <typename Int> /* constexpr */ std::pair<Int, Int> inv_gcd(Int\
    \ a, Int b) {\n    a %= b;\n    if (a < 0) a += b;\n    if (a == 0) return {b,\
    \ 0};\n    Int s = b, t = a, m0 = 0, m1 = 1;\n    while (t) {\n        Int u =\
    \ s / t;\n        s -= t * u, m0 -= m1 * u;\n        auto tmp = s;\n        s\
    \ = t, t = tmp, tmp = m0, m0 = m1, m1 = tmp;\n    }\n    if (m0 < 0) m0 += b /\
    \ s;\n    return {s, m0};\n}\n\ntemplate <typename Int>\n/* constexpr */ std::pair<Int,\
    \ Int> crt(const std::vector<Int> &r, const std::vector<Int> &m) {\n    assert(r.size()\
    \ == m.size());\n    int n = int(r.size());\n    // Contracts: 0 <= r0 < m0\n\
    \    Int r0 = 0, m0 = 1;\n    for (int i = 0; i < n; i++) {\n        assert(1\
    \ <= m[i]);\n        Int r1 = r[i] % m[i], m1 = m[i];\n        if (r1 < 0) r1\
    \ += m1;\n        if (m0 < m1) {\n            std::swap(r0, r1);\n           \
    \ std::swap(m0, m1);\n        }\n        if (m0 % m1 == 0) {\n            if (r0\
    \ % m1 != r1) return {0, 0};\n            continue;\n        }\n        Int g,\
    \ im;\n        std::tie(g, im) = inv_gcd<Int>(m0, m1);\n\n        Int u1 = m1\
    \ / g;\n        if ((r1 - r0) % g) return {0, 0};\n\n        Int x = (r1 - r0)\
    \ / g % u1 * im % u1;\n        r0 += x * m0;\n        m0 *= u1;\n        if (r0\
    \ < 0) r0 += m0;\n    }\n    return {r0, m0};\n}\n\n// \u87FB\u672C P.262\n//\
    \ \u4E2D\u56FD\u5270\u4F59\u5B9A\u7406\u3092\u5229\u7528\u3057\u3066\uFF0C\u8272\
    \u3005\u306A\u7D20\u6570\u3067\u5272\u3063\u305F\u4F59\u308A\u304B\u3089\u5143\
    \u306E\u5024\u3092\u5FA9\u5143\n// \u9023\u7ACB\u7DDA\u5F62\u5408\u540C\u5F0F\
    \ A * x = B mod M \u306E\u89E3\n// Requirement: M[i] > 0\n// Output: x = first\
    \ MOD second (if solution exists), (0, 0) (otherwise)\ntemplate <typename Int>\n\
    std::pair<Int, Int> linear_congruence(const std::vector<Int> &A, const std::vector<Int>\
    \ &B, const std::vector<Int> &M) {\n    Int r = 0, m = 1;\n    assert(A.size()\
    \ == M.size());\n    assert(B.size() == M.size());\n    for (int i = 0; i < (int)A.size();\
    \ i++) {\n        assert(M[i] > 0);\n        const Int ai = A[i] % M[i];\n   \
    \     Int a = ai * m, b = B[i] - ai * r, d = std::__gcd(M[i], a);\n        if\
    \ (b % d != 0) {\n            return std::make_pair(0, 0); // \u89E3\u306A\u3057\
    \n        }\n        Int t = b / d * mod_inverse<Int>(a / d, M[i] / d) % (M[i]\
    \ / d);\n        r += m * t;\n        m *= M[i] / d;\n    }\n    return std::make_pair((r\
    \ < 0 ? r + m : r), m);\n}\n\ntemplate <typename Int> Int power(Int x, Int n,\
    \ Int MOD) {\n    Int ans = 1;\n    while (n > 0) {\n        if (n & 1) (ans *=\
    \ x) %= MOD;\n        (x *= x) %= MOD;\n        n >>= 1;\n    }\n    return ans;\n\
    }\n\n// Find smallest primitive root for given prime P \uFF08\u6700\u5C0F\u306E\
    \u539F\u59CB\u6839\u63A2\u7D22\uFF09\n// Complexity: maybe O(sqrt(p))\n// Algorithm:\
    \ <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n// Verified: <https://yukicoder.me/submissions/405938>\n\
    // Sample:\n//  - 998244353 ( = (119 << 23) + 1 ) -> 3\n//  - 163577857 ( = (39\
    \ << 22) + 1 ) -> 23\n//  - 2 -> 1\n//  - 1 -> -1\ntemplate <typename Int = long\
    \ long> Int find_smallest_primitive_root(Int p) {\n    std::vector<Int> fac;\n\
    \    Int v = p - 1;\n    for (Int pp = 2; pp * pp <= v; pp++) { // prime factorization\
    \ of (p - 1)\n        int e = 0;\n        while (v % pp == 0) e++, v /= pp;\n\
    \        if (e) fac.push_back(pp);\n    }\n    if (v > 1) fac.push_back(v);\n\n\
    \    for (Int g = 1; g < p; g++) {\n        if (power<Int>(g, p - 1, p) != 1)\
    \ return -1;\n        bool ok = true;\n        for (auto pp : fac) {\n       \
    \     if (power<Int>(g, (p - 1) / pp, p) == 1) {\n                ok = false;\n\
    \                break;\n            }\n        }\n        if (ok) return g;\n\
    \    }\n    return -1;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: number/bare_mod_algebra.hpp
  requiredBy:
  - linear_algebra_matrix/linalg_longlong.hpp
  timestamp: '2021-09-05 19:07:53+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - tree/test/frequency_table_of_tree_distance_ntt.test.cpp
  - linear_algebra_matrix/test/linalg_ll_det.test.cpp
  - linear_algebra_matrix/test/linalg_longlong_matmul.test.cpp
  - linear_algebra_matrix/test/linalg_modint_multiplication.test.cpp
  - linear_algebra_matrix/test/linalg_longlong.test.cpp
documentation_of: number/bare_mod_algebra.hpp
layout: document
redirect_from:
- /library/number/bare_mod_algebra.hpp
- /library/number/bare_mod_algebra.hpp.html
title: number/bare_mod_algebra.hpp
---
