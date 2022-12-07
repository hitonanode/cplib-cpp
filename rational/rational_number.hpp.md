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
    - https://contest.yandex.com/contest/42710/problems/K
  bundledCode: "#line 2 \"rational/rational_number.hpp\"\n#include <limits>\n\n//\
    \ Rational number + {infinity(1 / 0), -infiity(-1 / 0), nan(0 / 0)} \uFF08\u6709\
    \u7406\u6570\uFF09\n// Do not compare any number with nan\n// Verified: Yandex\
    \ Cup 2022 Final E https://contest.yandex.com/contest/42710/problems/K\ntemplate\
    \ <class Int, bool AlwaysReduce = false> struct Rational {\n    Int num, den;\n\
    \    static constexpr Int my_gcd(Int a, Int b) {\n        // return __gcd(a, b);\n\
    \        if (a < 0) a = -a;\n        if (b < 0) b = -b;\n        while (a and\
    \ b) {\n            if (a > b)\n                a %= b;\n            else\n  \
    \              b %= a;\n        }\n        return a + b;\n    }\n    constexpr\
    \ Rational(Int num = 0, Int den = 1) : num(num), den(den) { normalize(); }\n \
    \   constexpr void normalize() noexcept {\n        if constexpr (AlwaysReduce)\
    \ { // reduction\n            Int g = my_gcd(num, den);\n            if (g) num\
    \ /= g, den /= g;\n        } else {\n            if (den == 0) {\n           \
    \     if (num > 1) num = 1;\n                if (num < -1) num = -1;\n       \
    \     }\n        }\n        if (den < 0) num = -num, den = -den; // denominator\
    \ >= 0\n    }\n    constexpr Rational operator+(const Rational &r) const noexcept\
    \ {\n        if (!den and !r.den) return Rational(num + r.num, den);\n       \
    \ return Rational(num * r.den + den * r.num, den * r.den);\n    }\n    constexpr\
    \ Rational operator-(const Rational &r) const noexcept {\n        if (!den and\
    \ !r.den) return Rational(num - r.num, den);\n        return Rational(num * r.den\
    \ - den * r.num, den * r.den);\n    }\n    constexpr Rational operator*(const\
    \ Rational &r) const noexcept {\n        return Rational(num * r.num, den * r.den);\n\
    \    }\n    constexpr Rational operator/(const Rational &r) const noexcept {\n\
    \        return Rational(num * r.den, den * r.num);\n    }\n    constexpr Rational\
    \ &operator+=(const Rational &r) noexcept { return *this = *this + r; }\n    constexpr\
    \ Rational &operator-=(const Rational &r) noexcept { return *this = *this - r;\
    \ }\n    constexpr Rational &operator*=(const Rational &r) noexcept { return *this\
    \ = *this * r; }\n    constexpr Rational &operator/=(const Rational &r) noexcept\
    \ { return *this = *this / r; }\n    constexpr Rational operator-() const noexcept\
    \ { return Rational(-num, den); }\n    constexpr Rational abs() const noexcept\
    \ { return Rational(num > 0 ? num : -num, den); }\n    constexpr bool operator==(const\
    \ Rational &r) const noexcept {\n        if constexpr (AlwaysReduce) {\n     \
    \       return num == r.num and den == r.den;\n        } else {\n            return\
    \ num * r.den == r.num * den;\n        }\n    }\n    constexpr bool operator!=(const\
    \ Rational &r) const noexcept { return !(*this == r); }\n    constexpr bool operator<(const\
    \ Rational &r) const noexcept {\n        if (den == 0 and r.den == 0)\n      \
    \      return num < r.num;\n        else if (den == 0)\n            return num\
    \ < 0;\n        else if (r.den == 0)\n            return r.num > 0;\n        else\n\
    \            return num * r.den < den * r.num;\n    }\n    constexpr bool operator<=(const\
    \ Rational &r) const noexcept {\n        return (*this == r) or (*this < r);\n\
    \    }\n    constexpr bool operator>(const Rational &r) const noexcept { return\
    \ r < *this; }\n    constexpr bool operator>=(const Rational &r) const noexcept\
    \ {\n        return (r == *this) or (r < *this);\n    }\n    constexpr explicit\
    \ operator double() const noexcept { return (double)num / (double)den; }\n   \
    \ constexpr explicit operator long double() const noexcept {\n        return (long\
    \ double)num / (long double)den;\n    }\n    template <class OStream> constexpr\
    \ friend OStream &operator<<(OStream &os, const Rational &x) {\n        return\
    \ os << x.num << '/' << x.den;\n    }\n};\n\ntemplate <class Int> struct std::numeric_limits<Rational<Int,\
    \ false>> {\n    static constexpr Rational<Int, false> max() noexcept {\n    \
    \    return std::numeric_limits<Int>::max();\n    }\n    static constexpr Rational<Int,\
    \ false> min() noexcept {\n        return std::numeric_limits<Int>::min();\n \
    \   }\n    static constexpr Rational<Int, false> lowest() noexcept {\n       \
    \ return std::numeric_limits<Int>::lowest();\n    }\n};\n"
  code: "#pragma once\n#include <limits>\n\n// Rational number + {infinity(1 / 0),\
    \ -infiity(-1 / 0), nan(0 / 0)} \uFF08\u6709\u7406\u6570\uFF09\n// Do not compare\
    \ any number with nan\n// Verified: Yandex Cup 2022 Final E https://contest.yandex.com/contest/42710/problems/K\n\
    template <class Int, bool AlwaysReduce = false> struct Rational {\n    Int num,\
    \ den;\n    static constexpr Int my_gcd(Int a, Int b) {\n        // return __gcd(a,\
    \ b);\n        if (a < 0) a = -a;\n        if (b < 0) b = -b;\n        while (a\
    \ and b) {\n            if (a > b)\n                a %= b;\n            else\n\
    \                b %= a;\n        }\n        return a + b;\n    }\n    constexpr\
    \ Rational(Int num = 0, Int den = 1) : num(num), den(den) { normalize(); }\n \
    \   constexpr void normalize() noexcept {\n        if constexpr (AlwaysReduce)\
    \ { // reduction\n            Int g = my_gcd(num, den);\n            if (g) num\
    \ /= g, den /= g;\n        } else {\n            if (den == 0) {\n           \
    \     if (num > 1) num = 1;\n                if (num < -1) num = -1;\n       \
    \     }\n        }\n        if (den < 0) num = -num, den = -den; // denominator\
    \ >= 0\n    }\n    constexpr Rational operator+(const Rational &r) const noexcept\
    \ {\n        if (!den and !r.den) return Rational(num + r.num, den);\n       \
    \ return Rational(num * r.den + den * r.num, den * r.den);\n    }\n    constexpr\
    \ Rational operator-(const Rational &r) const noexcept {\n        if (!den and\
    \ !r.den) return Rational(num - r.num, den);\n        return Rational(num * r.den\
    \ - den * r.num, den * r.den);\n    }\n    constexpr Rational operator*(const\
    \ Rational &r) const noexcept {\n        return Rational(num * r.num, den * r.den);\n\
    \    }\n    constexpr Rational operator/(const Rational &r) const noexcept {\n\
    \        return Rational(num * r.den, den * r.num);\n    }\n    constexpr Rational\
    \ &operator+=(const Rational &r) noexcept { return *this = *this + r; }\n    constexpr\
    \ Rational &operator-=(const Rational &r) noexcept { return *this = *this - r;\
    \ }\n    constexpr Rational &operator*=(const Rational &r) noexcept { return *this\
    \ = *this * r; }\n    constexpr Rational &operator/=(const Rational &r) noexcept\
    \ { return *this = *this / r; }\n    constexpr Rational operator-() const noexcept\
    \ { return Rational(-num, den); }\n    constexpr Rational abs() const noexcept\
    \ { return Rational(num > 0 ? num : -num, den); }\n    constexpr bool operator==(const\
    \ Rational &r) const noexcept {\n        if constexpr (AlwaysReduce) {\n     \
    \       return num == r.num and den == r.den;\n        } else {\n            return\
    \ num * r.den == r.num * den;\n        }\n    }\n    constexpr bool operator!=(const\
    \ Rational &r) const noexcept { return !(*this == r); }\n    constexpr bool operator<(const\
    \ Rational &r) const noexcept {\n        if (den == 0 and r.den == 0)\n      \
    \      return num < r.num;\n        else if (den == 0)\n            return num\
    \ < 0;\n        else if (r.den == 0)\n            return r.num > 0;\n        else\n\
    \            return num * r.den < den * r.num;\n    }\n    constexpr bool operator<=(const\
    \ Rational &r) const noexcept {\n        return (*this == r) or (*this < r);\n\
    \    }\n    constexpr bool operator>(const Rational &r) const noexcept { return\
    \ r < *this; }\n    constexpr bool operator>=(const Rational &r) const noexcept\
    \ {\n        return (r == *this) or (r < *this);\n    }\n    constexpr explicit\
    \ operator double() const noexcept { return (double)num / (double)den; }\n   \
    \ constexpr explicit operator long double() const noexcept {\n        return (long\
    \ double)num / (long double)den;\n    }\n    template <class OStream> constexpr\
    \ friend OStream &operator<<(OStream &os, const Rational &x) {\n        return\
    \ os << x.num << '/' << x.den;\n    }\n};\n\ntemplate <class Int> struct std::numeric_limits<Rational<Int,\
    \ false>> {\n    static constexpr Rational<Int, false> max() noexcept {\n    \
    \    return std::numeric_limits<Int>::max();\n    }\n    static constexpr Rational<Int,\
    \ false> min() noexcept {\n        return std::numeric_limits<Int>::min();\n \
    \   }\n    static constexpr Rational<Int, false> lowest() noexcept {\n       \
    \ return std::numeric_limits<Int>::lowest();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: rational/rational_number.hpp
  requiredBy: []
  timestamp: '2022-12-07 22:29:54+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: rational/rational_number.hpp
layout: document
title: "Rational number \uFF08\u6709\u7406\u6570\uFF09"
---

分子と分母の値をそれぞれ整数型で持つ有理数の実装．

## 使用方法

```cpp
Rational<__int128, true> r1;  // true: 約分する
Rational<__int128, false> r2;  // false: 約分しない，CHT など四則演算を繰り返さない場合はこちらが高速でよい
```

## 問題例

- [Yandex Cup 2022 Algorithm Final E. Stepwise subsequence](https://contest.yandex.com/contest/42710/problems/K/) : 有理数で CHT する．
