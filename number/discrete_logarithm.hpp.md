---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/discrete_logarithm.test.cpp
    title: number/test/discrete_logarithm.test.cpp
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://judge.yosupo.jp/problem/discrete_logarithm_mod>
  bundledCode: "#line 2 \"number/discrete_logarithm.hpp\"\n#include <algorithm>\n\
    #include <unordered_map>\n#include <utility>\n\n// CUT begin\n// Calculate log_A\
    \ B (MOD M) (baby-step gian-step)\n// DiscreteLogarithm dl(M, A);\n// lint ans\
    \ = dl.log(B);\n// Complexity: O(M^(1/2)) for each query\n// Verified: <https://judge.yosupo.jp/problem/discrete_logarithm_mod>\n\
    // Constraints: 0 <= A < M, B < M, 1 <= M <= 1e9  (M is not limited to prime)\n\
    struct DiscreteLogarithm {\n    using lint = long long int;\n    int M, stepsize;\n\
    \    lint baby_a, giant_a, g;\n    std::unordered_map<lint, int> baby_log_dict;\n\
    \n    lint inverse(lint a) {\n        lint b = M / g, u = 1, v = 0;\n        while\
    \ (b) {\n            lint t = a / b;\n            a -= t * b;\n            std::swap(a,\
    \ b);\n            u -= t * v;\n            std::swap(u, v);\n        }\n    \
    \    u %= M / g;\n        return u >= 0 ? u : u + M / g;\n    }\n\n    DiscreteLogarithm(int\
    \ mod, int a_new) : M(mod), baby_a(a_new % mod), giant_a(1) {\n        g = 1;\n\
    \        while (std::__gcd(baby_a, M / g) > 1) g *= std::__gcd(baby_a, M / g);\n\
    \        stepsize = 32; // lg(MAX_M)\n        while (stepsize * stepsize < M /\
    \ g) stepsize++;\n\n        lint now = 1 % (M / g), inv_g = inverse(baby_a);\n\
    \        for (int n = 0; n < stepsize; n++) {\n            if (!baby_log_dict.count(now))\
    \ baby_log_dict[now] = n;\n            (now *= baby_a) %= M / g;\n           \
    \ (giant_a *= inv_g) %= M / g;\n        }\n    }\n\n    // log(): returns the\
    \ smallest nonnegative x that satisfies a^x = b mod M, or -1 if there's no solution\n\
    \    lint log(lint b) {\n        b %= M;\n        lint acc = 1 % M;\n        for\
    \ (int i = 0; i < stepsize; i++) {\n            if (acc == b) return i;\n    \
    \        (acc *= baby_a) %= M;\n        }\n        if (b % g) return -1; // No\
    \ solution\n        lint now = b * giant_a % (M / g);\n        for (lint q = 1;\
    \ q <= M / stepsize + 1; q++) {\n            if (baby_log_dict.count(now)) return\
    \ q * stepsize + baby_log_dict[now];\n            (now *= giant_a) %= M / g;\n\
    \        }\n        return -1;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <unordered_map>\n#include <utility>\n\
    \n// CUT begin\n// Calculate log_A B (MOD M) (baby-step gian-step)\n// DiscreteLogarithm\
    \ dl(M, A);\n// lint ans = dl.log(B);\n// Complexity: O(M^(1/2)) for each query\n\
    // Verified: <https://judge.yosupo.jp/problem/discrete_logarithm_mod>\n// Constraints:\
    \ 0 <= A < M, B < M, 1 <= M <= 1e9  (M is not limited to prime)\nstruct DiscreteLogarithm\
    \ {\n    using lint = long long int;\n    int M, stepsize;\n    lint baby_a, giant_a,\
    \ g;\n    std::unordered_map<lint, int> baby_log_dict;\n\n    lint inverse(lint\
    \ a) {\n        lint b = M / g, u = 1, v = 0;\n        while (b) {\n         \
    \   lint t = a / b;\n            a -= t * b;\n            std::swap(a, b);\n \
    \           u -= t * v;\n            std::swap(u, v);\n        }\n        u %=\
    \ M / g;\n        return u >= 0 ? u : u + M / g;\n    }\n\n    DiscreteLogarithm(int\
    \ mod, int a_new) : M(mod), baby_a(a_new % mod), giant_a(1) {\n        g = 1;\n\
    \        while (std::__gcd(baby_a, M / g) > 1) g *= std::__gcd(baby_a, M / g);\n\
    \        stepsize = 32; // lg(MAX_M)\n        while (stepsize * stepsize < M /\
    \ g) stepsize++;\n\n        lint now = 1 % (M / g), inv_g = inverse(baby_a);\n\
    \        for (int n = 0; n < stepsize; n++) {\n            if (!baby_log_dict.count(now))\
    \ baby_log_dict[now] = n;\n            (now *= baby_a) %= M / g;\n           \
    \ (giant_a *= inv_g) %= M / g;\n        }\n    }\n\n    // log(): returns the\
    \ smallest nonnegative x that satisfies a^x = b mod M, or -1 if there's no solution\n\
    \    lint log(lint b) {\n        b %= M;\n        lint acc = 1 % M;\n        for\
    \ (int i = 0; i < stepsize; i++) {\n            if (acc == b) return i;\n    \
    \        (acc *= baby_a) %= M;\n        }\n        if (b % g) return -1; // No\
    \ solution\n        lint now = b * giant_a % (M / g);\n        for (lint q = 1;\
    \ q <= M / stepsize + 1; q++) {\n            if (baby_log_dict.count(now)) return\
    \ q * stepsize + baby_log_dict[now];\n            (now *= giant_a) %= M / g;\n\
    \        }\n        return -1;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: number/discrete_logarithm.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - number/test/discrete_logarithm.test.cpp
documentation_of: number/discrete_logarithm.hpp
layout: document
redirect_from:
- /library/number/discrete_logarithm.hpp
- /library/number/discrete_logarithm.hpp.html
title: number/discrete_logarithm.hpp
---