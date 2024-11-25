---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: number/test/nimber.test.cpp
    title: number/test/nimber.test.cpp
  - icon: ':heavy_check_mark:'
    path: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
    title: unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links:
    - https://en.wikipedia.org/wiki/Nimber
    - https://judge.yosupo.jp/submission/4542
    - https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850
  bundledCode: "#line 2 \"number/nimber.hpp\"\n#include <array>\n\n// Nimber (64 bit)\n\
    // Reference:\n// - https://judge.yosupo.jp/submission/4542 (Original implementation\
    \ idea)\n// - https://en.wikipedia.org/wiki/Nimber\n// - https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850\n\
    struct Nimber {\n    using ull = unsigned long long;\n    ull v;\n    const static\
    \ std::array<std::array<unsigned, 256>, 256> small_table;\n    const static std::array<std::array<std::array<ull,\
    \ 256>, 8>, 8> precalc;\n\n    explicit operator bool() const { return v != 0;\
    \ }\n    Nimber(ull val = 0) : v(val) {}\n    Nimber operator+(const Nimber &x)\
    \ const { return Nimber(v ^ x.v); }\n    Nimber operator-(const Nimber &x) const\
    \ { return Nimber(v ^ x.v); }\n    Nimber operator-() const { return *this; }\n\
    \    Nimber &operator+=(const Nimber &x) { return *this = *this + x; }\n    Nimber\
    \ &operator-=(const Nimber &x) { return *this = *this + x; }\n    template <class\
    \ IStream> friend IStream &operator>>(IStream &is, Nimber &x) {\n        ull v;\n\
    \        return is >> v, x = Nimber(v), is;\n    }\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const Nimber &x) {\n        return os\
    \ << x.v;\n    }\n    bool operator==(const Nimber &x) const { return v == x.v;\
    \ }\n    bool operator!=(const Nimber &x) const { return v != x.v; }\n    bool\
    \ operator<(const Nimber &x) const { return v < x.v; }\n\n    static ull _rec(ull\
    \ x, ull y) {\n        if (x == 0 or y == 0) return 0;\n        if (x < y) x ^=\
    \ y, y ^= x, x ^= y; // Make x >= y\n        if (y == 1) return x;\n        for\
    \ (int shift = 64 / 2;; shift >>= 1) {\n            ull mask = (1ULL << shift)\
    \ - 1;\n            if (y >> shift) {\n                ull v00 = _rec(x & mask,\
    \ y & mask);\n                ull v01 = _rec(x & mask, y >> shift);\n        \
    \        ull v10 = _rec(x >> shift, y & mask);\n                ull v11 = _rec(x\
    \ >> shift, y >> shift);\n                return v00 ^ ((v01 ^ v10 ^ v11) << shift)\
    \ ^ _rec(v11, 1ULL << (shift - 1));\n            } else if (x >> shift) {\n  \
    \              return (_rec(x >> shift, y) << shift) ^ _rec(x & mask, y);\n  \
    \          }\n        }\n    }\n    Nimber operator*(const Nimber &x) const {\n\
    \        ull ret = 0;\n        for (int d = 0; d < 8; ++d) {\n            for\
    \ (int e = 0; e < 8; ++e) {\n                ret ^= precalc[d][e][small_table[(v\
    \ >> (d * 8)) & 255][(x.v >> (e * 8)) & 255]];\n            }\n        }\n   \
    \     return Nimber(ret);\n    }\n    Nimber &operator*=(const Nimber &x) { return\
    \ *this = *this * x; }\n};\n\nconst std::array<std::array<unsigned, 256>, 256>\
    \ Nimber::small_table = []() {\n    std::array<std::array<unsigned, 256>, 256>\
    \ ret;\n    for (int i = 0; i < 256; ++i) {\n        for (int j = 0; j < 256;\
    \ ++j) ret[i][j] = _rec(i, j);\n    }\n    return ret;\n}();\nconst std::array<std::array<std::array<unsigned\
    \ long long, 256>, 8>, 8> Nimber::precalc = []() {\n    std::array<std::array<std::array<unsigned\
    \ long long, 256>, 8>, 8> ret;\n    for (int d = 0; d < 8; ++d) {\n        for\
    \ (int e = 0; e < 8; ++e) {\n            ull p = _rec(1ULL << (8 * d), 1ULL <<\
    \ (8 * e));\n            for (int i = 0; i < 256; ++i) ret[d][e][i] = _rec(p,\
    \ i);\n        }\n    }\n    return ret;\n}();\n"
  code: "#pragma once\n#include <array>\n\n// Nimber (64 bit)\n// Reference:\n// -\
    \ https://judge.yosupo.jp/submission/4542 (Original implementation idea)\n// -\
    \ https://en.wikipedia.org/wiki/Nimber\n// - https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850\n\
    struct Nimber {\n    using ull = unsigned long long;\n    ull v;\n    const static\
    \ std::array<std::array<unsigned, 256>, 256> small_table;\n    const static std::array<std::array<std::array<ull,\
    \ 256>, 8>, 8> precalc;\n\n    explicit operator bool() const { return v != 0;\
    \ }\n    Nimber(ull val = 0) : v(val) {}\n    Nimber operator+(const Nimber &x)\
    \ const { return Nimber(v ^ x.v); }\n    Nimber operator-(const Nimber &x) const\
    \ { return Nimber(v ^ x.v); }\n    Nimber operator-() const { return *this; }\n\
    \    Nimber &operator+=(const Nimber &x) { return *this = *this + x; }\n    Nimber\
    \ &operator-=(const Nimber &x) { return *this = *this + x; }\n    template <class\
    \ IStream> friend IStream &operator>>(IStream &is, Nimber &x) {\n        ull v;\n\
    \        return is >> v, x = Nimber(v), is;\n    }\n    template <class OStream>\
    \ friend OStream &operator<<(OStream &os, const Nimber &x) {\n        return os\
    \ << x.v;\n    }\n    bool operator==(const Nimber &x) const { return v == x.v;\
    \ }\n    bool operator!=(const Nimber &x) const { return v != x.v; }\n    bool\
    \ operator<(const Nimber &x) const { return v < x.v; }\n\n    static ull _rec(ull\
    \ x, ull y) {\n        if (x == 0 or y == 0) return 0;\n        if (x < y) x ^=\
    \ y, y ^= x, x ^= y; // Make x >= y\n        if (y == 1) return x;\n        for\
    \ (int shift = 64 / 2;; shift >>= 1) {\n            ull mask = (1ULL << shift)\
    \ - 1;\n            if (y >> shift) {\n                ull v00 = _rec(x & mask,\
    \ y & mask);\n                ull v01 = _rec(x & mask, y >> shift);\n        \
    \        ull v10 = _rec(x >> shift, y & mask);\n                ull v11 = _rec(x\
    \ >> shift, y >> shift);\n                return v00 ^ ((v01 ^ v10 ^ v11) << shift)\
    \ ^ _rec(v11, 1ULL << (shift - 1));\n            } else if (x >> shift) {\n  \
    \              return (_rec(x >> shift, y) << shift) ^ _rec(x & mask, y);\n  \
    \          }\n        }\n    }\n    Nimber operator*(const Nimber &x) const {\n\
    \        ull ret = 0;\n        for (int d = 0; d < 8; ++d) {\n            for\
    \ (int e = 0; e < 8; ++e) {\n                ret ^= precalc[d][e][small_table[(v\
    \ >> (d * 8)) & 255][(x.v >> (e * 8)) & 255]];\n            }\n        }\n   \
    \     return Nimber(ret);\n    }\n    Nimber &operator*=(const Nimber &x) { return\
    \ *this = *this * x; }\n};\n\nconst std::array<std::array<unsigned, 256>, 256>\
    \ Nimber::small_table = []() {\n    std::array<std::array<unsigned, 256>, 256>\
    \ ret;\n    for (int i = 0; i < 256; ++i) {\n        for (int j = 0; j < 256;\
    \ ++j) ret[i][j] = _rec(i, j);\n    }\n    return ret;\n}();\nconst std::array<std::array<std::array<unsigned\
    \ long long, 256>, 8>, 8> Nimber::precalc = []() {\n    std::array<std::array<std::array<unsigned\
    \ long long, 256>, 8>, 8> ret;\n    for (int d = 0; d < 8; ++d) {\n        for\
    \ (int e = 0; e < 8; ++e) {\n            ull p = _rec(1ULL << (8 * d), 1ULL <<\
    \ (8 * e));\n            for (int i = 0; i < 256; ++i) ret[d][e][i] = _rec(p,\
    \ i);\n        }\n    }\n    return ret;\n}();\n"
  dependsOn: []
  isVerificationFile: false
  path: number/nimber.hpp
  requiredBy: []
  timestamp: '2022-10-30 13:35:32+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - unionfind/test/potentialized_unionfind_F2.yuki1420.test.cpp
  - number/test/nimber.test.cpp
documentation_of: number/nimber.hpp
layout: document
title: "Nimber, Nim product \uFF08\u30CB\u30E0\u6570\uFF0C$\\mathbb{F}_{2^{64}}$\uFF09"
---

Nimber の実装．以下の実装方針は [yosupo さんの実装](https://judge.yosupo.jp/submission/4542) から学んだもの．

Nimber は非負整数として表されるが，特殊な和 $\oplus$ （実は bitwise xor 演算）と積 $\otimes$ が定義され，特に以下の性質を満たす：

- 交換・結合法則を満たす．
  - 特に，$2^{2^n}$ 未満のニム数全体はあるガロア体と同型．
- 種数 2．すなわち $x \oplus x = 0$ が常に成立．
- $x \otimes 2^{2^n} = x 2^{2^n} \, (x < 2^{2^n})$
- $2^{2^n} \otimes 2^{2^n} = (3/2) 2^{2^n}$

## Nim product の計算

本コードは，適切な前計算のもと 64 bit nimber 同士の乗算を効率的に行う．

本コードはまず以下の値を前計算する．

- $a \otimes b \, (0 \le a, b < 2^8)$
- $2^{8i} \otimes 2^{8j} \otimes k \, (0 \le i, j < 8, 0 \le k < 2^8)$

一般の $\mathbb{F}\_{2^{64}}$ 上の元 $x$, $y$ の積は，

$\displaystyle
x \otimes y = \left(\bigoplus\_{i=0}^7 2^{8i} \otimes x\_i \right) \otimes \left(\bigoplus\_{j=0}^7 2^{8j} \otimes y\_j \right)$

と 8 bit 毎に分解してこれを展開し，

$\displaystyle
\bigoplus\_{i, j} 2^{8i} \otimes 2^{8j} \otimes (x\_i \otimes y\_j)$

と整理することで，前計算の結果を用いて計算できる．

## 問題例

- [Library Checker: Nim Product](https://judge.yosupo.jp/problem/nim_product_64)

## 参考文献・リンク

- [Nimber - Wikipedia](https://en.wikipedia.org/wiki/Nimber)
- [Nim product - kyopro_friends’ diary](https://kyopro-friends.hatenablog.com/entry/2020/04/07/195850)
- [Library Checker](https://judge.yosupo.jp/submission/4542) yosupo さんの実装．
