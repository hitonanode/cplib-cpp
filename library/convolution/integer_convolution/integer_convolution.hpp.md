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


# :warning: convolution/integer_convolution/integer_convolution.hpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#0d028ccab5dd03f57c1809f14fa2b5bc">convolution/integer_convolution</a>
* <a href="{{ site.github.repository_url }}/blob/master/convolution/integer_convolution/integer_convolution.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-05 20:29:36+09:00




## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include <vector>

// f[n]のn >= 1に対して、全ての倍数n*iに対するf[n*i]の和が出てくる 計算量O(NlogN)
template <typename T>
void integer_zeta(std::vector<T> &f)
{
    int N = f.size() - 1;
    for (int i = 1; i <= N; i++) {
        for (int j = i * 2; j <= N; j += i) {
            f[i] += f[j];
        }
    }
}

// f[n]に対して、全てのnの倍数n*iに対するf[n*i]の和が出てくる 計算量O(NloglogN)
// 素数p毎に処理する高速ゼータ変換
// 使用例 <https://yukicoder.me/submissions/385043>
template <typename T>
void fast_integer_zeta(std::vector<T> &f)
{
    int N = f.size() - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p * p; j > 0; j -= p) f[j / p] += f[j];
    }
}

// fast_integer_zetaの逆演算 O(NloglogN)
// 使用例 <https://yukicoder.me/submissions/385120>
template <typename T>
void fast_integer_moebius(std::vector<T> &f)
{
    int N = f.size() - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = p; j <= N; j += p) f[j / p] -= f[j];
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "convolution/integer_convolution/integer_convolution.hpp"
#include <vector>

// f[n]のn >= 1に対して、全ての倍数n*iに対するf[n*i]の和が出てくる 計算量O(NlogN)
template <typename T>
void integer_zeta(std::vector<T> &f)
{
    int N = f.size() - 1;
    for (int i = 1; i <= N; i++) {
        for (int j = i * 2; j <= N; j += i) {
            f[i] += f[j];
        }
    }
}

// f[n]に対して、全てのnの倍数n*iに対するf[n*i]の和が出てくる 計算量O(NloglogN)
// 素数p毎に処理する高速ゼータ変換
// 使用例 <https://yukicoder.me/submissions/385043>
template <typename T>
void fast_integer_zeta(std::vector<T> &f)
{
    int N = f.size() - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = N / p * p; j > 0; j -= p) f[j / p] += f[j];
    }
}

// fast_integer_zetaの逆演算 O(NloglogN)
// 使用例 <https://yukicoder.me/submissions/385120>
template <typename T>
void fast_integer_moebius(std::vector<T> &f)
{
    int N = f.size() - 1;
    std::vector<int> is_prime(N + 1, 1);
    for (int p = 2; p <= N; p++) if (is_prime[p]) {
        for (int q = p * 2; q <= N; q += p) is_prime[q] = 0;
        for (int j = p; j <= N; j += p) f[j / p] -= f[j];
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

