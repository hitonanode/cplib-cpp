---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"rational/rational_number.hpp\"\n#include <iostream>\n\n\
    // CUT begin\n// Rational number + {infinity(1 / 0), -infiity(-1 / 0)} \uFF08\u6709\
    \u7406\u6570\uFF09\nstruct Rational {\n    using Int = long long int; // __int128\n\
    \    Int num, den;\n    static Int my_gcd(Int a, Int b) {\n        // return __gcd(a,\
    \ b);\n        if (a < 0) a = -a;\n        if (b < 0) b = -b;\n        while (a\
    \ and b) {\n            if (a > b)\n                a %= b;\n            else\n\
    \                b %= a;\n        }\n        return a + b;\n    }\n    Rational(Int\
    \ num = 0, Int den = 1) : num(num), den(den) { normalize(); }\n    void normalize()\
    \ { // reduction and making denominator nonnegative\n        Int g = my_gcd(num,\
    \ den);\n        num /= g, den /= g;\n        if (den < 0) num = -num, den = -den;\n\
    \    }\n    Rational operator+(const Rational &r) const { return Rational(num\
    \ * r.den + den * r.num, den * r.den); }\n    Rational operator-(const Rational\
    \ &r) const { return Rational(num * r.den - den * r.num, den * r.den); }\n   \
    \ Rational operator*(const Rational &r) const { return Rational(num * r.num, den\
    \ * r.den); }\n    Rational operator/(const Rational &r) const { return Rational(num\
    \ * r.den, den * r.num); }\n    Rational &operator+=(const Rational &r) { return\
    \ *this = *this + r; }\n    Rational &operator-=(const Rational &r) { return *this\
    \ = *this - r; }\n    Rational &operator*=(const Rational &r) { return *this =\
    \ *this * r; }\n    Rational &operator/=(const Rational &r) { return *this = *this\
    \ / r; }\n    Rational operator-() const { return Rational(-num, den); }\n   \
    \ Rational abs() const { return Rational(num > 0 ? num : -num, den); }\n    bool\
    \ operator==(const Rational &r) const { return num == r.num and den == r.den;\
    \ }\n    bool operator!=(const Rational &r) const { return num != r.num or den\
    \ != r.den; }\n    bool operator<(const Rational &r) const {\n        if (den\
    \ == 0 and r.den == 0)\n            return num < r.num;\n        else if (den\
    \ == 0)\n            return num < 0;\n        else if (r.den == 0)\n         \
    \   return r.num > 0;\n        else\n            return num * r.den < den * r.num;\n\
    \    }\n    bool operator<=(const Rational &r) const { return (*this == r) or\
    \ (*this < r); }\n    bool operator>(const Rational &r) const { return r < *this;\
    \ }\n    bool operator>=(const Rational &r) const { return (r == *this) or (r\
    \ < *this); }\n    explicit operator double() const { return (double)num / (double)den;\
    \ }\n    explicit operator long double() const { return (long double)num / (long\
    \ double)den; }\n    friend std::ostream &operator<<(std::ostream &os, const Rational\
    \ &x) { return os << x.num << '/' << x.den; }\n};\n"
  code: "#pragma once\n#include <iostream>\n\n// CUT begin\n// Rational number + {infinity(1\
    \ / 0), -infiity(-1 / 0)} \uFF08\u6709\u7406\u6570\uFF09\nstruct Rational {\n\
    \    using Int = long long int; // __int128\n    Int num, den;\n    static Int\
    \ my_gcd(Int a, Int b) {\n        // return __gcd(a, b);\n        if (a < 0) a\
    \ = -a;\n        if (b < 0) b = -b;\n        while (a and b) {\n            if\
    \ (a > b)\n                a %= b;\n            else\n                b %= a;\n\
    \        }\n        return a + b;\n    }\n    Rational(Int num = 0, Int den =\
    \ 1) : num(num), den(den) { normalize(); }\n    void normalize() { // reduction\
    \ and making denominator nonnegative\n        Int g = my_gcd(num, den);\n    \
    \    num /= g, den /= g;\n        if (den < 0) num = -num, den = -den;\n    }\n\
    \    Rational operator+(const Rational &r) const { return Rational(num * r.den\
    \ + den * r.num, den * r.den); }\n    Rational operator-(const Rational &r) const\
    \ { return Rational(num * r.den - den * r.num, den * r.den); }\n    Rational operator*(const\
    \ Rational &r) const { return Rational(num * r.num, den * r.den); }\n    Rational\
    \ operator/(const Rational &r) const { return Rational(num * r.den, den * r.num);\
    \ }\n    Rational &operator+=(const Rational &r) { return *this = *this + r; }\n\
    \    Rational &operator-=(const Rational &r) { return *this = *this - r; }\n \
    \   Rational &operator*=(const Rational &r) { return *this = *this * r; }\n  \
    \  Rational &operator/=(const Rational &r) { return *this = *this / r; }\n   \
    \ Rational operator-() const { return Rational(-num, den); }\n    Rational abs()\
    \ const { return Rational(num > 0 ? num : -num, den); }\n    bool operator==(const\
    \ Rational &r) const { return num == r.num and den == r.den; }\n    bool operator!=(const\
    \ Rational &r) const { return num != r.num or den != r.den; }\n    bool operator<(const\
    \ Rational &r) const {\n        if (den == 0 and r.den == 0)\n            return\
    \ num < r.num;\n        else if (den == 0)\n            return num < 0;\n    \
    \    else if (r.den == 0)\n            return r.num > 0;\n        else\n     \
    \       return num * r.den < den * r.num;\n    }\n    bool operator<=(const Rational\
    \ &r) const { return (*this == r) or (*this < r); }\n    bool operator>(const\
    \ Rational &r) const { return r < *this; }\n    bool operator>=(const Rational\
    \ &r) const { return (r == *this) or (r < *this); }\n    explicit operator double()\
    \ const { return (double)num / (double)den; }\n    explicit operator long double()\
    \ const { return (long double)num / (long double)den; }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const Rational &x) { return os << x.num << '/'\
    \ << x.den; }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: rational/rational_number.hpp
  requiredBy: []
  timestamp: '2020-11-18 20:25:12+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: rational/rational_number.hpp
layout: document
redirect_from:
- /library/rational/rational_number.hpp
- /library/rational/rational_number.hpp.html
title: rational/rational_number.hpp
---
