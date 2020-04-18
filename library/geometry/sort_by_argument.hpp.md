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


# :heavy_check_mark: geometry/sort_by_argument.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#ed7daeb157cd9b31e53896ad3c771a26">geometry</a>
* <a href="{{ site.github.repository_url }}/blob/master/geometry/sort_by_argument.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 18:32:38+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/geometry/test/sort_by_argument.test.cpp.html">geometry/test/sort_by_argument.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cmath>

// CUT begin
// Point on grid, sortable by its argument
struct P
{
    constexpr static double eps = 1e-2;
    long long X, Y;
    double theta;
    P() = default;
    P(long long x, long long y) : X(x), Y(y), theta(std::atan2(y, x)) {}
    bool operator<(const P &r) const
    {
        double b = theta - r.theta;
        return std::abs(b) > eps ? (b < 0) : (X * r.Y > r.X * Y);
    }
    bool operator==(const P &r) const
    {
        return std::abs(theta - r.theta) < eps and X * r.Y == r.X * Y;
    }
    void rotate_pi() {
        theta += M_PI;
        X *= -1;
        Y *= -1;
    }
};

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "geometry/sort_by_argument.hpp"
#include <cmath>

// CUT begin
// Point on grid, sortable by its argument
struct P
{
    constexpr static double eps = 1e-2;
    long long X, Y;
    double theta;
    P() = default;
    P(long long x, long long y) : X(x), Y(y), theta(std::atan2(y, x)) {}
    bool operator<(const P &r) const
    {
        double b = theta - r.theta;
        return std::abs(b) > eps ? (b < 0) : (X * r.Y > r.X * Y);
    }
    bool operator==(const P &r) const
    {
        return std::abs(theta - r.theta) < eps and X * r.Y == r.X * Y;
    }
    void rotate_pi() {
        theta += M_PI;
        X *= -1;
        Y *= -1;
    }
};

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

