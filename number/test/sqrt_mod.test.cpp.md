---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/sqrt_mod.hpp
    title: "Square root modulo prime \uFF08\u5E73\u65B9\u5270\u4F59\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/sqrt_mod
    links:
    - https://judge.yosupo.jp/problem/sqrt_mod
  bundledCode: "#line 1 \"number/test/sqrt_mod.test.cpp\"\n#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\
    \n#line 2 \"number/sqrt_mod.hpp\"\n#include <algorithm>\n#include <type_traits>\n\
    \n// Solve x^2 == a (MOD p) for prime p\n// If no solution exists, return -1\n\
    template <class Int> Int sqrt_mod(Int a, Int p) {\n    using Long =\n        std::conditional_t<std::is_same_v<Int,\
    \ int>, long long,\n                           std::conditional_t<std::is_same_v<Int,\
    \ long long>, __int128, void>>;\n\n    auto pow = [&](Int x, long long n) {\n\
    \        Int ans = 1, tmp = x;\n        while (n) {\n            if (n & 1) ans\
    \ = (Long)ans * tmp % p;\n            tmp = (Long)tmp * tmp % p, n /= 2;\n   \
    \     }\n        return ans;\n    };\n    if (a == 0) return 0;\n\n    a = (a\
    \ % p + p) % p;\n    if (p == 2) return a;\n    if (pow(a, (p - 1) / 2) != 1)\
    \ return -1;\n\n    int b = 1;\n    while (pow(b, (p - 1) / 2) == 1) ++b;\n\n\
    \    int e = 0;\n    Int m = p - 1;\n    while (m % 2 == 0) m /= 2, ++e;\n\n \
    \   Int x = pow(a, (m - 1) / 2), y = (Long)x * x % p * a % p;\n    x = (Long)x\
    \ * a % p;\n    Int z = pow(b, m);\n    while (y != 1) {\n        int j = 0;\n\
    \        Int t = y;\n        while (t != 1) t = (Long)t * t % p, ++j;\n      \
    \  z = pow(z, 1LL << (e - j - 1));\n        x = (Long)x * z % p;\n        z =\
    \ (Long)z * z % p;\n        y = (Long)y * z % p;\n        e = j;\n    }\n    return\
    \ std::min(x, p - x);\n}\n#line 3 \"number/test/sqrt_mod.test.cpp\"\n\n#include\
    \ <iostream>\nusing namespace std;\n\nint main() {\n    int T;\n    cin >> T;\n\
    \    while (T--) {\n        int Y, P;\n        cin >> Y >> P;\n        cout <<\
    \ sqrt_mod<int>(Y, P) << '\\n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/sqrt_mod\"\n#include \"\
    ../sqrt_mod.hpp\"\n\n#include <iostream>\nusing namespace std;\n\nint main() {\n\
    \    int T;\n    cin >> T;\n    while (T--) {\n        int Y, P;\n        cin\
    \ >> Y >> P;\n        cout << sqrt_mod<int>(Y, P) << '\\n';\n    }\n}\n"
  dependsOn:
  - number/sqrt_mod.hpp
  isVerificationFile: true
  path: number/test/sqrt_mod.test.cpp
  requiredBy: []
  timestamp: '2026-03-01 20:50:35+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/sqrt_mod.test.cpp
layout: document
redirect_from:
- /verify/number/test/sqrt_mod.test.cpp
- /verify/number/test/sqrt_mod.test.cpp.html
title: number/test/sqrt_mod.test.cpp
---
