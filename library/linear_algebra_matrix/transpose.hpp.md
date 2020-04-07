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


# :warning: linear_algebra_matrix/transpose.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#20f2c5d841ec31673050aaedd8b17f50">linear_algebra_matrix</a>
* <a href="{{ site.github.repository_url }}/blob/master/linear_algebra_matrix/transpose.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-07 23:39:55+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>

// CUT begin
template <typename T>
std::vector<std::vector<T>> trans(std::vector<std::vector<T>> v)
{
    int H = v.size(), W = v[0].size();
    std::vector<std::vector<T>> ret(W, std::vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ret[j][i] = v[i][j];
        }
    }
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "linear_algebra_matrix/transpose.hpp"
#include <vector>

// CUT begin
template <typename T>
std::vector<std::vector<T>> trans(std::vector<std::vector<T>> v)
{
    int H = v.size(), W = v[0].size();
    std::vector<std::vector<T>> ret(W, std::vector<T>(H));
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            ret[j][i] = v[i][j];
        }
    }
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

