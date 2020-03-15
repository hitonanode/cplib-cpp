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


# :heavy_check_mark: random/xorshift.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7ddf32e17a6ac5ce04a8ecbf782ca509">random</a>
* <a href="{{ site.github.repository_url }}/blob/master/random/xorshift.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/random/test/rolling_hash_w_modint.test.cpp.html">random/test/rolling_hash_w_modint.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <cstdint>

// CUT begin
uint32_t rand_int() // XorShift random integer generator
{
    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
double rand_double() { return (double)rand_int() / UINT32_MAX; }

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "random/xorshift.hpp"
#include <cstdint>

// CUT begin
uint32_t rand_int() // XorShift random integer generator
{
    static uint32_t x = 123456789, y = 362436069, z = 521288629, w = 88675123;
    uint32_t t = x ^ (x << 11);
    x = y;
    y = z;
    z = w;
    return w = (w ^ (w >> 19)) ^ (t ^ (t >> 8));
}
double rand_double() { return (double)rand_int() / UINT32_MAX; }

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

