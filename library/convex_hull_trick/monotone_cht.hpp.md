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


# :warning: convex_hull_trick/monotone_cht.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#a1f2c13e39c190602cc1599f47ad6179">convex_hull_trick</a>
* <a href="{{ site.github.repository_url }}/blob/master/convex_hull_trick/monotone_cht.hpp">View this file on GitHub</a>
    - Last commit date: 2020-06-09 22:15:57+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cassert>
#include <deque>
#include <utility>

// CUT begin
// Convex Hull Trick for monotone increasing queries, monotone decreasing slopes
// Each operation is amortized O(1)
// - add_line(a, b): Add `y = ax + b`, a must be monotone decreasing (if is_minimizer == true) / increasing (otherwise)
// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone increasing (if is_minimizer == true) / decreasing (otherwise)
// - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be monotone increasing FOR BOTH CASES.
// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s, x must be monotone increasing FOR BOTH CASES.
// Verified: <https://yukicoder.me/submissions/409156>
using T_CHT = long long int; // template<typename T_CHT>
struct MonotoneConvexHullTrick : std::deque<std::pair<T_CHT, T_CHT>> // (a, b) means `y = ax + b`
{
    using T_MP = __int128_t;
    bool is_minimizer; // If true, this instance calculates min. Otherwise, calculates max.
    MonotoneConvexHullTrick(bool is_minimizer) : is_minimizer(is_minimizer) {}
    void add_line(T_CHT a, T_CHT b) {  // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        assert(this->empty() or this->back().first > a);
        while (this->size() > 1u) {
            int sz = this->size();
            T_MP l = (T_MP)(this->back().second - (*this)[sz - 2].second) * (this->back().first - a); // Overflow might occur here.
            T_MP r = (T_MP)(b - this->back().second) * ((*this)[sz - 2].first - this->back().first);
            if (l < r) break;
            this->pop_back();
        }
        this->emplace_back(a, b);
    }
    T_CHT get(T_CHT x) { 
        while (this->size() > 1u and (*this)[0].first * x + (*this)[0].second >= (*this)[1].first * x + (*this)[1].second) {
            this->pop_front();
        }
        return ((*this)[0].first * x + (*this)[0].second) * (is_minimizer ? 1 : -1);
    }
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2 + b
    T_CHT parabola_get(T_CHT c, T_CHT x) { return get(x) + c * x * x; }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "convex_hull_trick/monotone_cht.hpp"
#include <cassert>
#include <deque>
#include <utility>

// CUT begin
// Convex Hull Trick for monotone increasing queries, monotone decreasing slopes
// Each operation is amortized O(1)
// - add_line(a, b): Add `y = ax + b`, a must be monotone decreasing (if is_minimizer == true) / increasing (otherwise)
// - add_convex_parabola(c, a, b): Add `y = c(x - a)^2 + b`, c is constant, a is monotone increasing (if is_minimizer == true) / decreasing (otherwise)
// - get(x): Calculate min/max. value of `y = ax + b`'s at point x, x must be monotone increasing FOR BOTH CASES.
// - parabola_get(c, x): Caclculate min/max. value of `y = c(x - a)^2 + b`'s, x must be monotone increasing FOR BOTH CASES.
// Verified: <https://yukicoder.me/submissions/409156>
using T_CHT = long long int; // template<typename T_CHT>
struct MonotoneConvexHullTrick : std::deque<std::pair<T_CHT, T_CHT>> // (a, b) means `y = ax + b`
{
    using T_MP = __int128_t;
    bool is_minimizer; // If true, this instance calculates min. Otherwise, calculates max.
    MonotoneConvexHullTrick(bool is_minimizer) : is_minimizer(is_minimizer) {}
    void add_line(T_CHT a, T_CHT b) {  // Add y = ax + b
        if (!is_minimizer) a = -a, b = -b;
        assert(this->empty() or this->back().first > a);
        while (this->size() > 1u) {
            int sz = this->size();
            T_MP l = (T_MP)(this->back().second - (*this)[sz - 2].second) * (this->back().first - a); // Overflow might occur here.
            T_MP r = (T_MP)(b - this->back().second) * ((*this)[sz - 2].first - this->back().first);
            if (l < r) break;
            this->pop_back();
        }
        this->emplace_back(a, b);
    }
    T_CHT get(T_CHT x) { 
        while (this->size() > 1u and (*this)[0].first * x + (*this)[0].second >= (*this)[1].first * x + (*this)[1].second) {
            this->pop_front();
        }
        return ((*this)[0].first * x + (*this)[0].second) * (is_minimizer ? 1 : -1);
    }
    void add_convex_parabola(T_CHT c, T_CHT a, T_CHT b) { add_line(c * a * (-2), c * a * a + b); } // Add y = c(x - a)^2 + b
    T_CHT parabola_get(T_CHT c, T_CHT x) { return get(x) + c * x * x; }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

