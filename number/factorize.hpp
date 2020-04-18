#pragma once
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
