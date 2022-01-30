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
    - https://atcoder.jp/contests/abc229/submissions/28887690
  bundledCode: "#line 1 \"number/dyadic_rational.hpp\"\n#include <cassert>\n#include\
    \ <limits>\n#include <type_traits>\n\n// Dyadic rational, surreal numbers \uFF08\
    \u8D85\u73FE\u5B9F\u6570\uFF09\n// https://atcoder.jp/contests/abc229/submissions/28887690\n\
    template <class Int, class Uint = unsigned long long> struct DyadicRational {\n\
    \    Int integ; // \u6574\u6570\u90E8\u5206\n    Uint frac; // \u5C0F\u6570\u90E8\
    \u5206\u306E\u5206\u5B50\n\n    static constexpr int FracLen = std::numeric_limits<Uint>::digits\
    \ - 1; // 2^63\n    static constexpr Uint denom = Uint(1) << FracLen;        \
    \             // \u5C0F\u6570\u90E8\u5206\u306E\u5206\u6BCD\n\n    DyadicRational(Int\
    \ x = 0) : integ(x), frac(0) {\n        static_assert(\n            0 < FracLen\
    \ and FracLen < std::numeric_limits<Uint>::digits, \"FracLen value error\");\n\
    \        static_assert(std::is_signed<Int>::value == true, \"Int must be signed\"\
    );\n    }\n    static DyadicRational _construct(Int x, Uint frac_) {\n       \
    \ DyadicRational ret(x);\n        ret.frac = frac_;\n        return ret;\n   \
    \ }\n    double to_double() const { return integ + double(frac) / denom; }\n\n\
    \    // static DyadicRational from_rational(Int num, int lg_den);\n    bool operator==(const\
    \ DyadicRational &r) const { return integ == r.integ and frac == r.frac; }\n \
    \   bool operator!=(const DyadicRational &r) const { return integ != r.integ or\
    \ frac != r.frac; }\n    bool operator<(const DyadicRational &r) const {\n   \
    \     return integ != r.integ ? integ < r.integ : frac < r.frac;\n    }\n    bool\
    \ operator<=(const DyadicRational &r) const { return (*this == r) or (*this <\
    \ r); }\n    bool operator>(const DyadicRational &r) const { return r < *this;\
    \ }\n    bool operator>=(const DyadicRational &r) const { return r <= *this; }\n\
    \n    DyadicRational operator+(const DyadicRational &r) const {\n        auto\
    \ i = integ + r.integ;\n        auto f = frac + r.frac;\n        if (f >= denom)\
    \ ++i, f -= denom; // overflow\n        return DyadicRational::_construct(i, f);\n\
    \    }\n    DyadicRational operator-(const DyadicRational &r) const {\n      \
    \  auto i = integ - r.integ;\n        auto f = frac - r.frac;\n        if (f >\
    \ denom) --i, f += denom; // overflow\n        return DyadicRational::_construct(i,\
    \ f);\n    }\n    DyadicRational operator-() const { return DyadicRational() -\
    \ *this; }\n    DyadicRational &operator+=(const DyadicRational &r) { return *this\
    \ = *this + r; }\n\n    DyadicRational right() const {\n        if (frac == 0)\
    \ {\n            if (integ >= 0) {\n                return DyadicRational(integ\
    \ + 1);\n            } else {\n                return DyadicRational::_construct(integ,\
    \ Uint(1) << (FracLen - 1));\n            }\n        }\n        int d = __builtin_ctzll(frac);\n\
    \        return DyadicRational::_construct(integ, frac ^ (Uint(1) << (d - 1)));\n\
    \    }\n    DyadicRational left() const {\n        if (frac == 0) {\n        \
    \    if (integ <= 0) {\n                return DyadicRational(integ - 1);\n  \
    \          } else {\n                return DyadicRational::_construct(integ -\
    \ 1, Uint(1) << (FracLen - 1));\n            }\n        }\n        int d = __builtin_ctzll(frac);\n\
    \        return DyadicRational::_construct(integ, frac ^ (Uint(3) << (d - 1)));\n\
    \    }\n\n    // Surreal number { l | r }\n    static DyadicRational surreal(const\
    \ DyadicRational &l, const DyadicRational &r) {\n        assert(l < r);\n    \
    \    DyadicRational x(0);\n        if (l.integ > 0) x = DyadicRational(l.integ);\n\
    \        if (r.integ < 0) x = DyadicRational(r.integ);\n        while (true) {\n\
    \            if (x <= l) {\n                x = x.right();\n            } else\
    \ if (x >= r) {\n                x = x.left();\n            } else {\n       \
    \         break;\n            }\n        }\n        return x;\n    }\n    template\
    \ <class OStream> friend OStream &operator<<(OStream &os, const DyadicRational\
    \ &x) {\n        return os << x.to_double();\n    }\n};\n// using dyrational =\
    \ DyadicRational<long long>;\n"
  code: "#include <cassert>\n#include <limits>\n#include <type_traits>\n\n// Dyadic\
    \ rational, surreal numbers \uFF08\u8D85\u73FE\u5B9F\u6570\uFF09\n// https://atcoder.jp/contests/abc229/submissions/28887690\n\
    template <class Int, class Uint = unsigned long long> struct DyadicRational {\n\
    \    Int integ; // \u6574\u6570\u90E8\u5206\n    Uint frac; // \u5C0F\u6570\u90E8\
    \u5206\u306E\u5206\u5B50\n\n    static constexpr int FracLen = std::numeric_limits<Uint>::digits\
    \ - 1; // 2^63\n    static constexpr Uint denom = Uint(1) << FracLen;        \
    \             // \u5C0F\u6570\u90E8\u5206\u306E\u5206\u6BCD\n\n    DyadicRational(Int\
    \ x = 0) : integ(x), frac(0) {\n        static_assert(\n            0 < FracLen\
    \ and FracLen < std::numeric_limits<Uint>::digits, \"FracLen value error\");\n\
    \        static_assert(std::is_signed<Int>::value == true, \"Int must be signed\"\
    );\n    }\n    static DyadicRational _construct(Int x, Uint frac_) {\n       \
    \ DyadicRational ret(x);\n        ret.frac = frac_;\n        return ret;\n   \
    \ }\n    double to_double() const { return integ + double(frac) / denom; }\n\n\
    \    // static DyadicRational from_rational(Int num, int lg_den);\n    bool operator==(const\
    \ DyadicRational &r) const { return integ == r.integ and frac == r.frac; }\n \
    \   bool operator!=(const DyadicRational &r) const { return integ != r.integ or\
    \ frac != r.frac; }\n    bool operator<(const DyadicRational &r) const {\n   \
    \     return integ != r.integ ? integ < r.integ : frac < r.frac;\n    }\n    bool\
    \ operator<=(const DyadicRational &r) const { return (*this == r) or (*this <\
    \ r); }\n    bool operator>(const DyadicRational &r) const { return r < *this;\
    \ }\n    bool operator>=(const DyadicRational &r) const { return r <= *this; }\n\
    \n    DyadicRational operator+(const DyadicRational &r) const {\n        auto\
    \ i = integ + r.integ;\n        auto f = frac + r.frac;\n        if (f >= denom)\
    \ ++i, f -= denom; // overflow\n        return DyadicRational::_construct(i, f);\n\
    \    }\n    DyadicRational operator-(const DyadicRational &r) const {\n      \
    \  auto i = integ - r.integ;\n        auto f = frac - r.frac;\n        if (f >\
    \ denom) --i, f += denom; // overflow\n        return DyadicRational::_construct(i,\
    \ f);\n    }\n    DyadicRational operator-() const { return DyadicRational() -\
    \ *this; }\n    DyadicRational &operator+=(const DyadicRational &r) { return *this\
    \ = *this + r; }\n\n    DyadicRational right() const {\n        if (frac == 0)\
    \ {\n            if (integ >= 0) {\n                return DyadicRational(integ\
    \ + 1);\n            } else {\n                return DyadicRational::_construct(integ,\
    \ Uint(1) << (FracLen - 1));\n            }\n        }\n        int d = __builtin_ctzll(frac);\n\
    \        return DyadicRational::_construct(integ, frac ^ (Uint(1) << (d - 1)));\n\
    \    }\n    DyadicRational left() const {\n        if (frac == 0) {\n        \
    \    if (integ <= 0) {\n                return DyadicRational(integ - 1);\n  \
    \          } else {\n                return DyadicRational::_construct(integ -\
    \ 1, Uint(1) << (FracLen - 1));\n            }\n        }\n        int d = __builtin_ctzll(frac);\n\
    \        return DyadicRational::_construct(integ, frac ^ (Uint(3) << (d - 1)));\n\
    \    }\n\n    // Surreal number { l | r }\n    static DyadicRational surreal(const\
    \ DyadicRational &l, const DyadicRational &r) {\n        assert(l < r);\n    \
    \    DyadicRational x(0);\n        if (l.integ > 0) x = DyadicRational(l.integ);\n\
    \        if (r.integ < 0) x = DyadicRational(r.integ);\n        while (true) {\n\
    \            if (x <= l) {\n                x = x.right();\n            } else\
    \ if (x >= r) {\n                x = x.left();\n            } else {\n       \
    \         break;\n            }\n        }\n        return x;\n    }\n    template\
    \ <class OStream> friend OStream &operator<<(OStream &os, const DyadicRational\
    \ &x) {\n        return os << x.to_double();\n    }\n};\n// using dyrational =\
    \ DyadicRational<long long>;\n"
  dependsOn: []
  isVerificationFile: false
  path: number/dyadic_rational.hpp
  requiredBy: []
  timestamp: '2022-01-30 12:05:36+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: number/dyadic_rational.hpp
layout: document
title: "Dyadic rational, surreal number \uFF08\u4E8C\u9032\u5206\u6570\u30FB\u56FA\
  \u5B9A\u5C0F\u6570\u70B9\u6570\uFF0CConway \u306E\u69CB\u6210\uFF09"
---

分母が二冪の有理数 `DyadicRational<Int, Uint = unsigned long long>` の実装，また超現実数の構成法に基づく $\\{ l \mid r \\}$ の計算．組合せゲーム理論などへの応用がある．

`Int` が整数部分を表すための符号付整数型で `int` や `long long` の利用を想定，`Uint` が小数部分を表すための符号なし整数型で `unsigned` や `unsigned long long` の利用を想定（`__uint128_t` も動くかもしれない）．メンバ変数 `integ`, `frac` がそれぞれ整数部分と小数部分に対応し，
$$
x = \mathrm{integ} + \frac{\mathrm{frac}}{2^\mathrm{FracLen}}
$$
がこのクラスのインスタンスが表す有理数 $x$ である．
実装の制約上分母のオーダーは（`Uint = unsigned long long` の場合）$2^{63}$ が上限となる．

## 使用方法

### `DyadicRational<Int>(Int x)`

コンストラクタ．整数 `x` に対応する元を生成する．

### `double to_double()`

インスタンスが表す有理数 $x$ を `double` 型に変換．

### `DyadicRational<Int> right()`

[Surreal number （超現実数）の構成過程を表す木](https://en.wikipedia.org/wiki/Surreal_number#/media/File:Surreal_number_tree.svg) において，現在の値 $x$ の右側の子の値を返す．

### `DyadicRational<Int> left()`

`right()` とは逆に，現在の値 $x$ の左側の子の値を返す．

### `DyadicRational<Int> DyadicRational<Int>::surreal(DyadicRational<Int> l, DyadicRational<Int> r)`

$l < r$ を満たす二進分数 $l$, $r$ について，$l < x < r$ を満たし surreal number の構成過程を表す木で根（$0$）に最も近い要素（Conway の記法に基づくと $\\{ l \mid r \\}$）の値を返す．$l < r$ を満たさない場合 runtime error となる．

現在は根から一歩ずつ `right()` または `left()` で探索していく実装になっているが，場合分けと bit 演算を頑張れば $O(1)$ になると思われる．

## 問題例

- [AtCoder Beginner Contest 229 H - Advance or Eat](https://atcoder.jp/contests/abc229/tasks/abc229_h)

### リンク

- [組合せゲーム理論入門(1)](http://www.ivis.co.jp/text/20111102.pdf) 組合せゲーム理論の観点からの解説．
- [解説 - NECプログラミングコンテスト2021(AtCoder Beginner Contest 229)](https://atcoder.jp/contests/abc229/editorial/2977) 非不偏ゲーム（Partisan Game）の問題例とその解き方．
  - [提出 #27486895 - NECプログラミングコンテスト2021(AtCoder Beginner Contest 229)](https://atcoder.jp/contests/abc229/submissions/27486895) Nyaan さんの実装．
