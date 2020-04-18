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


# :heavy_check_mark: number/test/miller-rabin.test.cpp

<a href="../../../index.html">Back to top page</a>

* category: <a href="../../../index.html#f11c31ed854a10cb04d51564b38e6849">number/test</a>
* <a href="{{ site.github.repository_url }}/blob/master/number/test/miller-rabin.test.cpp">View this file on GitHub</a>
    - Last commit date: 2020-04-19 04:48:57+09:00


* see: <a href="https://yukicoder.me/problems/1967">https://yukicoder.me/problems/1967</a>


## Depends on

* :heavy_check_mark: <a href="../../../library/number/factorize.hpp.html">number/factorize.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#include "number/factorize.hpp"
#define PROBLEM "https://yukicoder.me/problems/1967"
#include <iostream>

int main()
{
    int Q;
    std::cin >> Q;
    while (Q--) {
        long long n;
        std::cin >> n;
        std::cout << n << ' ' << is_prime(n) << '\n';
    }
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "number/factorize.hpp"
#include <array>
#include <algorithm>
#include <cassert>
#include <vector>

namespace SPRP
{
// <http://miller-rabin.appspot.com/>
const std::vector<std::vector<__int128>> bases{
    {126401071349994536},                              // < 291831
    {336781006125, 9639812373923155},                  // < 1050535501 (1e9)
    {2, 2570940, 211991001, 3749873356},               // < 47636622961201 (4e13)
    {2, 325, 9375, 28178, 450775, 9780504, 1795265022} // <= 1e64
};
inline int get_id(long long n)
{
    if (n < 291831) return 0;
    else if (n < 1050535501) return 1;
    else if (n < 47636622961201) return 2;
    else return 3;
}
} // namespace SPRP


// Miller-Rabin primality test
// <https://ja.wikipedia.org/wiki/%E3%83%9F%E3%83%A9%E3%83%BC%E2%80%93%E3%83%A9%E3%83%93%E3%83%B3%E7%B4%A0%E6%95%B0%E5%88%A4%E5%AE%9A%E6%B3%95>
// Complexity: O(lg n) per query
struct
{
    long long modpow(__int128 x, __int128 n, long long mod) noexcept
    {
        __int128 ret = 1;
        for (x %= mod; n; x = x * x % mod, n >>= 1) ret = (n & 1) ? ret * x % mod : ret;
        return ret;
    }
    bool operator()(long long n) noexcept
    {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        int s = __builtin_ctzll(n - 1);

        for (__int128 a : SPRP::bases[SPRP::get_id(n)])
        {
            a = modpow(a, (n - 1) >> s, n);
            bool may_composite = true;
            if (!a) return true;
            if (a == 1) continue;
            for (int r = s; r--; a = a * a % n) if (a == n - 1) may_composite = false;
            if (may_composite) return false;
        }
        return true;
    }
} is_prime;

struct
{
    // Pollard's rho algorithm: find factor greater than 1
    long long find_factor(long long n)
    {
        assert(n > 1);
        if (n % 2 == 0) return 2;
        if (is_prime(n)) return n;
        long long c = 1;
        auto f = [&](__int128 x) -> long long { return (x * x + c) % n; };

        for (int t = 1;; t++) {
            long long x0 = t, m = std::max(n >> 3, 1LL), x, ys, y = x0, r = 1, g, q = 1;
            do {
                x = y;
                for (int i = r; i--;) y = f(y);
                long long k = 0;
                do {
                    ys = y;
                    for (int i = std::min(m, r - k); i--;) y = f(y), q = __int128(q) * std::abs(x - y) % n;
                    g = std::__gcd<long long>(q, n);
                    k += m;
                } while (k < r and g <= 1);
                r <<= 1;
            } while (g <= 1);
            if (g == n) {
                do {
                    ys = f(ys);
                    g = std::__gcd(std::abs(x - ys), n);
                } while (g <= 1);
            }
            if (g != n) return g;
        }
    }

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
#line 2 "number/test/miller-rabin.test.cpp"
#define PROBLEM "https://yukicoder.me/problems/1967"
#include <iostream>

int main()
{
    int Q;
    std::cin >> Q;
    while (Q--) {
        long long n;
        std::cin >> n;
        std::cout << n << ' ' << is_prime(n) << '\n';
    }
}

```
{% endraw %}

<a href="../../../index.html">Back to top page</a>

