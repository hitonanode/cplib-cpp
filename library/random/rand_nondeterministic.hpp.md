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


# :heavy_check_mark: random/rand_nondeterministic.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7ddf32e17a6ac5ce04a8ecbf782ca509">random</a>
* <a href="{{ site.github.repository_url }}/blob/master/random/rand_nondeterministic.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Required by

* :heavy_check_mark: <a href="../linear_algebra_matrix/det_of_sparse_matrix.hpp.html">linear_algebra_matrix/det_of_sparse_matrix.hpp</a>


## Verified with

* :heavy_check_mark: <a href="../../verify/linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp.html">linear_algebra_matrix/test/det_of_sparse_matrix.test.cpp</a>
* :heavy_check_mark: <a href="../../verify/random/test/rolling_hash.test.cpp.html">random/test/rolling_hash.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <chrono>
#include <random>
using namespace std;

// CUT begin
struct rand_int_
{
    using lint = long long;
    mt19937 mt;
    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
    lint operator()(lint l, lint r) {
        uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
} rnd;

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "random/rand_nondeterministic.hpp"
#include <chrono>
#include <random>
using namespace std;

// CUT begin
struct rand_int_
{
    using lint = long long;
    mt19937 mt;
    rand_int_() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}
    lint operator()(lint x) { return this->operator()(0, x); } // [0, x)
    lint operator()(lint l, lint r) {
        uniform_int_distribution<lint> d(l, r - 1);
        return d(mt);
    }
} rnd;

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

