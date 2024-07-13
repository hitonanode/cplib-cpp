---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/rational_approximation.hpp
    title: "Rational approximation \uFF08\u6709\u7406\u6570\u8FD1\u4F3C\uFF09"
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.yosupo.jp/problem/rational_approximation
    links:
    - https://judge.yosupo.jp/problem/rational_approximation
  bundledCode: "#line 1 \"number/test/rational_approximation.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.yosupo.jp/problem/rational_approximation\"\n#line 2 \"number/rational_approximation.hpp\"\
    \n\n#include <cassert>\n#include <utility>\n#include <vector>\n\n// Rational approximation\
    \ based on Stern\u2013Brocot tree\n// Input: N > 0, num >= 0, den >= 0 (num >\
    \ 0 or den > 0)\n// return {{p, q}, {r, s}} where p/q <= num/den <= r/s. Strictly,\n\
    // - p/q = max(n / d | n / d <= num / den, 0 <= n <= N, 1 <= d <= N)\n// - r/s\
    \ = min(n / d | num / den <= n / d, 0 <= n <= N, 1 <= d <= N)\ntemplate <class\
    \ Int>\nstd::pair<std::pair<Int, Int>, std::pair<Int, Int>> rational_approximation(Int\
    \ N, Int num, Int den) {\n    assert(N >= 1);\n    assert(num >= 0);\n    assert(den\
    \ >= 0);\n    assert(num > 0 or den > 0);\n\n    if (num == Int(0)) return {{Int(0),\
    \ Int(1)}, {Int(0), Int(1)}}; // 0\n    if (den == Int(0)) return {{Int(1), Int(0)},\
    \ {Int(1), Int(0)}}; // inf\n\n    // p/q <= num/den <= r/s\n    Int p = 0, q\
    \ = 1, r = 1, s = 0;\n\n    bool is_left = false;\n    while (true) {\n      \
    \  Int max_steps = num / den;\n\n        if (is_left) {\n            // r + steps\
    \ * p <= N\n            // s + steps * q <= N\n\n            if (p > Int(0)) max_steps\
    \ = std::min(max_steps, (N - r) / p);\n            max_steps = std::min(max_steps,\
    \ (N - s) / q);\n\n            r += max_steps * p;\n            s += max_steps\
    \ * q;\n        } else {\n            // p + steps * r <= N\n            // q\
    \ + steps * s <= N\n\n            max_steps = std::min(max_steps, (N - p) / r);\n\
    \            if (s > Int(0)) max_steps = std::min(max_steps, (N - q) / s);\n\n\
    \            p += max_steps * r;\n            q += max_steps * s;\n        }\n\
    \n        if (is_left and !max_steps) break;\n\n        num -= max_steps * den;\n\
    \n        if (num == Int(0)) {\n            if (is_left) {\n                return\
    \ {{r, s}, {r, s}};\n            } else {\n                return {{p, q}, {p,\
    \ q}};\n            }\n        }\n\n        std::swap(num, den);\n        is_left\
    \ = !is_left;\n    }\n\n    return {{p, q}, {r, s}};\n}\n#line 3 \"number/test/rational_approximation.test.cpp\"\
    \n\n#line 5 \"number/test/rational_approximation.test.cpp\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int T;\n    cin >> T;\n    while (T--) {\n        int N, x, y;\n       \
    \ cin >> N >> x >> y;\n        const auto [l, r] = rational_approximation<int>(N,\
    \ x, y);\n        const auto [lnum, lden] = l;\n        const auto [rnum, rden]\
    \ = r;\n        cout << lnum << ' ' << lden << ' ' << rnum << ' ' << rden << '\\\
    n';\n    }\n}\n"
  code: "#define PROBLEM \"https://judge.yosupo.jp/problem/rational_approximation\"\
    \n#include \"../rational_approximation.hpp\"\n\n#include <cassert>\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int T;\n    cin >> T;\n    while (T--) {\n        int N, x, y;\n       \
    \ cin >> N >> x >> y;\n        const auto [l, r] = rational_approximation<int>(N,\
    \ x, y);\n        const auto [lnum, lden] = l;\n        const auto [rnum, rden]\
    \ = r;\n        cout << lnum << ' ' << lden << ' ' << rnum << ' ' << rden << '\\\
    n';\n    }\n}\n"
  dependsOn:
  - number/rational_approximation.hpp
  isVerificationFile: true
  path: number/test/rational_approximation.test.cpp
  requiredBy: []
  timestamp: '2024-07-14 00:23:24+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/rational_approximation.test.cpp
layout: document
redirect_from:
- /verify/number/test/rational_approximation.test.cpp
- /verify/number/test/rational_approximation.test.cpp.html
title: number/test/rational_approximation.test.cpp
---
