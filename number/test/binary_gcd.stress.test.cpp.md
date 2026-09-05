---
data:
  _extendedDependsOn:
  - icon: ':x:'
    path: number/binary_gcd.hpp
    title: Binary GCD
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: true
  _pathExtension: cpp
  _verificationStatusIcon: ':x:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A
  bundledCode: "#line 1 \"number/test/binary_gcd.stress.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\" // DUMMY\n\
    #line 2 \"number/binary_gcd.hpp\"\n#include <type_traits>\n\n// CUT begin\ntemplate\
    \ <typename Int> Int binary_gcd(Int x_, Int y_) {\n    using Uint = std::make_unsigned_t<Int>;\n\
    \    auto magnitude = [](Int v) -> Uint {\n        Uint u = static_cast<Uint>(v);\n\
    \        return v < 0 ? Uint(0) - u : u;\n    };\n    unsigned long long x = magnitude(x_),\
    \ y = magnitude(y_);\n    if (!x or !y) return x + y;\n    int n = __builtin_ctzll(x),\
    \ m = __builtin_ctzll(y);\n    x >>= n, y >>= m;\n    while (x != y) {\n     \
    \   if (x > y) {\n            x = (x - y) >> __builtin_ctzll(x - y);\n       \
    \ } else {\n            y = (y - x) >> __builtin_ctzll(y - x);\n        }\n  \
    \  }\n    return x << (n > m ? m : n);\n}\n#line 3 \"number/test/binary_gcd.stress.test.cpp\"\
    \n#include <iostream>\n#include <numeric>\nusing namespace std;\n\ntemplate <typename\
    \ Int> void test_binary_gcd(Int lo, Int hi) {\n    for (Int x = lo; x <= hi; x++)\
    \ {\n        for (Int y = lo; y <= hi; y++) {\n            auto g = gcd<Int>(x,\
    \ y);\n            if (g < 0) g = -g;\n            if (binary_gcd(x, y) != g)\
    \ {\n                cerr << \"Did not match : (x, y) = \" << x << ',' << y <<\
    \ ')' << endl;\n                throw;\n            }\n        }\n    }\n}\n\n\
    int main() {\n    test_binary_gcd<signed char>(-127, 126);\n    test_binary_gcd<short>(-1000,\
    \ 1000);\n    test_binary_gcd<int>(-1000, 1000);\n    test_binary_gcd<unsigned\
    \ int>(0, 2000);\n    test_binary_gcd<long long>(-1000, 1000);\n    test_binary_gcd<unsigned\
    \ long long>(0, 2000);\n    cout << \"Hello World\" << endl;\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../binary_gcd.hpp\"\n#include <iostream>\n#include <numeric>\n\
    using namespace std;\n\ntemplate <typename Int> void test_binary_gcd(Int lo, Int\
    \ hi) {\n    for (Int x = lo; x <= hi; x++) {\n        for (Int y = lo; y <= hi;\
    \ y++) {\n            auto g = gcd<Int>(x, y);\n            if (g < 0) g = -g;\n\
    \            if (binary_gcd(x, y) != g) {\n                cerr << \"Did not match\
    \ : (x, y) = \" << x << ',' << y << ')' << endl;\n                throw;\n   \
    \         }\n        }\n    }\n}\n\nint main() {\n    test_binary_gcd<signed char>(-127,\
    \ 126);\n    test_binary_gcd<short>(-1000, 1000);\n    test_binary_gcd<int>(-1000,\
    \ 1000);\n    test_binary_gcd<unsigned int>(0, 2000);\n    test_binary_gcd<long\
    \ long>(-1000, 1000);\n    test_binary_gcd<unsigned long long>(0, 2000);\n   \
    \ cout << \"Hello World\" << endl;\n}\n"
  dependsOn:
  - number/binary_gcd.hpp
  isVerificationFile: true
  path: number/test/binary_gcd.stress.test.cpp
  requiredBy: []
  timestamp: '2026-09-05 21:26:13+09:00'
  verificationStatus: TEST_WRONG_ANSWER
  verifiedWith: []
documentation_of: number/test/binary_gcd.stress.test.cpp
layout: document
redirect_from:
- /verify/number/test/binary_gcd.stress.test.cpp
- /verify/number/test/binary_gcd.stress.test.cpp.html
title: number/test/binary_gcd.stress.test.cpp
---
