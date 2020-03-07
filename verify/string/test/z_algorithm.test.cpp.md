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


# :x: string/test/z_algorithm.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/string/test/z_algorithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B</a>


## Depends on

* :x: <a href="../../../library/string/z_algorithm.hpp.html">string/z_algorithm.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <string>
#include <vector>
#include "string/z_algorithm.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

int main()
{
    string T, P;
    cin >> T >> P;
    vector<int> z = z_algorithm(P + "_" + T);
    int n = P.length();
    for (int i = n + 1; i < (int)z.size(); i++)
    {
        if (z[i] == n) printf("%d\n", i - n - 1);
    }
}
```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/test/z_algorithm.test.cpp"
#include <iostream>
#include <string>
#include <vector>
#line 2 "string/z_algorithm.hpp"
#include <string>
#include <vector>
using namespace std;

// CUT begin
// Z algorithm (length of longest common prefix for s[0:N] & s[i:N] for each i)
// Complexity: O(N)
// <http://snuke.hatenablog.com/entry/2014/12/03/214243>
vector<int> z_algorithm(const string &s) {
    vector<int> ans(s.size());
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
#line 5 "string/test/z_algorithm.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B"
using namespace std;

int main()
{
    string T, P;
    cin >> T >> P;
    vector<int> z = z_algorithm(P + "_" + T);
    int n = P.length();
    for (int i = n + 1; i < (int)z.size(); i++)
    {
        if (z[i] == n) printf("%d\n", i - n - 1);
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

