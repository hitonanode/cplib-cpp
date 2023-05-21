---
data:
  _extendedDependsOn:
  - icon: ':question:'
    path: number/min_max_semiring.hpp
    title: "Min-max semiring\uFF08(min, max) \u534A\u74B0\uFF09"
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
  bundledCode: "#line 1 \"number/test/min_max_semiring.test.cpp\"\n#define PROBLEM\
    \ \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\" // DUMMY\n\
    #line 1 \"number/min_max_semiring.hpp\"\n#include <limits>\n\n// min-max \u534A\
    \u74B0\uFF08\u52A0\u6CD5\u304C min, \u4E57\u6CD5\u304C max, \u96F6\u5143\u304C\
    \ INF, \u5358\u4F4D\u5143\u304C -INF\uFF09\n// Verified: abc236g\ntemplate <class\
    \ T> struct min_max_semiring {\n    T val;\n    min_max_semiring() : val(std::numeric_limits<T>::max())\
    \ {\n        static_assert(std::numeric_limits<T>::max() > 0,\n              \
    \        \"std::numeric_limits<>::max() must be properly defined\");\n    }\n\
    \    min_max_semiring(T x) : val(x) {}\n    static min_max_semiring id() { return\
    \ T(std::numeric_limits<T>::min()); }\n    static min_max_semiring max() { return\
    \ T(); }\n    min_max_semiring operator+(const min_max_semiring &r) const {\n\
    \        return (this->val > r.val ? r.val : this->val);\n    }\n    min_max_semiring\
    \ &operator+=(const min_max_semiring &r) { return *this = *this + r; }\n    min_max_semiring\
    \ operator*(const min_max_semiring &r) const {\n        return (this->val < r.val\
    \ ? r.val : this->val);\n    }\n    min_max_semiring &operator*=(const min_max_semiring\
    \ &r) { return *this = *this * r; }\n    bool operator==(const min_max_semiring\
    \ &r) const { return this->val == r.val; }\n    bool operator!=(const min_max_semiring\
    \ &r) const { return !(*this == r); }\n    template <class OStream> friend OStream\
    \ &operator<<(OStream &os, const min_max_semiring &x) {\n        return os <<\
    \ x.val;\n    }\n};\n#line 3 \"number/test/min_max_semiring.test.cpp\"\n#include\
    \ <algorithm>\n#include <cassert>\n#include <iostream>\n\ntemplate <class T> void\
    \ test_min_max_semiring() {\n    using R = min_max_semiring<T>;\n    for (int\
    \ x = -100; x <= 100; ++x) {\n        for (int y = -100; y <= 100; ++y) {\n  \
    \          T Tx = x, Ty = y;\n            assert(R(Tx) + R(Ty) == std::min(Tx,\
    \ Ty));\n            assert(!(R(Tx) + R(Ty) != std::min(Tx, Ty)));\n         \
    \   assert(R(Tx) * R(Ty) == std::max(Tx, Ty));\n            assert(!(R(Tx) * R(Ty)\
    \ != std::max(Tx, Ty)));\n\n            R A = R(Tx), B = R(Tx);\n            A\
    \ += R(Ty);\n            B *= R(Ty);\n            assert(A == R(std::min(Tx, Ty)));\n\
    \            assert(B == R(std::max(Tx, Ty)));\n        }\n    }\n}\n\nint main()\
    \ {\n    test_min_max_semiring<int>();\n    test_min_max_semiring<long long>();\n\
    \    test_min_max_semiring<double>();\n    test_min_max_semiring<long double>();\n\
    \    std::cout << \"Hello World\\n\";\n}\n"
  code: "#define PROBLEM \"https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ITP1_1_A\"\
    \ // DUMMY\n#include \"../min_max_semiring.hpp\"\n#include <algorithm>\n#include\
    \ <cassert>\n#include <iostream>\n\ntemplate <class T> void test_min_max_semiring()\
    \ {\n    using R = min_max_semiring<T>;\n    for (int x = -100; x <= 100; ++x)\
    \ {\n        for (int y = -100; y <= 100; ++y) {\n            T Tx = x, Ty = y;\n\
    \            assert(R(Tx) + R(Ty) == std::min(Tx, Ty));\n            assert(!(R(Tx)\
    \ + R(Ty) != std::min(Tx, Ty)));\n            assert(R(Tx) * R(Ty) == std::max(Tx,\
    \ Ty));\n            assert(!(R(Tx) * R(Ty) != std::max(Tx, Ty)));\n\n       \
    \     R A = R(Tx), B = R(Tx);\n            A += R(Ty);\n            B *= R(Ty);\n\
    \            assert(A == R(std::min(Tx, Ty)));\n            assert(B == R(std::max(Tx,\
    \ Ty)));\n        }\n    }\n}\n\nint main() {\n    test_min_max_semiring<int>();\n\
    \    test_min_max_semiring<long long>();\n    test_min_max_semiring<double>();\n\
    \    test_min_max_semiring<long double>();\n    std::cout << \"Hello World\\n\"\
    ;\n}\n"
  dependsOn:
  - number/min_max_semiring.hpp
  isVerificationFile: true
  path: number/test/min_max_semiring.test.cpp
  requiredBy: []
  timestamp: '2022-01-25 23:19:52+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: number/test/min_max_semiring.test.cpp
layout: document
redirect_from:
- /verify/number/test/min_max_semiring.test.cpp
- /verify/number/test/min_max_semiring.test.cpp.html
title: number/test/min_max_semiring.test.cpp
---
