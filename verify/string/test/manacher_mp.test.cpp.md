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


# :heavy_check_mark: string/test/manacher_mp.test.cpp

<a href="../../../index.html">Back to top page</a>

* <a href="{{ site.github.repository_url }}/blob/master/string/test/manacher_mp.test.cpp">View this file on GitHub</a>
    - Last commit date: 2019-12-08 18:22:34+09:00


* see: <a href="http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934">http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/string/manacher.hpp.html">string/manacher.hpp</a>
* :heavy_check_mark: <a href="../../../library/string/mp_algorithm.hpp.html">string/mp_algorithm.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <iostream>
#include <string>
#include <vector>
#include "string/manacher.hpp"
#include "string/mp_algorithm.hpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934"
using namespace std;

int main()
{
    int N;
    string T;
    cin >> N >> T;

    vector<int> mp = mp_algorithm(T);
    vector<int> mana = manacher(T);

    int rep = N - mp[N];
    for (int i = 2; i <= N; i++)
    {
        if (i + mana[i - 1] - 1 == N)
        {
            cout << i << endl;
            return 0;
        }
        if (mana[i - 1] < i) continue;
        if ((2 * i - 2) % rep == 0) {
            cout << i << endl;
            return 0;
        }
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "string/test/manacher_mp.test.cpp"
#include <iostream>
#include <string>
#include <vector>
#line 2 "string/manacher.hpp"
#include <string>
#include <vector>

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
#line 6 "string/test/manacher_mp.test.cpp"
#define PROBLEM "http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=2934"
using namespace std;

int main()
{
    int N;
    string T;
    cin >> N >> T;

    vector<int> mp = mp_algorithm(T);
    vector<int> mana = manacher(T);

    int rep = N - mp[N];
    for (int i = 2; i <= N; i++)
    {
        if (i + mana[i - 1] - 1 == N)
        {
            cout << i << endl;
            return 0;
        }
        if (mana[i - 1] < i) continue;
        if ((2 * i - 2) % rep == 0) {
            cout << i << endl;
            return 0;
        }
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

