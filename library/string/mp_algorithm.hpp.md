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


# :heavy_check_mark: string/mp_algorithm.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/mp_algorithm.hpp">View this file on GitHub</a>
    - Last commit date: 2019-08-12 12:36:28+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/string/test/manacher_mp.test.cpp.html">string/test/manacher_mp.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <string>
#include <vector>


std::vector<int> mp_algorithm(std::string s) {
    int N = s.length();
    std::vector<int> ret(N + 1, -1);
    int j = -1;
    for (int i = 0; i < N;  i++) {
        while (j >= 0 and s[i] != s[j]) j = ret[j];
        ret[i + 1] = ++j;
    }
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/mp_algorithm.hpp"
#include <string>
#include <vector>


std::vector<int> mp_algorithm(std::string s) {
    int N = s.length();
    std::vector<int> ret(N + 1, -1);
    int j = -1;
    for (int i = 0; i < N;  i++) {
        while (j >= 0 and s[i] != s[j]) j = ret[j];
        ret[i + 1] = ++j;
    }
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

