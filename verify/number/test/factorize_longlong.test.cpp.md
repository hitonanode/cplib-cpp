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


# :heavy_check_mark: number/test/factorize_longlong.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#f11c31ed854a10cb04d51564b38e6849">number/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/number/test/factorize_longlong.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 00:54:35+09:00


* see: <a href="https://judge.yosupo.jp/problem/factorize">https://judge.yosupo.jp/problem/factorize</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/number/factorize.hpp.html">number/factorize.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "number/factorize.hpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

int main()
{
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        long long a;
        std::cin >> a;
        auto ret = FactorizeLonglong(a);
        std::cout << ret.size();
        for (auto p : ret) std::cout << ' ' << p;
        std::cout << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "number/factorize.hpp"
#include <algorithm>
#include <cassert>
#include <vector>

struct
{
    long long modpow(__int128 x, __int128 n, long long mod)
    {
        __int128 ans = 1;
        while (n)
        {
            if (n & 1) (ans *= x) %= mod;
            (x *= x) %= mod;
            n >>= 1;
        }
        return ans;
    }
    // Miller-Rabin primality test
    // <https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95>
    bool is_prime(long long n)
    {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        int s = __builtin_ctzll(n - 1);
        long long d = (n - 1) >> s;
        // <http://miller-rabin.appspot.com/>
        for (auto a : {2, 325, 9375, 28178, 450775, 9780504, 1795265022})
        {
            __int128 ad = modpow(a, d, n);
            bool may_composite = true;
            if (ad <= 1) continue;
            for (int r = 0; r < s; r++, ad = ad * ad % n) if (ad == n - 1) may_composite = false;
            if (may_composite) return false;
        }
        return true;
    }

    // Pollard's rho algorithm: find factor greater than 1
    long long find_factor(long long n)
    {
        assert(n > 1);
        if (n % 2 == 0) return 2;
        if (is_prime(n)) return n;
        long long x, y, d, c = 1;
        auto f = [&](__int128 x) -> long long { return (x * x + c) % n; };
        for (;; c++)
        {
            x = 2, y = 2, d = 1;
            while (d == 1) {
                x = f(x);
                y = f(f(y));
                d = std::__gcd(std::abs(x - y), n);
            }
            if (d < n) break;
        }
        return d;
    }

    // not sorted
    std::vector<long long> operator()(long long n)
    {
        std::vector<long long> ret;
        while (n > 1) {
            long long f = find_factor(n);
            if (f < n) {
                auto tmp = operator()(f);
                ret.insert(ret.end(), tmp.begin(), tmp.end());
            }
            else ret.push_back(n);
            n /= f;
        }
        std::sort(ret.begin(), ret.end());
        return ret;
    }
} FactorizeLonglong;
#line 2 "number/test/factorize_longlong.test.cpp"
#include <iostream>
#define PROBLEM "https://judge.yosupo.jp/problem/factorize"

int main()
{
    int Q;
    std::cin >> Q;
    while (Q--)
    {
        long long a;
        std::cin >> a;
        auto ret = FactorizeLonglong(a);
        std::cout << ret.size();
        for (auto p : ret) std::cout << ' ' << p;
        std::cout << '\n';
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

