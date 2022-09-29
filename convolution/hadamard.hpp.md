---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: convolution/test/bitwise_and_conv.test.cpp
    title: convolution/test/bitwise_and_conv.test.cpp
  - icon: ':heavy_check_mark:'
    path: convolution/test/bitwise_xor_conv.test.cpp
    title: convolution/test/bitwise_xor_conv.test.cpp
  - icon: ':heavy_check_mark:'
    path: convolution/test/hadamard_xor.test.cpp
    title: convolution/test/hadamard_xor.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://codeforces.com/blog/entry/71899>
    - https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>
  bundledCode: "#line 2 \"convolution/hadamard.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Fast Walsh-Hadamard transform and its abstraction\n\
    // Tutorials: <https://codeforces.com/blog/entry/71899>\n//            <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>\n\
    template <typename T, typename F> void abstract_fwht(std::vector<T> &seq, F f)\
    \ {\n    const int n = seq.size();\n    assert(__builtin_popcount(n) == 1);\n\
    \    for (int w = 1; w < n; w *= 2) {\n        for (int i = 0; i < n; i += w *\
    \ 2) {\n            for (int j = 0; j < w; j++) { f(seq[i + j], seq[i + j + w]);\
    \ }\n        }\n    }\n}\n\ntemplate <typename T, typename F1, typename F2>\n\
    std::vector<T> bitwise_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv)\
    \ {\n    const int n = x.size();\n    assert(__builtin_popcount(n) == 1);\n  \
    \  assert(x.size() == y.size());\n    if (x == y) {\n        abstract_fwht(x,\
    \ f), y = x;\n    } else {\n        abstract_fwht(x, f), abstract_fwht(y, f);\n\
    \    }\n    for (size_t i = 0; i < x.size(); i++) { x[i] *= y[i]; }\n    abstract_fwht(x,\
    \ finv);\n    return x;\n}\n\n// bitwise xor convolution (FWHT-based)\n// ret[i]\
    \ = \\sum_j x[j] * y[i ^ j]\n// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()\n\
    template <typename T> std::vector<T> xorconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    auto f = [](T &lo, T &hi) {\n        T c = lo + hi;\n        hi =\
    \ lo - hi, lo = c;\n    };\n    auto finv = [](T &lo, T &hi) {\n        T c =\
    \ lo + hi;\n        hi = (lo - hi) / 2,\n        lo = c / 2; // Reconsider HEAVY\
    \ complexity of division by 2 when T is ModInt\n    };\n    return bitwise_conv(x,\
    \ y, f, finv);\n}\n\n// bitwise AND conolution\n// ret[i] = \\sum_{(j & k) ==\
    \ i} x[j] * y[k]\ntemplate <typename T> std::vector<T> andconv(std::vector<T>\
    \ x, std::vector<T> y) {\n    return bitwise_conv(\n        x, y, [](T &lo, T\
    \ &hi) { lo += hi; }, [](T &lo, T &hi) { lo -= hi; });\n}\n\n// bitwise OR convolution\n\
    // ret[i] = \\sum_{(j | k) == i} x[j] * y[k]\ntemplate <typename T> std::vector<T>\
    \ orconv(std::vector<T> x, std::vector<T> y) {\n    return bitwise_conv(\n   \
    \     x, y, [](T &lo, T &hi) { hi += lo; }, [](T &lo, T &hi) { hi -= lo; });\n\
    }\n"
  code: "#pragma once\n#include <cassert>\n#include <vector>\n\n// CUT begin\n// Fast\
    \ Walsh-Hadamard transform and its abstraction\n// Tutorials: <https://codeforces.com/blog/entry/71899>\n\
    //            <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>\n\
    template <typename T, typename F> void abstract_fwht(std::vector<T> &seq, F f)\
    \ {\n    const int n = seq.size();\n    assert(__builtin_popcount(n) == 1);\n\
    \    for (int w = 1; w < n; w *= 2) {\n        for (int i = 0; i < n; i += w *\
    \ 2) {\n            for (int j = 0; j < w; j++) { f(seq[i + j], seq[i + j + w]);\
    \ }\n        }\n    }\n}\n\ntemplate <typename T, typename F1, typename F2>\n\
    std::vector<T> bitwise_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv)\
    \ {\n    const int n = x.size();\n    assert(__builtin_popcount(n) == 1);\n  \
    \  assert(x.size() == y.size());\n    if (x == y) {\n        abstract_fwht(x,\
    \ f), y = x;\n    } else {\n        abstract_fwht(x, f), abstract_fwht(y, f);\n\
    \    }\n    for (size_t i = 0; i < x.size(); i++) { x[i] *= y[i]; }\n    abstract_fwht(x,\
    \ finv);\n    return x;\n}\n\n// bitwise xor convolution (FWHT-based)\n// ret[i]\
    \ = \\sum_j x[j] * y[i ^ j]\n// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()\n\
    template <typename T> std::vector<T> xorconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    auto f = [](T &lo, T &hi) {\n        T c = lo + hi;\n        hi =\
    \ lo - hi, lo = c;\n    };\n    auto finv = [](T &lo, T &hi) {\n        T c =\
    \ lo + hi;\n        hi = (lo - hi) / 2,\n        lo = c / 2; // Reconsider HEAVY\
    \ complexity of division by 2 when T is ModInt\n    };\n    return bitwise_conv(x,\
    \ y, f, finv);\n}\n\n// bitwise AND conolution\n// ret[i] = \\sum_{(j & k) ==\
    \ i} x[j] * y[k]\ntemplate <typename T> std::vector<T> andconv(std::vector<T>\
    \ x, std::vector<T> y) {\n    return bitwise_conv(\n        x, y, [](T &lo, T\
    \ &hi) { lo += hi; }, [](T &lo, T &hi) { lo -= hi; });\n}\n\n// bitwise OR convolution\n\
    // ret[i] = \\sum_{(j | k) == i} x[j] * y[k]\ntemplate <typename T> std::vector<T>\
    \ orconv(std::vector<T> x, std::vector<T> y) {\n    return bitwise_conv(\n   \
    \     x, y, [](T &lo, T &hi) { hi += lo; }, [](T &lo, T &hi) { hi -= lo; });\n\
    }\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/hadamard.hpp
  requiredBy: []
  timestamp: '2022-01-08 20:23:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - convolution/test/bitwise_xor_conv.test.cpp
  - convolution/test/bitwise_and_conv.test.cpp
  - convolution/test/hadamard_xor.test.cpp
documentation_of: convolution/hadamard.hpp
layout: document
redirect_from:
- /library/convolution/hadamard.hpp
- /library/convolution/hadamard.hpp.html
title: convolution/hadamard.hpp
---
