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


# :heavy_check_mark: string/manacher.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b45cffe084dd3d20d928bee85e7b0f21">string</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/manacher.hpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00




## Verified with

* :heavy_check_mark: <a href="../../verify/string/test/manacher_mp.test.cpp.html">string/test/manacher_mp.test.cpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include <string>
#include <vector>

// CUT begin
// Manacher's Algorithm: radius of palindromes
// Input: std::string of length N
// Output: std::vector<int> of size N
// Complexity: O(N)
// Sample:
// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]
// Reference: <https://snuke.hatenablog.com/entry/2014/12/02/235837>
std::vector<int> manacher(std::string S)
{
    std::vector<int> res(S.length());
    int i = 0, j = 0;
    while (i < (int)S.size()) {
        while (i - j >= 0 and i + j < (int)S.size() and S[i - j] == S[i + j]) j++;
        res[i] = j;
        int k = 1;
        while (i - k >= 0 and i + k < (int)S.size() and k + res[i - k] < j) res[i + k] = res[i - k], k++;
        i += k, j -= k;
    }
    return res;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/manacher.hpp"
#include <string>
#include <vector>

// CUT begin
// Manacher's Algorithm: radius of palindromes
// Input: std::string of length N
// Output: std::vector<int> of size N
// Complexity: O(N)
// Sample:
// - `sakanakanandaka` -> [1, 1, 2, 1, 4, 1, 4, 1, 2, 2, 1, 1, 1, 2, 1]
// Reference: <https://snuke.hatenablog.com/entry/2014/12/02/235837>
std::vector<int> manacher(std::string S)
{
    std::vector<int> res(S.length());
    int i = 0, j = 0;
    while (i < (int)S.size()) {
        while (i - j >= 0 and i + j < (int)S.size() and S[i - j] == S[i + j]) j++;
        res[i] = j;
        int k = 1;
        while (i - k >= 0 and i + k < (int)S.size() and k + res[i - k] < j) res[i + k] = res[i - k], k++;
        i += k, j -= k;
    }
    return res;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

