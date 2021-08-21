---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: number/binary_gcd.hpp
    title: Binary GCD
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"number/test/binary_gcd.stress.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\" // DUMMY\n\
    #line 2 \"number/binary_gcd.hpp\"\n\n// CUT begin\ntemplate <typename Int> Int\
    \ binary_gcd(Int x_, Int y_) {\n    unsigned long long x = x_ < 0 ? -x_ : x_,\
    \ y = y_ < 0 ? -y_ : y_;\n    if (!x or !y) return x + y;\n    int n = __builtin_ctzll(x),\
    \ m = __builtin_ctzll(y);\n    x >>= n, y >>= m;\n    while (x != y) {\n     \
    \   if (x > y) {\n            x = (x - y) >> __builtin_ctzll(x - y);\n       \
    \ } else {\n            y = (y - x) >> __builtin_ctzll(y - x);\n        }\n  \
    \  }\n    return x << (n > m ? m : n);\n}\n#line 3 \"number/test/binary_gcd.stress.test.cpp\"\
    \n#include <algorithm> // __gcd\n#include <iostream>\nusing namespace std;\n\n\
    template <typename Int> void test_binary_gcd(Int lo, Int hi) {\n    for (Int x\
    \ = lo; x <= hi; x++) {\n        for (Int y = lo; y <= hi; y++) {\n          \
    \  auto g = __gcd<Int>(x, y);\n            if (g < 0) g = -g;\n            if\
    \ (binary_gcd(x, y) != g) {\n                cerr << \"Did not match : (x, y)\
    \ = \" << x << ',' << y << ')' << endl;\n                throw;\n            }\n\
    \        }\n    }\n}\n\nint main() {\n    test_binary_gcd<int>(-1000, 1000);\n\
    \    test_binary_gcd<unsigned int>(0, 2000);\n    test_binary_gcd<long long>(-1000,\
    \ 1000);\n    test_binary_gcd<unsigned long long>(0, 2000);\n    cout << \"Hello\
    \ World\" << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../binary_gcd.hpp\"\n#include <algorithm> // __gcd\n#include\
    \ <iostream>\nusing namespace std;\n\ntemplate <typename Int> void test_binary_gcd(Int\
    \ lo, Int hi) {\n    for (Int x = lo; x <= hi; x++) {\n        for (Int y = lo;\
    \ y <= hi; y++) {\n            auto g = __gcd<Int>(x, y);\n            if (g <\
    \ 0) g = -g;\n            if (binary_gcd(x, y) != g) {\n                cerr <<\
    \ \"Did not match : (x, y) = \" << x << ',' << y << ')' << endl;\n           \
    \     throw;\n            }\n        }\n    }\n}\n\nint main() {\n    test_binary_gcd<int>(-1000,\
    \ 1000);\n    test_binary_gcd<unsigned int>(0, 2000);\n    test_binary_gcd<long\
    \ long>(-1000, 1000);\n    test_binary_gcd<unsigned long long>(0, 2000);\n   \
    \ cout << \"Hello World\" << endl;\n}\n"
  dependsOn:
  - number/binary_gcd.hpp
  isVerificationFile: true
  path: number/test/binary_gcd.stress.test.cpp
  requiredBy: []
  timestamp: '2021-08-21 15:46:09+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/binary_gcd.stress.test.cpp
layout: document
redirect_from:
- /verify/number/test/binary_gcd.stress.test.cpp
- /verify/number/test/binary_gcd.stress.test.cpp.html
title: number/test/binary_gcd.stress.test.cpp
---
