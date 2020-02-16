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


# :warning: random/custom_hash.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#7ddf32e17a6ac5ce04a8ecbf782ca509">random</a>
* <a href="{{ site.github.repository_url }}/blob/master/random/custom_hash.hpp">View this file on GitHub</a>
    - Last commit date: 2019-08-17 13:05:13+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <chrono>
#include <cstdlib>
using namespace std;

struct custom_hash
{
    // <https://codeforces.com/blog/entry/62393>
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


// Usage
#include <unordered_map>
unordered_map<int, int, custom_hash> robust_unordered_map;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, null_type, custom_hash> robust_hash_table; // fast unordered_set / unordered_map

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "random/custom_hash.hpp"
#include <chrono>
#include <cstdlib>
using namespace std;

struct custom_hash
{
    // <https://codeforces.com/blog/entry/62393>
    static uint64_t splitmix64(uint64_t x)
    {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const
    {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};


// Usage
#include <unordered_map>
unordered_map<int, int, custom_hash> robust_unordered_map;

#include <ext/pb_ds/assoc_container.hpp>
using namespace __gnu_pbds;
gp_hash_table<int, null_type, custom_hash> robust_hash_table; // fast unordered_set / unordered_map

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

