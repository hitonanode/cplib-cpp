---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    links:
    - http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>
    - https://atcoder.jp/contests/atc001/submissions/9243440>
  bundledCode: "#line 2 \"convolution/fft_double.hpp\"\n#include <complex>\n#include\
    \ <utility>\n#include <vector>\n\n// CUT begin\n// Convolution by FFT (Fast Fourier\
    \ Transform)\n// Algorithm based on <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n\
    // Verified: ATC001C (168 ms) <https://atcoder.jp/contests/atc001/submissions/9243440>\n\
    using cmplx = std::complex<double>;\nvoid fft(int N, std::vector<cmplx> &a, double\
    \ dir)\n{\n    int i = 0;\n    for (int j = 1; j < N - 1; j++) {\n        for\
    \ (int k = N >> 1; k > (i ^= k); k >>= 1);\n        if (j < i) std::swap(a[i],\
    \ a[j]);\n    }\n\n    std::vector<cmplx> zeta_pow(N);\n    for (int i = 0; i\
    \ < N; i++) {\n        double theta = M_PI / N * i * dir;\n        zeta_pow[i]\
    \ = {cos(theta), sin(theta)};\n    }\n\n    for (int m = 1; m < N; m *= 2) {\n\
    \        for (int y = 0; y < m; y++) {\n            cmplx fac = zeta_pow[N / m\
    \ * y];\n            for (int x = 0; x < N; x += 2 * m) {\n                int\
    \ u = x + y;\n                int v = x + y + m;\n                cmplx s = a[u]\
    \ + fac * a[v];\n                cmplx t = a[u] - fac * a[v];\n              \
    \  a[u] = s;\n                a[v] = t;\n            }\n        }\n    }\n}\n\
    template<typename T>\nstd::vector<cmplx> conv_cmplx(const std::vector<T> &a, const\
    \ std::vector<T> &b)\n{\n    int N = 1;\n    while (N < (int)a.size() + (int)b.size())\
    \ N *= 2;\n    std::vector<cmplx> a_(N), b_(N);\n    for (int i = 0; i < (int)a.size();\
    \ i++) a_[i] = a[i];\n    for (int i = 0; i < (int)b.size(); i++) b_[i] = b[i];\n\
    \    fft(N, a_, 1);\n    fft(N, b_, 1);\n    for (int i = 0; i < N; i++) a_[i]\
    \ *= b_[i];\n    fft(N, a_, -1);\n    for (int i = 0; i < N; i++) a_[i] /= N;\n\
    \    return a_;\n}\n// retval[i] = \\sum_j a[j]b[i - j]\n// Requirement: length\
    \ * max(a) * max(b) < 10^15\ntemplate<typename T>\nstd::vector<long long int>\
    \ fftconv(const std::vector<T> &a, const std::vector<T> &b)\n{\n    std::vector<cmplx>\
    \ ans = conv_cmplx(a, b);\n    std::vector<long long int> ret(ans.size());\n \
    \   for (int i = 0; i < (int)ans.size(); i++) ret[i] = floor(ans[i].real() + 0.5);\n\
    \    return ret;\n}\n"
  code: "#pragma once\n#include <complex>\n#include <utility>\n#include <vector>\n\
    \n// CUT begin\n// Convolution by FFT (Fast Fourier Transform)\n// Algorithm based\
    \ on <http://kirika-comp.hatenablog.com/entry/2018/03/12/210446>\n// Verified:\
    \ ATC001C (168 ms) <https://atcoder.jp/contests/atc001/submissions/9243440>\n\
    using cmplx = std::complex<double>;\nvoid fft(int N, std::vector<cmplx> &a, double\
    \ dir)\n{\n    int i = 0;\n    for (int j = 1; j < N - 1; j++) {\n        for\
    \ (int k = N >> 1; k > (i ^= k); k >>= 1);\n        if (j < i) std::swap(a[i],\
    \ a[j]);\n    }\n\n    std::vector<cmplx> zeta_pow(N);\n    for (int i = 0; i\
    \ < N; i++) {\n        double theta = M_PI / N * i * dir;\n        zeta_pow[i]\
    \ = {cos(theta), sin(theta)};\n    }\n\n    for (int m = 1; m < N; m *= 2) {\n\
    \        for (int y = 0; y < m; y++) {\n            cmplx fac = zeta_pow[N / m\
    \ * y];\n            for (int x = 0; x < N; x += 2 * m) {\n                int\
    \ u = x + y;\n                int v = x + y + m;\n                cmplx s = a[u]\
    \ + fac * a[v];\n                cmplx t = a[u] - fac * a[v];\n              \
    \  a[u] = s;\n                a[v] = t;\n            }\n        }\n    }\n}\n\
    template<typename T>\nstd::vector<cmplx> conv_cmplx(const std::vector<T> &a, const\
    \ std::vector<T> &b)\n{\n    int N = 1;\n    while (N < (int)a.size() + (int)b.size())\
    \ N *= 2;\n    std::vector<cmplx> a_(N), b_(N);\n    for (int i = 0; i < (int)a.size();\
    \ i++) a_[i] = a[i];\n    for (int i = 0; i < (int)b.size(); i++) b_[i] = b[i];\n\
    \    fft(N, a_, 1);\n    fft(N, b_, 1);\n    for (int i = 0; i < N; i++) a_[i]\
    \ *= b_[i];\n    fft(N, a_, -1);\n    for (int i = 0; i < N; i++) a_[i] /= N;\n\
    \    return a_;\n}\n// retval[i] = \\sum_j a[j]b[i - j]\n// Requirement: length\
    \ * max(a) * max(b) < 10^15\ntemplate<typename T>\nstd::vector<long long int>\
    \ fftconv(const std::vector<T> &a, const std::vector<T> &b)\n{\n    std::vector<cmplx>\
    \ ans = conv_cmplx(a, b);\n    std::vector<long long int> ret(ans.size());\n \
    \   for (int i = 0; i < (int)ans.size(); i++) ret[i] = floor(ans[i].real() + 0.5);\n\
    \    return ret;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/fft_double.hpp
  requiredBy: []
  timestamp: '2020-03-07 22:40:57+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convolution/fft_double.hpp
layout: document
redirect_from:
- /library/convolution/fft_double.hpp
- /library/convolution/fft_double.hpp.html
title: convolution/fft_double.hpp
---
