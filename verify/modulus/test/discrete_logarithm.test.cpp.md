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


# :heavy_check_mark: modulus/test/discrete_logarithm.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#1e1bae9d81a5584838c517ca3b5198a4">modulus/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/modulus/test/discrete_logarithm.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-03-07 22:54:47+09:00


* see: <a href="https://judge.yosupo.jp/problem/discrete_logarithm_mod">https://judge.yosupo.jp/problem/discrete_logarithm_mod</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/modulus/discrete_logarithm.hpp.html">modulus/discrete_logarithm.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"
#include "modulus/discrete_logarithm.hpp"
#include <iostream>

int main()
{
    int T;
    std::cin >> T;
    while (T--) {
        int X, Y, M;
        std::cin >> X >> Y >> M;
        DiscreteLogarithm dl(M, X);
        std::cout << dl.log(Y) << std::endl;
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 1 "modulus/test/discrete_logarithm.test.cpp"
#define PROBLEM "https://judge.yosupo.jp/problem/discrete_logarithm_mod"
#line 2 "modulus/discrete_logarithm.hpp"
#include <algorithm>
#include <unordered_map>
#include <utility>

// CUT begin
// Calculate log_A B (MOD M) (baby-step gian-step)
// DiscreteLogarithm dl(M, A);
// lint ans = dl.log(B);
// Complexity: O(M^(1/2)) for each query
// Verified: <https://judge.yosupo.jp/problem/discrete_logarithm_mod>
// Constraints: 0 <= A < M, B < M, 1 <= M <= 1e9  (M is not limited to prime)
struct DiscreteLogarithm
{
    using lint = long long int;
    int M, stepsize;
    lint baby_a, giant_a, g;
    std::unordered_map<lint, int> baby_log_dict;

    lint inverse(lint a) {
        lint b = M / g, u = 1, v = 0;
        while (b) {
            lint t = a / b;
            a -= t * b; std::swap(a, b);
            u -= t * v; std::swap(u, v);
        }
        u %= M / g;
        return u >= 0 ? u : u + M / g;
    }

    DiscreteLogarithm(int mod, int a_new) : M(mod), baby_a(a_new % mod), giant_a(1) {
        g = 1;
        while (std::__gcd(baby_a, M / g) > 1) g *= std::__gcd(baby_a, M / g);
        stepsize = 32;  // lg(MAX_M)
        while (stepsize * stepsize < M / g) stepsize++;

        lint now = 1 % (M / g), inv_g = inverse(baby_a);
        for (int n = 0; n < stepsize; n++) {
            if (!baby_log_dict.count(now)) baby_log_dict[now] = n;
            (now *= baby_a) %= M / g;
            (giant_a *= inv_g) %= M / g;
        }
    }

    // log(): returns the smallest nonnegative x that satisfies a^x = b mod M, or -1 if there's no solution
    lint log(lint b) {
        b %= M;
        lint acc = 1 % M;
        for (int i = 0; i < stepsize; i++) {
            if (acc == b) return i;
            (acc *= baby_a) %= M;
        }
        if (b % g) return -1;  // No solution
        lint now = b * giant_a % (M / g);
        for (lint q = 1; q <= M / stepsize + 1; q++) {
            if (baby_log_dict.count(now)) return q * stepsize + baby_log_dict[now];
            (now *= giant_a) %= M / g;
        }
        return -1;
    }
};
#line 3 "modulus/test/discrete_logarithm.test.cpp"
#include <iostream>

int main()
{
    int T;
    std::cin >> T;
    while (T--) {
        int X, Y, M;
        std::cin >> X >> Y >> M;
        DiscreteLogarithm dl(M, X);
        std::cout << dl.log(Y) << std::endl;
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

