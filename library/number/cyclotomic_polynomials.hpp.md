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


# :warning: number/cyclotomic_polynomials.hpp

<a href="../../index.html">Back to top page</a>

* category: <a href="../../index.html#b1bc248a7ff2b2e95569f56de68615df">number</a>
* <a href="{{ site.github.repository_url }}/blob/master/number/cyclotomic_polynomials.hpp">View this file on GitHub</a>
    - Last commit date: 2020-04-04 22:42:12+09:00




## Depends on

* :heavy_check_mark: <a href="eratosthenes.hpp.html">number/eratosthenes.hpp</a>


## Code

<a id="unbundled"></a>
{% raw %}
```cpp
#pragma once
#include "number/eratosthenes.hpp"
#include <vector>

// CUT begin
// cyclotomic polynominals : 円分多項式
// ret[i][j] = [x^j]\Phi_i(x) for i <= Nmax, which are known to be integers
std::vector<std::vector<int>> cyclotomic_polynomials(int Nmax)
{
    std::vector<int> moebius = SieveOfEratosthenes(Nmax).GenerateMoebiusFunctionTable();
    std::vector<std::vector<int>> ret(Nmax + 1);
    auto multiply = [](const std::vector<int> &a, const std::vector<int> &b) { // a * b
        std::vector<int> ret(int(a.size() + b.size()) - 1);
        for (size_t i = 0; i < a.size(); i++) for (size_t j = 0; j < b.size(); j++) {
                ret[i + j] += a[i] * b[j];
        }
        return ret;
    };
    auto divide = [](std::vector<int> a, const std::vector<int> &b) { // a / b, abs(b[0]) = 1
        std::vector<int> ret(int(a.size()) - int(b.size()) + 1);
        for (size_t i = 0; i < ret.size(); i++) {
            ret[i] = a[i] / b[0];
            for (size_t j = 0; j < b.size(); j++) a[i + j] -= ret[i] * b[j];
        }
        while (ret.size() and !ret.back()) ret.pop_back();
        return ret;
    };

    for (int n = 0; n <= Nmax; n++) {
        std::vector<std::vector<int>> num, den;
        for (int d = 1; d <= n; d++) if (n % d == 0 and moebius[d]) {
            std::vector<int> r(n / d + 1);
            r[0] = -1, r.back() = 1;
            (moebius[d] > 0 ? num : den).push_back(r);
        }
        std::vector<int> phi{1};
        for (auto v : num) phi = multiply(phi, v);
        for (auto v : den) phi = divide(phi, v);
        ret[n] = phi;
    }
    return ret;
}

```
{% endraw %}

<a id="bundled"></a>
{% raw %}
```cpp
#line 2 "number/eratosthenes.hpp"
#include <cassert>
#include <map>
#include <numeric>
#include <vector>

// CUT begin
// Sieve of Eratosthenes
// (*this)[i] = (divisor of i, greater than 1)
// Example: [0, 1, 2, 3, 2, 5, 3, 7, 2, 3, 2, 11, ...]
// Complexity: Space O(MAXN), Time (construction) O(MAXNloglogMAXN)
struct SieveOfEratosthenes : std::vector<int>
{
    std::vector<int> primes;
    SieveOfEratosthenes(int MAXN) : std::vector<int>(MAXN + 1) {
        std::iota(begin(), end(), 0);
        for (int i = 2; i <= MAXN; i++) {
            if ((*this)[i] == i) {
                primes.push_back(i);
                for (int j = i; j <= MAXN; j += i) (*this)[j] = i;
            }
        }
    }
    using T = long long int;
    // Prime factorization for x <= MAXN^2
    // Complexity: O(log x)          (x <= MAXN)
    //             O(MAXN / logMAXN) (MAXN < x <= MAXN^2)
    std::map<T, int> Factorize(T x) {
        assert(x <= 1LL * (int(size()) - 1) * (int(size()) - 1));
        std::map<T, int> ret;
        if (x < int(size())) {
            while (x > 1) {
                ret[(*this)[x]]++;
                x /= (*this)[x];
            }
        }
        else {
            for (auto p : primes) {
                while (!(x % p)) x /= p, ret[p]++;
                if (x == 1) break;
            }
            if (x > 1) ret[x]++;
        }
        return ret;
    }
    std::vector<T> Divisors(T x) {
        std::vector<T> ret{1};
        for (auto p : Factorize(x)) {
            int n = ret.size();
            for (int i = 0; i < n; i++) {
                for (T a = 1, d = 1; d <= p.second; d++) {
                    a *= p.first;
                    ret.push_back(ret[i] * a);
                }
            }
        }
        return ret; // Not sorted
    }
    // Moebius function Table
    // return: [0=>0, 1=>1, 2=>-1, 3=>-1, 4=>0, 5=>-1, 6=>1, 7=>-1, 8=>0, ...]
    std::vector<int> GenerateMoebiusFunctionTable() {
        std::vector<int> ret(size());
        for (int i = 1; i < int(size()); i++) {
            if (i == 1) ret[i] = 1;
            else if ((i / (*this)[i]) % (*this)[i] == 0) ret[i] = 0;
            else ret[i] = -ret[i / (*this)[i]];
        }
        return ret;
    }
};
// SieveOfEratosthenes sieve(100000);
#line 4 "number/cyclotomic_polynomials.hpp"

// CUT begin
// cyclotomic polynominals : 円分多項式
// ret[i][j] = [x^j]\Phi_i(x) for i <= Nmax, which are known to be integers
std::vector<std::vector<int>> cyclotomic_polynomials(int Nmax)
{
    std::vector<int> moebius = SieveOfEratosthenes(Nmax).GenerateMoebiusFunctionTable();
    std::vector<std::vector<int>> ret(Nmax + 1);
    auto multiply = [](const std::vector<int> &a, const std::vector<int> &b) { // a * b
        std::vector<int> ret(int(a.size() + b.size()) - 1);
        for (size_t i = 0; i < a.size(); i++) for (size_t j = 0; j < b.size(); j++) {
                ret[i + j] += a[i] * b[j];
        }
        return ret;
    };
    auto divide = [](std::vector<int> a, const std::vector<int> &b) { // a / b, abs(b[0]) = 1
        std::vector<int> ret(int(a.size()) - int(b.size()) + 1);
        for (size_t i = 0; i < ret.size(); i++) {
            ret[i] = a[i] / b[0];
            for (size_t j = 0; j < b.size(); j++) a[i + j] -= ret[i] * b[j];
        }
        while (ret.size() and !ret.back()) ret.pop_back();
        return ret;
    };

    for (int n = 0; n <= Nmax; n++) {
        std::vector<std::vector<int>> num, den;
        for (int d = 1; d <= n; d++) if (n % d == 0 and moebius[d]) {
            std::vector<int> r(n / d + 1);
            r[0] = -1, r.back() = 1;
            (moebius[d] > 0 ? num : den).push_back(r);
        }
        std::vector<int> phi{1};
        for (auto v : num) phi = multiply(phi, v);
        for (auto v : den) phi = divide(phi, v);
        ret[n] = phi;
    }
    return ret;
}

```
{% endraw %}

<a href="../../index.html">Back to top page</a>

