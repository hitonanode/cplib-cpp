---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: convolution/hadamard.hpp
    title: convolution/hadamard.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://yukicoder.me/problems/no/1240
    links:
    - https://yukicoder.me/problems/no/1240
  bundledCode: "#line 2 \"convolution/hadamard.hpp\"\n#include <cassert>\n#include\
    \ <vector>\n\n// CUT begin\n// Fast Walsh-Hadamard transform and its abstraction\n\
    // Tutorials: <https://codeforces.com/blog/entry/71899>\n//            <https://csacademy.com/blog/fast-fourier-transform-and-variations-of-it>\n\
    template <typename T, typename F> void abstract_fwht(std::vector<T>& seq, F f)\
    \ {\n    const int n = seq.size();\n    assert(__builtin_popcount(n) == 1);\n\
    \    for (int w = 1; w < n; w *= 2) {\n        for (int i = 0; i < n; i += w *\
    \ 2) {\n            for (int j = 0; j < w; j++) { f(seq[i + j], seq[i + j + w]);\
    \ }\n        }\n    }\n}\n\ntemplate <typename T, typename F1, typename F2> std::vector<T>\
    \ bitwise_conv(std::vector<T> x, std::vector<T> y, F1 f, F2 finv) {\n    const\
    \ int n = x.size();\n    assert(__builtin_popcount(n) == 1);\n    assert(x.size()\
    \ == y.size());\n    if (x == y) {\n        abstract_fwht(x, f), y = x;\n    }\
    \ else {\n        abstract_fwht(x, f), abstract_fwht(y, f);\n    }\n    for (size_t\
    \ i = 0; i < x.size(); i++) { x[i] *= y[i]; }\n    abstract_fwht(x, finv);\n \
    \   return x;\n}\n\n// bitwise xor convolution (FWHT-based)\n// ret[i] = \\sum_j\
    \ x[j] * y[i ^ j]\n// if T is integer, ||x||_1 * ||y||_1 * 2 < numeric_limits<T>::max()\n\
    template <typename T> std::vector<T> xorconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    auto f = [](T& lo, T& hi) {\n        T c = lo + hi;\n        hi =\
    \ lo - hi, lo = c;\n    };\n    auto finv = [](T& lo, T& hi) {\n        T c =\
    \ lo + hi;\n        hi = (lo - hi) / 2, lo = c / 2; // Reconsider HEAVY complexity\
    \ of division by 2 when T is ModInt\n    };\n    return bitwise_conv(x, y, f,\
    \ finv);\n}\n\n// bitwise AND conolution\n// ret[i] = \\sum_{(j & k) == i} x[j]\
    \ * y[k]\ntemplate <typename T> std::vector<T> andconv(std::vector<T> x, std::vector<T>\
    \ y) {\n    return bitwise_conv(\n        x, y, [](T& lo, T& hi) { lo += hi; },\
    \ [](T& lo, T& hi) { lo -= hi; });\n}\n\n// bitwise OR convolution\n// ret[i]\
    \ = \\sum_{(j | k) == i} x[j] * y[k]\ntemplate <typename T> std::vector<T> orconv(std::vector<T>\
    \ x, std::vector<T> y) {\n    return bitwise_conv(\n        x, y, [](T& lo, T&\
    \ hi) { hi += lo; }, [](T& lo, T& hi) { hi -= lo; });\n}\n#line 2 \"convolution/test/hadamard_xor.test.cpp\"\
    \n#define PROBLEM \"https://yukicoder.me/problems/no/1240\"\n#include <iostream>\n\
    using namespace std;\n\nint main() {\n    cin.tie(nullptr), ios::sync_with_stdio(false);\n\
    \n    int N, X;\n    cin >> N >> X;\n    vector<int> A(N);\n    for (auto &x :\
    \ A) { cin >> x; }\n    const int D = 18;\n    vector<long long> cnt(1 << D);\n\
    \    for (auto a : A) cnt[a]++;\n    cnt = xorconv(cnt, cnt);\n    cnt[0] -= N;\n\
    \    long long ret = 0;\n\n    for (int d = 0; d < D; d++) {\n        vector<long\
    \ long> cntd(1 << D);\n        int nd = 0;\n        for (auto a : A)\n       \
    \     if (((a >> d) & 1) == 0) { cntd[a]++, nd++; }\n        cntd = xorconv(cntd,\
    \ cntd);\n        cntd[0] -= nd;\n        for (int i = 0; i < X; i++) { ret +=\
    \ (1LL << d) * (cnt[i] - cntd[i]) / 2; }\n    }\n    cout << ret << '\\n';\n}\n"
  code: "#include \"../hadamard.hpp\"\n#define PROBLEM \"https://yukicoder.me/problems/no/1240\"\
    \n#include <iostream>\nusing namespace std;\n\nint main() {\n    cin.tie(nullptr),\
    \ ios::sync_with_stdio(false);\n\n    int N, X;\n    cin >> N >> X;\n    vector<int>\
    \ A(N);\n    for (auto &x : A) { cin >> x; }\n    const int D = 18;\n    vector<long\
    \ long> cnt(1 << D);\n    for (auto a : A) cnt[a]++;\n    cnt = xorconv(cnt, cnt);\n\
    \    cnt[0] -= N;\n    long long ret = 0;\n\n    for (int d = 0; d < D; d++) {\n\
    \        vector<long long> cntd(1 << D);\n        int nd = 0;\n        for (auto\
    \ a : A)\n            if (((a >> d) & 1) == 0) { cntd[a]++, nd++; }\n        cntd\
    \ = xorconv(cntd, cntd);\n        cntd[0] -= nd;\n        for (int i = 0; i <\
    \ X; i++) { ret += (1LL << d) * (cnt[i] - cntd[i]) / 2; }\n    }\n    cout <<\
    \ ret << '\\n';\n}\n"
  dependsOn:
  - convolution/hadamard.hpp
  isVerificationFile: true
  path: convolution/test/hadamard_xor.test.cpp
  requiredBy: []
  timestamp: '2020-12-20 04:05:21+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: convolution/test/hadamard_xor.test.cpp
layout: document
redirect_from:
- /verify/convolution/test/hadamard_xor.test.cpp
- /verify/convolution/test/hadamard_xor.test.cpp.html
title: convolution/test/hadamard_xor.test.cpp
---
