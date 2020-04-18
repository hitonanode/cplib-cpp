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
<script type="text/javascript" src="../../../assets/js/copy-button.js"></script>
<link rel="stylesheet" href="../../../assets/css/copy-button.css" />


# :heavy_check_mark: string/test/z_algorithm.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1a7427d145086499c399a0f95224a581">string/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/string/test/z_algorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-18 21:15:29+09:00


* see: <a href="https://judge.yosupo.jp/problem/zalgorithm">https://judge.yosupo.jp/problem/zalgorithm</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/z_algorithm.hpp.html">string/z_algorithm.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "string/z_algorithm.hpp"
#include <cstdio>
#include <iostream>
#include <string>
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

int main()
{
    std::string S;
    std::cin >> S;
    for (auto x : z_algorithm(S))
    {
        printf("%d ", x);
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "string/z_algorithm.hpp"
#include <string>
#include <vector>

// CUT begin
// Z algorithm (length of longest common prefix for s[0:N] & s[i:N] for each i)
// Complexity: O(N)
// <http://snuke.hatenablog.com/entry/2014/12/03/214243>
std::vector<int> z_algorithm(const std::string &s) {
    std::vector<int> ans(s.size());
    ans[0] = s.size();
    int i = 1, j = 0;
    while (i < (int)s.size()) {
        while (i + j < (int)s.size() && s[j] == s[i + j]) ++j;
        ans[i] = j;
        if (!j) {
            ++i;
            continue;
        }
        int k = 1;
        while (i + k < (int)s.size() && k + ans[k] < j) ans[i + k] = ans[k], ++k;
        i += k;
        j -= k;
    }
    return ans;
}
#line 2 "string/test/z_algorithm.test.cpp"
#include <cstdio>
#include <iostream>
#line 5 "string/test/z_algorithm.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/zalgorithm"

int main()
{
    std::string S;
    std::cin >> S;
    for (auto x : z_algorithm(S))
    {
        printf("%d ", x);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

