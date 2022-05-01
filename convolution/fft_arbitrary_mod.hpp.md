---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://ei1333.github.io/luzhiled/snippets/math/arbitrary-mod-convolution.html
  bundledCode: "#line 2 \"convolution/fft_arbitrary_mod.hpp\"\n#include <cassert>\n\
    #include <cmath>\n#include <vector>\n\n// Arbitrary mod (<1e9) FFT/convolution\n\
    // MAXA*MAXB*N <= 1e15 (double), 1e19 (long double)\n// Based on https://ei1333.github.io/luzhiled/snippets/math/arbitrary-mod-convolution.html\n\
    namespace fft_arbitrary_mod {\nusing T_FFT = long double;\nconstexpr int D_FFT\
    \ = 15;\nstruct cmplx {\n    T_FFT x, y;\n    cmplx() : x(0), y(0) {}\n    cmplx(T_FFT\
    \ x, T_FFT y) : x(x), y(y) {}\n    inline cmplx operator+(const cmplx &r) const\
    \ { return cmplx(x + r.x, y + r.y); }\n    inline cmplx operator-(const cmplx\
    \ &r) const { return cmplx(x - r.x, y - r.y); }\n    inline cmplx operator*(const\
    \ cmplx &r) const {\n        return cmplx(x * r.x - y * r.y, x * r.y + y * r.x);\n\
    \    }\n    inline cmplx conj() const { return cmplx(x, -y); }\n};\nint fftbase\
    \ = 1;\nstd::vector<cmplx> fftrts = {{0, 0}, {1, 0}};\nstd::vector<int> fftrev\
    \ = {0, 1};\nvoid ensure_base(int nbase) {\n    if (nbase <= fftbase) return;\n\
    \    fftrev.resize(1 << nbase);\n    fftrts.resize(1 << nbase);\n    for (int\
    \ i = 0; i < (1 << nbase); i++) {\n        fftrev[i] = (fftrev[i >> 1] >> 1) +\
    \ ((i & 1) << (nbase - 1));\n    }\n    while (fftbase < nbase) {\n        T_FFT\
    \ angle = acosl(-1.0L) * 2.0L / (1 << (fftbase + 1));\n        for (int i = 1\
    \ << (fftbase - 1); i < (1 << fftbase); i++) {\n            fftrts[i << 1] = fftrts[i];\n\
    \            T_FFT angle_i = angle * (2 * i + 1 - (1 << fftbase));\n         \
    \   fftrts[(i << 1) + 1] = {cos(angle_i), sin(angle_i)};\n        }\n        ++fftbase;\n\
    \    }\n}\nvoid fft(int n, std::vector<cmplx> &a) {\n    assert((n & (n - 1))\
    \ == 0);\n    int zeros = __builtin_ctz(n);\n    ensure_base(zeros);\n    int\
    \ shift = fftbase - zeros;\n    for (int i = 0; i < n; i++) {\n        if (i <\
    \ (fftrev[i] >> shift)) { std::swap(a[i], a[fftrev[i] >> shift]); }\n    }\n \
    \   for (int k = 1; k < n; k <<= 1) {\n        for (int i = 0; i < n; i += 2 *\
    \ k) {\n            for (int j = 0; j < k; j++) {\n                cmplx z = a[i\
    \ + j + k] * fftrts[j + k];\n                a[i + j + k] = a[i + j] - z;\n  \
    \              a[i + j] = a[i + j] + z;\n            }\n        }\n    }\n}\n\n\
    // Convolution for ModInt class\n// retval[i] = \\sum_j a[j] b[i - j]\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> convolution_mod(std::vector<MODINT> a,\
    \ std::vector<MODINT> b) {\n    int need = int(a.size() + b.size()) - 1;\n   \
    \ int nbase = 0;\n    while ((1 << nbase) < need) nbase++;\n    int sz = 1 <<\
    \ nbase;\n    std::vector<cmplx> fa(sz);\n    for (int i = 0; i < (int)a.size();\
    \ i++)\n        fa[i] = {(T_FFT)(a[i].val() & ((1LL << D_FFT) - 1)), (T_FFT)(a[i].val()\
    \ >> D_FFT)};\n    fft(sz, fa);\n    std::vector<cmplx> fb(sz);\n    if (a ==\
    \ b)\n        fb = fa;\n    else {\n        for (int i = 0; i < (int)b.size();\
    \ i++)\n            fb[i] = {(T_FFT)(b[i].val() & ((1LL << D_FFT) - 1)), (T_FFT)(b[i].val()\
    \ >> D_FFT)};\n        fft(sz, fb);\n    }\n    T_FFT ratio = 0.25L / sz;\n  \
    \  cmplx r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);\n    for (int i = 0;\
    \ i <= (sz >> 1); i++) {\n        int j = (sz - i) & (sz - 1);\n        cmplx\
    \ a1 = (fa[i] + fa[j].conj());\n        cmplx a2 = (fa[i] - fa[j].conj()) * r2;\n\
    \        cmplx b1 = (fb[i] + fb[j].conj()) * r3;\n        cmplx b2 = (fb[i] -\
    \ fb[j].conj()) * r4;\n        if (i != j) {\n            cmplx c1 = (fa[j] +\
    \ fa[i].conj());\n            cmplx c2 = (fa[j] - fa[i].conj()) * r2;\n      \
    \      cmplx d1 = (fb[j] + fb[i].conj()) * r3;\n            cmplx d2 = (fb[j]\
    \ - fb[i].conj()) * r4;\n            fa[i] = c1 * d1 + c2 * d2 * r5;\n       \
    \     fb[i] = c1 * d2 + c2 * d1;\n        }\n        fa[j] = a1 * b1 + a2 * b2\
    \ * r5;\n        fb[j] = a1 * b2 + a2 * b1;\n    }\n    fft(sz, fa);\n    fft(sz,\
    \ fb);\n    std::vector<MODINT> ret(sz);\n    long long bp = MODINT(2).pow(D_FFT).val();\n\
    \    long long cp = MODINT(2).pow(D_FFT * 2).val();\n    for (int i = 0; i < need;\
    \ i++) {\n        long long aa = llround(fa[i].x);\n        long long bb = llround(fb[i].x);\n\
    \        long long cc = llround(fa[i].y);\n        aa = MODINT(aa).val(), bb =\
    \ MODINT(bb).val(), cc = MODINT(cc).val();\n        ret[i] = aa + (bb * bp) +\
    \ (cc * cp);\n        //   ret[i] = aa + (bb << DFFT) + (cc << (DFFT * 2));\n\
    \    }\n    return ret;\n}\n\n} // namespace fft_arbitrary_mod\n"
  code: "#pragma once\n#include <cassert>\n#include <cmath>\n#include <vector>\n\n\
    // Arbitrary mod (<1e9) FFT/convolution\n// MAXA*MAXB*N <= 1e15 (double), 1e19\
    \ (long double)\n// Based on https://ei1333.github.io/luzhiled/snippets/math/arbitrary-mod-convolution.html\n\
    namespace fft_arbitrary_mod {\nusing T_FFT = long double;\nconstexpr int D_FFT\
    \ = 15;\nstruct cmplx {\n    T_FFT x, y;\n    cmplx() : x(0), y(0) {}\n    cmplx(T_FFT\
    \ x, T_FFT y) : x(x), y(y) {}\n    inline cmplx operator+(const cmplx &r) const\
    \ { return cmplx(x + r.x, y + r.y); }\n    inline cmplx operator-(const cmplx\
    \ &r) const { return cmplx(x - r.x, y - r.y); }\n    inline cmplx operator*(const\
    \ cmplx &r) const {\n        return cmplx(x * r.x - y * r.y, x * r.y + y * r.x);\n\
    \    }\n    inline cmplx conj() const { return cmplx(x, -y); }\n};\nint fftbase\
    \ = 1;\nstd::vector<cmplx> fftrts = {{0, 0}, {1, 0}};\nstd::vector<int> fftrev\
    \ = {0, 1};\nvoid ensure_base(int nbase) {\n    if (nbase <= fftbase) return;\n\
    \    fftrev.resize(1 << nbase);\n    fftrts.resize(1 << nbase);\n    for (int\
    \ i = 0; i < (1 << nbase); i++) {\n        fftrev[i] = (fftrev[i >> 1] >> 1) +\
    \ ((i & 1) << (nbase - 1));\n    }\n    while (fftbase < nbase) {\n        T_FFT\
    \ angle = acosl(-1.0L) * 2.0L / (1 << (fftbase + 1));\n        for (int i = 1\
    \ << (fftbase - 1); i < (1 << fftbase); i++) {\n            fftrts[i << 1] = fftrts[i];\n\
    \            T_FFT angle_i = angle * (2 * i + 1 - (1 << fftbase));\n         \
    \   fftrts[(i << 1) + 1] = {cos(angle_i), sin(angle_i)};\n        }\n        ++fftbase;\n\
    \    }\n}\nvoid fft(int n, std::vector<cmplx> &a) {\n    assert((n & (n - 1))\
    \ == 0);\n    int zeros = __builtin_ctz(n);\n    ensure_base(zeros);\n    int\
    \ shift = fftbase - zeros;\n    for (int i = 0; i < n; i++) {\n        if (i <\
    \ (fftrev[i] >> shift)) { std::swap(a[i], a[fftrev[i] >> shift]); }\n    }\n \
    \   for (int k = 1; k < n; k <<= 1) {\n        for (int i = 0; i < n; i += 2 *\
    \ k) {\n            for (int j = 0; j < k; j++) {\n                cmplx z = a[i\
    \ + j + k] * fftrts[j + k];\n                a[i + j + k] = a[i + j] - z;\n  \
    \              a[i + j] = a[i + j] + z;\n            }\n        }\n    }\n}\n\n\
    // Convolution for ModInt class\n// retval[i] = \\sum_j a[j] b[i - j]\ntemplate\
    \ <typename MODINT>\nstd::vector<MODINT> convolution_mod(std::vector<MODINT> a,\
    \ std::vector<MODINT> b) {\n    int need = int(a.size() + b.size()) - 1;\n   \
    \ int nbase = 0;\n    while ((1 << nbase) < need) nbase++;\n    int sz = 1 <<\
    \ nbase;\n    std::vector<cmplx> fa(sz);\n    for (int i = 0; i < (int)a.size();\
    \ i++)\n        fa[i] = {(T_FFT)(a[i].val() & ((1LL << D_FFT) - 1)), (T_FFT)(a[i].val()\
    \ >> D_FFT)};\n    fft(sz, fa);\n    std::vector<cmplx> fb(sz);\n    if (a ==\
    \ b)\n        fb = fa;\n    else {\n        for (int i = 0; i < (int)b.size();\
    \ i++)\n            fb[i] = {(T_FFT)(b[i].val() & ((1LL << D_FFT) - 1)), (T_FFT)(b[i].val()\
    \ >> D_FFT)};\n        fft(sz, fb);\n    }\n    T_FFT ratio = 0.25L / sz;\n  \
    \  cmplx r2(0, -1), r3(ratio, 0), r4(0, -ratio), r5(0, 1);\n    for (int i = 0;\
    \ i <= (sz >> 1); i++) {\n        int j = (sz - i) & (sz - 1);\n        cmplx\
    \ a1 = (fa[i] + fa[j].conj());\n        cmplx a2 = (fa[i] - fa[j].conj()) * r2;\n\
    \        cmplx b1 = (fb[i] + fb[j].conj()) * r3;\n        cmplx b2 = (fb[i] -\
    \ fb[j].conj()) * r4;\n        if (i != j) {\n            cmplx c1 = (fa[j] +\
    \ fa[i].conj());\n            cmplx c2 = (fa[j] - fa[i].conj()) * r2;\n      \
    \      cmplx d1 = (fb[j] + fb[i].conj()) * r3;\n            cmplx d2 = (fb[j]\
    \ - fb[i].conj()) * r4;\n            fa[i] = c1 * d1 + c2 * d2 * r5;\n       \
    \     fb[i] = c1 * d2 + c2 * d1;\n        }\n        fa[j] = a1 * b1 + a2 * b2\
    \ * r5;\n        fb[j] = a1 * b2 + a2 * b1;\n    }\n    fft(sz, fa);\n    fft(sz,\
    \ fb);\n    std::vector<MODINT> ret(sz);\n    long long bp = MODINT(2).pow(D_FFT).val();\n\
    \    long long cp = MODINT(2).pow(D_FFT * 2).val();\n    for (int i = 0; i < need;\
    \ i++) {\n        long long aa = llround(fa[i].x);\n        long long bb = llround(fb[i].x);\n\
    \        long long cc = llround(fa[i].y);\n        aa = MODINT(aa).val(), bb =\
    \ MODINT(bb).val(), cc = MODINT(cc).val();\n        ret[i] = aa + (bb * bp) +\
    \ (cc * cp);\n        //   ret[i] = aa + (bb << DFFT) + (cc << (DFFT * 2));\n\
    \    }\n    return ret;\n}\n\n} // namespace fft_arbitrary_mod\n"
  dependsOn: []
  isVerificationFile: false
  path: convolution/fft_arbitrary_mod.hpp
  requiredBy: []
  timestamp: '2022-05-01 16:11:38+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: convolution/fft_arbitrary_mod.hpp
layout: document
redirect_from:
- /library/convolution/fft_arbitrary_mod.hpp
- /library/convolution/fft_arbitrary_mod.hpp.html
title: convolution/fft_arbitrary_mod.hpp
---
