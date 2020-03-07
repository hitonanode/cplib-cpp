---
layout: default
---

<!-- mathjax config similar to math.stackexchange -->
<script type="text/javascript" async
  src="https://cdnjs.cloudflare.com/ajax/libs/mathjax/2.7.5/MathJax.js?config=TeX-MML-AM_CHTML">
</script>
<script type="text/x-mathjax-config">
  MathJax.Hub.Config({
    TeX: { equationNumbers: { autoNumber: "AMS" }},
    tex2jax: {
      inlineMath: [ ['$','$'] ],
      processEscapes: true
    },
    "HTML-CSS": { matchFontHeight: false },
    displayAlign: "left",
    displayIndent: "2em"
  });
</script>

<script type="text/javascript" src="https://cdnjs.cloudflare.com/ajax/libs/jquery/3.4.1/jquery.min.js"></script>
<script src="https://cdn.jsdelivr.net/npm/jquery-balloon-js@1.1.2/jquery.balloon.min.js" integrity="sha256-ZEYs9VrgAeNuPvs15E39OsyOJaIkXEEt10fzxJ20+2I=" crossorigin="anonymous"></script>
<script type="text/javascript" src="../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../assets/css/copy-button.css" />


# :warning: rational/rational_number.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#086ac53f0f2847a22b2a7364bcf50206">rational</a>
* <a href="{{ site.github.repository_url }}/blob/master/rational/rational_number.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <iostream>

// CUT begin
// Rational number + {infinity(1 / 0), -infiity(-1 / 0)} （有理数）
struct Rational {
    using Int = long long int; // __int128
    Int num, den;
    static Int my_gcd(Int a, Int b) {
        // return __gcd(a, b);
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (a and b) {
            if (a > b) a %= b;
            else b %= a;
        }
        return a + b;
    }
    Rational(Int num = 0, Int den = 1) : num(num), den(den) { normalize(); }
    void normalize() { // reduction and making denominator nonnegative
        Int g = my_gcd(num, den); num /= g, den /= g;
        if (den < 0) num = -num, den = -den;
    }
    Rational operator+(const Rational &r) const { return Rational(num * r.den + den * r.num, den * r.den); }
    Rational operator-(const Rational &r) const { return Rational(num * r.den - den * r.num, den * r.den); }
    Rational operator*(const Rational &r) const { return Rational(num * r.num, den * r.den); }
    Rational operator/(const Rational &r) const { return Rational(num * r.den, den * r.num); }
    Rational &operator+=(const Rational &r) { return *this = *this + r; }
    Rational &operator-=(const Rational &r) { return *this = *this - r; }
    Rational &operator*=(const Rational &r) { return *this = *this * r; }
    Rational &operator/=(const Rational &r) { return *this = *this / r; }
    Rational operator-() const { return Rational(-num, den); }
    Rational abs() const { return Rational(num > 0 ? num : -num, den); }
    bool operator==(const Rational &r) const { return num == r.num and den == r.den; }
    bool operator!=(const Rational &r) const { return num != r.num or den != r.den; }
    bool operator<(const Rational &r) const {
        if (den == 0 and r.den == 0) return num < r.num;
        else if (den == 0) return num < 0;
        else if (r.den == 0) return r.num > 0;
        else return num * r.den < den * r.num;
    }
    bool operator<=(const Rational &r) const { return (*this == r) or (*this < r); }
    bool operator>(const Rational &r) const { return r < *this; }
    explicit operator double() const { return (double)num / (double)den; }
    explicit operator long double() const { return (long double)num / (long double)den; }
    friend std::ostream &operator<<(std::ostream &os, const Rational &x) { os << x.num << '/' << x.den; return os; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "rational/rational_number.hpp"
#include <iostream>

// CUT begin
// Rational number + {infinity(1 / 0), -infiity(-1 / 0)} （有理数）
struct Rational {
    using Int = long long int; // __int128
    Int num, den;
    static Int my_gcd(Int a, Int b) {
        // return __gcd(a, b);
        if (a < 0) a = -a;
        if (b < 0) b = -b;
        while (a and b) {
            if (a > b) a %= b;
            else b %= a;
        }
        return a + b;
    }
    Rational(Int num = 0, Int den = 1) : num(num), den(den) { normalize(); }
    void normalize() { // reduction and making denominator nonnegative
        Int g = my_gcd(num, den); num /= g, den /= g;
        if (den < 0) num = -num, den = -den;
    }
    Rational operator+(const Rational &r) const { return Rational(num * r.den + den * r.num, den * r.den); }
    Rational operator-(const Rational &r) const { return Rational(num * r.den - den * r.num, den * r.den); }
    Rational operator*(const Rational &r) const { return Rational(num * r.num, den * r.den); }
    Rational operator/(const Rational &r) const { return Rational(num * r.den, den * r.num); }
    Rational &operator+=(const Rational &r) { return *this = *this + r; }
    Rational &operator-=(const Rational &r) { return *this = *this - r; }
    Rational &operator*=(const Rational &r) { return *this = *this * r; }
    Rational &operator/=(const Rational &r) { return *this = *this / r; }
    Rational operator-() const { return Rational(-num, den); }
    Rational abs() const { return Rational(num > 0 ? num : -num, den); }
    bool operator==(const Rational &r) const { return num == r.num and den == r.den; }
    bool operator!=(const Rational &r) const { return num != r.num or den != r.den; }
    bool operator<(const Rational &r) const {
        if (den == 0 and r.den == 0) return num < r.num;
        else if (den == 0) return num < 0;
        else if (r.den == 0) return r.num > 0;
        else return num * r.den < den * r.num;
    }
    bool operator<=(const Rational &r) const { return (*this == r) or (*this < r); }
    bool operator>(const Rational &r) const { return r < *this; }
    explicit operator double() const { return (double)num / (double)den; }
    explicit operator long double() const { return (long double)num / (long double)den; }
    friend std::ostream &operator<<(std::ostream &os, const Rational &x) { os << x.num << '/' << x.den; return os; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

